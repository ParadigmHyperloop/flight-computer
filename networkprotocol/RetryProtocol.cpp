//
//  RetryProtocol.cpp
//  networkprotocol
//
//  Created by Logan on 1/20/18.
//

#include "RetryProtocol.hpp"

#include <boost/asio/high_resolution_timer.hpp>

void RetryProtocol::rawWrite(boost::asio::ip::udp::socket& socket, const std::string& message, bool& success) const {
    
    try {
        
        // Boost.Asio doesn't have timeouts built in, so we simulate that
        boost::asio::io_service& io_service = socket.get_io_service();
        io_service.reset();
        
        // When this timer signals, the write will have timed out
        bool timed_out = false;
        boost::asio::high_resolution_timer timer(io_service, std::chrono::milliseconds(TIMEOUT_MILLISECONDS));
                                             
        socket.async_send(boost::asio::buffer(message), [&timer](boost::system::error_code error, size_t bytes) { timer.cancel(); });
        
        timer.async_wait([&socket, &timed_out](boost::system::error_code error) {
            
            // We timed out, so we should cancel the write
            if (error != boost::asio::error::operation_aborted)  {
                
                timed_out = true;
                socket.cancel();
                
            }
            
        });
        
        io_service.run_one();
        io_service.run();
        
        success = !timed_out;
        
    } catch (std::runtime_error e) {
        
        // Write did not succeed
        std::cout << "Error with raw write: " << e.what() << std::endl;
        success = false;
        
    }
    
}

std::string RetryProtocol::rawRead(boost::asio::ip::udp::socket& socket, bool& success) const {
    
    try {
        
        // Boost.Asio doesn't have timeouts built in, so we simulate that
        boost::asio::io_service& io_service = socket.get_io_service();
        io_service.reset();
        
        // When this timer signals, the write will have timed out
        bool timed_out = false;
        boost::asio::high_resolution_timer timer(io_service, std::chrono::milliseconds(TIMEOUT_MILLISECONDS));
        
        // We need to do a null read to figure out how many bytes we have
        socket.async_receive(boost::asio::null_buffers(), [&timer](boost::system::error_code error, size_t bytes) { timer.cancel(); });
        
        timer.async_wait([&socket, &timed_out](boost::system::error_code error) {
            
            // We timed out, so we should cancel the read
            if (error != boost::asio::error::operation_aborted)  {
                
                timed_out = true;
                socket.cancel();
           
            }
            
        });
        
        io_service.run_one();
        io_service.run();
        
        // In order to continue reading, we need to ensure that there was no timeout
        if (!timed_out) {
            
            size_t num_bytes = socket.available();
            
            std::shared_ptr<char> buffer = std::shared_ptr<char>(new char[num_bytes]);
            size_t packet_size = socket.receive(boost::asio::buffer(buffer.get(), num_bytes));
            
            std::string str;
            
            // The string must be resized to store the entire packet inside. packet_size might not be equal to num_bytes, so we must use packet_size
            str.resize(packet_size);
            memcpy(str.data(), buffer.get(), packet_size);
            
            success = true;
            return str;
            
        } else {
            
            success = false;
            return "";
            
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
