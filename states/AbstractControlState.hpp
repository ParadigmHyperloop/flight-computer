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
#include "boost/date_time/posix_time/posix_time.hpp"
#include "PodState.hpp"

/*** An abstract class for representing shared functionality between different types of control states. ***/
class AbstractControlState {
    
    protected:
    
    boost::posix_time::ptime entered;
    std::shared_ptr<AbstractControlState> *lastState;
    const int stateNumber;
    
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
    AbstractControlState(boost::posix_time::ptime entered, std::shared_ptr<AbstractControlState> *lastState, int stateNumber);
    
    public:
    /**
     * Determines the next state that the pod will transition into based on sensor data read.
     *
     * @return The type of state to transition into.
     */
    virtual int determineNextState() = 0;
    
    /**
     * Determines the next state that the pod will transition into based on sensor data read.
     *
     */
    virtual void transitionToNextState(int state, const PodState *globalState) = 0;
    
    /**
     * Gets the time in microseconds that this state was entered.
     *
     * @return an integer time in microseconds
     */
    virtual boost::posix_time::ptime returnEnteredTime() {
        return entered;
    }
    
    /**
     * Returns the current count of how many states the pod has been in.
     *
     * @return the integer corresponding to this state number
     */
    int returnStateNumber();
    
};

#endif /* AbstractControlState_hpp */
