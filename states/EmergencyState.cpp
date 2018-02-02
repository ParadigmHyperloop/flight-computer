//
//  EmergencyState.cpp
//  networkprotocol
//
//  Created by Dan Hartman on 1/22/18.
//

#include "EmergencyState.hpp"

EmergencyState::EmergencyState(int stateNum) : AbstractControlState(boost::posix_time::microsec_clock::universal_time(), nullptr, stateNum) {
    stateName = "Emergency";
}

std::string EmergencyState::returnStateName() {
    return "Emergency";
}

