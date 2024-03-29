#include "TextDialogView.h"
#include "style.h"
#include "app_util.h"
#include "settings.h"

#define TD_WIDTH                300
#define TD_HEIGHT               25
#define TD_DISPLAY_WIDTH        300
#define TD_DISPLAY_HEIGHT       35
#define TD_DISPLAY_FONT_WIDTH   1
#define TD_DISPLAY_FONT_HEIGHT  1
#define TD_CHAR_FONT_HEIGHT     1
#define TD_CHAR_FONT_WIDTH      1
#define TD_CHAR_WIDTH           15
#define TD_CHAR_HEIGHT          25

TextDialogView::TextDialogView(TFT_eSPI& display) : ViewBase(display) {
    _textContainer = std::make_shared<Container>(display);
    _textDisplay = std::make_shared<TextElement>(display);
}

TextDialogView::~TextDialogView() { }

void TextDialogView::init() {
    _window->addVisualElement(_header)
        .addVisualElement(_textContainer)
        .addVisualElement(_textDisplay)
        .addVisualElement(_navButtonContainer);
    _navButtonContainer->addVisualElement(_navButtonBack)
        .addVisualElement(_navButtonSelect);
    _textDisplay->getTextComponent()
        .setFont(FREE_SANS_BOLD_12PT7B)
        .setFontColour(COLOUR_BLACK)
        .setFontSize(TD_DISPLAY_FONT_WIDTH, TD_DISPLAY_FONT_HEIGHT);
    _textDisplay->setWidth(TD_DISPLAY_WIDTH)
        .setHeight(TD_DISPLAY_HEIGHT)
        .addBorder(COLOUR_DARKCYAN)
        .setBackgroundColour(COLOUR_DARKGREY);
    _textContainer->setOrientation(Container::Row)
        .setWidth(TD_WIDTH)
        .setHeight(TD_HEIGHT);

    app_util::configureSelectButton(_navButtonSelect.get());
    app_util::configureBackButton(_navButtonBack.get());
    app_util::configureMainWindow(_window.get());
    app_util::configureNavButtonContainer(_navButtonContainer.get());
    
    // order matters for alignment: align top-level container first, then down
    _window->align();
    
    // call to principal container draws all elements
    DEBUG_SERIAL_LN("Drawing window");
    _window->draw();
}

void TextDialogView::setTextDisplay(const String& str) {
    _textDisplay->getTextComponent().setDisplayString(str);
}

void TextDialogView::redrawTextDisplay() {
    _textDisplay->draw();
}

void TextDialogView::addCharacterElement(std::shared_ptr<UIButton> element) {
    _configureCharacterElement(element);
    _textContainer->addVisualElement(element);
}

void TextDialogView::_configureCharacterElement(std::shared_ptr<UIButton> element) {
    element->getTextComponent()
        .setFontSize(TD_CHAR_FONT_WIDTH, TD_CHAR_FONT_HEIGHT)
        .setFont(FREE_MONO_BOLD_9PT7B)
        .setFontColour(MB_FONT_COLOUR);
    element->setFontFocusColour(MB_FONT_FOCUS_COLOUR)
        .setFocusColour(COLOUR_DARKGREY)
        .setWidth(TD_CHAR_WIDTH)
        .setHeight(TD_CHAR_HEIGHT)
        .setBackgroundColour(MB_COLOUR)
        .addBorder(MB_BORDER_COLOUR);
}
