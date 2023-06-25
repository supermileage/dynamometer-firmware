#ifndef _VISUAL_ELEMENT_H_
#define _VISUAL_ELEMENT_H_

#include "Adafruit_GFX.h"
#include "ui_util.h"

using namespace ui_util;

/**
 * @brief base class representing a displayable element
*/
class VisualElement {
    public:
        VisualElement(Adafruit_GFX& display);
        virtual ~VisualElement();

        VisualElement& setParent(VisualElement* parent);
        
        /**
         * @brief get position (top left corner)
        */
        Point getPosition();

        /**
         * @brief get width of visual element
        */
        virtual int16_t getWidth() = 0;

        /**
         * @brief get height of visual element
        */
        virtual int16_t getHeight() = 0;

        /**
         * @brief set position (top left corner)
        */
        VisualElement& setPosition(Point pos);

        /**
         * @brief get background colour: 5-6-5 16-bit colour
        */
        uint16_t getBackgroundColour();

        /**
         * @brief set background to 5-6-5 16-bit colour
        */
        VisualElement& setBackgroundColour(uint16_t colour);

        /**
         * @brief add border line with 16-bit 5-6-5 colour and 1-pixel thickness
         * @note width is thickness of borderline
        */
        VisualElement& addBorder(uint16_t colour);

        /**
         * @brief draw visual element to screen
        */
        virtual void draw();

        /**
         * @brief clear visual element from screen
        */
        virtual void clear() = 0;

    protected:
        Adafruit_GFX& _display;
        VisualElement* _parent = nullptr;
        Point _position = Point { 0, 0 };
        uint16_t _backgroundColour = 0;
        uint16_t _borderColour = 0;
        int16_t _borderWidth = 0;
        bool _hasBorder = false;

        /**
         * @brief internal draw method
         * 
         * @param colour background colour for draw
        */
        virtual void _drawInternal(uint16_t colour) = 0;

};

#endif