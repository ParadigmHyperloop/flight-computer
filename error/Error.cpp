//
//  Error.cpp
//  networkprotocol
//
//  Created by Logan on 1/24/18.
//

#include "Error.hpp"

#include "Instigator.hpp" 

void ErrorHandler::signalError(const ErrorInstigator* instigator, const std::string& message) {
    
    std::string instigator_str = "Unknown instigator";
    
    if (instigator) {
        instigator->instigatorDesc(instigator_str);
    }
        
    std::cout << "Error: " << message << "\nInstigator: " << instigator_str << std::endl;
    
}
