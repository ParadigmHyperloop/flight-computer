//
//  Connection.cpp
//  networkprotocol
//
//  Created by Logan on 1/20/18.
//

#include "Connection.hpp"

Connection::Connection(std::string hostname, int port, std::shared_ptr<RetryProtocol> retry_protocol, std::string connection_name) :
                      _hostname(hostname), _port(port), _retry_protocol(retry_protocol), _connection_name(connection_name) {
    
    // All of the information is saved, so we can now connect to the server
    connect();
    
}

void Connection::connect() {
    
    // Resolve the hostname so boost can understand it
    boost::asio::ip::udp::resolver resolver(_io_service);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(),_hostname, std::to_string(_port));
    boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);
    
    // This needs to be done as a pointer as the socket has no default constructor
    _socket = std::unique_ptr<boost::asio::ip::udp::socket>(new boost::asio::ip::udp::socket(_io_service));
    _socket->connect(receiver_endpoint);
    
    _connection_time = time(0);
    std::cout << "Started the connection \"" << _connection_name << "\" at " << ctime(&_connection_time) << std::endl;
    
}

void Connection::write(const std::string& message) const { _retry_protocol->write(*_socket, message, _connection_name); }
std::string Connection::read() const { return _retry_protocol->read(*_socket, _connection_name); }
