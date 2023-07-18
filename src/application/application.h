#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <unordered_map>

#include "settings.h"

namespace application {
    /**
     * @brief ApplicationState is enum representing all application states
     * @note add state here when adding new state to application
    */
    enum ApplicationState {
        NullState = -1,
        MainMenu,
        GlobalSettingsMenu,
        CalibrationMenu,
        CalibrationMode,
        CalibrationSettings,
        AutoControlMenu,
        AutoControlMode,
        AutoControlSettings,
        ManualControlMenu,
        ManualControlMode,
        ManualControlSettings,
        TextDialog,
        Sandbox
    };

    /**
     * @brief represents state information which can be used for transitions and navigation
     * @note you can think of this data structure as a json settings object, as the config map is a
     * dictionary which can be used to store arbitrary state information
    */
    struct StateInfo {
        ApplicationState state;
        String header = "";
        std::unordered_map<uint8_t, String> config;
        uint8_t inFocus = 0;

        /**
         * @brief reset to null state
        */
        void reset() {
            state = NullState;
            header = "";
            inFocus = 0;
            config.clear();
        }

        /**
         * @brief add everything in info.config to this StateInfo config
        */
        void addToConfig(StateInfo& info) {
            for (auto const& pair : info.config) {
                config[pair.first] = pair.second;
            }
        }

        String toString() {
            String ret = " -- State Info Object -- ";
            ret += "\tstate:\t" + String(state);
            ret += "\theader:\t" + String(header);
            ret += "\tinFocus:\t" + String((int)inFocus);
            ret += "\tconfig:";
            for (auto const& pair : config) {
                ret += "\t\t{ " + String((int)pair.first) + ", " + pair.second + " } ";
            }
            return ret;
        }
    };

    extern std::unordered_map<uint8_t, String> GlobalSettings;

    /* config string indices */
    #define CONFIG_ID_NULL                          0
    #define CONFIG_ID_EDIT_STRING_GLOBAL_ID         1
    #define CONFIG_ID_OUTPUT_FILE_GLOBAL_ID         2
    #define CONFIG_ID_INPUT_FILE_GLOBAL_ID          3
    #define CONFIG_ID_VALUE_IDS                     4
    #define CONFIG_ID_LOGGING_INTERVAL              5

    /* path ids */
    #define CONFIG_ID_DEFAULT_OUTPUT_FILENAME       6
    #define CONFIG_ID_DEFAULT_INPUT_FILENAME        7
    #define CONFIG_ID_CALIBRATION_OUTPUT_FILENAME   8
    #define CONFIG_ID_CALIBRATION_INPUT_FILENAME    9
    #define CONFIG_ID_AUTO_OUTPUT_FILENAME          10
    #define CONFIG_ID_AUTO_INPUT_FILENAME           11
    #define CONFIG_ID_MANUAL_OUTPUT_FILENAME        12

    enum ValueId {
        Force = 0,
        AngularVelocity,
        AngularAccel,
        DynoRpm,
        BpmVoltage,
        BpmCurrent,
        Time,
        VescRpm,
        VescDuty,
        VescCurrent,
    };
}

#endif