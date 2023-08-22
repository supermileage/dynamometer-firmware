#ifndef _CALIBRATION_CONTROLLER_H_
#define _CALIBRATION_CONTROLLER_H_

#include "SessionController.h"
#include "CalibrationView.h"

#include "Sensor/SensorOptical.h"
#include "Sensor/SensorForce.h"
#include "System/CsvFile.h"
#include "ui/CircularElement.h"

#define CAL_INPUT_NUM_COLUMNS 3

class CalibrationController : public SessionController {
    public:
        CalibrationController(ApplicationContext& context, TFT_eSPI& display, SensorOptical& optical, SensorForce& force);
        ~CalibrationController();
        void init(InputManager& manager, StateInfo& info);
        void handle() override;

    private:
        std::shared_ptr<CalibrationView> _view;
        CsvFile _inputCsv;
        uint32_t _startTime = 0;
        uint32_t _nextOutputTime = 0;
        uint32_t _nextBpmVoltage = 0;
        uint32_t _nextVescRpm = 0;
        std::array<std::function<void(const String&)>, CAL_INPUT_NUM_COLUMNS> _inputParsers;
        uint32_t _lastLogTime = 0;
        bool _calibrationEnabled = false;
        bool _recordingStopped = false;
        String _inputFilename = "";

        // input handlers
        void _handleInputSerial(input_data_t d) override;
        void _handleInputEncoder(input_data_t d) override;
        void _handleInputEncoderSelect(input_data_t d) override;
        void _handleInputBack(input_data_t d) override;
        void _handleInputSelect(input_data_t d) override;
        void _handleInputBrakeButton(input_data_t d) override;
        void _handleInputBrakePot(input_data_t d) override;

        void _initializeInputCsv(String& filename);
        std::function<void(const String&)> _getInputCsvParser(ValueId id);
};

#endif