#include "TextComponent.h"

TextComponent::~TextComponent() { }

void TextComponent::setOwner(VisualElement* owner) {
    _owner = owner;
}

const String& TextComponent::getDisplayString() {
    return _displayString;
}

TextComponent& TextComponent::setDisplayString(const String& str) {
    _displayString = str;
    _textChanged = true;
    return *this;
}

TextComponent& TextComponent::setFont(const GFXfont* font) {
    _font = font;
    _textChanged = true;
    _heightComputed = false;
    return *this;
}

TextComponent& TextComponent::setFontColour(const uint16_t colour) {
    _fontColour = colour;
    return *this;
}

uint16_t TextComponent::getFontColour() {
    return _fontColour;
}

TextComponent& TextComponent::setFontSize(uint8_t w, uint8_t h) {
    _textSizeX = w;
    _textSizeY = h;
    _textChanged = true;
    return *this;
}

void TextComponent::draw(Adafruit_GFX& display) {
    if (_textChanged) {
        _textWidth = ui_util::computeStringDimensions(_font, _displayString, _textSizeX, _textSizeY).x;
        
        // prevent text from moving around a bunch on the y axis if display string changes
        if (!_heightComputed) {
            _textHeight = ui_util::computeCharacterDimensions(_font, (uint8_t)'L', _textSizeX, _textSizeY).y;
            _heightComputed = true;
        }
        _textChanged = false;
    }

    _drawInternal(display, _fontColour);
}

void TextComponent::draw(Adafruit_GFX& display, uint16_t colour) {
    _drawInternal(display, colour);
}

void TextComponent::_drawInternal(Adafruit_GFX& display, uint16_t colour) {
    display.setFont(_font);
    display.setTextColor(colour, _owner->getBackgroundColour());
    display.setTextSize(_textSizeX, _textSizeY);

    // horizontally center text in field
    int16_t cursorX = _owner->getPosition().x + (_owner->getWidth() - _textWidth) / 2;
    // vertically center text in field
    int16_t height = _owner->getHeight();
    int16_t cursorY = _owner->getPosition().y + height - _textSizeY - (height - _textHeight) / 2;
    // cursor is bottom left of text region
    display.setCursor(cursorX, cursorY);
    display.write(_displayString.c_str());
}
