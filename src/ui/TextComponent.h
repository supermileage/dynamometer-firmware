#ifndef _TEXT_COMPONENT_H
#define _TEXT_COMPONENT_H

#include "Arduino.h"
#include "Adafruit_GFX.h"

#include "VisualElement.h"

class TextComponent {
    public:
        ~TextComponent();
        
        /**
         * @brief sets visual element owner of this text component
        */
        void setOwner(VisualElement* owner);

        /**
         * @brief returns display string of this text component
        */
        const String& getDisplayString();

        /**
         * @brief sets display string of this text component
        */
        TextComponent& setDisplayString(const String& str);

        /**
         * @brief sets font of this text component
        */
        TextComponent& setFont(const GFXfont* font);

        /**
         * @brief sets the 16-bit 5-6-5 RGB font colour of this text component
        */
        TextComponent& setFontColour(const uint16_t colour);

        /**
         * @brief gets the 16-bit 5-6-5 RGB font colour of this text component
        */
        uint16_t getFontColour();

        /**
         * @brief sets the values by which font width and height will be scaled
        */
        TextComponent& setFontSize(uint8_t w, uint8_t h);

        /**
         * @brief computes and returns Point with x, y representing width and height of display string
        */
        ui_util::Point computeDisplaySize();

        /**
         * @brief draw -- only to be called from within VisualElement owner of this class
        */
        void draw(Adafruit_GFX& display);

    private:
        VisualElement* _owner;
        String _displayString = "";
        String _nextString = "";
        GFXfont const* _font = nullptr;
        uint16_t _fontColour = 0;
        int16_t _textWidth = 0;
        int16_t _textHeight = 0;
        uint8_t _textSizeX = 1;
        uint8_t _textSizeY = 1;
        bool _stringChanged = true;
        bool _fontChanged = true;
        bool _colourChanged = true;

        void _drawInternal(Adafruit_GFX& display, uint16_t colour);
        void _drawOptimized(Adafruit_GFX& display, int16_t x, int16_t y);

};

#endif