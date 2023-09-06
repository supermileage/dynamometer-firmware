#ifndef _SETTINGS_VIEW_H_
#define _SETTINGS_VIEW_H_

#include <vector>

#include "ViewBase.h"
#include "application.h"

class SettingsView : public ViewBase {
    public:
        SettingsView(TFT_eSPI& display);
        ~SettingsView();
        void init();
        std::shared_ptr<UIButton> buildInputFilenameDisplay(String& filename);
        std::shared_ptr<UIButton> buildOutputFilenameDisplay(String& filename);
        std::shared_ptr<UIButton> buildOutputValueButton(application::ValueId id);
        std::shared_ptr<UIButton> buildIntervalButton(String& interval);

    private:
        std::shared_ptr<Container> _menuContainer = nullptr;
        std::shared_ptr<Container> _inputContainer = nullptr;
        std::shared_ptr<Container> _outputContainer = nullptr;
        std::shared_ptr<Container> _outputRow = nullptr;
        std::shared_ptr<Container> _valueButtonsContainer = nullptr;
        uint8_t _numButtons = 0;

        void _configureModifyButton(std::shared_ptr<UIButton> button);
        void _configureFilenameText(std::shared_ptr<TextElement> txt, String& filename);
        void _configureSectionHeader(std::shared_ptr<TextElement> header, String& text, int16_t width);
        void _outputContainerInit();
        void _outputRowInit();
};

#endif