#include "ControllerMenu.h"

using namespace application;

ControllerMenu::ControllerMenu(ApplicationContext& context, Adafruit_GFX& display, uint8_t inFocus) :
    ControllerBase(context, display, inFocus) {
        _menu = new MenuView(display);
}

ControllerMenu::~ControllerMenu() {
    DEBUG_STATE_TRANSITION_LN("Clearing event queue");
    DEBUG_STATE_TRANSITION_LN("~ControllerMenu");
    delete _menu;

    // delete all UIButtons generated from call to init
    for (const auto& pair : _buttonCallbackMap) {
        delete pair.second.first;
    }
}

void ControllerMenu::init(InputManager& manager, const std::vector<MenuButtonData>& buttonConfigs) {
    // register all input callbacks with input manager
    ControllerBase::init(manager);

    DEBUG_STATE_TRANSITION_LN("Initializing new ControllerMenu");
    DEBUG_STATE_TRANSITION_LN("buttonConfigs.size() = " + String(buttonConfigs.size()));
    for (uint8_t i = 0; i < buttonConfigs.size(); i++) {
        const MenuButtonData& data = buttonConfigs[i];

        DEBUG_STATE_TRANSITION_LN("ButtonData:");
        DEBUG_STATE_TRANSITION_LN("state: " + app_util::stateToString(data.state) + " -- text: " + data.text);
        UIButton* cur = new UIButton(_display);
        _menu->addMenuButton(cur, data.text);
        _buttonCallbackMap[i] = std::make_pair(cur, [this, data]() { _context.setNextState(data.state); });
    }

    DEBUG_STATE_TRANSITION_LN("Initializing view");
    UIEventHandler::instance().addEvent( [this]() { _menu->init(); } );
    UIEventHandler::instance().addEvent( [this]() { _buttonCallbackMap[_inFocus].first->focus(); } );
}

MenuView& ControllerMenu::getView() {
    return *_menu;
}

void ControllerMenu::_handleInputSerial(input_data_t d) {
    DEBUG_STATE_TRANSITION_LN("Serial input received: " + String(d));

    switch (d) {
        case 65:
            _shiftFocus(-1);
            break;
        case 66:
            _shiftFocus(1);
            break;
        case 10:
            _triggerStateChange();
            break;
        case 13:
            _selectCurrent();
            break;
        case 8:
            _navigateBack();
            break;
        default:
            // do nothing
            break;
    }
}

void ControllerMenu::_handleInputEncoder(input_data_t d) {
    _moveFocus(d);
}

void ControllerMenu::_handleInputEncoderSelect(input_data_t d) {
    if (d) {
        _selectCurrent();
    } else {
        _triggerStateChange();
    }
}

void ControllerMenu::_handleInputBack(input_data_t d) {
    // if (d) {
    //     UIElement* cur = _buttonCallbackMap[_inFocus].first;
    //     UIEventHandler::instance().addEvent([this,cur]() { cur->focus(); _menu->back(); });
    // } else {
    //     _navigateBack();
    // }
}

void ControllerMenu::_handleInputSelect(input_data_t d) {
    // if (d) {
    //     _selectCurrent();
    // } else {
    //     _triggerStateChange();
    // }
}

void ControllerMenu::_navigateBack() {
    _context.revertState();
    UIEventHandler::instance().addEvent([this]() {
        _menu->back();
        _context.setStateTransitionFlag();
    });
}

void ControllerMenu::_shiftFocus(int32_t offset) {
    UIElement* cur = _buttonCallbackMap[_inFocus].first;
    UIEventHandler::instance().addEvent( [cur]() { cur->revert(); } );

    // compute index of new focussed element
    int32_t modVal = _buttonCallbackMap.size();
    input_data_t val = ((_inFocus + offset) % modVal + modVal) % modVal;
    _inFocus = static_cast<uint8_t>(val);

    // focus new element
    cur = _buttonCallbackMap[_inFocus].first;
    UIEventHandler::instance().addEvent([cur]() { cur->focus(); });
}

void ControllerMenu::_selectCurrent() {
    UIElement* cur = _buttonCallbackMap[_inFocus].first;
    UIEventHandler::instance().addEvent([this, cur]() {
            DEBUG_STATE_TRANSITION_LN("Prelim state change render event invoked");
            cur->select();
            _menu->select();
            DEBUG_STATE_TRANSITION_LN("Prelim state change render event complete");
        });
}

void ControllerMenu::_triggerStateChange() {
    UIElement* cur = _buttonCallbackMap[_inFocus].first;
    UIEventHandler::instance().addEvent(
        [this, cur]() {
            DEBUG_STATE_TRANSITION_LN("Final state change render event invoked");
            cur->revert();
            _menu->revert();
            _context.setStateTransitionFlag(); // set flag after render actions are complete
            DEBUG_STATE_TRANSITION_LN("Final state change render event complete");
        });
    (_buttonCallbackMap[_inFocus].second)();
}


