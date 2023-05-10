#include "UIEventHandler.h"

#include <algorithm>

UIEventHandler* UIEventHandler::_instance = nullptr;

UIEventHandler::UIEventHandler() { }

UIEventHandler::~UIEventHandler() { }

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
    bool queueEmpty = _eventQueue.empty();
    mutex_exit(&_eventQueueMtx);

    while (!queueEmpty) {
        mutex_enter_blocking(&_eventQueueMtx);
        std::function<void()> event = _eventQueue.front();
        _eventQueue.pop();
        mutex_exit(&_eventQueueMtx);

        // must run event outside of mutex lock so other core doesn't stall
        (event)();

        mutex_enter_blocking(&_eventQueueMtx);
        queueEmpty = _eventQueue.empty();
        mutex_exit(&_eventQueueMtx);
    }

    uint32_t currentTime = millis();
    for (ui_util::Animation* animation : _animations) {
        animation->run(currentTime);
    }
}

void UIEventHandler::addEvent(std::function<void(void)> action) {
    mutex_enter_blocking(&_eventQueueMtx);
    _eventQueue.push(action);
    mutex_exit(&_eventQueueMtx);
}

void UIEventHandler::addAnimation(ui_util::Animation* animation) {
    mutex_enter_blocking(&_eventQueueMtx);
    _eventQueue.push([this, animation]() {
        _animations.push_back(animation);
    });
    mutex_exit(&_eventQueueMtx);
}

void UIEventHandler::removeAnimation(ui_util::Animation* animation) {
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
