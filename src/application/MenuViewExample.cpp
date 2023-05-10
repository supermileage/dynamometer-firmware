#include "MenuViewExample.h"

#include "settings.h"
#include "graphics/colour.h"
#include "graphics/fonts.h"
#include "ui/UIEventHandler.h"

#define WINDOW_TOP_LEFT Point { 5, 5 }
#define WINDOW_WIDTH 310
#define WINDOW_HEIGHT 230
#define HEADER_WIDTH 200
#define HEADER_HEIGHT 25

#define MENU_WIDTH 290
#define MENU_HEIGHT 180
#define MENU_BUTTON_HEIGHT 30
#define MENU_BUTTON_WIDTH 200

#define NAV_WIDTH 260
#define NAV_HEIGHT 35
#define NAV_BUTTON_HEIGHT 25
#define NAV_BUTTON_WIDTH 80

MenuViewExample::MenuViewExample(Adafruit_GFX& display) : _display(display) {
    _window = new Container(_display);
    _header = new TextElement(_display);
    _menuContainer = new Container(_display);
    _navButtonContainer = new Container(_display);
    _menuButton1 = new UIButton(_display);
    _menuButton2 = new UIButton(_display);
    _menuButton3 = new UIButton(_display);
    _navButton1 = new UIButton(_display);
    _navButton2 = new UIButton(_display);

    _interactives.push_back(_menuButton1);
    _interactives.push_back(_menuButton2);
    _interactives.push_back(_menuButton3);
    _interactives.push_back(_navButton1);
    _interactives.push_back(_navButton2);
}

MenuViewExample::~MenuViewExample() {
    delete _window;
    delete _header;
    delete _menuContainer;
    delete _navButtonContainer;
    delete _menuButton1;
    delete _menuButton2;
    delete _menuButton3;
    delete _navButton1;
    delete _navButton2;
}

void MenuViewExample::init() {
    _window->addVisualElement(_header).addVisualElement(_menuContainer);
    _menuContainer->addVisualElement(_menuButton1).addVisualElement(_menuButton2)
        .addVisualElement(_menuButton3).addVisualElement(_navButtonContainer);
    _navButtonContainer->addVisualElement(_navButton1).addVisualElement(_navButton2);

    _header->getTextComponent().setDisplayString("Example Header")
        .setFontColour(COLOUR_WHITE).setFont(FREE_SANS_12PT7B);
    _header->setWidth(HEADER_WIDTH).setHeight(HEADER_HEIGHT).setBackgroundColour(COLOUR_BLACK);
    
    _menuButton1->getTextComponent().setDisplayString("Button 1").setFontSize(1,1)
        .setFontColour(COLOUR_BLACK).setFont(FREE_SANS_BOLD_9PT7B);
    _menuButton1->setFontFocusColour(COLOUR_WHITE).setFocusColour(COLOUR_BLACK)
        .setWidth(MENU_BUTTON_WIDTH).setHeight(MENU_BUTTON_HEIGHT)
        .setBackgroundColour(COLOUR_LIGHTGREY).addBorder(COLOUR_BLACK);

    _menuButton2->getTextComponent().setDisplayString("Button 2").setFontSize(1,1)
        .setFontColour(COLOUR_BLACK).setFont(FREE_SANS_BOLD_9PT7B);
    _menuButton2->setFontFocusColour(COLOUR_WHITE).setFocusColour(COLOUR_BLACK)
        .setWidth(MENU_BUTTON_WIDTH).setHeight(MENU_BUTTON_HEIGHT)
        .setBackgroundColour(COLOUR_LIGHTGREY).addBorder(COLOUR_BLACK);

    _menuButton3->getTextComponent().setDisplayString("Button 3").setFontSize(1,1)
        .setFontColour(COLOUR_BLACK).setFont(FREE_SANS_BOLD_9PT7B);
    _menuButton3->setFontFocusColour(COLOUR_WHITE).setFocusColour(COLOUR_BLACK)
        .setWidth(MENU_BUTTON_WIDTH).setHeight(MENU_BUTTON_HEIGHT)
        .setBackgroundColour(COLOUR_LIGHTGREY).addBorder(COLOUR_BLACK);

    _navButton1->getTextComponent().setDisplayString("Back").setFontSize(1,1)
        .setFontColour(COLOUR_WHITE).setFont(FREE_SANS_BOLD_9PT7B);
    _navButton1->setFontFocusColour(COLOUR_WHITE).setFocusColour(COLOUR_PURPLE)
        .setWidth(NAV_BUTTON_WIDTH).setHeight(NAV_BUTTON_HEIGHT)
        .setBackgroundColour(COLOUR_RED).addBorder(COLOUR_BLACK);

    _navButton2->getTextComponent().setDisplayString("Select").setFontSize(1,1)
        .setFontColour(COLOUR_WHITE).setFont(FREE_SANS_BOLD_9PT7B);
    _navButton2->setFontFocusColour(COLOUR_WHITE).setFocusColour(COLOUR_DARKCYAN)
        .setWidth(NAV_BUTTON_WIDTH).setHeight(NAV_BUTTON_HEIGHT)
        .setBackgroundColour(COLOUR_GREEN).addBorder(COLOUR_BLACK);

    // padding
    _window->setOrientation(Container::Column).setWidth(WINDOW_WIDTH).setHeight(WINDOW_HEIGHT)
        .setPosition(WINDOW_TOP_LEFT).setBackgroundColour(COLOUR_BLACK).addBorder(COLOUR_RED);
    _menuContainer->setOrientation(Container::Column).setWidth(MENU_WIDTH).setHeight(MENU_HEIGHT)
        .setBackgroundColour(COLOUR_DARKGREY).addBorder(COLOUR_MAGENTA);
    _navButtonContainer->setOrientation(Container::Row).setWidth(NAV_WIDTH).setHeight(NAV_HEIGHT)
        .setBackgroundColour(COLOUR_NAVY).addBorder(COLOUR_BLACK);
    
    // order matters for alignment: align top-level container first, then down
    _window->align();
    _menuContainer->align();
    _navButtonContainer->align();

    // call to principal container draws all elements
    _window->draw();

    _cur = 0;
    _interactives[_cur]->focus();
}

