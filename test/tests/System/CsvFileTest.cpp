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
#include "CsvFile.h"

/* Generated Test Data (for test cases where you append to existing file) */
extern const char* appendTestData1;
extern const char* appendTestData2;

/* Helpers */
void initializeInputFolder();
void initializeOutputFolder();
String getTestInputPath();
String getTestOutputPath();

TEST_CASE( "CsvFile tests", "[CsvFile]" ) {
	CsvFile logfile;
    initializeInputFolder();
    initializeOutputFolder();
    String input = getTestInputPath();
    String output = getTestOutputPath();
    
    SECTION("Test 1 -- create file and write to file") {

        // create file with four columns
        String outputFileName = output += "test-1.csv";
        bool success = logfile.create(outputFileName, 4);

        // check if file has been created and number of columns is correct
        REQUIRE( success );
        REQUIRE( logfile.getNumColumns() == 4 );

        // adds header and adds a few entries
        logfile.setHeader("optimus,prime,big,boy");
        logfile.addEntry("7");
        logfile.addEntry("11");
        logfile.addEntry("13");
        logfile.addEntry("17");
        logfile.addEntry("21");
        logfile.addEntry("23");
        logfile.addEntry("27");
        logfile.addEntry("31");
        logfile.saveToDisk();
        
        // check if file output is correct
        File output = SD.open(outputFileName, FILE_READ);
        String line1 = output.readLine();
        String line2 = output.readLine();
        String line3 = output.readLine();

        REQUIRE( line1.equals(String("optimus,prime,big,boy\r\n")) );
        REQUIRE( line2.equals(String("7,11,13,17\r\n")) );
        REQUIRE( line3.equals(String("21,23,27,31\r\n")) );

        // adds a few rows
        logfile.addRow("1,2,3,4");
        logfile.addRow("5,6,7,8");
        logfile.addEntry("9");
        logfile.addEntry("10");
        logfile.addRow("11,12");
        logfile.addRow("13,14,15,16");
        logfile.saveToDisk();

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
        success = logfile.close();

        // check file was closed
        REQUIRE( success );

        // make sure we cannot write to file anymore
        logfile.setHeader("this should not be written to file");
        logfile.addEntry("this should not be written to file");
        logfile.addRow("this should not be written to file");
    }

    SECTION("Test 2 -- open file with correct number of columns") {

        // create new file
        String outputFileName = output += "test-2.csv";
        bool success = logfile.create(outputFileName, 4);
        logfile.setHeader("this,is,the,header");
        logfile.addRow("this,is,a,row");
        logfile.saveToDisk();
        logfile.close();

        // try to open file with 4 columns
        success = logfile.open(outputFileName, 4);

        // check file is successfully created
        REQUIRE( success );
        REQUIRE( logfile.getNumColumns() == 4 );

        // write some stuff
        logfile.addRow("this,is,another,row");
        logfile.saveToDisk();

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
        bool success = logfile.create(outputFileName, 4);
        logfile.setHeader("this,is,the,header");
        logfile.addRow("this,is,a,row");
        logfile.saveToDisk();
        logfile.close();

        // create new file
        String expectedFileName = output + "test-3(1).csv";
        success = logfile.open(outputFileName, 3);

        // check file is successfully created
        REQUIRE( success );
        REQUIRE( logfile.getNumColumns() == 3 );

        // write some stuff
        logfile.addEntry("7");
        logfile.addEntry("11");
        logfile.addEntry("13");
        logfile.addEntry("17");
        logfile.addEntry("21");
        logfile.addEntry("23");
        logfile.saveToDisk();

        // check if file output is correct
        File output = SD.open(expectedFileName, FILE_READ);
        String line1 = output.readLine();
        String line2 = output.readLine();

        REQUIRE( logfile.getFileName().equals(expectedFileName) );
        REQUIRE( line1.equals(String("7,11,13\r\n")) );
        REQUIRE( line2.equals(String("17,21,23\r\n")) );
    }
    
    SECTION("Test 4 -- create new file") {

        // create new file
        String outputFileName = output + "test-4.csv";
        bool success = logfile.create(outputFileName, 4);

        // write some stuff
        logfile.addEntry("7");
        logfile.addEntry("11");
        logfile.addEntry("13");
        logfile.addEntry("17");
        logfile.saveToDisk();

        // check file is successfully created
        REQUIRE( success );
        REQUIRE( logfile.getFileName().equals(outputFileName) );
        
        // check file output
        File output = SD.open(outputFileName, FILE_READ);
        String line1 = output.readLine();
        REQUIRE( line1.equals(String("7,11,13,17\r\n")) );

        // close file and check file name is empty string
        logfile.close();
        REQUIRE( logfile.getFileName().equals("") );
    }

    SECTION("Test 5 -- create file that already exists") {

        // create new file
        String outputFileName = output + "test-5.csv";
        bool success = logfile.create(outputFileName, 4);

        String expectedFileName = output + "test-5(1).csv";

        // try to create file with the same file name as the previously created file
        success = logfile.create(outputFileName, 4);

        // check file is successfully created
        REQUIRE( success );
        REQUIRE( logfile.getFileName().equals(expectedFileName) );
        
        // close file and check file name is empty string
        logfile.close();
        REQUIRE( logfile.getFileName().equals("") );
    }

    SECTION("Test 6 -- file name generation logic") {
        String outputFileName = output + "test-6(5).csv";
        String expectedFileName = output + "test-6(6).csv";
        logfile.create(outputFileName, 1);
        logfile.close();
        logfile.create(outputFileName, 1);
        REQUIRE( logfile.getFileName().equals(expectedFileName) );
        logfile.close();
        REQUIRE( logfile.getFileName().equals("") );
        
        outputFileName = output + "test-6(2048).csv";
        expectedFileName = output + "test-6(2049).csv";
        logfile.create(outputFileName, 1);
        logfile.close();
        logfile.create(outputFileName, 1);
        REQUIRE( logfile.getFileName().equals(expectedFileName) );
        logfile.close();
        REQUIRE( logfile.getFileName().equals("") );
        
        outputFileName = output + "(1024)(2048)(1).csv";
        expectedFileName = output + "(1024)(2048)(2).csv";
        logfile.create(outputFileName, 1);
        logfile.close();
        logfile.create(outputFileName, 1);
        REQUIRE( logfile.getFileName().equals(expectedFileName) );
        logfile.close();
        REQUIRE( logfile.getFileName().equals("") );
        
        outputFileName = output + "test(1a).csv";
        expectedFileName = output + "test(1a)(1).csv";
        logfile.create(outputFileName, 1);
        logfile.close();
        logfile.create(outputFileName, 1);
        REQUIRE( logfile.getFileName().equals(expectedFileName) );
        logfile.close();
        REQUIRE( logfile.getFileName().equals("") );
    }

    SECTION("CsvFile::readEntry test -- 3 rows of well-formatted data") {
        logfile.open(input + String("input-test.csv"), 4, FILE_READ);

        REQUIRE ( logfile.readEntry().equals("deep") );
        REQUIRE ( logfile.readEntry().equals("sea") );
        REQUIRE ( logfile.readEntry().equals("fibre") );
        REQUIRE ( logfile.readEntry().equals("optic") );

        REQUIRE ( logfile.readEntry().equals("1") );
        REQUIRE ( logfile.readEntry().equals("2") );
        REQUIRE ( logfile.readEntry().equals("3") );
        REQUIRE ( logfile.readEntry().equals("4") );
        
        REQUIRE ( logfile.readEntry().equals("5") );
        REQUIRE ( logfile.readEntry().equals("6") );
        REQUIRE ( logfile.readEntry().equals("7") );

        String secondLast = logfile.readEntry();
        REQUIRE ( secondLast.equals("8") );

        String last = logfile.readEntry();
        REQUIRE ( last.length() == 0 );

        logfile.close();
    }

    SECTION("CsvFile::readEntry test -- 2 rows, no terminating CRLF") {
        logfile.open(input + String("input-test-no-CRLF.csv"), 4, FILE_READ);

        REQUIRE ( logfile.readEntry().equals("deep") );
        REQUIRE ( logfile.readEntry().equals("sea") );
        REQUIRE ( logfile.readEntry().equals("fibre") );
        REQUIRE ( logfile.readEntry().equals("optic") );

        REQUIRE ( logfile.readEntry().equals("1") );
        REQUIRE ( logfile.readEntry().equals("2") );
        REQUIRE ( logfile.readEntry().equals("3") );
        REQUIRE ( logfile.readEntry().equals("4") );
        
        String last = logfile.readEntry();
        REQUIRE ( last.length() == 0 );

        logfile.close();
    }

    SECTION("CsvFile::readRow test") {
        logfile.open(input + String("input-test.csv"), 4, FILE_READ);
        std::vector<String> row1 = logfile.readRow();
        std::vector<String> row2 = logfile.readRow();
        std::vector<String> row3 = logfile.readRow();

        REQUIRE( row1.size() == 4 );
        REQUIRE( row2.size() == 4 );
        REQUIRE( row3.size() == 4 );

        REQUIRE ( row1[0].equals("deep") );
        REQUIRE ( row1[1].equals("sea") );
        REQUIRE ( row1[2].equals("fibre") );
        REQUIRE ( row1[3].equals("optic") );

        REQUIRE ( row2[0].equals("1") );
        REQUIRE ( row2[1].equals("2") );
        REQUIRE ( row2[2].equals("3") );
        REQUIRE ( row2[3].equals("4") );

        std::vector<String> last = logfile.readRow();
        REQUIRE ( last.size() == 0 );

        logfile.close();
    }

    SECTION("CsvFile::readRow test -- no terminating CRLF") {
        logfile.open(input + String("input-test-no-CRLF.csv"), 4, FILE_READ);
        std::vector<String> row1 = logfile.readRow();
        std::vector<String> row2 = logfile.readRow();

        REQUIRE( row1.size() == 4 );
        REQUIRE( row2.size() == 4 );

        REQUIRE ( row1[0].equals("deep") );
        REQUIRE ( row1[1].equals("sea") );
        REQUIRE ( row1[2].equals("fibre") );
        REQUIRE ( row1[3].equals("optic") );

        REQUIRE ( row2[0].equals("1") );
        REQUIRE ( row2[1].equals("2") );
        REQUIRE ( row2[2].equals("3") );
        REQUIRE ( row2[3].equals("4") );

        std::vector<String> last = logfile.readRow();
        REQUIRE ( last.size() == 0 );

        logfile.close();
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
