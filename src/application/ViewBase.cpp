#include "ViewBase.h"
#include "settings.h"
#include "app_util.h"

ViewBase::ViewBase(TFT_eSPI& display) : _display(display) {
    _window = std::make_unique<Container>(_display);
    _header = std::make_shared<TextElement>(_display);
    _navButtonContainer = std::make_shared<Container>(_display);
    _navButtonSelect = std::make_shared<UIButton>(_display);
    _navButtonBack = std::make_shared<UIButton>(_display);
}

ViewBase::~ViewBase() { }

void ViewBase::setHeader(const String& str) {
    DEBUG_SERIAL_LN("Setting header: " + str);
    app_util::configureHeader(_header.get(), str);
}

void ViewBase::select() {
    DEBUG_SERIAL_LN("ViewBase::select");
    _navButtonSelect->select();
}

void ViewBase::back() {
    DEBUG_SERIAL_LN("ViewBase::back");
    _navButtonBack->select();
}

void ViewBase::revert() {
    DEBUG_SERIAL_LN("ViewBase::revert");
    _navButtonBack->revert();
    _navButtonSelect->revert();
}