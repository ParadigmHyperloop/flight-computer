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
#include "boost/date_time/posix_time/posix_time.hpp"

/*** A class that represents the initial startup state of the pod. ***/
class StandbyState : public AbstractControlState {
    
  public:
    /**
     * Creates a new instance of a StandbyState.
     *
     * @param entered
     * The time that this state was entered.
     *
     */
    StandbyState(int stateNum);
    
    virtual std::string returnStateName();
};

#endif /* StandbyState_hpp */
