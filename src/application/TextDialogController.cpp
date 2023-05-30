#include "TextDialogController.h"
#include "ui/UIEventHandler.h"

#define FIRST_CHAR  '.' // 46 (not that certain characters have been co-opted to represent others)
#define LAST_CHAR   'z' // 122
#define CHAR_RANGE  (LAST_CHAR - FIRST_CHAR)

const std::unordered_map<char,char> TextDialogController::SpecialCharacters = {
    { '/', ' ' }, // '/' maps to ' '
    { ' ', '/' }, 
    { '.', '-' }, // '.' maps to '-'
    { '-', '.' },
};

TextDialogController::TextDialogController(ApplicationContext& context, Adafruit_GFX& display)
    : ControllerBase(context, display) {
    _view = std::make_shared<TextDialogView>(_display);
}

TextDialogController::~TextDialogController() {
    DEBUG_SERIAL_LN("~TextDialogController");
}

void TextDialogController::init(InputManager& manager, StateInfo& info) {
    ControllerBase::init(manager);

    // get extension and initialize text
    _info = info;
    _editStringId = static_cast<uint8_t>(info.config[CONFIG_ID_EDIT_STRING_ID].toInt());

    if (application::GlobalSettings.find(_editStringId) != application::GlobalSettings.end()) {
        _text = application::GlobalSettings[_editStringId];
    } else {
        _text = "";
        DEBUG_SERIAL_LN("No global config entry for text entry: " + String(_editStringId));
    }
    int i = _text.lastIndexOf('.');
    if (i != -1) {
        _extension = _text.substring(i);
        for (; i < _text.length(); i++) {
            _text[i] = ' ';
        }
        for (; i < MAX_TEXT_LENGTH; i++) {
            _text += ' ';
        }
    }

    DEBUG_SERIAL_LN("Edit String ID: " + String(_editStringId));

    // initialize character selector buttons
    for (i = 0; i < MAX_TEXT_LENGTH; i++) {
        char cur = _text[i];
        std::shared_ptr<UIButton> button = std::make_shared<UIButton>(_display);
        button->getTextComponent().setDisplayString(String(cur));
        _view->addCharacterElement(button);
        _characterElements.push_back(button);
    }

    // header and display text
    _view->setHeader(info.header);
    String displayText = _removeWhitespace(_text) + _extension;
    _view->setTextDisplay(displayText);

    // initialize view and animation
    auto self = shared_from_this();
    UIEventHandler::instance().addEvent( [this, self]() {  _view->init(); } );
    _currentAnimation = std::make_shared<TextFocusAnimation>(_characterElements[_inFocus]);
    UIEventHandler::instance().addAnimation(_currentAnimation);
}

TextDialogView& TextDialogController::getView() {
    return *_view;
}

void TextDialogController::_handleInputSerial(input_data_t d) {
    DEBUG_STATE_TRANSITION_LN("Serial input received: " + String(d));
    switch (d) {
        case 65:    // up
            // _shiftFocus(-1);
            break;
        case 66:    // down 
            // _shiftFocus(1);
            break;
        case 8:     // backspace
            _navigateBack();
            break;
        case 10:    // enter '\n'
            // _triggerStateChange();
            break;
        case 13:    // enter '\r'
            // _selectCurrent();
            break;
        default:    // do nothing
            break;
    }
}

