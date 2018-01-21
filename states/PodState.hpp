//
//  PodState.hpp
//  FlightCP
//
//  Created by Dan Hartman on 1/20/18.
//

#ifndef podState_h
#define podState_h

#include "AbstractControlState.hpp"

/*** A struct that represents the global pod state. ***/
struct PodState {
    
    /*
     * Initializes the global state variable.
     * This can only be allocated once and any attempt to do so multiple times will do nothing.
     */
    static AbstractControlState *globalState();
    
    private:
    
    /**
     * Creates a new instance of a PodState
     *
     */
    PodState();
};
    
#endif /* podState_h */
