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

boost::posix_time::time_duration *HEARTBEAT_TIMEOUT = new boost::posix_time::microseconds(10000000);

/*** Defines the constructor for PodState. ***/
PodState::PodState() {
}

/*** Defines a global podstate if not already defined ***/
//PodState *PodState::globalState() {
//
//    static std::unique_ptr<AbstractControlState> _state;
//
//    // If not already allocated then allocate, otherwise do nothing.
//    if(!_state) {
//        _state = std::unique_ptr<AbstractControlState>(new StandbyState(1));
//    }
//
//    return _state.get();
//}

// Finish defining this once I determine what information renders specific statee transitions.
int PodState::determineNextState()  {
    
    boost::posix_time::time_duration difference = boost::posix_time::microsec_clock::universal_time() - flightState->returnEnteredTime();
    if (difference.total_microseconds() >= HEARTBEAT_TIMEOUT->total_microseconds()) {
        return 0;
    }
    return 1;
}
