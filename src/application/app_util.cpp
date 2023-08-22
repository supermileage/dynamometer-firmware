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
        case GlobalSettingsMenu:
            return "Global Settings";
        case CalibrationMenu:
            return "Calibration Menu";
        case CalibrationMode:
            return "Calibration Mode";
        case CalibrationSettings:
            return "Calibration Settings";
        case AutoControlMenu:
            return "Manual Control Menu";
        case AutoControlMode:
            return "Manual Control Mode";
        case AutoControlSettings:
            return "Manual Control Settings";
        case ManualControlMenu:
            return "Manual Control Menu";
        case ManualControlMode:
            return "Manual Control Mode";
        case ManualControlSettings:
            return "Manual Control Settings";
        case TextDialog:
            return "Text Dialog";
        default:
            return "Does not exist";
    }
}                 

const String app_util::valueToHeader(application::ValueId id) {
    switch (id) {
        case Force:
            return "force";
        case AngularVelocity:
            return "avel";
        case AngularAccel:
            return "accel";
        case DynoRpm:
            return "rpm";
        case BpmVoltage:
            return "bpm";
        case BpmCurrent:
            return "bpmcur";
        case Time:
            return "time";
        case VescRpm:
            return "vrpm";
        case VescDuty:
            return "vduty";
        case VescCurrent:
            return "vcur";
        default:
            return "undefined";
    }
}

const String app_util::valueToUnit(application::ValueId id) {
    switch (id) {
        case Force:
            return "lbs";
        case AngularVelocity:
            return "rad/s";
        case AngularAccel:
            return "rad/s2";
        case DynoRpm:
            return "rpm";
        case BpmVoltage:
            return "V";
        case BpmCurrent:
            return "A";
        case Time:
            return "";
        case VescRpm:
            return "rpm";
        case VescDuty:
            return "";
        case VescCurrent:
            return "A";
        default:
            return "undefined";
    }
}

const ValueId app_util::headerToValue(const String& header) {
    if (header.compareTo("force") == 0) {
        return Force;
    } else if (header.compareTo("avel") == 0) {
        return AngularVelocity;
    } else if (header.compareTo("accel") == 0) {
        return AngularAccel;
    } else if (header.compareTo("rpm") == 0) {
        return DynoRpm;
    } else if (header.compareTo("bpm") == 0) {
        return BpmVoltage;
    } else if (header.compareTo("bpmcur") == 0) {
        return BpmCurrent;
    } else if (header.compareTo("time") == 0) {
        return Time;
    } else if (header.compareTo("vrpm") == 0) {
        return VescRpm;
    } else if (header.compareTo("vduty") == 0) {
        return VescDuty;
    } else if (header.compareTo("vcur") == 0) {
        return VescCurrent;
    } else {
        return Invalid;
    }
}