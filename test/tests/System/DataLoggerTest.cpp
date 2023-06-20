#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <array>
#include <filesystem>

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

	DataLogger logger(true);
    logger.init(0);
    initializeInputFolder();
    initializeOutputFolder();
    String input = getTestInputPath();
    String output = getTestOutputPath();
    

    DEBUG_SERIAL_LN("\n\nSTARTING TESTS\n");
    
    SECTION("Test 1 -- create file and write to file") {

        // create file with four columns
        String outputFileName = output += "test-1.csv";
        bool success = logger.create(outputFileName, 4);

        // check if file has been created and number of columns is correct
        REQUIRE( success );
        REQUIRE( logger.getNumColumns() == 4 );

        // adds header and adds a few entries
        logger.setHeader("optimus,prime,big,boy");
        logger.addEntry("7");
        logger.addEntry("11");
        logger.addEntry("13");
        logger.addEntry("17");
        logger.addEntry("21");
        logger.addEntry("23");
        logger.addEntry("27");
        logger.addEntry("31");
        
        // check if file output is correct
        File output = SD.open(outputFileName, FILE_READ);
        String line1 = output.readLine();
        String line2 = output.readLine();
        String line3 = output.readLine();

        REQUIRE( line1.equals(String("optimus,prime,big,boy\r\n")) );
        REQUIRE( line2.equals(String("7,11,13,17\r\n")) );
        REQUIRE( line3.equals(String("21,23,27,31\r\n")) );

        // adds a few rows
        logger.addRow("1,2,3,4");
        logger.addRow("5,6,7,8");
        logger.addEntry("9");
        logger.addEntry("10");
        logger.addRow("11,12");
        logger.addRow("13,14,15,16");

        output.close();

        // check if file output is correct
        output = SD.open(outputFileName, FILE_READ);
        output.readLine();output.readLine();output.readLine();
        String line4 = output.readLine();
        String line5 = output.readLine();
        String line6 = output.readLine();
        String line7 = output.readLine();

        REQUIRE( line4.equals(String("1,2,3,4\r\n")) );
        REQUIRE( line5.equals(String("5,6,7,8\r\n")) );
        REQUIRE( line6.equals(String("9,10,11,12\r\n")) );
        REQUIRE( line7.equals(String("13,14,15,16\r\n")) );

        output.close();

        // try closing file
        success = logger.close();

        // check file was closed
        REQUIRE( success );

        // make sure we cannot write to file anymore
        logger.setHeader("this should not be written to file");
        logger.addEntry("this should not be written to file");
        logger.addRow("this should not be written to file");
    }

    SECTION("Test 2 -- open file with correct number of columns") {

        // create new file
        String outputFileName = output += "test-2.csv";
        bool success = logger.create(outputFileName, 4);
        logger.setHeader("this,is,the,header");
        logger.addRow("this,is,a,row");
        logger.close();

        // try to open file with 4 columns
        success = logger.open(outputFileName, 4);

        // check file is successfully created
        REQUIRE( success );
        REQUIRE( logger.getNumColumns() == 4 );

        // write some stuff
        logger.addRow("this,is,another,row");

        // check if file output is correct
        File output = SD.open(outputFileName, FILE_READ);
        String line1 = output.readLine();
        String line2 = output.readLine();
        String line3 = output.readLine();

        REQUIRE( line1.equals(String("this,is,the,header\r\n")) );
        REQUIRE( line2.equals(String("this,is,a,row\r\n")) );
        REQUIRE( line3.equals(String("this,is,another,row\r\n")) );
    }

    SECTION("Test 3 -- open file with wrong number of columns") {
        // create new file
        String outputFileName = output + "test-3.csv";
        bool success = logger.create(outputFileName, 4);
        logger.setHeader("this,is,the,header");
        logger.addRow("this,is,a,row");
        logger.close();

        // create new file
        String expectedFileName = output + "test-3(1).csv";
        success = logger.open(outputFileName, 3);

        // check file is successfully created
        REQUIRE( success );
        REQUIRE( logger.getNumColumns() == 3 );

        // write some stuff
        logger.addEntry("7");
        logger.addEntry("11");
        logger.addEntry("13");
        logger.addEntry("17");
        logger.addEntry("21");
        logger.addEntry("23");

        // check if file output is correct
        File output = SD.open(expectedFileName, FILE_READ);
        String line1 = output.readLine();
        String line2 = output.readLine();

        REQUIRE( logger.getFileName().equals(expectedFileName) );
        REQUIRE( line1.equals(String("7,11,13\r\n")) );
        REQUIRE( line2.equals(String("17,21,23\r\n")) );
    }
    
    SECTION("Test 4 -- create new file") {

        // create new file
        String outputFileName = output + "test-4.csv";
        bool success = logger.create(outputFileName, 4);

        // write some stuff
        logger.addEntry("7");
        logger.addEntry("11");
        logger.addEntry("13");
        logger.addEntry("17");

        // check file is successfully created
        REQUIRE( success );
        REQUIRE( logger.getFileName().equals(outputFileName) );
        
        // check file output
        File output = SD.open(outputFileName, FILE_READ);
        String line1 = output.readLine();
        REQUIRE( line1.equals(String("7,11,13,17\r\n")) );

        // close file and check file name is empty string
        logger.close();
        REQUIRE( logger.getFileName().equals("") );
    }

    SECTION("Test 5 -- create file that already exists") {

        // create new file
        String outputFileName = output + "test-5.csv";
        bool success = logger.create(outputFileName, 4);

        String expectedFileName = output + "test-5(1).csv";

        // try to create file with the same file name as the previously created file
        success = logger.open(outputFileName, 4);

        // check file is successfully created
        REQUIRE( success );
        REQUIRE( logger.getFileName().equals(expectedFileName) );
        
        // close file and check file name is empty string
        logger.close();
        REQUIRE( logger.getFileName().equals("") );
    }

    SECTION("Test 6 -- file name generation logic") {
        String outputFileName = output + "test-6(5).csv";
        String expectedFileName = output + "test-6(6).csv";
        logger.create(outputFileName, 1);
        logger.close();
        logger.create(outputFileName, 1);
        REQUIRE( logger.getFileName().equals(expectedFileName) );
        logger.close();
        REQUIRE( logger.getFileName().equals("") );
        
        outputFileName = output + "test-6(2048).csv";
        expectedFileName = output + "test-6(2049).csv";
        logger.create(outputFileName, 1);
        logger.close();
        logger.create(outputFileName, 1);
        REQUIRE( logger.getFileName().equals(expectedFileName) );
        logger.close();
        REQUIRE( logger.getFileName().equals("") );
        
        outputFileName = output + "(1024)(2048)(1).csv";
        expectedFileName = output + "(1024)(2048)(2).csv";
        logger.create(outputFileName, 1);
        logger.close();
        logger.create(outputFileName, 1);
        REQUIRE( logger.getFileName().equals(expectedFileName) );
        logger.close();
        REQUIRE( logger.getFileName().equals("") );
        
        outputFileName = output + "test(1a).csv";
        expectedFileName = output + "test(1a)(1).csv";
        logger.create(outputFileName, 1);
        logger.close();
        logger.create(outputFileName, 1);
        REQUIRE( logger.getFileName().equals(expectedFileName) );
        logger.close();
        REQUIRE( logger.getFileName().equals("") );
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
    for (uint32_t i = 0; i < testFileNames.size(); i++) {
        const char* testFileName = testFileNames[i];
        std::string testFilePath = path + std::string(testFileName);

        int fd;
        if ((fd = open(testFilePath.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0) {
            std::cout << "unable to open input file -- " << strerror(errno) << ":\n" << testFilePath << std::endl;
            continue;
        }
        const char* testFileData = testFileContents[i];
        if (write(fd, testFileData, strlen(testFileData)) < 0) {
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
    std::string cwd = std::filesystem::canonical("/proc/self/exe");
    std::size_t pos = cwd.find("bin/");

    if (pos == string::npos) {
        pos = cwd.find("dynamometer-firmware/test/");

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
