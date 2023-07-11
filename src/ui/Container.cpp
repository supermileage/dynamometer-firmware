#include "Container.h"

#define CONTAINER_HORIZONTAL_BITMASK    0xf
#define CONTAINER_VERTICAL_BITMASK      0xf0

Container::Container(Adafruit_GFX& display) : RectangularElement(display) { }

Container::~Container() { }

Container& Container::setPadding(int16_t padding) {
    _padding = padding;
    return *this;
}

Container& Container::addVisualElement(std::shared_ptr<VisualElement> element, Alignment align) {
    element->setParent(this);
    _children.push_back(std::make_pair(element, align));
    return *this;
}

void Container::draw() {
    // draw background and border
    VisualElement::draw();
    
    for (auto pair : _children) {
        std::shared_ptr<VisualElement> element = pair.first;
        element->draw();
    }
}

Container& Container::setOrientation(Orientation o) {
    _orientation = o;
    return *this;
}

void Container::alignElements() {
    switch (_orientation) {
        case Column:
            _alignElementsHorizontal();
            _applyVerticalSpacing();
            break;
        case Row:
            _alignElementsVertical();
            _applyHorizontalSpacing();
            break;
        default:
            break;
    }
}

void Container::_alignElementsHorizontal() {
    for (auto pair : _children) {
        std::shared_ptr<VisualElement> element = pair.first;
        Alignment alignment = pair.second;
        int16_t positionX = _position.x + _getHorizontalOffset(pair, _width);
        element->setPosition(Point { positionX, element->getPosition().y });
    }
}

void Container::_alignElementsVertical() {
    // TODO: implement left/right alignment
    for (auto pair : _children) {
        std::shared_ptr<VisualElement> element = pair.first;
        int16_t elementY = _position.y + _getVerticalOffset(pair, _height);
        element->setPosition(Point { element->getPosition().x, elementY });
    }
}

void Container::_applyVerticalSpacing() {
    int16_t totalHeightChildren = 0;
    for (auto pair : _children) {
        totalHeightChildren += pair.first->getHeight();
    }

    // equal vertical space between all elements
    int16_t padding = (_height - totalHeightChildren) / (_children.size() + 1);
    int16_t cur = _position.y + padding;
    for (auto pair : _children) {
        std::shared_ptr<VisualElement> element = pair.first;
        int16_t top = cur - padding / 2;
        int16_t height = padding + element->getHeight();
        int16_t elementY = top + _getVerticalOffset(pair, height);
        element->setPosition(Point { element->getPosition().x, elementY });
        cur += (padding + element->getHeight());
    }
}

void Container::_applyHorizontalSpacing() {
    int16_t totalWidthChildren = 0;
    for (auto pair : _children) {
        totalWidthChildren += pair.first->getWidth();
    }

    int16_t padding = (_width - totalWidthChildren) / (_children.size() + 1);
    int16_t cur = _position.x + padding;
    for (auto pair : _children) {
        std::shared_ptr<VisualElement> element = pair.first;
        int16_t left = cur - padding / 2;
        int16_t width = padding + element->getWidth();
        int16_t elementX = left + _getHorizontalOffset(pair, width);
        element->setPosition(Point { elementX, element->getPosition().y });
        cur += (padding + element->getWidth());
    }
}

int16_t Container::_getHorizontalOffset(std::pair<std::shared_ptr<VisualElement>, Alignment> pair, int16_t width) {
    switch (pair.second & CONTAINER_HORIZONTAL_BITMASK) {
        case CONTAINER_ALIGNMENT_RIGHT:
            return (width - pair.first->getWidth()) - _padding;
        case CONTAINER_ALIGNMENT_MIDDLE:
            // middle -- ignore padding
            return (width - pair.first->getWidth()) / 2;
        default:
            // CONTAINER_ALIGNMENT_LEFT
            return _padding;
    }
}

int16_t Container::_getVerticalOffset(std::pair<std::shared_ptr<VisualElement>, Alignment> pair, int16_t height) {
    switch (pair.second & CONTAINER_VERTICAL_BITMASK) {
        case CONTAINER_ALIGNMENT_TOP:
            return height - pair.first->getHeight() - _padding;
        case CONTAINER_ALIGNMENT_CENTRE:
            // center -- ignore padding
            return (height - pair.first->getHeight()) / 2;
        default:
            // CONTAINER_ALIGNMENT_BOTTOM
            return _padding;
    }
}
