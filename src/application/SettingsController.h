#ifndef _SETTINGS_CONTROLLER_H_
#define _SETTINGS_CONTROLLER_H_

#include <memory>
#include <functional>

#include "ControllerBase.h"
#include "SettingsView.h"

class SettingsController : public ControllerBase {
    public:
        SettingsController(ApplicationContext& context, TFT_eSPI& display);
        ~SettingsController();

        /**
         * @brief connects SettingsController with ui inputs and configures settings menu
         * @param manager input manager which will be set to update this controller with UI events
         * @param info current state info object
        */
        void init(InputManager& manager, StateInfo& info);

    private:
        enum CallbackStatus { Focus, Unfocus, DoNothing };
        typedef std::function<CallbackStatus(input_data_t)> callback_t; // callback returns 

        std::shared_ptr<SettingsView> _view;
        std::vector<std::pair<std::shared_ptr<UIButton>, callback_t>> _buttonCallbackPairs;
        std::array<bool, application::NUM_VALUE_IDS> _selectedIds;
        String _inputFilename = "";
        String _outputFilename = "";
        bool _intervalButtonSelected = false;

        void _initializeInputSettings(uint8_t id);
        void _initializeOutputSettings(uint8_t id);
        void _initializeIntervalSettings(uint16_t interval);
        CallbackStatus _handleInputStringSelected(uint8_t id, input_data_t d);
        CallbackStatus _handleOutputStringSelected(uint8_t id, input_data_t d);
        CallbackStatus _handleValueIdSelected(application::ValueId id, input_data_t d);
        CallbackStatus _handleIntervalSelected(input_data_t d);
        void _transitionToTextDialog(uint8_t id, const char* header);
        std::vector<application::ValueId> _getSelectedIds();

        // input handlers
        void _handleInputSerial(input_data_t d) override;
        void _handleInputEncoder(input_data_t d) override;
        void _handleInputEncoderSelect(input_data_t d) override;
        void _handleInputBack(input_data_t d) override;
        void _handleInputSelect(input_data_t d) override;
        void _handleInputBrakeButton(input_data_t d) override;

        void _onButtonSelected(input_data_t d);
        void _shiftFocus(int32_t offset);
};

#endif