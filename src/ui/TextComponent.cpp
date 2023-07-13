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

ui_util::Point TextComponent::computeDisplaySize() {
    return ui_util::Point {
        .x = ui_util::computeStringDimensions(_font, _nextString, _textSizeX, _textSizeY).x,
        .y = ui_util::computeCharacterDimensions(_font, DEFAULT_SIZE_CHAR, _textSizeX, _textSizeY).x
    };
}

void TextComponent::draw(Adafruit_GFX& display) {
    // only call draw if something has changed
    if (_fontChanged || _stringChanged || _colourChanged) {
        _drawInternal(display, _fontColour);
        _displayString = _nextString;
        _stringChanged = false;
        _fontChanged = false;
        _colourChanged = false;
    }
}

void TextComponent::_drawInternal(Adafruit_GFX& display, uint16_t colour) {
    if (_fontChanged) {
        ui_util::Point dim = computeDisplaySize();
        _stringWidth = dim.x;
        _charHeight = dim.y;
    }
    // horizontally center text in field
    int16_t cursorX = _owner->getPosition().x + (_owner->getWidth() - _stringWidth) / 2;
    // vertically center text in field (cursor is bottom left of text region)
    int16_t height = _owner->getHeight();
    int16_t cursorY = _owner->getPosition().y + height - (height - _charHeight) / 2;

    display.setFont(_font);
    display.setTextSize(_textSizeX, _textSizeY);
    display.setCursor(cursorX, cursorY);
    display.setTextColor(colour, _owner->getBackgroundColour());
    display.write(_nextString.c_str());
}

