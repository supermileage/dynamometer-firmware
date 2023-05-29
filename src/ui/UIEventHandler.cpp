#include "UIEventHandler.h"

#include <algorithm>

#include "settings.h"

UIEventHandler* UIEventHandler::_instance = nullptr;

UIEventHandler::UIEventHandler() { }

UIEventHandler::~UIEventHandler() {
    clearAnimations();
    clearEventQueue();
}

UIEventHandler& UIEventHandler::instance() {
    if (_instance == nullptr) {
        _instance = new UIEventHandler();
    }
    return *_instance;
}

void UIEventHandler::init() {
    mutex_init(&_eventQueueMtx);
}

void UIEventHandler::run() {
    mutex_enter_blocking(&_eventQueueMtx);

    if (!_eventQueue.empty()) {
        DEBUG_STATE_TRANSITION_LN("Event queue not empty");
        std::function<void()> event = _eventQueue.front();
        _eventQueue.pop();
        mutex_exit(&_eventQueueMtx);

        // run event outside of mutex
        DEBUG_STATE_TRANSITION_LN("Invoking event from UIEventHandler");
        (event)();
    } else {
        mutex_exit(&_eventQueueMtx);
    }

    for (std::shared_ptr<ui_util::Animation> animation : _animations) {
        animation->run(millis());
    }
}

void UIEventHandler::addEvent(std::function<void(void)> action) {
    DEBUG_STATE_TRANSITION_LN("adding action to event queue");
    mutex_enter_blocking(&_eventQueueMtx);
    DEBUG_STATE_TRANSITION_LN("pushing action to event queue");
    _eventQueue.push(action);
    mutex_exit(&_eventQueueMtx);
    DEBUG_STATE_TRANSITION_LN("exiting addEvent()");
}

void UIEventHandler::addAnimation(std::shared_ptr<ui_util::Animation> animation) {
    mutex_enter_blocking(&_eventQueueMtx);
    _eventQueue.push([this, animation]() {
        _animations.push_back(animation);
    });
    mutex_exit(&_eventQueueMtx);
}

void UIEventHandler::removeAnimation(std::shared_ptr<ui_util::Animation> animation) {
    mutex_enter_blocking(&_eventQueueMtx);
    _eventQueue.push([this, animation]() {
        _animations.erase(std::remove(_animations.begin(), _animations.end(), animation), _animations.end());
    });
    mutex_exit(&_eventQueueMtx);
}

void UIEventHandler::clearEventQueue() {
    mutex_enter_blocking(&_eventQueueMtx);
    while (!_eventQueue.empty()) {
        _eventQueue.pop();
    }
    mutex_exit(&_eventQueueMtx);
}

void UIEventHandler::clearAnimations() {
    mutex_enter_blocking(&_eventQueueMtx);
    _animations.clear();
    mutex_exit(&_eventQueueMtx);
}
