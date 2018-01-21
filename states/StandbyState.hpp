//
//  StandbyState.hpp
//  core
//
//  Created by Dan Hartman on 1/18/18.
//

#ifndef StandbyState_hpp
#define StandbyState_hpp

#include <stdio.h>
#include "AbstractControlState.hpp"

class StandbyState : public AbstractControlState {
    
    virtual void getNextState() {
        
    }
    virtual void makeNextState() {
        
    }
    
    StandbyState(time_t entered) : AbstractControlState(entered, nullptr, 1) {
    
    }
    
};

#endif /* StandbyState_hpp */
