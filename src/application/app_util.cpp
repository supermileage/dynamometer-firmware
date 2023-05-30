#include "app_util.h"
#include "style.h"

void app_util::configureMainWindow(Container* window) {
    window->setOrientation(W_ORIENTATION)
        .setWidth(W_WIDTH)
        .setHeight(W_HEIGHT)
        .setPosition(W_TOP_LEFT)
        .setBackgroundColour(W_COLOUR)
        .addBorder(W_BORDER_COLOUR);
}

void app_util::configureHeader(TextElement* header, const String& displayString) {
    header->getTextComponent()
        .setDisplayString(displayString)
        .setFont(HEADER_FONT)
        .setFontColour(HEADER_FONT_COLOUR)
        .setFontSize(HEADER_FONT_WIDTH, HEADER_FONT_HEIGHT);
    header->setWidth(HEADER_WIDTH)
        .setHeight(HEADER_HEIGHT)
        .setBackgroundColour(HEADER_COLOUR);
}

void app_util::configureMenuContainer(Container* container) {
    container->setOrientation(MC_ORIENTATION)
        .setWidth(MC_WIDTH)
        .setHeight(MC_HEIGHT)
        .setBackgroundColour(MC_COLOUR)
        .addBorder(MC_BORDER_COLOUR);
}

void app_util::configureMenuButton(UIButton* button, const String& displayString) {
    button->getTextComponent()
        .setDisplayString(displayString)
        .setFont(MB_FONT)
        .setFontSize(MB_FONT_WIDTH, MB_FONT_HEIGHT)
        .setFontColour(MB_FONT_COLOUR);
    button->setFontFocusColour(MB_FONT_FOCUS_COLOUR)
        .setFocusColour(MB_FOCUS_COLOUR)
        .setWidth(MB_WIDTH)
        .setHeight(MB_HEIGHT)
        .setBackgroundColour(MB_COLOUR)
        .addBorder(MB_BORDER_COLOUR);
}

void app_util::configureNavButtonContainer(Container* container) {
    container->setOrientation(NC_ORIENTATION)
        .setWidth(NC_WIDTH)
        .setHeight(NC_HEIGHT)
        .setBackgroundColour(NC_COLOUR)
        .addBorder(NC_BORDER_COLOUR);
}

void app_util::configureNavButton(UIButton* button) {
    button->getTextComponent()
        .setFont(NB_FONT)
        .setFontSize(NB_FONT_WIDTH, NB_FONT_HEIGHT)
        .setFontColour(NB_FONT_COLOUR);
    button->setFontFocusColour(NB_FONT_FOCUS_COLOUR)
        .setWidth(NB_WIDTH)
        .setHeight(NB_HEIGHT)
        .addBorder(COLOUR_BLACK);
}

void app_util::configureBackButton(UIButton* button) {
    button->setFocusColour(BACK_FOCUS_COLOUR).setBackgroundColour(BACK_COLOUR);

    if (button->getTextComponent().getDisplayString().equals("")) {
        // if display string hasn't been modified, set to default
        button->getTextComponent()
            .setDisplayString(BACK_STRING);
    }
    configureNavButton(button);
}

void app_util::configureSelectButton(UIButton* button) {
    button->setFocusColour(SELECT_FOCUS_COLOUR).setBackgroundColour(SELECT_COLOUR);

    if (button->getTextComponent().getDisplayString().equals("")) {
        button->getTextComponent()
            .setDisplayString(SELECT_STRING);
    }
    configureNavButton(button);
}

const String app_util::stateToString(ApplicationState state) {
    switch (state) {
        case MainMenu:
            return "Main Menu";
        case ManualControlMenu:
            return "Manual Control";
        case CalibrationMenu:
            return "Calibration";
        case SettingsMenu:
            return "Settings";
        case CalibrationMode:
            return "Calibration Mode";
        case CalibrationSettings:
            return "Calibration Settings";
        default:
            return "Does not exist";
    }
}