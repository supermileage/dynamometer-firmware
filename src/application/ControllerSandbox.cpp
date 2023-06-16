#include "ControllerSandbox.h"

#include "graphics/colour.h"
#include "graphics/fonts.h"
#include "ui/UIEventHandler.h"
#include "System/HardwarePotentiometer.h"

#define GAUGE_MIN_VAL 0
#define GAUGE_MAX_VAL POTENTIOMETER_MAX

#define GAUGE_RADIUS 65
#define GAUGE_BACKGROUND_COLOUR COLOUR_DARKGREY

#define SCREEN_CENTER_X (320 / 2)
#define SCREEN_CENTER_Y (240 / 2)

ControllerSandbox::ControllerSandbox(ApplicationContext& context, Adafruit_GFX& display) :
    ControllerBase(context, display) { }

ControllerSandbox::~ControllerSandbox() { }

void ControllerSandbox::init(InputManager& manager) {
    // register all inputs with this controller
    ControllerBase::init(manager);

    // setup sandbox header
    _header = std::make_unique<TextElement>(_display);
    _header->getTextComponent()
        .setFont(FREE_SANS_9PT7B)
        .setDisplayString("potentiometer gauge")
        .setFontColour(COLOUR_WHITE)
        .setFontSize(1,1);
    _header->setWidth(320)
        .setHeight(35)
        .setPosition(ui_util::Point { 0, 0 });

    // setup gauge
    _gauge = std::make_unique<CircularGauge>(_display, GAUGE_MIN_VAL, GAUGE_MAX_VAL);
    _gauge->setRadius(GAUGE_RADIUS)
        .setBackgroundColour(GAUGE_BACKGROUND_COLOUR)
        .setPosition(ui_util::Point { SCREEN_CENTER_X - GAUGE_RADIUS, SCREEN_CENTER_Y - GAUGE_RADIUS });

    // initialize gauge and display
    int32_t val = manager.read(ID_BRAKE_POT);
    auto self = shared_from_this();

    UIEventHandler::instance().addEvent(
        [this, self, val]() {
            _header->draw();
            _gauge->setDisplayValue(val);
            _gauge->draw();
        }
    );
}

void ControllerSandbox::_handleInputSerial(input_data_t d) {
    DEBUG_SERIAL_LN("Serial input received: " + String(d));
    switch (d) {
        case 65:    // up
            _gaugeValueChanged(static_cast<int32_t>(_gauge->getDisplayValue() - 1));
            break;
        case 66:    // down 
            _gaugeValueChanged(static_cast<int32_t>(_gauge->getDisplayValue() + 1));
            break;
        default:    // do nothing
            break;
    }
}

void ControllerSandbox::_handleInputBrakePot(input_data_t d) {
    _gaugeValueChanged(static_cast<int32_t>(d));
}

void ControllerSandbox::_gaugeValueChanged(int32_t d) {
    auto self = shared_from_this();
    UIEventHandler::instance().addEvent(
        [this, self, d]() {
            _gauge->setDisplayValue(d);
            _gauge->draw();
        }
    );
}

