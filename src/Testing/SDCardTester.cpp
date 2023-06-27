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

	
	int sum;
	int numOfTrials = 100;
	String filename = "";

	// create a template string with 1000 characters
	String templateString = "";
	for (int i = 0; i < 1000; i++)
		templateString += "X";

	// create a template csv entry
	String templateEntry = "1.0";




	
	// ***************************************************************************************************************************************** //
	
	// Test 1 - how long does it take to write a 1000 character string to the sd card?
	Serial.println("\n\nTest 1: how long does it take to write a 1000 character string to the sd card?");

	sum = 0;
	for (int i = 0; i < numOfTrials; i++) {
		String prefix = "test1[";
		String suffix = "].txt";
		filename = prefix + i;
		filename = filename + suffix;

		// initialize
		logger.create(filename, 1);
		
		// start test
		start = micros();

		// writes 1000 characters to file
		logger.addEntry(templateString);
		logger.saveToDisk();

		// end test
		end = micros();
		deltaTime = end - start;

		Serial.print("   Trial ");
		Serial.print((i + 1));
		Serial.print(": ");
		Serial.print(deltaTime);
		Serial.println(" micros");

		sum += deltaTime;
		logger.close();
	}
	Serial.print("\nAverage time: ");
	Serial.print((float)sum / numOfTrials);
	Serial.println(" micros");




	// ***************************************************************************************************************************************** //

	// Test 2 - how long does it take to write a single column entry for a csv file?
	Serial.println("\n\nTest 2: how long does it take to write a single column entry for a csv file?");
	Serial.println("Entry: \"1.0\"");

	sum = 0;
	for (int i = 0; i < numOfTrials; i++) {
		String prefix = "test2[";
		String suffix = "].txt";
		filename = prefix + i;
		filename = filename + suffix;

		// initialize
		logger.create(filename, 1);

		// start test
		start = micros();

		// writes single entry to file
		logger.addEntry(templateEntry);
		logger.saveToDisk();

		// end test
		end = micros();
		deltaTime = end - start;

		Serial.print("   Trial ");
		Serial.print((i + 1));
		Serial.print(": ");
		Serial.print(deltaTime);
		Serial.println(" micros");

		sum += deltaTime;
		logger.close();
	}
	Serial.print("\nAverage time: ");
	Serial.print((float)sum / numOfTrials);
	Serial.println(" micros");


	// ***************************************************************************************************************************************** //

	// Test 3 - how long does it take to write 5 column entries for a csv file?
	Serial.println("\n\nTest 3: how long does it take to write five column entries for a csv file (osync = false)?");

	sum = 0;
	for (int i = 0; i < numOfTrials; i++) {
		String prefix = "test3[";
		String suffix = "].txt";
		filename = prefix + i;
		filename = filename + suffix;

		// initialize
		logger.create(filename, 5);

		// start test
		start = micros();

		// writes single entry to file
		logger.addEntry(templateEntry);
		logger.addEntry(templateEntry);
		logger.addEntry(templateEntry);
		logger.addEntry(templateEntry);
		logger.addEntry(templateEntry);
		logger.saveToDisk();

		// end test
		end = micros();
		deltaTime = end - start;

		Serial.print("   Trial ");
		Serial.print((i + 1));
		Serial.print(": ");
		Serial.print(deltaTime);
		Serial.println(" micros");

		sum += deltaTime;
		logger.close();
	}
	Serial.print("\nAverage time: ");
	Serial.print((float)sum / numOfTrials);
	Serial.println(" micros");


	// ***************************************************************************************************************************************** //
	
	// Test 4 - how long does it take to open a file and read 1000 bytes from sd card into a buffer?
	Serial.println("\n\nTest 4: how long does it take to open a file and read 1000 bytes from sd card into a buffer?");

	// intialize
	logger.create("test4.txt", 0);
	logger.addEntry(templateString);
	logger.saveToDisk();
	logger.close();

	sum = 0;
	for (int i = 0; i < numOfTrials; i++) {

		// start test
		start = micros();

		// opens previous file and reads 1000 characters
		int num = 1000;
		String result = logger.openAndRead("test4.txt", num);

		// end test
		end = micros();
		deltaTime = end - start;

		Serial.print("   Trial ");
		Serial.print((i + 1));
		Serial.print(": ");
		if (result.length() != num) {
			Serial.print(deltaTime);
			Serial.println(" micros");
		} else {
			Serial.println(" Use larger file. Could not complete test.");
			break;
		}
		// DEBUG_SERIAL_LN("Charaters read: " + result);
		sum += deltaTime;
	}
	Serial.print("\nAverage time: ");
	Serial.print((float)sum / numOfTrials);
	Serial.println(" micros");
}