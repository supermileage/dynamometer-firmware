#include "DisplayWindow.h"

DisplayWindow::DisplayWindow() { }

DisplayWindow::DisplayWindow(String& header) : _header(header) { }

DisplayWindow::~DisplayWindow() { }

void DisplayWindow::addBorder(int16_t width, int16_t height, int16_t thickness, uint16_t colour) {
    _borderWidth = width;
    _borderHeight = height;
    _borderThickness = thickness;
    _borderColour = colour;
    _hasBorder = true;
}

void DisplayWindow::addVisualElements(std::vector<VisualElement*>& elements) {
    _elements = elements;
}

void DisplayWindow::draw() {
    if (_hasBorder) {
        // draw border
    }

    if (_header.length() != 0) {

    }
    
    for (VisualElement* element : _elements) {
        element->draw();
    }
}

void DisplayWindow::clear() {
    if (_hasBorder) {
        // erase border
    }

    if (_header.length() != 0) {

    }
    
    for (VisualElement* element : _elements) {
        element->draw();
    }
}
