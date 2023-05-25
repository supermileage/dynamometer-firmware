#include <unistd.h>
#include <iostream>
#include <string>

#include "test_config.h"
#include "Arduino.h"
#include "DataLogger.h"

String getTestInputPath();
String getTestOutputPath();

TEST_CASE( "DataLogger tests", "[DataLogger]" ) {
	DataLogger logger(0, true);

    String input = getTestInputPath();
    String output = getTestOutputPath();

    SECTION("example test -- open file for write") {
        String exampleFile = input += "example-input-test.csv";
        bool success = logger.open(exampleFile, 4);

        REQUIRE( success );
        REQUIRE( logger.getNumColumns() == 4 );
    }

    SECTION("example test -- create new file for write") {
        String exampleFile = input += "example-output-test.csv";
        bool success = logger.create(exampleFile, 4);

        REQUIRE( success );
        REQUIRE( logger.getNumColumns() == 4 );
    }
}

std::string getTestDirectoryPath() {
    char buf[PATH_MAX];

    if (getcwd(buf, sizeof(buf)) == NULL) {
        std::cout << "failed to get directory path" << std::endl;
    }

    std::string cwd(buf);
    std::size_t pos = cwd.find("bin");

    if (pos == string::npos) {
        pos = cwd.find("dynamometer-firmware");

        if (pos == string::npos) {
            std::cout << "failed to find path: please rename project folder to dynamometer-firmware" << std::endl;
            return cwd;
        }

        pos += strlen("dynamometer-firmware/test/");
        cwd.append("/test/");
    }

    return cwd.substr(0,pos);
}

String getTestInputPath() {
    std::string ret = getTestDirectoryPath();
    ret.append("input/");
    return String(ret.c_str());
}

String getTestOutputPath() {
    std::string ret = getTestDirectoryPath();
    ret.append("output/");
    return String(ret.c_str());
}
