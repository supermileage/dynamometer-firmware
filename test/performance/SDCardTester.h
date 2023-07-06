
#ifndef _SD_CARD_TESTER_H_
#define _SD_CARD_TESTER_H_

#include "Arduino.h"
#include "SPI.h"
#include "System/CsvFile.h"

using namespace std;

class SDCardTester {
    public:
        SDCardTester();
        ~SDCardTester();
        void testFilePerformance(CsvFile& logger);

    private:
};

#endif