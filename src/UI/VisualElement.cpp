#include "VisualElement.h"

VisualElement::~VisualElement() { }

void VisualElement::setParent(VisualElement* parent) {
    _parent = parent;
}

Point VisualElement::getPosition() {
    return _position;
}

void VisualElement::setPosition(Point pos) {
    _position = pos;
}

int16_t VisualElement::getWidth() {
    return _width;
}

int16_t VisualElement::getHeight() {
    return _height;
}

void VisualElement::setWidth(int16_t width) {
    _width = width;
    _onResize();
}

void VisualElement::setHeight(int16_t height) {
    _height = height;
    _onResize();
}

uint16_t VisualElement::getBackgroundColour() {
    return _backgroundColour;
}

void VisualElement::setBackgroundColour(uint16_t colour) {
    _backgroundColour = colour;
}

void VisualElement::addBorder(int16_t width, int16_t height, int16_t thickness, uint16_t colour) {
    _borderWidth = width;
    _borderHeight = height;
    _borderThickness = thickness;
    _borderColour = colour;
    _hasBorder = true;
}
