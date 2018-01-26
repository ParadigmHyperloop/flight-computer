//
//  CommandServer.cpp
//  networkprotocol
//
//  Created by Logan on 1/21/18.
//

#include "CommandServer.hpp"

#include <functional>

std::hash<std::string> _str_hasher;

CommandServer::CommandServer(int port) : _acceptor(_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
                                         _thread(&CommandServer::runServer, this), _command_queue(0) {}

CommandServer::~CommandServer() {
    
    // The thread will stop after the event loop is stopped, but we still need to join
    _io_service.stop();
    _thread.join();

}

std::shared_ptr<CommandTicket>  CommandServer::addCommandConnection(std::string command, const boost::function<void()>& function) {
    
    size_t hash = _str_hasher(command);
    
    // We need to ensure that there is a connection
    if (!_signals.count(hash))
        _signals[hash] = boost::signals2::signal<void()>();
    
    return std::shared_ptr<CommandTicket>(new CommandTicket(_signals[hash].connect(function)));
    
}

void CommandServer::resolveCommands() {
    
    size_t command;
    while (_command_queue.pop(command)) {
        
        if (_signals.count(command))
            _signals[command]();

    }
    
}

void CommandServer::runServer() {
    
    // We want to accept new connections and then run the service so that new connecitons can come in and send messages
    accept();
    _io_service.run();
    
}

void CommandServer::accept() {
    
    std::shared_ptr<CommandConnection> new_connection = std::shared_ptr<CommandConnection>(new CommandConnection(_io_service));
    _acceptor.async_accept(new_connection->getSocket(), [this, new_connection](boost::system::error_code error) {
        
        // Add the connection to the vector
        _connections.push_back(new_connection);
        
        recieveMessage(new_connection);
        
        accept();
        
    });
    
}

void CommandServer::recieveMessage(std::shared_ptr<CommandConnection> connection) {
    
    boost::asio::ip::tcp::socket& socket = connection->getSocket();
    
    // Use a null buffer so we can read a variable size buffer
    socket.async_receive(boost::asio::null_buffers(), [this, &socket, connection](boost::system::error_code error, size_t bytes) {
        
        size_t num_bytes = socket.available();
        
        // Only read stuff from the socket if we have data to read
        if (num_bytes) {
            
            std::shared_ptr<char> buffer = std::shared_ptr<char>(new char[num_bytes]);
            size_t packet_size = socket.receive(boost::asio::buffer(buffer.get(), num_bytes));
            
            std::string str;
            
            // The string must be resized to store the entire packet inside. packet_size might not be equal to num_bytes, so we must use packet_size
            // We subtract 1 byte because there is an extra null one
            str.resize(packet_size - 1);
            memcpy(const_cast<char*>(str.data()), buffer.get(), packet_size - 1);
        
            _command_queue.push(_str_hasher(str));
            
            recieveMessage(connection);
            
        } else {
            
            // No bytes were recieved so the connection should be terminated
            closeConnection(connection);
            
        }
        
    });
    
}

void CommandServer::closeConnection(std::shared_ptr<CommandConnection> connection) {
    
    connection->getSocket().close();
    
    // We need to remove it so the memory is released
    std::vector<std::shared_ptr<CommandConnection>>::iterator i = _connections.begin();
    for (; i != _connections.end(); i++) {
        
        if (i->get() == connection.get())
            break;
        
    }
    
    _connections.erase(i);
    _connections.shrink_to_fit();
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CommandConnection::CommandConnection(boost::asio::io_service& io_service) :
                                     _socket(io_service) {}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CommandTicket::CommandTicket() : _connection() {}

CommandTicket::CommandTicket(boost::signals2::connection connection) : _connection(connection) {}

CommandTicket::~CommandTicket() {
    
    // Ensure that the connection is connected if we are to disconnect it 
    if (_connection.connected())
        _connection.disconnect();
    else std::cout << "CommandTicket was unused: " << this << std::endl;
    
}
