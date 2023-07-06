#include "SDCardTester.h"

using namespace std;

#define DEBUG_OUTPUT_TRIAL 0

SDCardTester::SDCardTester() {};
SDCardTester::~SDCardTester() {};

void SDCardTester::testFilePerformance (CsvFile& logger) {
	
	// time tracking variables
	int start;
	int end;
	int deltaTime;

	
	int sum;
	int numTrials = 100;
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
	
	// initialize
	logger.create("test1.txt", 1);
	
	for (int i = 0; i < numTrials; i++) {
		// start test
		start = micros();

		// writes 1000 characters to file
		logger.addEntry(templateString);
		logger.saveToDisk();

		// end test
		end = micros();
		deltaTime = end - start;

		#if DEBUG_OUTPUT_TRIAL
		Serial.print("   Trial ");
		Serial.print((i + 1));
		Serial.print(": ");
		Serial.print(deltaTime);
		Serial.println(" micros");
		#endif

		sum += deltaTime;
	}
	logger.close();
	Serial.print("\nAverage time: ");
	Serial.print((float)sum / numTrials);
	Serial.println(" micros");




	// ***************************************************************************************************************************************** //

	// Test 2 - how long does it take to write a single column entry for a csv file?
	Serial.println("\n\nTest 2: how long does it take to write a single column entry for a csv file?");
	Serial.println("Entry: \"1.0\"");

	// initialize
	logger.create("test2.csv", 1);

	sum = 0;
	for (int i = 0; i < numTrials; i++) {
		// start test
		start = micros();

		// writes single entry to file
		logger.addEntry(templateEntry);
		logger.saveToDisk();

		// end test
		end = micros();
		deltaTime = end - start;

		#if DEBUG_OUTPUT_TRIAL
		Serial.print("   Trial ");
		Serial.print((i + 1));
		Serial.print(": ");
		Serial.print(deltaTime);
		Serial.println(" micros");
		#endif

		sum += deltaTime;
	}
	logger.close();
	Serial.print("\nAverage time: ");
	Serial.print((float)sum / numTrials);
	Serial.println(" micros");


	// ***************************************************************************************************************************************** //

	// Test 3 - how long does it take to write 5 column entries for a csv file?
	Serial.println("\n\nTest 3: how long does it take to write five column entries for a csv file (osync = false)?");

	// initialize
	logger.create("test3.csv", 5);


	sum = 0;
	for (int i = 0; i < numTrials; i++) {
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

		#if DEBUG_OUTPUT_TRIAL
		Serial.print("   Trial ");
		Serial.print((i + 1));
		Serial.print(": ");
		Serial.print(deltaTime);
		Serial.println(" micros");
		#endif

		sum += deltaTime;
	}
	logger.close();
	Serial.print("\nAverage time: ");
	Serial.print((float)sum / numTrials);
	Serial.println(" micros");


	// ***************************************************************************************************************************************** //
	
	// Test 4 - how long does it take to open a file and read 1000 bytes from sd card into a buffer?
	Serial.println("\n\nTest 4: how long does it take to open a file and read 1000 bytes from sd card into a buffer?");

	// intialize test
	if (SD.exists("test4.csv")) {
		SD.remove("test4.csv");
	}
	logger.open("test4.csv", 1);
	for (int i = 0; i < numTrials; i++) {
		logger.addEntry(templateString);
		logger.saveToDisk();
	}
	logger.close();

	// open and read file
	File readFile = SD.open("test4.csv", FILE_READ);
	
	sum = 0;
	char buf[1002] = { };
	for (int i = 0; i < numTrials; i++) {

		// start test
		start = micros();

		// opens previous file and reads 1000 characters
		int num = 1000;
		int count = 0;
		if ((count = readFile.readBytesUntil('\n', buf, 1002)) < 0) {
			Serial.println("ERROR READING FILE, ABORTING TEST");
			break;
		}

		// end test
		end = micros();
		deltaTime = end - start;

		#if DEBUG_OUTPUT_TRIAL
		Serial.print("   Trial ");
		Serial.print((i + 1));
		Serial.print(": ");
		#endif
		if (count > 0) {
			#if DEBUG_OUTPUT_TRIAL
			Serial.print(deltaTime);
			Serial.println(" micros");
			#endif
		} else {
			Serial.println("Reached end of file before test completed.  Use larger file");
			break;
		}
		// DEBUG_SERIAL_LN("Charaters read: " + result);
		sum += deltaTime;
	}
	Serial.print("\nAverage time: ");
	Serial.print((float)sum / numTrials);
	Serial.println(" micros");
}