#ifndef _DATA_LOGGER_H_
#define _DATA_LOGGER_H_

#include <SD.h>
#include "settings.h"

class DataLogger {
	public:
		bool open(String fileName);
		void writeColumn()

};

#endif