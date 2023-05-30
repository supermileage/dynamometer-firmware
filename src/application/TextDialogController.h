#ifndef _TEXT_DIALOG_CONTROLLER_H_
#define _TEXT_DIALOG_CONTROLLER_H_

#include <memory>
#include <unordered_map>

#include "ControllerBase.h"
#include "ApplicationContext.h"
#include "TextDialogView.h"
#include "ui/ui_util.h"

#define TEXT_FOCUS_ANIMATION_INTERVAL   750
#define MAX_TEXT_LENGTH                 20

class TextDialogController : public ControllerBase {
    public:
        /**
         * @brief contains set of special characters which aren't in order with other ascii characters
        */
        static const std::unordered_map<char,char> SpecialCharacters;

        TextDialogController(ApplicationContext& context, Adafruit_GFX& display);
        ~TextDialogController();

        /**
         * @brief connects TextDialogController with ui inputs and configures text display
         * @param manager input manager which will be set to update this controller with UI events
         * @param info current state info object
        */
        void init(InputManager& manager, StateInfo& info);

        /**
         * @brief returns view owned by this controller
        */
        TextDialogView& getView();

    private:
        class TextFocusAnimation : public Animation {
            public:
                TextFocusAnimation(std::shared_ptr<UIElement> element) :
                    Animation(TEXT_FOCUS_ANIMATION_INTERVAL, true), _element(element) { }
                ~TextFocusAnimation() {
                    DEBUG_STATE_TRANSITION_LN("~TextFocusAnimation");
                }
                void run(uint32_t time) override;
            private:
                std::shared_ptr<UIElement> _element;
                bool _focussed = false;
        };

        std::shared_ptr<TextDialogView> _view;
        std::shared_ptr<TextFocusAnimation> _currentAnimation = nullptr;
        std::vector<std::shared_ptr<UIButton>> _characterElements;
        String _text;
        String _extension = "";
        uint8_t _editStringId;
        bool _rotarySwitchHeld = false;
        bool _brakeButtonHeld = false;
        bool _buttonHeld = false;

        void _handleInputSerial(input_data_t d) override;
        void _handleInputEncoder(input_data_t d) override;
        void _handleInputEncoderSelect(input_data_t d) override;
        void _handleInputBack(input_data_t d) override;
        void _handleInputSelect(input_data_t d) override;
        void _handleInputBrakeButton(input_data_t d) override;

        void _navigateBack();
        void _buttonChanged(input_data_t d);
        String _removeWhitespace(const String& str);

};

#endif