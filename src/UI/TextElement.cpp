#include "TextElement.h"

TextElement::TextElement(Adafruit_ILI9341& display) : _display(display) {
    _textComponent.setOwner(this);
}

TextElement::~TextElement() { }

void TextElement::draw() {
    if (_parent->getBackgroundColour() != _backgroundColour) {
        // draw background
    }

    if (_hasBorder) {
        // draw border
    }

    _textComponent.draw(_display);
}

void TextElement::clear() {
    if (_parent->getBackgroundColour() != _backgroundColour) {
        // draw background
    }

    if (_hasBorder) {
        // draw border
    }

    _textComponent.draw(_display);
}

TextComponent& TextElement::getTextComponent() {
    return _textComponent;
}

void TextElement::_onResize() {
    // resize text element
}