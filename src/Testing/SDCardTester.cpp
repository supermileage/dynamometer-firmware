#include "settings.h"
#include "SDCardTester.h"
#include "../System/DataLogger.h"

using namespace std;

SDCardTester::SDCardTester() {};
SDCardTester::~SDCardTester() {};

void SDCardTester::testFilePerformance (DataLogger logger) {
	
	// time tracking variables
	int start;
	int end;
	int deltaTime;

	// create a template string with 1000 characters
	String templateString = "";
	for (int i = 0; i < 1000; i++)
		templateString += "X";

	// create a template csv entry
	String templateEntry = "1.0";




	
	// ***************************************************************************************************************************************** //
	
	// Test 1 - how long does it take to write a 1000 character string to the sd card?
	DEBUG_SERIAL_LN("Test 1: how long does it take to write a 1000 character string to the sd card?");

	// initialize
	logger.create("test1.txt", 0);
	
	// start test
	start = micros();

	// writes 1000 characters to file
	logger.addEntry(templateString);
	logger.saveToDisk();

	// end test
	end = micros();
	deltaTime = end - start;

	DEBUG_SERIAL("It took ");
	DEBUG_SERIAL(deltaTime);
	DEBUG_SERIAL_LN(" micros to conduct test 1.");

	logger.close();




	// ***************************************************************************************************************************************** //

	// Test 2 - how long does it take to write a single column entry for a csv file?
	DEBUG_SERIAL_LN("Test 2: how long does it take to write a single column entry for a csv file?");

	// initialize
	logger.create("test2.txt", 0);

	// start test
	start = micros();

	// writes single entry to file
	logger.addEntry(templateEntry);
	logger.saveToDisk();

	// end test
	end = micros();
	deltaTime = end - start;

	DEBUG_SERIAL("It took ");
	DEBUG_SERIAL(deltaTime);
	DEBUG_SERIAL_LN(" micros to conduct test 2.");

	logger.close();






	// ***************************************************************************************************************************************** //
	
	// Test 3 - how long does it take to open a file and read 1000 bytes from sd card into a buffer?
	DEBUG_SERIAL_LN("Test 3: how long does it take to open a file and read 1000 bytes from sd card into a buffer?");

	// intialize
	logger.create("test3.txt", 0);
	logger.addEntry(templateString);
	logger.saveToDisk();
	logger.close();

	// start test
	start = micros();

	// opens previous file and reads 1000 characters
    int num = 1000;
	String result = logger.openAndRead("test3.txt", num);

	// end test
	end = micros();
	deltaTime = end - start;
	if (result.length() != num) {
		DEBUG_SERIAL("It took ");
		DEBUG_SERIAL(deltaTime);
		DEBUG_SERIAL_LN(" micros to conduct test 3.");
    } else {
		DEBUG_SERIAL_LN("Use larger file. Could not complete test.");
    }
	DEBUG_SERIAL_LN("Charaters read: " + result);
	logger.close();
}