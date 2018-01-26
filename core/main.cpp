//
// Created by Logan on 1/18/18.
//

#include <iostream>
#include <boost/asio.hpp>
#include <states.hpp>

#include "PodState.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

int main(int argc, char** argv) {

    std::cout << "Starting up flight computer..." << std::endl;
    
    //PodState *internalState = new PodState();
    int nextState;
    
    sleep(5);
    
    std::cout << "Starting hyperloop..." << std::endl;
    std::cout << "Pod internal state allocated at address: "  <<  std::endl;
    
//    while (1) {
//        nextState = internalState->determineNextState();
//        //internalState->transitionToNextState(nextState, internalState);
//        std::cout << "Heartbeat timeout, transitioning to emergency state" << std::endl;
//    }
    return 0;

}
