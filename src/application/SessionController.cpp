#include "SessionController.h"
#include "ui/UIEventHandler.h"
#include "System/ErrorLogger.h"

#define DEFAULT_LOGGING_INTERVAL 100

#define OUTPUT_FILENAME_ID      CONFIG_ID_OUTPUT_FILE_GLOBAL_ID
#define VALUE_IDS               CONFIG_ID_VALUE_IDS
#define LOGGING_INTERVAL_ID     CONFIG_ID_LOGGING_INTERVAL

SessionController::SessionController(ApplicationContext& context, Adafruit_GFX& display,
    SensorOptical& optical, SensorForce& force) : ControllerBase(context, display),
        _optical(optical), _force(force) { }

SessionController::~SessionController() { }

void SessionController::init(InputManager& manager, StateInfo& info) {
    // initialize inputs
    ControllerBase::init(manager);
    
    // initialize output file
    _initializeOutput(info);

    // set logging interval
    if (info.config.find(LOGGING_INTERVAL_ID) != info.config.end()) {
        uint32_t interval = info.config[LOGGING_INTERVAL_ID].toInt();
        dyno_assert(interval != 0);
        _loggingInterval = interval;
    } else {
        dyno_log_str("SessionController: no logging interval defined -- setting to default " + String(DEFAULT_LOGGING_INTERVAL) + "ms");
        _loggingInterval = DEFAULT_LOGGING_INTERVAL;
    }

    _info = info;
}

void SessionController::_logValues() {
    for (std::function<String(void)> logger : _valueLoggers) {
        _outputCsv.addEntry(logger());
    }
}

void SessionController::_initializeOutput(StateInfo& info) {
    dyno_assert(info.config.find(OUTPUT_FILENAME_ID) != info.config.end());
    int id = info.config[OUTPUT_FILENAME_ID].toInt();
    dyno_assert(id != CONFIG_ID_NULL);
    
    // check if output filename available in local config, otherwise use global
    if (info.config.find(id) != info.config.end()) {
        _outputFilename = info.config[id];
    } else if (application::GlobalSettings.find(id) != application::GlobalSettings.end()) {
        _outputFilename = application::GlobalSettings[id];
    } else {
        dyno_log_str("SessionController: No entry for output filename with id " + String(id) + " in local/global info object");
        _outputFilename = application::GlobalSettings[CONFIG_ID_DEFAULT_OUTPUT_FILENAME];
    }

    // initialize csv file and value loggers
    dyno_assert(info.config.find(VALUE_IDS) != info.config.end());
    String& valueIdStr = info.config[VALUE_IDS];
    _valueIds = _parseValueIdStr(valueIdStr);
    _initializeValueLoggers(_valueIds);
    _initializeOutputCsv(_valueIds, _outputFilename);
}

String SessionController::_getHeaderFromIds(const std::vector<ValueId>& ids) {
    String header = "";
    for (int i = 0; i < ids.size(); i++) {
        header += app_util::valueToHeader(ids[i]);
        
        if (i < ids.size() - 1) {
            header += ',';
        }
    }
    return header;
}

void SessionController::_initializeValueLoggers(const std::vector<ValueId>& ids) {
    for (ValueId id : ids) {
        _valueLoggers.push_back(_getValueLogger(id));
    }
}

void SessionController::_initializeOutputCsv(const std::vector<ValueId>& ids, String& filename) {
    if (_outputCsv.create(filename, ids.size())) {
        String header = _getHeaderFromIds(ids);
        _outputCsv.setHeader(header);
        filename = _outputCsv.getFileName();
    } else {
        dyno_log_str("Unable to create file with name: " + String(filename));
        filename = "error";
    }
}

std::vector<ValueId> SessionController::_parseValueIdStr(String& valueIds) {
    std::vector<ValueId> vec;
    int first = 0;
    int last = 1;
    while (last > 0) {
        last = valueIds.substring(first).indexOf(',');
        int valueId;
        if (last < 0) {
            valueId = valueIds.substring(first).toInt();
        } else {
            valueId = valueIds.substring(first, first + last).toInt();
            first = first + last + 1;
        }
        vec.push_back(static_cast<ValueId>(valueId));
    }
    return vec;
}

std::function<String(void)> SessionController::_getValueLogger(ValueId id) {
    switch (id) {
        case Force:
            return [this]() { return String(_force.getForce()); };
        case AngularVelocity:
            return [this]() { return String(_optical.getAngularVelocity()); };
        case AngularAccel:
            // TODO: angular acceleration logger
            return []() { return "0.00"; };
        case DynoRpm:
            // TODO: dyno rpm logger
            return []() { return "0.00"; };
        case BpmVoltage:
            // TODO: bpm voltage logger
            return []() { return "0.00"; };
        case BpmCurrent:
            // TODO: bpm current logger
            return []() { return "0.00"; };
        case Time:
            // TODO: time logger
            return []() { return "0.00"; };
        case VescRpm:
            // TODO: vesc rpm logger
            return []() { return "0.00"; };
        case VescDuty:
            // TODO: vesc duty logger
            return []() { return "0.00"; };
        case VescCurrent:
            // TODO: vesc current logger
            return []() { return "0.00"; };
        default:
            dyno_log_str("SessionController: no logging function for ValueId: " + String(id));
            return []() { return "undefined"; };
    }
}

int SessionController::_countEntries(String& row) {
    if (row.length() == 0) {
        return 0;
    }
    int count = 1;
    for (int i = 0; i < row.length(); i++) {
        if (row[i] == ',') {
            count++;
        }
    }
    return count;
}