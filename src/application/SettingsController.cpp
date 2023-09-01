#include "SettingsController.h"
#include "System/ErrorLogger.h"
#include "ui/UIEventHandler.h"

#define INPUT_FILENAME_ID       CONFIG_ID_INPUT_FILE_GLOBAL_ID
#define OUTPUT_FILENAME_ID      CONFIG_ID_OUTPUT_FILE_GLOBAL_ID
#define VALUE_IDS               CONFIG_ID_VALUE_IDS
#define LOGGING_INTERVAL_ID     CONFIG_ID_LOGGING_INTERVAL

// TODO
// write code to update button selection via rotary encoder
// END TODO

SettingsController::SettingsController(ApplicationContext& context, TFT_eSPI& display) :
    ControllerBase(context, display) {
        _view = std::make_shared<SettingsView>(display);
}

SettingsController::~SettingsController() { }

void SettingsController::init(InputManager& manager, StateInfo& info) {
    ControllerBase::init(manager);

    _info = info;
    _inFocus = info.inFocus;

    // check if we have input file global id and display (if it exists)
    int inputId = _info.config[INPUT_FILENAME_ID].toInt();
    if (inputId > -1) {
        dyno_assert(application::GlobalSettings.find(inputId) != application::GlobalSettings.end());
        _initializeInputSettings(static_cast<uint8_t>(inputId));
    }

    // set up output file and value id display
    int outputId = _info.config[OUTPUT_FILENAME_ID].toInt();
    dyno_assert(outputId != -1);
    dyno_assert(application::GlobalSettings.find(outputId) != application::GlobalSettings.end());
    _initializeOutputSettings(static_cast<uint8_t>(outputId));

    // set up logging interval display
    int interval = _info.config[LOGGING_INTERVAL_ID].toInt();
    if (interval < 0) {
        interval = application::GlobalSettings[LOGGING_INTERVAL_ID].toInt();
    }
    dyno_assert(interval != -1);
    _initializeIntervalSettings(static_cast<uint16_t>(interval));

    _view->setHeader(_info.header);
}

void SettingsController::_initializeInputSettings(uint8_t id) {
    _inputFilename = application::GlobalSettings[id];
    std::shared_ptr<UIButton> button = _view->buildInputFilenameDisplay(_inputFilename);
    callback_t callback =
        std::bind(&SettingsController::_handleInputStringSelected, this, id, std::placeholders::_1);
    _buttonCallbackPairs.push_back(std::make_pair(button, callback));
}

void SettingsController::_initializeOutputSettings(uint8_t id) {
    _outputFilename = application::GlobalSettings[id];
    std::shared_ptr<UIButton> button = _view->buildOutputFilenameDisplay(_outputFilename);
    callback_t callback =
        std::bind(&SettingsController::_handleOutputStringSelected, this, id, std::placeholders::_1);
    _buttonCallbackPairs.push_back(std::make_pair(button, callback));

    // create buttons for selection
    for (int i = 0; i < NUM_VALUE_IDS; i++) {
        ValueId vid = static_cast<ValueId>(i);
        std::shared_ptr<UIButton> button = _view->buildOutputValueButton(vid);
        callback_t callback =
            std::bind(&SettingsController::_handleValueIdSelected, this, vid, std::placeholders::_1);
        _buttonCallbackPairs.push_back(std::make_pair(button, callback));
    }
}

void SettingsController::_initializeIntervalSettings(uint16_t interval) {
    std::shared_ptr<UIButton> button = _view->buildIntervalButton(interval);
    callback_t callback =
        std::bind(&SettingsController::_handleIntervalSelected, this, std::placeholders::_1);
    _buttonCallbackPairs.push_back(std::make_pair(button, callback));
}

SettingsController::CallbackStatus SettingsController::_handleInputStringSelected(uint8_t id, input_data_t d) {
    if (d){
        _transitionToTextDialog(id, "modify input filename");
    }
    return DoNothing;
}

