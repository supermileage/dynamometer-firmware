#include "Container.h"

Container::Container(Adafruit_ILI9341& display, uint16_t backgroundColour) :
    _display(display), _backgroundColour(backgroundColour) { }

Container::~Container() { }

void Container::addBorder(int16_t width, int16_t height, int16_t thickness, uint16_t colour) {
    _borderWidth = width;
    _borderHeight = height;
    _borderThickness = thickness;
    _borderColour = colour;
    _hasBorder = true;
}

void Container::setBackgroundColour(uint16_t colour) {
    _backgroundColour = colour;
}

void Container::addVisualElements(std::vector<VisualElement*>& elements) {
    _elements = elements;
}

void Container::draw() {
    if (_hasBorder) {
        // draw border
    }
    
    for (VisualElement* element : _elements) {
        element->draw();
    }
}

void Container::clear() {
    if (_hasBorder) {
        // erase border
    }
    
    for (VisualElement* element : _elements) {
        element->draw();
    }
}

void Container::alignElements(Alignment alignment) {
    // align elements left, right or center
}
