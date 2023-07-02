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

    /* config ids */
    #define CONFIG_ID_EDIT_STRING_ID            0
    #define CONFIG_ID_DEFAULT_OUTPUT_FILENAME   1
    #define CONFIG_ID_DEFAULT_INPUT_FILENAME    2
    #define CONFIG_ID_DIALOG_START_STRING       3
}

#endif