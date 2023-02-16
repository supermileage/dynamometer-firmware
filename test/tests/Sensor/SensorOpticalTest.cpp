#include "test_config.h"
#include "SensorOptical.h"

/* Helpers */
void simulateAperturePasses(SensorOptical& optical, uint32_t numPasses);

TEST_CASE( "SensorOptical::getAngularVelocity", "[SensorOptical]" ) {
	SensorOptical optical(1, INPUT);
    setMicros(0);

    SECTION("full rotation in one second") {
        optical.begin();
        simulateAperturePasses(optical, SensorOptical::NumApertures);
        setMicros(1000000);
        REQUIRE( optical.getAngularVelocity() == Approx(3.14).margin(0.01) );
    }

    SECTION("full rotation in half a second") {
        optical.begin();
        simulateAperturePasses(optical, SensorOptical::NumApertures);
        setMicros(500000);
        REQUIRE( optical.getAngularVelocity() == Approx(6.28).margin(0.01) );
    }

    SECTION("quarter rotation in 50 milliseconds") {
        optical.begin();
        simulateAperturePasses(optical, SensorOptical::NumApertures / 4);
        setMicros(50000);
        REQUIRE( optical.getAngularVelocity() == Approx(15.7).margin(0.01) );
    }

    SECTION("quarter rotation in 1 second") {
        optical.begin();
        simulateAperturePasses(optical, SensorOptical::NumApertures / 4);
        setMicros(1000000);
        REQUIRE( optical.getAngularVelocity() == Approx(0.78).margin(0.01) );
    }

    SECTION("eighth rotation in 1 second") {
        optical.begin();
        simulateAperturePasses(optical, SensorOptical::NumApertures / 8);
        setMicros(1000000);
        REQUIRE( optical.getAngularVelocity() == Approx(0.39).margin(0.01) );
    }

    SECTION("sixteenth rotation in 10 milliseconds") {
        optical.begin();
        simulateAperturePasses(optical, SensorOptical::NumApertures / 16);
        setMicros(10000);
        REQUIRE( optical.getAngularVelocity() == Approx(19.63).margin(0.01) );
    }
}

void simulateAperturePasses(SensorOptical& optical, uint32_t numPasses) {
    PinStatus status = 0;
    for (uint32_t i = 0; i < numPasses * 2; i++) {
        setDigitalRead(status);
        optical.handle();
        status = !status;
    }
}