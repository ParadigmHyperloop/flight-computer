//
//  EmergencyState.hpp
//  networkprotocol
//
//  Created by Dan Hartman on 1/22/18.
//

#ifndef EmergencyState_hpp
#define EmergencyState_hpp

#include <stdio.h>
#include "AbstractControlState.hpp"

class EmergencyState : public AbstractControlState {

    
  public:
    /**
     * Creates a new instance of a EmergencyState.
     *
     * @param entered
     * The time that this state was entered.
     *
     */
    EmergencyState(int stateNum);
    
    virtual std::string returnStateName();
};

#endif /* EmergencyState_hpp */
