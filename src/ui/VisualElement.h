#ifndef _VISUAL_ELEMENT_H_
#define _VISUAL_ELEMENT_H_

#include "Adafruit_GFX.h"
#include "ui_util.h"
#include "settings.h"

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
         * @brief set position (top left corner)
        */
        VisualElement& setPosition(Point pos);
        
        /**
         * @brief get width of visual element relative to its position
        */
        int16_t getWidth();
        
        /**
         * @brief set width of visual element relative to its position
        */
        VisualElement& setWidth(int16_t width);
        
        /**
         * @brief get height of visual element relative to its position
        */
        int16_t getHeight();

        /**
         * @brief set height of visual element relative to its position
        */
        VisualElement& setHeight(int16_t height);

        /**
         * @brief get background colour: 5-6-5 16-bit colour
        */
        uint16_t getBackgroundColour();

        /**
         * @brief set background to 5-6-5 16-bit colour
        */
        VisualElement& setBackgroundColour(uint16_t colour);


        /**
         * @brief add border with 16-bit 5-6-5 colour and width/height
         * 
         * @note width/height match _width/_height fields by default; max width = 320 and max height = 240
        */
        VisualElement& addBorder(uint16_t colour, int16_t width = -1, int16_t height = -1);

        /**
         * @brief draw visual element to screen
        */
        virtual void draw();

        /**
         * @brief clear visual element from screen
        */
        void clear();

    protected:
        Adafruit_GFX& _display;
        VisualElement* _parent = nullptr;
        Point _position = Point { 0, 0 };
        int16_t _width = 0;
        int16_t _height = 0;
        uint16_t _backgroundColour = 0;
        uint16_t _borderColour = 0;
        int16_t _borderWidth = 0;
        int16_t _borderHeight = 0;
        bool _hasBorder = false;

        /**
         * @brief resize event handler
        */
        virtual void _onResize() = 0;

};

#endif