#ifndef _CONTROLLER_SANDBOX_H_
#define _CONTROLLER_SANDBOX_H_

#include <memory>

#include "ControllerBase.h"
#include "ui/CircularGauge.h"
#include "ui/TextElement.h"

class ControllerSandbox : public ControllerBase {
    public:
        ControllerSandbox(ApplicationContext& context, Adafruit_GFX& display);
        ~ControllerSandbox();
        void init(InputManager& manager) override;

    private:
        std::unique_ptr<TextElement> _header;
        std::unique_ptr<CircularGauge> _gauge;

        void _handleInputSerial(input_data_t d) override;
        void _handleInputBrakePot(input_data_t d) override;

        void _gaugeValueChanged(input_data_t d);
};

#endif