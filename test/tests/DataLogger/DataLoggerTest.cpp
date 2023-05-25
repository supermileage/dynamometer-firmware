#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <string>

#include "test_config.h"
#include "Arduino.h"
#include "DataLogger.h"

/* Helpers */
void initializeOutputFolder();
String getTestInputPath();
String getTestOutputPath();

TEST_CASE( "DataLogger tests", "[DataLogger]" ) {
	DataLogger logger(0, true);
    initializeOutputFolder();
    String input = getTestInputPath();
    String output = getTestOutputPath();

    SECTION("example test -- open file for write") {
        String exampleFile = input += "example-input-test.csv";
        bool success = logger.open(exampleFile, 4);

        REQUIRE( success );
        REQUIRE( logger.getNumColumns() == 4 );
    }

    SECTION("example test -- create new file for write") {
        String exampleFile = output += "example-output-test.csv";
        bool success = logger.create(exampleFile, 4);

        REQUIRE( success );
        REQUIRE( logger.getNumColumns() == 4 );

        logger.setHeader("optimus,prime,big,boy");
        logger.addEntry("7");
        logger.addEntry("11");
        logger.addEntry("13");
        logger.addEntry("17");

        File output = SD.open(exampleFile, FILE_READ);
        String line1 = output.readLine();
        String line2 = output.readLine();

        REQUIRE( line1.equals(String("optimus,prime,big,boy\r\n")));
        REQUIRE( line2.equals(String("7,11,13,17")));
    }
}

/* Helpers */
bool g_foldersInitialized = false;

void initializeOutputFolder() {
    if (g_foldersInitialized) {
        return;
    }

    std::string path(getTestOutputPath().c_str());
    struct stat st = { 0 };

    if (stat(path.c_str(), &st) != -1) {
        DIR *d = opendir(path.c_str());
        struct dirent *p;

        while ((p = readdir(d))) {
            if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
                continue;
            }

            std::string cur = path + std::string(p->d_name);
            if (remove(cur.c_str()) == -1) {
                std::cout << "unable to remove file " << cur.c_str() << " from directory: " <<
                    strerror(errno) << std::endl;
            }
        }

        closedir(d);

        if (rmdir(path.c_str()) != 0) {
            std::cout << "failed to delete output directory: " << strerror(errno) << std::endl;
        }
    }

    if (mkdir(path.c_str(),  S_IRWXU | S_IRWXG | S_IRWXO)) {
        std::cout << "failed to delete output directory: " << strerror(errno) << std::endl;
    }

    g_foldersInitialized = true;
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
