//
//  Instigator.hpp
//  networkprotocol
//
//  Created by Logan on 1/24/18.
//

#ifndef Instigator_hpp
#define Instigator_hpp

#include <iostream>
#include <sstream>

class ErrorInstigator {
    
    public:
    
        /**
         * Creates a string description of the object that instigated the error.
         *
         * @param out
         * The string that will contain the description of the instigator after the function is run.
         */
        virtual void instigatorDesc(std::string& out) const;
    
    protected:
    
        /**
         * Creates a string that gives the details that all insigators should include.
         *
         * @param out
         * The string that will contain the description of the instigator after the function is run.
         */
        void genericDescription(std::string& out) const;
    
        /**
         * Returns the name of the class of this instigator
         *
         * @return
         * The name of the class.
         */
        virtual std::string className() const = 0;
    
        /**
         * Used to get the typeid for subclasses
         *
         * @return
         * typeid(this).name()
         */
        virtual const char* getTypeid() const;
    
};

#define ERROR_INSTIGATOR protected: \
                            std::string className() const; \
                            virtual const char* getTypeid() const { return typeid(this).name(); } \
                         private: \

#endif /* Instigator_hpp */
