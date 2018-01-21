//
//  AbstractControlState.cpp
//  FlightCP
//
//  Created by Dan Hartman on 1/18/18.
//

#include "AbstractControlState.hpp"

/*** Defines the constructor for an AbstractControlState. ***/
AbstractControlState::AbstractControlState(time_t entered, std::shared_ptr<AbstractControlState> *lastState, int stateNumber) : entered(entered), lastState(lastState), stateNumber(stateNumber) {}

/*** Simple getter funnction that returns the number of states we've been in. ***/
int AbstractControlState::returnStateNumber() {
    return stateNumber;
}
