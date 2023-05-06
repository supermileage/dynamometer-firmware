#ifndef _TEXT_COMPONENT_H
#define _TEXT_COMPONENT_H

#include "Arduino.h"
#include "Adafruit_ILI9341.h"

#include "VisualElement.h"

class TextComponent {
    public:
        TextComponent();
        TextComponent(String& _displayString);
        ~TextComponent();
        
        /**
         * @brief sets visual element owner of this text component
        */
        void setOwner(VisualElement const* owner);

        /**
         * @brief returns display string of this text component
        */
        const String& getDisplayString();

        /**
         * @brief sets display string of this text component
        */
        void setDisplayString(const String& str);

        /**
         * @brief sets font of this text component
        */
        void setFont(const GFXfont* font);

        /**
         * @brief sets the 16-bit 5-6-5 RGB font colour of this text component
        */
        void setFontColour(const uint16_t colour);

        /**
         * @brief draw -- only intended to be called from within VisualElement owner of this class
        */
        void draw(const Adafruit_ILI9341& display);

        /**
         * @brief clear text -- only intended to be called from within VisualElement owner of this class
        */
        void clear(const Adafruit_ILI9341& display);

    private:
        VisualElement const* _owner;
        String _displayString = "";
        GFXfont const* _font;
        uint16_t _fontColour;

};

#endif