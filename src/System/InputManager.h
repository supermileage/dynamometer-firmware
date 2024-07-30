#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include <unordered_map>
#include "HardwareInput.h"

/**
 * @brief input manager class hooks up dyno inputs to their respective functions
 * 
 * @note sensor inputs are handled by sensor classes -- this class deals with assignable user inputs
*/
class InputManager {
    public:
        InputManager();
        ~InputManager();

        /**
         * @brief call initialize on all inputs
        */
        void begin();

        /**
         * @brief run all inputs
        */
        void handle();

        /**
         * @brief add input with id to id->input map
        */
        void registerInput(uint8_t id, HardwareInput* input);

        /**
         * @brief bind input with id to callback action
         * @note action will replace currently assigned input callback for id
        */
        void registerAction(uint8_t id, InputCallback action);

        /**
         * @brief return read value for input with id
        */
       input_data_t read(uint8_t id);
        
    private:
        std::unordered_map<uint8_t, HardwareInput*> _inputMap;
};

#endif