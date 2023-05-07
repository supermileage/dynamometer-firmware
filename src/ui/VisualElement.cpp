#include "VisualElement.h"

VisualElement::VisualElement(Adafruit_ILI9341& display) : _display(display) { }

VisualElement::~VisualElement() { }

VisualElement& VisualElement::setParent(VisualElement* parent) {
    _parent = parent;
    return *this;
}

Point VisualElement::getPosition() {
    return _position;
}

VisualElement& VisualElement::setPosition(Point pos) {
    _position = pos;
    return *this;
}

int16_t VisualElement::getWidth() {
    return _width;
}

int16_t VisualElement::getHeight() {
    return _height;
}

VisualElement& VisualElement::setWidth(int16_t width) {
    _width = width;
    _onResize();
    return *this;
}

VisualElement& VisualElement::setHeight(int16_t height) {
    _height = height;
    _onResize();
    return *this;
}

uint16_t VisualElement::getBackgroundColour() {
    return _backgroundColour;
}

VisualElement& VisualElement::setBackgroundColour(uint16_t colour) {
    _backgroundColour = colour;
    return *this;
}

VisualElement& VisualElement::addBorder(uint16_t colour, int16_t width, int16_t height) {
    _borderColour = colour;
    _borderWidth = width == -1 ? _width : width;
    _borderHeight = height == -1 ? _height : height;
    _hasBorder = true;
    return *this;
}

void VisualElement::draw() {
    if (_parent && _parent->getBackgroundColour() != _backgroundColour) {
        _display.fillRect(_position.x, _position.y, _width, _height, _backgroundColour);
    }

    if (_hasBorder) {
        // compute border inset to center border with background
        int16_t insetX = (_width - _borderWidth) / 2;
        int16_t insetY = (_height - _borderHeight) / 2;
        _display.drawRect(_position.x + insetX, _position.y + insetY,
            _borderWidth, _borderHeight, _borderColour);
    }
}

void VisualElement::clear() {
    uint16_t colour;
    if (_parent) {
        colour = _parent->getBackgroundColour();
    } else {
        colour = _backGroundColour;
    }
    _display.fillRect(_position.x, _position.y, _width, _height, colour);
}
