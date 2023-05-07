#ifndef _MENU_EXAMPLE_H_
#define _MENU_EXAMPLE_H_

#include "ui/Container.h"
#include "ui/UIButton.h"
#include "ui/TextElement.h"
#include "graphics/colour.h"
#include "graphics/fonts.h"

class MenuExample {
    public:
        MenuExample(Adafruit_ILI9341& display) :_display(display) {
            _window = new Container(_display);
            _header = new TextElement(_display);
            _buttonContainer = new Container(_display);
            _button1 = new UIButton(_display);
            _button2 = new UIButton(_display);
            _button3 = new UIButton(_display);
        }

        ~MenuExample() {
            delete _window;
            delete _header;
            delete _buttonContainer;
            delete _button1;
            delete _button2;
            delete _button3;
        }

        void begin() {
            _window->addVisualElement(_header);
            _window->addVisualElement(_buttonContainer);
            _buttonContainer->addVisualElement(_button1);
            _buttonContainer->addVisualElement(_button2);
            _buttonContainer->addVisualElement(_button3);

            _header->getTextComponent().setDisplayString("Example Header")
                .setFontColour(COLOUR_WHITE).setFont(FREE_SANS_12PT7B);
            _header->setWidth(200).setHeight(25).setBackgroundColour(COLOUR_BLACK);
            
            _button1->getTextComponent().setDisplayString("Button 1").setFontSize(2,2)
                .setFontColour(COLOUR_BLACK).setFont(FREE_SANS_BOLD_9PT7B);
            _button1->setWidth(200).setHeight(35).setBackgroundColour(COLOUR_LIGHTGREY)
                .addBorder(COLOUR_BLACK);

            _button2->getTextComponent().setDisplayString("Button 2").setFontSize(2,2)
                .setFontColour(COLOUR_BLACK).setFont(FREE_SANS_BOLD_9PT7B);
            _button2->setWidth(200).setHeight(35).setBackgroundColour(COLOUR_LIGHTGREY)
                .addBorder(COLOUR_BLACK);

            _button3->getTextComponent().setDisplayString("Button 3").setFontSize(2,2)
                .setFontColour(COLOUR_BLACK).setFont(FREE_SANS_BOLD_9PT7B);
            _button3->setWidth(200).setHeight(35).setBackgroundColour(COLOUR_LIGHTGREY)
                .addBorder(COLOUR_BLACK);

            // padding
            _window->setWidth(300).setHeight(220).setPosition(Point { 10, 10 })
                .setBackgroundColour(COLOUR_BLACK).addBorder(COLOUR_RED);
            _buttonContainer->setWidth(280).setHeight(160).setBackgroundColour(COLOUR_DARKGREY).
                addBorder(COLOUR_MAGENTA);

            _window->alignElements();
            _buttonContainer->alignElements();

            _window->draw();
        }

        void handle() {

        }


    private:
        Adafruit_ILI9341& _display;
        Container* _window;
        TextElement* _header;
        Container* _buttonContainer;
        UIButton* _button1;
        UIButton* _button2;
        UIButton* _button3;
};

#endif