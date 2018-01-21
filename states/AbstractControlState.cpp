//
//  AbstractControlState.cpp
//  FlightCP
//
//  Created by Dan Hartman on 1/18/18.
//

#include "AbstractControlState.hpp"

AbstractControlState::AbstractControlState(time_t entered, AbstractControlState *lastState) : entered(entered), lastState(lastState) {}

void AbstractControlState::test() {
    
    
    
}


