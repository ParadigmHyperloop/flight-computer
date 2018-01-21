//
//  AbstractControlState.hpp
//  FlightCP
//
//  Created by Dan Hartman on 1/18/18.
//

#ifndef AbstractControlState_hpp
#define AbstractControlState_hpp

#include <stdio.h>
#include <time.h>
#include <boost/shared_ptr.hpp>

/*** An abstract class for representing shared functionality between different types of control states. ***/
class AbstractControlState {
    
    protected:
    
    long entered;
    std::shared_ptr<AbstractControlState> *lastState;
    int stateNumber;
    
    /**
     * Determines the next state that the pod will transition into based on sensor data read.
     *
     */
    virtual void getNextState() = 0;
    
    /**
     * Determines the next state that the pod will transition into based on sensor data read.
     *
     */
    virtual void makeNextState() = 0;
    
    /**
     * Returns the current count of how many states the pod has been in.
     *
     */
    int returnStateNumber();
    
    /**
     * Creates a new instance of an AbstractControlState reprenting what the pod is doing at the current moment in time.
     *
     * @param entered
     * The time that this state was entered.
     *
     * @param lastState
     * A pointer to the state before this one.
     *
     * @param stateNumber
     * This is the n'th state that the pod has been in... ie: there have been (n - 1) state transitions.
     *
     */
    AbstractControlState(time_t entered, std::shared_ptr<AbstractControlState> *lastState, int stateNumber);
    

};

#endif /* AbstractControlState_hpp */
