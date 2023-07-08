#ifndef _SYSTEM_UTIL_H_
#define _SYSTEM_UTIL_H_

#include "Arduino.h"

namespace system_util {
    /**
     * @brief generates unique name if filename already exists -- file.csv -> file(1).csv
    */
    String uniquifyFilename(String filename);
}

#endif