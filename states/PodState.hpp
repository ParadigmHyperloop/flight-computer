//
//  podState.hpp
//  FlightCP
//
//  Created by Dan Hartman on 1/20/18.
//

#ifndef podState_h
#define podState_h

#include "AbstractControlState.hpp"

/*** A struct that represents the global pod state. ***/
struct PodState {
    
    static PodState *globalState();
    
    private:
    PodState();
};
    
#endif /* podState_h */
