#include "SettingsView.h"

SettingsView::SettingsView(TFT_eSPI& display) : ViewBase(display) { }

SettingsView::~SettingsView() { }

std::shared_ptr<UIButton> SettingsView::buildInputFilenameDisplay(String& filename) {
    _inputContainer = std::make_unique<Container>(_display);
    return std::make_shared<UIButton>(_display);
}

std::shared_ptr<UIButton> SettingsView::buildOutputFilenameDisplay(String& filename) {
    _outputContainer = std::make_unique<Container>(_display);
    return std::make_shared<UIButton>(_display);
}

std::shared_ptr<UIButton> SettingsView::buildOutputValueButton(application::ValueId id) {
    return std::make_shared<UIButton>(_display);
}

std::shared_ptr<UIButton> SettingsView::buildIntervalButton(uint16_t interval) {
    return std::make_shared<UIButton>(_display);
}
