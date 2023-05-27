#include "TextDialogView.h"
#include "style.h"
#include "app_util.h"
#include "settings.h"

#define TD_FONT_HEIGHT      1
#define TD_FONT_WIDTH       1
#define TD_WIDTH            15
#define TD_HEIGHT           25

TextDialogView::TextDialogView(Adafruit_GFX& display) : ViewBase(display) {
    _textContainer = new Container(display);
}

TextDialogView::~TextDialogView() {
    delete _textContainer;
}

void TextDialogView::init() {
    _window->addVisualElement(_header).addVisualElement(_textContainer)
        .addVisualElement(_navButtonContainer);
    _navButtonContainer->addVisualElement(_navButtonBack).addVisualElement(_navButtonSelect);

    app_util::configureSelectButton(_navButtonSelect);
    app_util::configureBackButton(_navButtonBack);
    app_util::configureMainWindow(_window);
    app_util::configureNavButtonContainer(_navButtonContainer);
    _textContainer->setOrientation(Container::Row).setWidth(300).setHeight(25);
    
    // order matters for alignment: align top-level container first, then down
    _window->align();
    _textContainer->align();
    _navButtonContainer->align();
    

    // call to principal container draws all elements
    DEBUG_STATE_TRANSITION_LN("Drawing window");
    _window->draw();
}

void TextDialogView::addCharacterElement(UIButton* element) {
    _configureCharacterElement(element);
    _textContainer->addVisualElement(element);
}

void TextDialogView::_configureCharacterElement(UIButton* element) {
    element->getTextComponent().setFontSize(TD_FONT_WIDTH, TD_FONT_HEIGHT).setFont(FREE_MONO_BOLD_9PT7B)
        .setFontColour(MB_FONT_COLOUR);
    element->setFontFocusColour(MB_FONT_FOCUS_COLOUR).setFocusColour(MB_FOCUS_COLOUR)
        .setWidth(TD_WIDTH).setHeight(TD_HEIGHT).setBackgroundColour(MB_COLOUR)
        .addBorder(MB_BORDER_COLOUR);
}
