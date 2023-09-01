#ifndef _SETTINGS_VIEW_H_
#define _SETTINGS_VIEW_H_

#include <vector>

#include "ViewBase.h"
#include "application.h"

class SettingsView : public ViewBase {
    public:
        SettingsView(TFT_eSPI& display);
        ~SettingsView();
        std::shared_ptr<UIButton> buildInputFilenameDisplay(String& filename);
        std::shared_ptr<UIButton> buildOutputFilenameDisplay(String& filename);
        std::shared_ptr<UIButton> buildOutputValueButton(application::ValueId id);
        std::shared_ptr<UIButton> buildIntervalButton(uint16_t interval);

    private:
        std::shared_ptr<Container> _inputContainer = nullptr;
        std::shared_ptr<Container> _outputContainer = nullptr;
        std::shared_ptr<Container> _valueButtonsContainer = nullptr;
};

#endif