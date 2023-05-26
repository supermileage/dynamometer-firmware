#include "MenuView.h"

#include "settings.h"
#include "graphics/colour.h"
#include "graphics/fonts.h"
#include "application/app_util.h"

MenuView::MenuView(Adafruit_GFX& display) : _display(display) {
    _window = new Container(_display);
    _header = new TextElement(_display);
    _menuContainer = new Container(_display);
    _navButtonContainer = new Container(_display);
    _navButtonSelect = new UIButton(_display);
    _navButtonBack = new UIButton(_display);
}

MenuView::~MenuView() {
    DEBUG_STATE_TRANSITION_LN("~MenuView");
    delete _window;
    delete _header;
    delete _menuContainer;
    delete _navButtonContainer;
    delete _navButtonSelect;
    delete _navButtonBack;
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

void MenuView::setHeader(const String& str) {
    DEBUG_STATE_TRANSITION_LN("Setting header: " + str);
    app_util::configureHeader(_header, str);
}


void MenuView::addMenuButton(UIButton* button, const String& str) {
    app_util::configureMenuButton(button, str);
    _menuContainer->addVisualElement(button);
}

void MenuView::select() {
    DEBUG_STATE_TRANSITION_LN("MenuView::select");
    _navButtonSelect->select();
}

void MenuView::back() {
    DEBUG_STATE_TRANSITION_LN("MenuView::back");
    _navButtonBack->select();
}

void MenuView::revert() {
    DEBUG_STATE_TRANSITION_LN("MenuView::revert");
    _navButtonBack->revert();
    _navButtonSelect->revert();
}
