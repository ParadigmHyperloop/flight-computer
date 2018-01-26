//
//  StandbyState.cpp
//  FlightCP
//
//  Created by Dan Hartman on 1/18/18.
//

#include "StandbyState.hpp"
#include "PodState.hpp"
#include "EmergencyState.hpp"

// Finish defining this once I determine what information renders specific statee transitions.
//int StandbyState::determineNextState()  {
//
//    boost::posix_time::time_duration difference = boost::posix_time::microsec_clock::universal_time() - returnEnteredTime();
//    if (difference.total_microseconds() >= HEARTBEAT_TIMEOUT->total_microseconds()) {
//        return 0;
//    }
//    return 1;
//}
/*
// Finish defining this once I determine what information renders specific statee transitions.
void StandbyState::transitionToNextState(int state, const PodState *globalState) {
    if (state != returnStateNumber()) {
        *(globalState->flightState) = new EmergencyState();
    }
}*/
