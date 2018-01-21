//
//  RetryProtocol.cpp
//  networkprotocol
//
//  Created by Logan on 1/20/18.
//

#include "RetryProtocol.hpp"

void RetryProtocol::rawWrite(boost::asio::ip::udp::socket& socket, const std::string& message, bool& success) const {
    
    try {
        
        // Boost.Asio doesn't have timeouts, so we simulate this with a seperate thread
        boost::thread thread = boost::thread([&socket, &success, &message] {
        
            socket.send(boost::asio::buffer(message));
            
        });
                                             
        // If we dont finish in time we consider that a read error
        if (!thread.timed_join(boost::posix_time::milliseconds(TIMEOUT_MILLISECONDS))) {
         
             thread.interrupt();
             success = false;
         
        } else success = true;
        
    } catch (std::runtime_error e) {
        
        // Write did not succeed
        std::cout << "Error with raw write: " << e.what() << std::endl;
        success = false;
        
    }
    
}

std::string RetryProtocol::rawRead(boost::asio::ip::udp::socket& socket, bool& success) const {
    
    try {
        
        success = false;
        
        size_t num_bytes;
        
        // Boost.Asio doesn't have timeouts, so we simulate this with a seperate thread
        boost::thread thread = boost::thread([&socket, &success, &num_bytes] {
            
            // We need to do a null read to figure out how many bytes we have
            socket.receive(boost::asio::null_buffers());
            num_bytes = socket.available();
            
        });
        
        // If we dont finish in time we consider that a read error
        if (!thread.timed_join(boost::posix_time::milliseconds(TIMEOUT_MILLISECONDS))) {
         
            thread.interrupt();
            success = false;
            return "";
            
        } else {
            
            std::shared_ptr<char> buffer = std::shared_ptr<char>(new char[num_bytes]);
            size_t packet_size = socket.receive(boost::asio::buffer(buffer.get(), num_bytes));
            
            std::string str;
            
            // The string must be resized to store the entire packet inside. packet_size might not be equal to num_bytes, so we must use packet_size
            str.resize(packet_size);
            memcpy(str.data(), buffer.get(), packet_size);
            
            success = true;
            return str;
            
        }
        
    } catch (std::runtime_error e) {
        
        // Read did not succeed
        std::cout << "Error with raw read: " << e.what() << std::endl;
        return "";
        
    }
    
}

void RetryProtocol::signalFailure() const {
    
    std::cerr << "There was a network failure!\n";
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SimpleRetryProtocol::write(boost::asio::ip::udp::socket& socket, const std::string& message) const {
    
    bool success;
    rawWrite(socket, message, success);
    
    if (!success)
        signalFailure();
    
}

std::string SimpleRetryProtocol::read(boost::asio::ip::udp::socket& socket) const {
    
    bool success;
    std::string message = rawRead(socket, success);
    
    if (!success)
        signalFailure();
    
    // If rawRead fails, the message will be an empty string, so we can return it here as well
    return message;
    
}
