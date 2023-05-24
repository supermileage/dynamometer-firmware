#ifndef _APPLICATION_H_
#define _APPLICATION_H_

namespace application {
    /**
     * @brief ApplicationState is enum representing all application states
     * @note add state here when adding new state to application
    */
    enum ApplicationState {
        MainMenu = 0,
        ManualControlMenu = 1,
        CalibrationMenu = 2,
        SettingsMenu = 3
    };

    /**
     * @brief represents state information which can be used for transitions and navigation
    */
    struct StateData {
        ApplicationState state;
        uint8_t inFocus;
    };
}

#endif