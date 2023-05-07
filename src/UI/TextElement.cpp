#include "TextElement.h"

TextElement::TextElement(Adafruit_ILI9341& display) : VisualElement(display) {
    _textComponent.setOwner(this);
}

TextElement::~TextElement() { }

void TextElement::draw() {
    // draw background and border
    VisualElement::draw();

    _textComponent.draw(_display);
}

void TextElement::clear() {
    if (_parent->getBackgroundColour() != _backgroundColour) {
        // TODO: draw background
    }

    if (_hasBorder) {
        // TODO: draw border
    }

    _textComponent.draw(_display);
}

TextComponent& TextElement::getTextComponent() {
    return _textComponent;
}

void TextElement::_onResize() {
    // TODO: resize text element
}