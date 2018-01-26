//
//  SimpleRetryProtocol.cpp
//  networkprotocol
//
//  Created by Logan on 1/21/18.
//

#include "SimpleRetryProtocol.hpp"

SimpleRetryProtocol::SimpleRetryProtocol(std::shared_ptr<ErrorHandler> error_handler) : NRetryProtocol(1, error_handler) {}
