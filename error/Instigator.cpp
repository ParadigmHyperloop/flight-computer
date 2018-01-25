//
//  Instigator.cpp
//  networkprotocol
//
//  Created by Logan on 1/24/18.
//

#include "Instigator.hpp"

void ErrorInstigator::instigatorDesc(std::string& out) const {
    
    // Give only the generic description. Ensure we warn that the functions for this were not fully implemented
    genericDescription(out);
    out += "\nError was raised by unimplemented instigator.\nInformation here should be taken with a grain of salt.\n";
    
}

void ErrorInstigator::genericDescription(std::string& out) const {
    
    const char* type_id = getTypeid();
    
    // Cast to a void* to ensure that we dont accidentally invoke the << operator
    const void * addr = static_cast<const void*>(this);
    
    std::stringstream stream;
    stream << addr;
    std::string addr_str = stream.str();
    
    out = addr_str + ", Typeid name: " + type_id + ", Class name: " + className();
    
}

const char* ErrorInstigator::getTypeid() const { return typeid(this).name(); }