SettingsController::CallbackStatus SettingsController::_handleOutputStringSelected(uint8_t id, input_data_t d) {
    if (d) {
        _transitionToTextDialog(id, "modify output filename");
    }
    return DoNothing;
}

SettingsController::CallbackStatus SettingsController::_handleValueIdSelected(application::ValueId id, input_data_t d) {
    if (d) {
        _selectedIds[id] = !_selectedIds[id];
    }
    return _selectedIds[id] ? Focus : Unfocus;
}

SettingsController::CallbackStatus SettingsController::_handleIntervalSelected(input_data_t d) {
    _intervalButtonSelected = !!d;
    return _intervalButtonSelected ? Focus : Unfocus;
}

void SettingsController::_transitionToTextDialog(uint8_t id, const char* header) {
    _info.state = application::TextDialog;
    _info.header = String(header);
    _info.config[CONFIG_ID_EDIT_STRING_GLOBAL_ID] = String(id);
    std::vector<ValueId> ids = _getSelectedIds();
    _info.config[VALUE_IDS] = app_util::packValueIdString(ids);
    _info.inFocus = _inFocus;

    if (!_context.trySetNextState(_info)) {
        return;
    }

    auto self = shared_from_this();
    UIEventHandler::instance().addEvent(
        [this, self]() {
            _context.setStateTransitionFlag();
        }
    );
}

std::vector<ValueId> SettingsController::_getSelectedIds() {
    std::vector<ValueId> ret;
    for (int i = 0; i < NUM_VALUE_IDS; i++) {
        if (_selectedIds[i]) {
            ret.push_back(static_cast<ValueId>(i));
        }
    }
    return ret;
}

void SettingsController::_handleInputEncoder(input_data_t d) {
    if (_intervalButtonSelected) {
        // modify interval
    } else {
        _shiftFocus(d);
    }
}

void SettingsController::_handleInputEncoderSelect(input_data_t d) {
    _onButtonSelected(d);
}

void SettingsController::_handleInputBack(input_data_t d) {
    if (d) {   
        if (!_context.tryRevertState()) {
            return;
        }

        auto self = shared_from_this();
        UIEventHandler::instance().addEvent([this, self]() {
            _context.setStateTransitionFlag();
        });
    }
}

void SettingsController::_handleInputSelect(input_data_t d) {
    if (d) {
        std::vector<ValueId> ids = _getSelectedIds();
        _info.config[VALUE_IDS] = app_util::packValueIdString(ids);
        _info.inFocus = _inFocus;

        if (!_context.tryUpdateAndReturn(_info)) {
            return;
        }
        
        auto self = shared_from_this();
        UIEventHandler::instance().addEvent(
            [this, self]() {
                _view->select();
                _context.setStateTransitionFlag(); // set flag after render actions are complete
            }
        );
    }
}

void SettingsController::_handleInputBrakeButton(input_data_t d) {
    _onButtonSelected(d);
}

void SettingsController::_onButtonSelected(input_data_t d) {
    auto button = _buttonCallbackPairs[_inFocus].first;
    auto callback = _buttonCallbackPairs[_inFocus].second;

    // invoke callback
    CallbackStatus status = callback(d);

    // update display
    if (status == CallbackStatus::Focus) {
        // trigger select
        UIEventHandler::instance().addEvent({
            [button]() {
                button->focus();
            }
        });
    } else if (status == CallbackStatus::Unfocus) {
        // trigger deselect
        UIEventHandler::instance().addEvent({
            [button]() {
                button->revert();
            }
        });
    }
}

void SettingsController::_shiftFocus(int32_t offset) {
    auto button = _buttonCallbackPairs[_inFocus].first;
    UIEventHandler::instance().addEvent( [button]() { cur->revert(); } );

    // compute index of new focussed element
    _inFocus = static_cast<uint8_t>(_computeIndexOffset(_inFocus, offset, _buttonInfoPairs.size()));

    // focus new element
    button = _buttonCallbackPairs[_inFocus].first;
    UIEventHandler::instance().addEvent([button]() { cur->focus(); });
}

