#include "test_config.h"

#include "SensorOptical.h"

TEST_CASE( "SensorOptical::getRpm", "[SensorOptical]" ) {
	SensorOptical optical(1, INPUT);

    setMicros(1000);
    
    REQUIRE( optical.getAngularVelocity() == 0 );
}