#include "VisualElement.h"

VisualElement::VisualElement(TFT_eSPI& display) : _display(display) { }

VisualElement::~VisualElement() { }

VisualElement& VisualElement::setParent(VisualElement* parent) {
    _parent = parent;
    return *this;
}

uint16_t VisualElement::getTypeId() {
    return _typeId;
}

Point VisualElement::getPosition() {
    return _position;
}

VisualElement& VisualElement::setPosition(Point pos) {
    _position = pos;
    return *this;
}

uint16_t VisualElement::getBackgroundColour() {
    return _backgroundColour;
}

VisualElement& VisualElement::setBackgroundColour(uint16_t colour) {
    _backgroundColour = colour;
    return *this;
}

VisualElement& VisualElement::addBorder(uint16_t colour) {
    _borderColour = colour;
    _hasBorder = true;
    return *this;
}

void VisualElement::draw() {
    _drawInternal(_backgroundColour);
}

