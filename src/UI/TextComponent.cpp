#include "TextComponent.h"

TextComponent::TextComponent() { }

TextComponent::TextComponent(String& displayString) : _displayString(displayString) { }

TextComponent::~TextComponent() { }

void TextComponent::setOwner(VisualElement const* owner) {
    _owner = owner;
}

const String& TextComponent::getDisplayString() {
    return _displayString;
}

void TextComponent::setDisplayString(const String& str) {
    _displayString = str;
}

void TextComponent::setFont(const GFXfont* font) {
    _font = font;
}

void TextComponent::setFontColour(const uint16_t colour) {
    _fontColour = colour;
}

void TextComponent::draw(const Adafruit_ILI9341& display) {
    // write text to screen
}

void TextComponent::clear(const Adafruit_ILI9341& display) {
    // clear text from screen (get background colour from owner)
}
