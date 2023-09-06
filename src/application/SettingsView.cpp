#include "SettingsView.h"
#include "graphics/colour.h"
#include "graphics/fonts.h"
#include "app_util.h"
#include "style.h"

// settings menu macros
#define SM_WIDTH                        300
#define SM_HEIGHT                       (W_HEIGHT - HEADER_HEIGHT - NC_HEIGHT)
#define SM_SECTION_HEADER_HEIGHT        20
#define SM_SECTION_HEADER_WIDTH         54
#define SM_FILE_EDIT_BUTTON_WIDTH       70
#define SM_FILE_EDIT_BUTTON_HEIGHT      20
#define SM_FILENAME_HEIGHT              SM_FILE_EDIT_BUTTON_HEIGHT
#define SM_FILENAME_WIDTH               (SM_WIDTH - SM_FILE_EDIT_BUTTON_WIDTH)
#define SM_INPUT_SECTION_HEIGHT         (SM_SECTION_HEADER_HEIGHT + SM_FILENAME_HEIGHT)
#define SM_INPUT_SECTION_WIDTH          SM_WIDTH
#define SM_OUTPUT_SECTION_HEIGHT        (SM_HEIGHT - SM_INPUT_SECTION_HEIGHT - 10)
#define SM_OUTPUT_SECTION_WIDTH         SM_WIDTH

#define SM_VALUE_BUTTON_HEIGHT          SM_FILENAME_HEIGHT
#define SM_VALUE_BUTTON_WIDTH           54

#define SM_INTERVAL_BUTTON_HEIGHT       SM_FILENAME_HEIGHT
#define SM_INTERVAL_BUTTON_WIDTH        70
#define SM_INTERVAL_LABEL_HEIGHT        SM_FILENAME_HEIGHT
#define SM_INTERVAL_LABEL_WIDTH         120

#define SM_VALUE_BUTTONS_PER_ROW        5

SettingsView::SettingsView(TFT_eSPI& display) : ViewBase(display) {
    _menuContainer = std::make_shared<Container>(_display);
    _menuContainer->setHeight(SM_HEIGHT)
        .setWidth(SM_WIDTH)
        .setBackgroundColour(COLOUR_BLACK);
}

SettingsView::~SettingsView() { }

void SettingsView::init() {
    _window->addVisualElement(_header)
        .addVisualElement(_menuContainer);
    _navButtonContainer->addVisualElement(_navButtonBack)
        .addVisualElement(_navButtonSelect);
    _window->addVisualElement(_navButtonContainer);

    if (_inputContainer) {
        _menuContainer->addVisualElement(_inputContainer, Container::TopMiddle);
    }
    if (_outputContainer) {
        _menuContainer->addVisualElement(_outputContainer);
    }

    app_util::configureSelectButton(_navButtonSelect.get());
    app_util::configureBackButton(_navButtonBack.get());
    app_util::configureMainWindow(_window.get());
    app_util::configureNavButtonContainer(_navButtonContainer.get());

    _window->align();
    _window->draw();
}

std::shared_ptr<UIButton> SettingsView::buildInputFilenameDisplay(String& filename) {
    _inputContainer = std::make_unique<Container>(_display);
    _inputContainer->setOrientation(Container::Column)
        .setWidth(SM_INPUT_SECTION_WIDTH)
        .setHeight(SM_INPUT_SECTION_HEIGHT)
        .setBackgroundColour(COLOUR_DARKGREY);

    std::shared_ptr<TextElement> header = std::make_shared<TextElement>(_display);
    String headerText = String("input:");
    _configureSectionHeader(header, headerText, SM_SECTION_HEADER_WIDTH);

    std::shared_ptr<TextElement> element = std::make_shared<TextElement>(_display);
    _configureFilenameText(element, filename);

    std::shared_ptr<UIButton> button = std::make_shared<UIButton>(_display);
    _configureModifyButton(button);

    // set up row
    std::shared_ptr<Container> row = std::make_shared<Container>(_display);
    row->setOrientation(Container::Row)
        .addVisualElement(element, Container::CentreLeft)
        .addVisualElement(button, Container::CentreRight)
        .setWidth(SM_INPUT_SECTION_WIDTH)
        .setHeight(SM_FILENAME_HEIGHT)
        .setBackgroundColour(COLOUR_DARKGREY);

    // add all elements to input container
    _inputContainer->addVisualElement(header, Container::CentreLeft)
        .addVisualElement(row, Container::CentreLeft);

    return button;
}

