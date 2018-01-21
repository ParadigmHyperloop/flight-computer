//
//  StandbyState.hpp
//  FlightCP
//
//  Created by Dan Hartman on 1/18/18.
//

#ifndef StandbyState_hpp
#define StandbyState_hpp

#include <stdio.h>
#include "AbstractControlState.hpp"

/*** A class that represents the initial startup state of the pod. ***/
class StandbyState : public AbstractControlState {
    
    void getNextState();
    
    void makeNextState();
    
    
public:
    /**
     * Creates a new instance of a StandbyState.
     *
     * @param entered
     * The time that this state was entered.
     *
     */
    StandbyState(long entered) : AbstractControlState(entered, nullptr, 1) {
    
    }
    
};

#endif /* StandbyState_hpp */
