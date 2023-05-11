#include "MenuViewExample.h"

#include "settings.h"
#include "graphics/colour.h"
#include "graphics/fonts.h"
#include "application/app_util.h"

MenuViewExample::MenuViewExample(Adafruit_GFX& display) : _display(display) {
    _window = new Container(_display);
    _header = new TextElement(_display);
    _menuContainer = new Container(_display);
    _navButtonContainer = new Container(_display);
    _navButtonSelect = new UIButton(_display);
    _navButtonBack = new UIButton(_display);
}

MenuViewExample::~MenuViewExample() {
    delete _window;
    delete _header;
    delete _menuContainer;
    delete _navButtonContainer;
    delete _navButtonSelect;
    delete _navButtonBack;
}

void MenuViewExample::init() {
    _window->addVisualElement(_header).addVisualElement(_menuContainer);
    _menuContainer->addVisualElement(_navButtonContainer);
    _navButtonContainer->addVisualElement(_navButtonBack).addVisualElement(_navButtonSelect);

    app_util::configureHeader(_header, "main menu");
    app_util::configureSelectButton(_navButtonSelect);
    app_util::configureBackButton(_navButtonBack);
    app_util::configureMainWindow(_window);
    app_util::configureMenuContainer(_menuContainer);
    app_util::configureNavButtonContainer(_navButtonContainer);
    
    // order matters for alignment: align top-level container first, then down
    _window->align();
    _menuContainer->align();
    _navButtonContainer->align();

    // call to principal container draws all elements
    _window->draw();
}

void MenuViewExample::addMenuButton(UIButton* button, const String& str) {
    app_util::configureMenuButton(button, str);
    _menuContainer->addVisualElement(button);
}

void MenuViewExample::select() {
    _navButtonSelect->select();
}

void MenuViewExample::back() {
    _navButtonBack->select();
}

