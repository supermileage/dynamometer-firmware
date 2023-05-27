#ifndef _DYNO_DISPLAY_H_
#define _DYNO_DISPLAY_H_

#include "pico/mutex.h"
#include <queue>
#include <functional>

#include "ui_util.h"

/**
 * @brief handles threadsafe event queue and animations
 * 
 * @note can also be tasked with running non-rendering-related events
*/
class UIEventHandler {
    public:
        ~UIEventHandler();

        static UIEventHandler& instance();

        /**
         * @brief initializes mutexes
        */
        void init();

        /**
         * @brief handles event queue and animations
         * @note only executes one event per call to loop
        */
        void run();

        /**
         * @brief add event to event queue
        */
        void addEvent(std::function<void(void)> action);

        /**
         * @brief add animation
        */
        void addAnimation(ui_util::Animation* animation);

        /**
         * @brief remove animation
         * @note this will call delete on animation only if Animation::deleteOnTermination() returns true
        */
        void removeAnimation(ui_util::Animation* animation);

        /**
         * @brief clears all events from queue
        */
        void clearEventQueue();

        /**
         * @brief clears all animations
         * 
         * @note this will not call delete on any of the animation ptrs: freeing data is the user's responsibility
        */
        void clearAnimations();

    private:
        static UIEventHandler* _instance;
        mutex_t _eventQueueMtx;
        std::queue<std::function<void(void)>> _eventQueue;
        std::vector<ui_util::Animation*> _animations;

        UIEventHandler();

};

#endif