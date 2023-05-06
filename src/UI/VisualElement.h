#ifndef _VISUAL_ELEMENT_H_
#define _VISUAL_ELEMENT_H_

#include "ui_util.h"

using namespace ui_util;

/**
 * @brief base class representing a displayable element
*/
class VisualElement {
    public:
        virtual ~VisualElement();

        void setParent(VisualElement* parent);
        
        /**
         * @brief get position (top left corner)
        */
        Point getPosition();

        /**
         * @brief set position (top left corner)
        */
        void setPosition(Point pos);
        
        /**
         * @brief get width of visual element relative to its position
        */
        int16_t getWidth();
        
        /**
         * @brief set width of visual element relative to its position
        */
        void setWidth(int16_t width);
        
        /**
         * @brief get height of visual element relative to its position
        */
        int16_t getHeight();

        /**
         * @brief set height of visual element relative to its position
        */
        void setHeight(int16_t height);

        /**
         * @brief get background colour: 5-6-5 16-bit colour
        */
        uint16_t getBackgroundColour();

        /**
         * @brief set background to 5-6-5 16-bit colour
        */
        void setBackgroundColour(uint16_t colour);


        /**
         * @brief add border with width, height, thickness and 16-bit 5-6-5 colour
         * 
         * @note max width = 320 and max height = 240
        */
        void addBorder(int16_t width, int16_t height, int16_t thickness, uint16_t colour);

        /**
         * @brief draw visual element to screen
        */
        virtual void draw() = 0;

        /**
         * @brief clear visual element from screen
        */
        virtual void clear() = 0;

    protected:
        VisualElement* _parent = nullptr;
        Point _position = Point { 0, 0 };
        int16_t _width = 0;
        int16_t _height = 0;
        uint16_t _backgroundColour = 0;
        int16_t _borderWidth = 0;
        int16_t _borderHeight = 0;
        int16_t _borderThickness = 0;
        uint16_t _borderColour = 0;
        bool _hasBorder = false;

        /**
         * @brief resize event handler
        */
        virtual void _onResize() = 0;

};

#endif