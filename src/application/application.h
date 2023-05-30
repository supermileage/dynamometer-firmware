#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <unordered_map>

namespace application {
    /**
     * @brief ApplicationState is enum representing all application states
     * @note add state here when adding new state to application
    */
    enum ApplicationState {
        NullState = -1,
        MainMenu = 0,
        ManualControlMenu = 1,
        CalibrationMenu = 2,
        SettingsMenu = 3,
        CalibrationMode = 4,
        CalibrationSettings = 5,
        TextDialog = 6
    };

    /**
     * @brief represents state information which can be used for transitions and navigation
     * @note you can think of this data structure as a json settings object, as the config map is a
     * dictionary which can be used to store arbitrary state information
    */
    struct StateData {
        ApplicationState state;
        std::unordered_map<uint8_t, String> config;
        uint8_t inFocus;

        /**
         * @brief reset to null state
        */
        void reset() {
            state = NullState;
            inFocus = 0;
            config.clear();
        }
    };

    /* config ids */
    #define CONFIG_ID_MENU_HEADER       0
}

#endif