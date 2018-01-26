//
//  NRetryProtocol.cpp
//  networkprotocol
//
//  Created by Logan on 1/21/18.
//

#include "NRetryProtocol.hpp"

NRetryProtocol::NRetryProtocol(int num_retries, std::shared_ptr<ErrorHandler> error_handler) : RetryProtocol(error_handler),
                              _num_retries(num_retries) {}

void NRetryProtocol::write(boost::asio::ip::udp::socket& socket, const std::string& message, const ErrorInstigator* instigator) const {
    
    bool success = false;
    
    for (int i = 0; i < _num_retries; i++) {
        
        rawWrite(socket, message, success);
        if (success)
            break;
        
    }
    
    if (!success)
        signalFailure("Write error", instigator);
    
}

std::string NRetryProtocol::read(boost::asio::ip::udp::socket& socket, const ErrorInstigator* instigator) const {
    
    bool success = false;
    std::string message;
    
    for (int i = 0; i < _num_retries; i++) {
        
        message = rawRead(socket, success);
        if (success)
            break;
        
    }
    
    if (!success)
        signalFailure("Read error", instigator);
    
    // If rawRead fails, the message will be an empty string, so we can return it here as well
    return message;
    
}
