#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <array>

#include "test_config.h"
#include "Arduino.h"
#include "DataLogger.h"

/* Generated Test Data (for test cases where you append to existing file) */
extern const char* appendTestData1;
extern const char* appendTestData2;

/* Helpers */
void initializeInputFolder();
void initializeOutputFolder();
String getTestInputPath();
String getTestOutputPath();

TEST_CASE( "DataLogger tests", "[DataLogger]" ) {
	DataLogger logger(0, true);
    initializeInputFolder();
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

/* Generated Test Data */
const std::array<const char*,2> testFileNames = { "append-test-data1.csv", "append-test-data2.csv" };
const std::array<const char*,2> testFileContents = { appendTestData1, appendTestData2 };

// ends with CRLF
const char* appendTestData1 =
    "property1,property2,property3\r\n"
    "11.11,22.22,33.33\r\n"
    "44.44,55.55,66.66\r\n";
// does not end with CRLF
const char* appendTestData2 =
    "property1,property2,property3\r\n"
    "11.11,22.22,33.33\r\n"
    "44.44,55.55,66.66";

/* Helpers */
bool g_inputFolderInitialized = false;
bool g_outputFolderInitialized = false;

// resets generated test cases in input folder
void initializeInputFolder() {
    if (g_inputFolderInitialized) {
        return;
    }

    std::string path(getTestInputPath().c_str());
    // check if entry's name is the same as generated test cases
    for (int i = 0; i < testFileNames.size(); i++) {
        const char* testFileName = testFileNames[i];
        std::string testFilePath = path + std::string(testFileName);

        int fd;
        if ((fd = open(testFilePath.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0) {
            std::cout << "unable to open input file " << testFileName << ": " <<
                strerror(errno) << std::endl;
            continue;
        }
        const char* testFileData = testFileContents[i];
        if (write(fd, testFileData, strlen(testFileData)) < strlen(testFileData)) {
            std::cout << "could not write test data to test file " << testFileName << ": " << strerror(errno) << std::endl;
        }

        if (close(fd) < 0) {
            std::cout << "failed to close test file " << testFileName << ": " << strerror(errno) << std::endl;
        }
    }
    g_inputFolderInitialized = true;
}

// remove and remake output folder
void initializeOutputFolder() {
    if (g_outputFolderInitialized) {
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

    if (mkdir(path.c_str(),  S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
        std::cout << "failed to create output directory: " << strerror(errno) << std::endl;
    }

    g_outputFolderInitialized = true;
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
