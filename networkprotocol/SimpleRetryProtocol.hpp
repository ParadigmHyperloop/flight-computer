//
//  SimpleRetryProtocol.hpp
//  networkprotocol
//
//  Created by Logan on 1/21/18.
//

#ifndef SimpleRetryProtocol_hpp
#define SimpleRetryProtocol_hpp

#include "NRetryProtocol.hpp"

/** A simple retry protocol. If a read or write fails, an error will be signaled immediately. */
class SimpleRetryProtocol : public NRetryProtocol {
    
    public:
    
        /** Creates a retry protocol that will signal failure immediately if a read or a write fails */
        SimpleRetryProtocol();
    
};

#endif /* SimpleRetryProtocol_hpp */
