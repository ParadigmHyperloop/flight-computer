//
//  NRetryProtocol.cpp
//  networkprotocol
//
//  Created by Logan on 1/21/18.
//

#include "NRetryProtocol.hpp"

NRetryProtocol::NRetryProtocol(int num_retries) : _num_retries(num_retries) {}

void NRetryProtocol::write(boost::asio::ip::udp::socket& socket, const std::string& message, const std::string& caller_name) const {
    
    bool success = false;
    
    for (int i = 0; i < _num_retries; i++) {
        
        rawWrite(socket, message, success);
        if (success)
            break;
        
    }
    
    if (!success)
        signalFailure("Write called from " + caller_name);
    
}

std::string NRetryProtocol::read(boost::asio::ip::udp::socket& socket, const std::string& caller_name) const {
    
    bool success = false;
    std::string message;
    
    for (int i = 0; i < _num_retries; i++) {
        
        message = rawRead(socket, success);
        if (success)
            break;
        
    }
    
    if (!success)
        signalFailure("Read called from " + caller_name);
    
    // If rawRead fails, the message will be an empty string, so we can return it here as well
    return message;
    
}
