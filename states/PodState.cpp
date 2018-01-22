//
//  PodState.cpp
//  FlightCP
//
//  Created by Dan Hartman on 1/20/18.
//

#include <stdio.h>
#include <time.h>

#include "PodState.hpp"
#include "StandbyState.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

/*** Defines the constructor for PodState. ***/
PodState::PodState() {
}

/*** Defines a global podstate if not already defined ***/
AbstractControlState *PodState::globalState() {
    
    static std::unique_ptr<AbstractControlState> _state;
    
    // If not already allocated then allocate, otherwise do nothing.
    if(!_state) {
        _state = std::unique_ptr<AbstractControlState>(new StandbyState(1));
    }
    
    return _state.get();
}