void TextDialogController::_handleInputEncoder(input_data_t d) {
    if (_buttonHeld) {
        std::shared_ptr<UIButton> cur = _characterElements[_inFocus];
        char c = _text[_inFocus];
        if (SpecialCharacters.find(c) != SpecialCharacters.end()) {
            c = SpecialCharacters.at(c);
        }

        c = static_cast<char>(_computeIndexOffset(c - FIRST_CHAR, d, CHAR_RANGE) + FIRST_CHAR);
        if (SpecialCharacters.find(c) != SpecialCharacters.end()) {
            c = SpecialCharacters.at(c);
        }

        TextComponent& text = cur->getTextComponent().setDisplayString(String(c));
        text.setDisplayString(String(c));
        _text[_inFocus] = c;

        String displayText = _removeWhitespace(_text) + _extension;
        _view->setTextDisplay(displayText);
        auto self = shared_from_this();
        UIEventHandler::instance().addEvent([cur, this, self]() {
                cur->select();
                _view->redrawTextDisplay();
            });
    } else {
        uint8_t next = static_cast<uint8_t>(_computeIndexOffset(_inFocus, d, _characterElements.size()));

        if (next != _inFocus) {
            std::shared_ptr<UIElement> cur = _characterElements[_inFocus];
            UIEventHandler::instance().addEvent([cur]() { cur->revert(); });
            UIEventHandler::instance().removeAnimation(_currentAnimation);

            _inFocus = next;
            cur = _characterElements[_inFocus];
            _currentAnimation = std::make_shared<TextFocusAnimation>(cur);
            UIEventHandler::instance().addAnimation(_currentAnimation);
        }
    }
}

void TextDialogController::_handleInputEncoderSelect(input_data_t d) {
    if (d) {
        if (!_rotarySwitchHeld && !_brakeButtonHeld) {
            _buttonChanged(d);
        }
        _rotarySwitchHeld = true;
    } else {
        if (_rotarySwitchHeld && !_brakeButtonHeld) {
            _buttonChanged(d);
        }
        _rotarySwitchHeld = false;
    }
}

void TextDialogController::_handleInputBack(input_data_t d) {
    // TODO: back confirmation dialog
}

void TextDialogController::_handleInputSelect(input_data_t d) {
    if (d) {
        application::GlobalSettings[_editStringId] = _removeWhitespace(_text) + _extension;
        _info.inFocus = _inFocus;

        if (!_context.tryUpdateAndReturn(_info)) {
            return;
        }

        UIEventHandler::instance().removeAnimation(_currentAnimation);
        auto self = shared_from_this();
        UIEventHandler::instance().addEvent(
            [this, self]() {
                _view->select();
                _context.setStateTransitionFlag(); // set flag after render actions are complete
            });
    }
}

void TextDialogController::_handleInputBrakeButton(input_data_t d) {
    if (d) {
        if (!_rotarySwitchHeld && !_brakeButtonHeld) {
            _buttonChanged(d);
        }
        _brakeButtonHeld = true;
    } else {
        if (_brakeButtonHeld && !_rotarySwitchHeld) {
            _buttonChanged(d);
        }
        _brakeButtonHeld = false;
    }
}

void TextDialogController::_navigateBack() {
    if (!_context.tryRevertState()) {
        return;
    }

    auto self = shared_from_this();
    UIEventHandler::instance().addEvent([this, self]() {
        _view->back();
        _context.setStateTransitionFlag();
    });
    UIEventHandler::instance().removeAnimation(_currentAnimation);
}

void TextDialogController::_buttonChanged(input_data_t d) {
    if (d) {
        _buttonHeld = true;
        UIEventHandler::instance().removeAnimation(_currentAnimation);
        _currentAnimation = nullptr;
        std::shared_ptr<UIButton> cur = _characterElements[_inFocus];
        UIEventHandler::instance().addEvent([cur]() { cur->select(); });
    } else {
        _buttonHeld = false;
        std::shared_ptr<UIButton> cur = _characterElements[_inFocus];
        _currentAnimation = std::make_shared<TextFocusAnimation>(cur);
        UIEventHandler::instance().addAnimation(_currentAnimation);
    }
}

String TextDialogController::_removeWhitespace(const String& str) {
    String ret = "";
    for (char c : str) {
        if (c != ' ') {
            ret += c;
        }
    }
    return ret;
}

/* text focus animation */

void TextDialogController::TextFocusAnimation::run(uint32_t time) {
    if (time >= _interval + _lastTime) {
        if (_focussed) {
            _element->revert();
        } else {
            _element->focus();
        }
        _focussed = !_focussed;
        _lastTime = time;
    }
}
