#include "VisualElement.h"

VisualElement::VisualElement(Adafruit_ILI9341& display) : _display(display) { }

VisualElement::~VisualElement() { }

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
