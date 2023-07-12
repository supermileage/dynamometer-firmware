#include "TextComponent.h"

TextComponent::~TextComponent() { }

void TextComponent::setOwner(VisualElement* owner) {
    _owner = owner;
}

const String& TextComponent::getDisplayString() {
    return _displayString;
}

TextComponent& TextComponent::setDisplayString(const String& str) {
    _stringChanged = !_displayString.equals(str);
    _nextString = str;
    return *this;
}

TextComponent& TextComponent::setFont(const GFXfont* font) {
    _fontChanged = (_font != font);
    _font = font;
    return *this;
}

TextComponent& TextComponent::setFontColour(const uint16_t colour) {
    _colourChanged = (colour != _fontColour) || _colourChanged;
    _fontColour = colour;
    return *this;
}

uint16_t TextComponent::getFontColour() {
    return _fontColour;
}

TextComponent& TextComponent::setFontSize(uint8_t w, uint8_t h) {
    _fontChanged = (_textSizeX != w) || (_textSizeY != h) || _fontChanged;
    _textSizeX = w;
    _textSizeY = h;
    return *this;
}

void TextComponent::draw(Adafruit_GFX& display) {
    if (_fontChanged || _nextString.length() != _displayString.length()) {
        _textWidth = ui_util::computeStringDimensions(_font, _nextString, _textSizeX, _textSizeY).x;
        _textHeight = ui_util::computeCharacterDimensions(_font, (uint8_t)'0', _textSizeX, _textSizeY).y;
    }
    // only call draw if something has changed
    if (_fontChanged || _stringChanged || _colourChanged) {
        _drawInternal(display, _fontColour);
    }
}

void TextComponent::_drawInternal(Adafruit_GFX& display, uint16_t colour) {
    display.setFont(_font);
    display.setTextColor(colour, _owner->getBackgroundColour());
    display.setTextSize(_textSizeX, _textSizeY);

    // horizontally center text in field
    int16_t cursorX = _owner->getPosition().x + (_owner->getWidth() - _textWidth) / 2;
    // vertically center text in field (cursor is bottom left of text region)
    int16_t height = _owner->getHeight();
    int16_t cursorY = _owner->getPosition().y + height - _textSizeY - (height - _textHeight) / 2;
    
    if (!_fontChanged && !_colourChanged && _nextString.length() == _displayString.length()) {
        _drawOptimized(display, cursorX, cursorY);
    } else {
        display.setCursor(cursorX, cursorY);
        display.write(_nextString.c_str());
    }
    _displayString = _nextString;
    _stringChanged = false;
    _fontChanged = false;
    _colourChanged = false;
}

void TextComponent::_drawOptimized(Adafruit_GFX& display, int16_t x, int16_t y) {
    for (uint16_t i = 0; i < _displayString.length(); i++) {
        char c = _displayString[i];
        int16_t w = ui_util::computeCharacterDimensions(_font, c, _textSizeX, _textSizeY).x;
        if (c != _nextString[i]) {
            display.fillRect(x, y - (_textHeight - 1), w, _textHeight, _owner->getBackgroundColour());
            display.setCursor(x, y);
            display.write((uint8_t)_nextString[i]);
        }
        x += w;
    }
}