std::shared_ptr<UIButton> SettingsView::buildOutputFilenameDisplay(String& filename) {
    _outputContainerInit();
    std::shared_ptr<TextElement> header = std::make_shared<TextElement>(_display);
    String headerText = String("output:");
    _configureSectionHeader(header, headerText, SM_SECTION_HEADER_WIDTH);
    std::shared_ptr<TextElement> element = std::make_shared<TextElement>(_display);
    _configureFilenameText(element, filename);
    std::shared_ptr<UIButton> button = std::make_shared<UIButton>(_display);
    _configureModifyButton(button);

    // set up row
    _outputRowInit();
    _outputRow->addVisualElement(element, Container::CentreLeft)
        .addVisualElement(button, Container::CentreRight);
    // add all elements to input container
    _outputContainer->addVisualElement(header, Container::CentreLeft)
        .addVisualElement(_outputRow, Container::TopLeft);

    return button;
}

std::shared_ptr<UIButton> SettingsView::buildOutputValueButton(application::ValueId id) {
    _outputContainerInit();

    if ((_numButtons % SM_VALUE_BUTTONS_PER_ROW) == 0) {
        _outputRowInit();
        _outputContainer->addVisualElement(_outputRow);
    }

    ++_numButtons;
    std::shared_ptr<UIButton> button = std::make_shared<UIButton>(_display);
    const String name = app_util::valueToHeader(id);
    app_util::configureMenuButton(button.get(), name);

    button->setHeight(SM_VALUE_BUTTON_HEIGHT)
        .setWidth(SM_VALUE_BUTTON_WIDTH);
    _outputRow->addVisualElement(button);
    return button;
}

std::shared_ptr<UIButton> SettingsView::buildIntervalButton(String& interval) {
    _outputContainerInit();
    _outputRowInit();
    _outputContainer->addVisualElement(_outputRow);

    std::shared_ptr<TextElement> label = std::make_shared<TextElement>(_display);
    String text = String("logging interval:");
    _configureSectionHeader(label, text, SM_INTERVAL_LABEL_WIDTH);
    _outputRow->addVisualElement(label);

    std::shared_ptr<UIButton> button = std::make_shared<UIButton>(_display);
    app_util::configureMenuButton(button.get(), interval);
    button->setHeight(SM_INTERVAL_BUTTON_HEIGHT)
        .setWidth(SM_INTERVAL_BUTTON_WIDTH);
    _outputRow->addVisualElement(button);

    return button;
}

void SettingsView::_configureModifyButton(std::shared_ptr<UIButton> button) {
    String str = String("modify");
    app_util::configureMenuButton(button.get(), str);
    button->setWidth(SM_FILE_EDIT_BUTTON_WIDTH)
        .setHeight(SM_FILE_EDIT_BUTTON_HEIGHT);
}

void SettingsView::_configureFilenameText(std::shared_ptr<TextElement> txt, String& filename) {
    txt->getTextComponent()
        .setDisplayString(filename)
        .setFont(FREE_SERIF_9PT7B)
        .setFontColour(COLOUR_WHITE)
        .setFontSize(1,1);
    txt->setWidth(SM_FILENAME_WIDTH)
        .setHeight(SM_FILENAME_HEIGHT)
        .setBackgroundColour(COLOUR_MIDGREY);
}

void SettingsView::_configureSectionHeader(std::shared_ptr<TextElement> header, String& text, int16_t width) {
    header->getTextComponent()
        .setDisplayString(String(text))
        .setFont(FREE_SERIF_9PT7B)
        .setFontColour(COLOUR_WHITE)
        .setFontSize(1,1);
    header->setWidth(width)
        .setHeight(SM_SECTION_HEADER_HEIGHT)
        .setBackgroundColour(COLOUR_DARKGREY);
}

void SettingsView::_outputContainerInit() {
    if (!_outputContainer) {
        _outputContainer = std::make_unique<Container>(_display);
        _outputContainer->setOrientation(Container::Column)
            .setWidth(SM_OUTPUT_SECTION_WIDTH)
            .setHeight(SM_OUTPUT_SECTION_HEIGHT)
            .setBackgroundColour(COLOUR_DARKGREY);
    }
}

void SettingsView::_outputRowInit() {
    _outputRow = std::make_shared<Container>(_display);
    _outputRow->setOrientation(Container::Row)
        .setWidth(SM_OUTPUT_SECTION_WIDTH)
        .setHeight(SM_FILENAME_HEIGHT)
        .setBackgroundColour(COLOUR_DARKGREY);
}
