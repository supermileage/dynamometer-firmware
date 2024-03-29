#include "ValueTextComponent.h"

ui_util::Point ValueTextComponent::computeDisplaySize() {
    ui_util::Point dim = ui_util::computeCharacterDimensions(_font, DEFAULT_SIZE_CHAR, _textSize);
    int16_t len = 0;
    for (int i = 0; i < _nextString.length(); i++) {
        char c = _nextString[i];
        if (isdigit(c)) {
            len += dim.x;
        } else {
            len += ui_util::computeCharacterDimensions(_font, c, _textSize).x;
        }
    }
    dim.x = len;
    return dim;
}

void ValueTextComponent::_drawInternal(TFT_eSPI& display, uint16_t colour) {
    if (_fontChanged || _nextString.length() != _displayString.length()) {
        _stringWidth = ui_util::computeStringDimensions(_font, _nextString, _textSize).x;

        if (_fontChanged) {
            ui_util::Point dimensions = ui_util::computeCharacterDimensions(_font, DEFAULT_SIZE_CHAR, _textSize);
            _charWidth = dimensions.x;
            _charHeight = dimensions.y;
        }
    }

    // horizontally center text in field
    int16_t cursorX = _owner->getPosition().x + (_owner->getWidth() - _stringWidth) / 2;
    // vertically center text in field (cursor is bottom left of text region)
    int16_t height = _owner->getHeight();
    int16_t cursorY = _owner->getPosition().y + height - (height - _charHeight) / 2;

    display.setFreeFont(_font);
    display.setTextSize(_textSize);

    if (!_fontChanged && !_colourChanged && _nextString.length() == _displayString.length()) {
        _drawOptimized(display, colour, cursorX, cursorY);
    } else {
        _redraw(display, colour, cursorX, cursorY);
    }
    _displayString = _nextString;
    _stringChanged = false;
    _fontChanged = false;
    _colourChanged = false;
}

void ValueTextComponent::_drawOptimized(TFT_eSPI& display, uint16_t colour, int16_t x, int16_t y) {
    for (uint16_t i = 0; i < _displayString.length(); i++) {
        char next = _nextString[i];
        char cur = _displayString[i];

        if (next != cur) {
            display.setCursor(x, y);
            display.setTextColor(_owner->getBackgroundColour());
            display.write(cur);

            display.setCursor(x, y);
            display.setTextColor(colour, _owner->getBackgroundColour());
            display.write(next);
        }

        if (isdigit(next) || isdigit(cur)) {
            x += _charWidth;
        } else {
            x += ui_util::computeCharacterDimensions(_font, next, _textSize).x;
        }
    }
}

void ValueTextComponent::_redraw(TFT_eSPI& display, uint16_t colour, int16_t x, int16_t y) {
    display.setTextColor(colour, _owner->getBackgroundColour());
    for (int i = 0; i < _nextString.length(); i++) {
        display.setCursor(x, y);
        char c = _nextString[i];
        display.write(c);
        if (isdigit(c)) {
            x += _charWidth;
        } else {
            x += ui_util::computeCharacterDimensions(_font, c, _textSize).x;
        }
    }
}