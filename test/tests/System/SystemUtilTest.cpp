#include "test_config.h"
#include "Arduino.h"
#include "System/system_util.h"

#define MAX_SIZE 5

using namespace system_util;

struct test_data {
    int n1;
    int n2;
};

TEST_CASE( "FixedStack tests", "[FixedStack]" ) {
    FixedStack<test_data, MAX_SIZE> fixed_stack;

    SECTION("fixed stack -- add and pop once") {
        test_data input = test_data { .n1 = 1, .n2 = 2 };
        fixed_stack.push(input);

        REQUIRE( !fixed_stack.empty() );
        REQUIRE( fixed_stack.size() == 1 );

        test_data output = fixed_stack.top();
        fixed_stack.pop();

        REQUIRE( fixed_stack.empty() );
        REQUIRE( fixed_stack.size() == 0 );
        REQUIRE( output.n1 == 1 );
        REQUIRE( output.n2 == 2 );
    }

    SECTION("fixed stack -- add more than maxsize") {
        test_data input;

        for (int i = 0; i < (MAX_SIZE + 3); i++) {
            input = test_data { .n1 = i*2, .n2 = i*2+1 };
            fixed_stack.push(input);
        }
        
        REQUIRE( !fixed_stack.empty() );
        REQUIRE( fixed_stack.size() == MAX_SIZE );

        uint16_t cur_size = MAX_SIZE;
        int i = MAX_SIZE + 3;
        test_data output;
        while (!fixed_stack.empty()) {
            output = fixed_stack.top();
            fixed_stack.pop();
            --cur_size; --i;

            REQUIRE( output.n1 == i*2 );
            REQUIRE( output.n2 == i*2+1 );
            REQUIRE( fixed_stack.size() == cur_size );
        }
        REQUIRE( fixed_stack.empty() );
    }
}