#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>
#include "Arduino.h"
#include "Adafruit_ILI9341.h"

#include "graphics/colour.h"
#include "VisualElement.h"

/**
 * @brief Container class provides border and background for set of visual elements
 * 
*/
class Container {
    public:
        enum Alignment { Left, Center, Right };
        
        /**
         * @brief initialize container class with background colour
        */
        Container(Adafruit_ILI9341& display, uint16_t backgroundColour = COLOUR_BLACK);

        ~Container();

        /**
         * @brief add border with width, height, thickness and 16-bit 5-6-5 colour
         * 
         * @note max width = 320 and max height = 240
        */
        void addBorder(int16_t width, int16_t height, int16_t thickness, uint16_t colour);

        /**
         * @brief sets background colour
        */
        void setBackgroundColour(uint16_t colour);

        /**
         * @brief add set of visual elements contained within window display
        */
        void addVisualElements(std::vector<VisualElement*>& elements);

        /**
         * @brief draws header, optional border and all visual elements in window
        */
        void draw();

        /**
         * @brief clears header, optional border and all visual elements in window
        */
        void clear();

        /**
         * @brief aligns elements (best effort) -- Center by default
        */
       void alignElements(Alignment alignment = Center);

    private:
        std::vector<VisualElement*> _elements;
        Adafruit_ILI9341& _display;
        int16_t _borderWidth = 0;
        int16_t _borderHeight = 0;
        int16_t _borderThickness = 0;
        uint16_t _borderColour = 0;
        uint16_t _backgroundColour = 0;
        bool _hasBorder = false;
};

#endif