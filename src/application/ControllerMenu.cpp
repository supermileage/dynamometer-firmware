#include "ControllerMenu.h"

using namespace application;

ControllerMenu::ControllerMenu(ApplicationContext& context, TFT_eSPI& display) :
    ControllerBase(context, display) {
        _menu = std::make_shared<MenuView>(display);
}

ControllerMenu::~ControllerMenu() {
    DEBUG_SERIAL_LN("~ControllerMenu");
}

void ControllerMenu::init(InputManager& manager, StateInfo& info, const std::vector<MenuButtonInfo>& buttonConfigs) {
    // register all input callbacks with input manager
    ControllerBase::init(manager);

    DEBUG_SERIAL_LN("Initializing new ControllerMenu");
    DEBUG_SERIAL_LN("buttonConfigs.size() = " + String(buttonConfigs.size()));

    _menu->setHeader(info.header);
    _info = info; // cache state info (we need to pass config to next state)
    _inFocus = info.inFocus;

    for (uint8_t i = 0; i < buttonConfigs.size(); i++) {
        const MenuButtonInfo& buttonInfo = buttonConfigs[i];

        DEBUG_SERIAL_LN("ButtonData:");
        DEBUG_SERIAL_LN("state: " + app_util::stateToString(buttonInfo.info.state) + " -- text: " + buttonInfo.text);

        // create menu button with associated capture lambda
        std::shared_ptr<UIButton> button = std::make_shared<UIButton>(_display);
        _menu->addMenuButton(button, buttonInfo.text);
        _buttonInfoPairs.push_back(std::make_pair(button, buttonInfo));
    }

    auto self = shared_from_this();
    auto cur = _buttonInfoPairs[_inFocus].first;
    UIEventHandler::instance().addEvent( [this, self, cur]() {
            _menu->init();
            cur->focus();
        });
}

MenuView& ControllerMenu::getView() {
    return *_menu;
}

void ControllerMenu::_handleInputSerial(input_data_t d) {
    DEBUG_SERIAL_LN("Serial input received: " + String(d));
    switch (d) {
        case 65:    // up
        case 119:    // w
            _shiftFocus(-1);
            break;
        case 66:    // down 
        case 115:    // s
            _shiftFocus(1);
            break;
        case 8:     // backspace
        case 113:    // q
            _navigateBack();
            break;
        case 10:    // enter '\n'
            _triggerStateChange();
            break;
        case 13:    // enter '\r'
            _selectCurrent();
            break;
        case 101:    // e
            _selectCurrent();
            _triggerStateChange();
            break;
        default:    // do nothing
            break;
    }
}

void ControllerMenu::_handleInputEncoder(input_data_t d) {
    _shiftFocus(d);
}

void ControllerMenu::_handleInputEncoderSelect(input_data_t d) {
    if (d && !_buttonHeld) {
        DEBUG_SERIAL_LN("Encoder Select High");
        _buttonHeld = true;
        _selectCurrent();
    } else {
        DEBUG_SERIAL_LN("Encoder Select Low");
        if (_buttonHeld) {
            _buttonHeld = false;
            _triggerStateChange();
        }
    }
}

void ControllerMenu::_handleInputBack(input_data_t d) {
    
    if (d) {
         UIElement* cur = _buttonInfoPairs[_inFocus].first.get();

         //UIElement* cur = _buttonInfoPairs[_inFocus].first;
         UIEventHandler::instance().addEvent([this,cur]() { cur->focus(); _menu->back(); });
    } else {
        _navigateBack();
    }
    
}

void ControllerMenu::_handleInputSelect(input_data_t d) {
    if (d) {
         _selectCurrent();
    } else {
         _triggerStateChange();
    }
}

void ControllerMenu::_navigateBack() {
    if (!_context.tryRevertState()) {
        return;
    }

    DEBUG_SERIAL_LN("Navigate Back");
    auto self = shared_from_this();
    UIEventHandler::instance().addEvent([this, self]() {
        _menu->back();
        _context.setStateTransitionFlag();
    });
}

void ControllerMenu::_shiftFocus(int32_t offset) {
    DEBUG_SERIAL_LN("Shift Focus");
    auto cur = _buttonInfoPairs[_inFocus].first;
    auto self = shared_from_this();
    UIEventHandler::instance().addEvent( [cur, self]() { cur->revert(); } );

    // compute index of new focussed element
    _inFocus = static_cast<uint8_t>(_computeIndexOffset(_inFocus, offset, _buttonInfoPairs.size()));

    // focus new element
    cur = _buttonInfoPairs[_inFocus].first;
    UIEventHandler::instance().addEvent([cur, self]() { cur->focus(); });
}

void ControllerMenu::_selectCurrent() {
    DEBUG_SERIAL_LN("Select Current");
    auto cur = _buttonInfoPairs[_inFocus].first;
    auto self = shared_from_this();
    UIEventHandler::instance().addEvent([this, cur, self]() {
            cur->select();
            _menu->select();
        });
}

void ControllerMenu::_triggerStateChange() {
    // update _info object before call
    MenuButtonInfo buttonInfo = _buttonInfoPairs[_inFocus].second;
    _info.state = buttonInfo.info.state;
    _info.inFocus = 0;
    _info.header = buttonInfo.text;
    _info.addToConfig(buttonInfo.info);

    if (!_context.trySetNextState(_info)) {
        return;
    }

    DEBUG_SERIAL_LN("Trigger State Changed");
    auto button = _buttonInfoPairs[_inFocus].first;
    auto self = shared_from_this();
    UIEventHandler::instance().addEvent(
        [this, button, self]() {
            button->revert();
            _menu->revert();
            _context.setStateTransitionFlag(); // set flag after render actions are complete
        });
}
