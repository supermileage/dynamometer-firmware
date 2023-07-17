#ifndef _CONTROLLER_MENU_H_
#define _CONTROLLER_MENU_H_

#include <vector>
#include <utility>
#include <memory>

#include "settings.h"
#include "System/InputManager.h"
#include "ui/UIEventHandler.h"
#include "ui/UIButton.h"

#include "MenuView.h"
#include "ApplicationContext.h"
#include "application.h"
#include "ControllerBase.h"

/**
 * @brief represents configurable default menu for dyno with customizable navigation buttons
*/
class ControllerMenu : public ControllerBase {
    public:
        /**
         * @brief menu button configuration data with display text and state which button transitions to
        */
        struct MenuButtonInfo {
            const String text;
            StateInfo info;
        };

        ControllerMenu(ApplicationContext& context, TFT_eSPI& display);
        ~ControllerMenu();

        /**
         * @brief connects ControllerMenu with ui inputs and configures interactive buttons
         * @param manager input manager which will be set to update this controller with UI events
         * @param buttonConfigs ui button data to configure the interactive buttons of this menu
        */
        void init(InputManager& manager, StateInfo& state, const std::vector<MenuButtonInfo>& buttonConfigs);

        /**
         * @brief returns view associated with this controller
        */
        MenuView& getView();

    private:
        std::shared_ptr<MenuView> _menu;
        std::vector<std::pair<std::shared_ptr<UIButton>, MenuButtonInfo>> _buttonInfoPairs;
        bool _buttonHeld = false;

        // ControllerBase already provides default input handler implementations, so you only
        // need to override the inputs you want to use

        void _handleInputSerial(input_data_t d) override;
        void _handleInputEncoder(input_data_t d) override;
        void _handleInputEncoderSelect(input_data_t d) override;
        void _handleInputBack(input_data_t d) override;
        void _handleInputSelect(input_data_t d) override;

        /* actions */
        void _navigateBack();
        void _shiftFocus(int32_t offset);
        void _selectCurrent();
        void _triggerStateChange();
};

#endif