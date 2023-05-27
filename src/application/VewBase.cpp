#include "ViewBase.h"
#include "settings.h"
#include "app_util.h"

ViewBase::ViewBase(Adafruit_GFX& display) : _display(display) {
    _window = new Container(_display);
    _header = new TextElement(_display);
    _navButtonContainer = new Container(_display);
    _navButtonSelect = new UIButton(_display);
    _navButtonBack = new UIButton(_display);
}

ViewBase::~ViewBase() {
    delete _window;
    delete _header;
    delete _navButtonContainer;
    delete _navButtonSelect;
    delete _navButtonBack;
}

void ViewBase::setHeader(const String& str) {
    DEBUG_STATE_TRANSITION_LN("Setting header: " + str);
    app_util::configureHeader(_header, str);
}

void ViewBase::select() {
    DEBUG_STATE_TRANSITION_LN("ViewBase::select");
    _navButtonSelect->select();
}

void ViewBase::back() {
    DEBUG_STATE_TRANSITION_LN("ViewBase::back");
    _navButtonBack->select();
}

void ViewBase::revert() {
    DEBUG_STATE_TRANSITION_LN("ViewBase::revert");
    _navButtonBack->revert();
    _navButtonSelect->revert();
}