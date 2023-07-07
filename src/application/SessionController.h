#ifndef _SESSION_CONTROLLER_H_
#define _SESSION_CONTROLLER_H_

#include <functional>

#include "ControllerBase.h"
#include "SessionView.h"

using namespace application;

class SessionController;

typedef arduino::String (SessionController::*Method)(void);

/**
 * @brief abstract base class for controller implementations of dyno's data collection modes
*/
class SessionController : public ControllerBase {
    public:
        SessionController(ApplicationContext& context, Adafruit_GFX& display, SensorOptical& optical,
            SensorForce& force, DataLogger& logger);
        ~SessionController();

        /**
         * @brief initialize session output and set logging interval
         * @note info object config is expected to contain index of output file; if it does not,
         * it will be initialized to default output (see application/application.cpp)
        */
        virtual void init(InputManager& manager, StateInfo& info);

    protected:
        std::shared_ptr<SessionView> _view;
        SensorOptical& _optical;
        SensorForce& _force;
        DataLogger& _logger;
        uint32_t _loggingInterval;
        std::vector<std::function<String(void)>> _valueLoggers; // tandem with _valueIds
        std::vector<ValueId> _valueIds;                         // tandem with _valueLoggers
        bool _loggingEnabled = false;

        void _handleInputSerial(input_data_t d) override;
        void _handleInputBack(input_data_t d) override;
        void _handleInputSelect(input_data_t d) override;
        void _logValues();

    private:
        void _initializeOutput(StateInfo& info);
        std::vector<ValueId> _parseValueIdStr(String& valueIds);
        String _getHeaderFromIds(const std::vector<ValueId>& valueIds);
        void _initializeValueLoggers(const std::vector<ValueId>& values);
        std::function<String(void)> _getValueLogger(ValueId id);
        int _countEntries(String& row);
};

#endif