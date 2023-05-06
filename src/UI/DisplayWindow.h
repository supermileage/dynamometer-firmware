#ifndef _DISPLAY_WINDOW_H_
#define _DISPLAY_WINDOW_H_

#include <vector>
#include "Arduino.h"
#include "VisualElement.h"

/**
 * @brief DisplayWindow class handles display and selection of a set of visual elements
*/
class DisplayWindow {
    public:
        DisplayWindow();
        DisplayWindow(String& header);
        ~DisplayWindow();

        /**
         * @brief add border with width, height, thickness and 16-bit 5-6-5 colour
         * 
         * @note max width = 320 and max height = 240
        */
        void addBorder(int16_t width, int16_t height, int16_t thickness, uint16_t colour);

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

    private:
        String _header;
        std::vector<VisualElement*> _elements;
        int16_t _borderWidth = 0;
        int16_t _borderHeight = 0;
        int16_t _borderThickness = 0;
        uint16_t _borderColour = 0;
        bool _hasBorder = false;  
};

#endif