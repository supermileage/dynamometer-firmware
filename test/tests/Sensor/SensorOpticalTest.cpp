#include "test_config.h"

#include "SensorOptical.h"

TEST_CASE( "SensorOptical::getAngularVelocity", "[SensorOptical]" ) {
	SensorOptical optical(1, INPUT);

    setMillis(1000);
	setMicros(1000);
    REQUIRE( optical.getAngularVelocity() == 0 );
}