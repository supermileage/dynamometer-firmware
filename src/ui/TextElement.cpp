#include "TextElement.h"

TextElement::TextElement(Adafruit_GFX& display) : RectangularElement(display) {
    _textComponent.setOwner(this);
}

TextElement::~TextElement() { }

void TextElement::draw() {
    // draw background and border
    VisualElement::draw();
    _textComponent.draw(_display);
}

void TextElement::redraw() {
    _textComponent.draw(_display);
}

TextComponent& TextElement::getTextComponent() {
    return _textComponent;
}

TextElement& TextElement::computeDimensions() {
    ui_util::Point dim = _textComponent.computeDisplaySize();
    _width = dim.x;
    _height = dim.y;
    return *this;
}
