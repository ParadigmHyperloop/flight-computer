//
//  Error.hpp
//  networkprotocol
//
//  Created by Logan on 1/24/18.
//

#ifndef Error_hpp
#define Error_hpp

#include "Instigator.hpp"

class ErrorHandler {
  
    public:
    
        /**
         * Signals an error from the given instigator and with the given message. The handler function will also be called.
         *
         * @param instigator
         * The instigator of this error. If it is nullptr, the instigator message is "Unknown Instigator"
         *
         * @param message
         * The error message to be displayed.
         *
         */
        void signalError(const ErrorInstigator* instigator, const std::string& message);
    
    
};



#endif /* Error_hpp */
