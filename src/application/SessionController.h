#ifndef _SESSION_CONTROLLER_H_
#define _SESSION_CONTROLLER_H_

#include <functional>

#include "application.h"
#include "Sensor/SensorOptical.h"
#include "Sensor/SensorForce.h"
#include "System/CsvFile.h"
#include "System/BpmControl.h"
#include "ControllerBase.h"


using namespace application;

/**
 * @brief abstract base class for controller implementations of dyno's data collection modes
*/
class SessionController : public ControllerBase {
    public:
        SessionController(ApplicationContext& context, TFT_eSPI& display, SensorForce& force, SensorOptical& optical, BpmControl& bpm) ;
        ~SessionController();

        void init(InputManager& m) override {
            ControllerBase::init(m);
            // do some stuff
        }

    protected:
        SensorOptical& _optical;
        SensorForce& _force;
        BpmControl& _bpm;
        uint32_t _bpmDutyCycle;
        uint32_t _loggingInterval;
        std::vector<std::function<String(void)>> _valueLoggers; // tandem with _valueIds
        std::vector<ValueId> _valueIds;                         // tandem with _valueLoggers
        String _outputFilename = "";
        bool _loggingEnabled;

        /**
         * @brief initialize output logging -- logging interval, value loggers and output csv
         * @ info object must contain logging interval, csv value id string and output filename
        */
        void _initializeOutput(StateInfo& info);

        /**
         * @brief initializes output csv file, generating header from value ids
         * @note modifies filename
        */
        void _initializeOutputCsv(const std::vector<ValueId>& ids, String& filename);
        void _closeOutputCsv();
        void _logValues();

    private:
        CsvFile _outputCsv;

        std::vector<ValueId> _parseValueIdStr(String& valueIds);
        String _getHeaderFromIds(const std::vector<ValueId>& ids);
        void _initializeValueLoggers(const std::vector<ValueId>& ids);
        std::function<String(void)> _getValueLogger(ValueId id);

        void _navigateBack();

        void _handleInputBack(input_data_t d) override;
        void _handleInputBrakePot(input_data_t d) override;
        void _handleInputBrakeButton(input_data_t d) override;
        
};

#endif