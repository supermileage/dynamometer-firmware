#ifndef _SESSION_CONTROLLER_H_
#define _SESSION_CONTROLLER_H_

#include <functional>

#include "application.h"
#include "Sensor/SensorOptical.h"
#include "Sensor/SensorForce.h"
#include "System/CsvFile.h"
#include "ControllerBase.h"

using namespace application;

/**
 * @brief abstract base class for controller implementations of dyno's data collection modes
*/
class SessionController : public ControllerBase {
    public:
        SessionController(ApplicationContext& context, Adafruit_GFX& display, SensorOptical& optical, SensorForce& force);
        ~SessionController();

        /**
         * @brief initialize session output and set logging interval
         * @note info object config is expected to contain index of output file; if it does not,
         * it will be initialized to default output (see application/application.cpp)
        */
        virtual void init(InputManager& manager, StateInfo& info);

    protected:
        SensorOptical& _optical;
        SensorForce& _force;
        uint32_t _loggingInterval;
        CsvFile _outputCsv;
        std::vector<std::function<String(void)>> _valueLoggers; // tandem with _valueIds
        std::vector<ValueId> _valueIds;                         // tandem with _valueLoggers
        String _outputFilename = "";
        bool _loggingEnabled;

        /**
         * @brief initializes output csv file
         * @note CsvFile::create may generate a unique name to avoid overwriting other files --
         * filename will be set to this name
        */
        void _initializeOutputCsv(const std::vector<ValueId>& ids, String& filename);
        void _logValues();

    private:
        void _initializeOutput(StateInfo& info);
        std::vector<ValueId> _parseValueIdStr(String& valueIds);
        String _getHeaderFromIds(const std::vector<ValueId>& ids);
        void _initializeValueLoggers(const std::vector<ValueId>& ids);
        std::function<String(void)> _getValueLogger(ValueId id);
        int _countEntries(String& row);
};

#endif