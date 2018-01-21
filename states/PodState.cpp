//
//  PodState.cpp
//  networkprotocol
//
//  Created by Dan Hartman on 1/20/18.
//

#include <stdio.h>
#include "PodState.hpp"

/*** Defines a global podstate if not already defined ***/
PodState *PodState::globalState() {
    
    static std::unique_ptr<PodState> _state;
    
    if(!_state) {
        _state = std::unique_ptr<PodState>(new PodState());
    }
    
    return _state.get();
}
