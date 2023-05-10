#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include <unordered_map>

#include "Handleable.h"
#include "HardwareInput.h"

/**
 * @brief input manager class hooks up dyno inputs to their respective functions
 * 
 * @note sensor inputs are handled by sensor classes -- this class is to deal with assignable user inputs
*/
class InputManager : public Handleable {
    public:
        InputManager();
        ~InputManager();

        /**
         * @brief call initalize on all inputs
        */
        void begin() override;

        /**
         * @brief run all inputs
        */
        void handle() override;

        /**
         * @brief add input with id to id->input map
        */
        void registerInput(uint8_t id, HardwareInput* input);

        /**
         * @brief bind input with id to callback action
         * 
         * @note para
        */
        void registerAction(uint8_t id, InputCallback action);
        
    private:
        std::unordered_map<uint8_t, HardwareInput*> _inputMap;
};

#endif