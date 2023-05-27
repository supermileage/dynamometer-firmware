#include "MenuView.h"

#include "settings.h"
#include "graphics/colour.h"
#include "graphics/fonts.h"
#include "app_util.h"

MenuView::MenuView(Adafruit_GFX& display) : ViewBase(display) {
    _menuContainer = new Container(_display);
}

MenuView::~MenuView() {
    DEBUG_STATE_TRANSITION_LN("~MenuView");
    delete _menuContainer;
}

void MenuView::init() {
    _window->addVisualElement(_header).addVisualElement(_menuContainer);
    _menuContainer->addVisualElement(_navButtonContainer);
    _navButtonContainer->addVisualElement(_navButtonBack).addVisualElement(_navButtonSelect);

    DEBUG_STATE_TRANSITION_LN("Configuring Buttons");
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
    DEBUG_STATE_TRANSITION_LN("Drawing window");
    _window->draw();
}

void MenuView::addMenuButton(UIButton* button, const String& str) {
    app_util::configureMenuButton(button, str);
    _menuContainer->addVisualElement(button);
}
