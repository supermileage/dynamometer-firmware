#ifndef _TEXT_DIALOG_CONTROLLER_H_
#define _TEXT_DIALOG_CONTROLLER_H_

#include "ControllerBase.h"
#include "ApplicationContext.h"
#include "TextDialogView.h"
#include "ui/ui_util.h"

#define TEXT_FOCUS_ANIMATION_INTERVAL 750

class TextDialogController : public ControllerBase {
    public:
        TextDialogController(ApplicationContext context, Adafruit_GFX& display, uint8_t inFocus);
        ~TextDialogController();

        /**
         * @brief connects TextDialogController with ui inputs and configures text display
         * @param manager input manager which will be set to update this controller with UI events
         * @param start starting string which will be displayed in dialog
        */
        void init(InputManager& manager, const String& start);

        /**
         * @brief returns view owned by this controller
        */
        TextDialogView& getView();

    private:
        class TextFocusAnimation : public Animation {
            public:
                TextFocusAnimation(UIElement* element) :
                    Animation(TEXT_FOCUS_ANIMATION_INTERVAL, true), _element(element) { }
                void run(uint32_t time) override;
            private:
                UIElement* _element;
                bool _focussed = false;
        };

        TextDialogView* _view;
        TextFocusAnimation* _currentAnimation = nullptr;
        int16_t _maxTextLength = 20;
        std::vector<UIButton*> _characterElements;
        bool _selectHeld = false;

        void _handleInputSerial(input_data_t d) override;
        void _handleInputEncoder(input_data_t d) override;
        void _handleInputEncoderSelect(input_data_t d) override;
        void _handleInputBack(input_data_t d) override;
        void _handleInputSelect(input_data_t d) override;
};

#endif