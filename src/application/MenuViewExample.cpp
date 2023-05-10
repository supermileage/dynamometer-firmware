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

    app_util::configureHeader(_header, "Example Header");
    app_util::configureMenuButton(_menuButton1, "Button 1");
    app_util::configureMenuButton(_menuButton2, "Button 2");
    app_util::configureMenuButton(_menuButton3, "Button 3");
    app_util::configureBackButton(_navButton1);
    app_util::configureSelectButton(_navButton2);
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

void MenuViewExample::run() {
    if (millis() > _lastTime + 1000) {
        _lastTime = millis();
        UIElement* cur = _interactives[_cur];
        cur->focus();
        delay(1000);
        cur->revert();
        _cur = (_cur + 1) % _interactives.size();
    }
}

