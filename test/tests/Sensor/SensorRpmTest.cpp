#include "test_config.h"

#include "SensorRpm.h"

TEST_CASE( "SensorRpm::getRpm", "[SensorRpm]" ) {
	SensorRpm rpm(1, INPUT);

    setMicros(1000);
    
    REQUIRE( rpm.getRpm() == 0 );
}