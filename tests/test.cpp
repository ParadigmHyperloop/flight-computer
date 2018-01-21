//
//  test.cpp
//  tests
//
//  Created by Logan on 1/18/18.
//

#define BOOST_TEST_MODULE tests
#include <boost/test/unit_test.hpp>

#include <states.hpp>

BOOST_AUTO_TEST_CASE(tempTest) {
    
    BOOST_CHECK_EQUAL(foobar, true);
    
}
