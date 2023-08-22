#include "CalibrationController.h"
#include "System/ErrorLogger.h"
#include "ui/UIEventHandler.h"

#define INPUT_FILENAME_ID CONFIG_ID_INPUT_FILE_GLOBAL_ID

CalibrationController::CalibrationController(ApplicationContext& context, TFT_eSPI& display,
    SensorOptical& optical, SensorForce& force) : SessionController(context, display, optical, force) {
            _view = std::make_shared<CalibrationView>(display);
}

CalibrationController::~CalibrationController() { }

void CalibrationController::init(InputManager& manager, StateInfo& info) {
    ControllerBase::init(manager);
    SessionController::_initializeOutput(info);

    // get input filename and initialize output csv
    dyno_assert(info.config.find(INPUT_FILENAME_ID) != info.config.end());
    int id = info.config[INPUT_FILENAME_ID].toInt();
    dyno_assert(id != CONFIG_ID_NULL);
    // check if input filename available in local config, otherwise use global
    if (info.config.find(id) != info.config.end()) {
        _inputFilename = info.config[id];
    } else if (application::GlobalSettings.find(id) != application::GlobalSettings.end()) {
        _inputFilename = application::GlobalSettings[id];
    } else {
        dyno_log_str("SessionController: No entry for input filename with id " + String(id) + " in local/global info object");
        _inputFilename = application::GlobalSettings[CONFIG_ID_DEFAULT_INPUT_FILENAME];
    }
    _initializeInputCsv(_inputFilename);

    _view->setHeader("calibration mode");
}

uint32_t g_sum = 0;
uint32_t g_count = 0;

void CalibrationController::handle() {
    _optical.handle();
    _force.handle();

    if (_calibrationEnabled) {
        // read and handle csv input data
        if (millis() >= _nextOutputTime) {
            // TODO: update io with next inputCsv values
            // write _nextBpmVoltage to bpm controller
            // write _nextVescRpm to vesc controller
            // END TODO

            // set next values (including _nextOutputTime)
            for (int i = 0 ; i < CAL_INPUT_NUM_COLUMNS; i++) {
                String entry = _inputCsv.readEntry();
                _inputParsers[i](entry);
                // end automation if we've reached eof
                _calibrationEnabled = (entry.compareTo("") != 0);
            }
        }

        // handle logging output data
        if (millis() >= _lastLogTime + _loggingInterval) {
            SessionController::_logValues();
            _lastLogTime = millis();
        }
    }

    // UPDATE VIEW to display controller and sensor values
}

void CalibrationController::_initializeInputCsv(String& filename) {
    if (_inputCsv.open(filename, CAL_INPUT_NUM_COLUMNS, O_READ)) {
        filename = _inputCsv.getFileName();
    } else {
        dyno_log_str("Unable to open file with name: " + String(filename));
        filename = "error";
        return;
    }

    // set up input parsers
    for (int i = 0; i < CAL_INPUT_NUM_COLUMNS; i++) {
        String header = _inputCsv.readEntry();
        _inputParsers[i] = _getInputCsvParser(app_util::headerToValue(header));
    }
}

std::function<void(const String&)> CalibrationController::_getInputCsvParser(ValueId id) {
    switch (id) {
        case Time:
            return [this](const String& t) {
                _nextOutputTime = _startTime + static_cast<uint32_t>(t.toInt());
            };
        case BpmVoltage:
            return [this](const String& v) {
                _nextBpmVoltage =  static_cast<uint32_t>(v.toInt());
            };
        case VescRpm:
            return [this](const String& rpm) { 
                _nextVescRpm = static_cast<uint32_t>(rpm.toInt());
            };
        default:
            dyno_log_str("CalibrationController: no csv input parser for ValueId: " + String(id));
            return [](const String& _) { };
    }
}

void CalibrationController::_handleInputBack(input_data_t d) {
    if (d && _calibrationEnabled && !_recordingStopped) {
        // STOP recording
        // update navigation buttons to display Cancel and Save

        _calibrationEnabled = false;
        _recordingStopped = true;
    } else if (d && _recordingStopped) {
        // RESET input / output and set view to rdy recording mode

        _recordingStopped = false;
    } else if (d && !_calibrationEnabled && !_recordingStopped) {
        // return to previous menu
        if (!_context.tryRevertState()) {
            return;
        }

        auto self = shared_from_this();
        UIEventHandler::instance().addEvent([this, self]() {
            _context.setStateTransitionFlag();
        });
    }
}

void CalibrationController::_handleInputSelect(input_data_t d) {
    if (d && !_calibrationEnabled && _recordingStopped) {
        // SAVE output
        // RESET input/output csv and set view to rdy recording mode

        _recordingStopped = false;
    } else if (d && !_calibrationEnabled && !_recordingStopped) {
        // START recording

        _calibrationEnabled = true;
        _startTime = millis();

        // view displays recording mode
    }
}