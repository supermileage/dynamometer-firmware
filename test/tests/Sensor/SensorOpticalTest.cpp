#include "test_config.h"
#include "SensorOptical.h"

/* Helpers */
void simulateAperturePasses(SensorOptical& optical, uint32_t numPasses);

TEST_CASE( "SensorOptical::getAngularVelocity", "[SensorOptical]" ) {
	SensorOptical optical(0, 0, 12);
    setMicros(0);

    SECTION("full rotation in one second") {
        optical.begin();
        pio_counter_set_count(SensorOptical::NumApertures);
        setMicros(1000000);
        REQUIRE( optical.getAngularVelocity() == Approx(6.28).margin(0.01) );
    }

    SECTION("full rotation in half a second") {
        optical.begin();
        pio_counter_set_count(SensorOptical::NumApertures);
        setMicros(500000);
        REQUIRE( optical.getAngularVelocity() == Approx(12.56).margin(0.01) );
    }

    SECTION("quarter rotation in 50 milliseconds") {
        optical.begin();
        pio_counter_set_count(SensorOptical::NumApertures / 4);
        setMicros(50000);
        REQUIRE( optical.getAngularVelocity() == Approx(31.415).margin(0.01) );
    }

    SECTION("quarter rotation in 1 second") {
        optical.begin();
        pio_counter_set_count(SensorOptical::NumApertures / 4);
        setMicros(1000000);
        REQUIRE( optical.getAngularVelocity() == Approx(1.571).margin(0.01) );
    }

    SECTION("eighth rotation in 1 second") {
        optical.begin();
        pio_counter_set_count(SensorOptical::NumApertures / 8);
        setMicros(1000000);
        REQUIRE( optical.getAngularVelocity() == Approx(0.785).margin(0.01) );
    }

    SECTION("sixteenth rotation in 10 milliseconds") {
        optical.begin();
        pio_counter_set_count(SensorOptical::NumApertures / 16);
        setMicros(10000);
        REQUIRE( optical.getAngularVelocity() == Approx(39.268).margin(0.01) );
    }
}