#include "test_config.h"
#include "SensorOptical.h"
#include "Arduino.h"

/* Helpers */
void simulateAperturePasses(SensorOptical& optical, uint32_t numPasses);

TEST_CASE( "SensorOptical::getAngularVelocity", "[SensorOptical]" ) {
	SensorOptical optical(0, 0, 10000);
    setMicros(0);

    String s1("123");
    String s2 = (String)"123";

    SECTION("full rotation in one second") {
        optical.begin();
        setMicros(1000000);
        simulateAperturePasses(optical, SensorOptical::NumApertures);
        REQUIRE( optical.getAngularVelocity() == Approx(6.28).margin(0.01) );
    }

    SECTION("full rotation in half a second") {
        optical.begin();
        setMicros(500000);
        simulateAperturePasses(optical, SensorOptical::NumApertures);
        REQUIRE( optical.getAngularVelocity() == Approx(12.56).margin(0.01) );
    }

    SECTION("quarter rotation in 50 milliseconds") {
        optical.begin();
        setMicros(50000);
        simulateAperturePasses(optical, SensorOptical::NumApertures / 4);
        REQUIRE( optical.getAngularVelocity() == Approx(31.415).margin(0.01) );
    }

    SECTION("quarter rotation in 1 second") {
        optical.begin();
        setMicros(1000000);
        simulateAperturePasses(optical, SensorOptical::NumApertures / 4);
        REQUIRE( optical.getAngularVelocity() == Approx(1.571).margin(0.01) );
    }

    SECTION("eighth rotation in 1 second") {
        optical.begin();
        setMicros(1000000);
        simulateAperturePasses(optical, SensorOptical::NumApertures / 8);
        REQUIRE( optical.getAngularVelocity() == Approx(0.785).margin(0.01) );
    }

    SECTION("sixteenth rotation in 10 milliseconds") {
        optical.begin();
        setMicros(10000);
        simulateAperturePasses(optical, SensorOptical::NumApertures / 16);
        REQUIRE( optical.getAngularVelocity() == Approx(39.268).margin(0.01) );
    }
}

void simulateAperturePasses(SensorOptical& optical, uint count) {
    pio_counter_set_count(count);
    optical.handle();
}