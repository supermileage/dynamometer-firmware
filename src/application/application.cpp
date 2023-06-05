#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "application.h"

using namespace application;

// copy of config macros for reference
// #define CONFIG_ID_EDIT_STRING_ID            0
// #define CONFIG_ID_DEFAULT_OUTPUT_FILENAME   1
// #define CONFIG_ID_DEFAULT_INPUT_FILENAME    2
// #define CONFIG_ID_DIALOG_START_STRING       3

std::unordered_map<uint8_t, String> application::GlobalSettings = {
    { CONFIG_ID_DEFAULT_OUTPUT_FILENAME, "default-out.csv" },
    { CONFIG_ID_DEFAULT_INPUT_FILENAME, "default-in.csv" },
};

#endif