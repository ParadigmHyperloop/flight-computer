//
//  PodState.hpp
//  FlightCP
//
//  Created by Dan Hartman on 1/20/18.
//

#ifndef podState_h
#define podState_h

#include "AbstractControlState.hpp"
#include "StandbyState.hpp"

/*** A struct that represents the global pod state. ***/
struct PodState {

    public:
    std::shared_ptr<AbstractControlState> flightState = std::shared_ptr<AbstractControlState>(new StandbyState(1));
    
    /**
     * Determines the next state that the pod will transition into based on sensor data read.
     *
     * @return The type of state to transition into.
     */
    int determineNextState();
    
    /**
     * Determines the next state that the pod will transition into based on sensor data read.
     *
     */
    void transitionToNextState();
    
    /*
     * Initializes the global state variable.
     * This can only be allocated once and any attempt to do so multiple times will do nothing.
     */
    static PodState *globalState();
    
    private:
    
    /**
     * Creates a new instance of a PodState
     *
     */
    PodState();
};
    
#endif /* podState_h */
