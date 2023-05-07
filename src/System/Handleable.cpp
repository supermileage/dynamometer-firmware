#include "Handleable.h"
#include <algorithm>

Handleable::Handleable() {
	Handleable::Handler::instance().add(this);
}

Handleable::~Handleable() {
	Handleable::Handler::instance().remove(this);
}

Handleable::Handler* Handleable::Handler::_instance;

void Handleable::handleAll() {
    Handleable::Handler::instance().handle();
}

Handleable::Handler &Handleable::Handler::instance() {
    if (!_instance) {
        _instance = new Handleable::Handler();
    }
    return *_instance;
}

void Handleable::Handler::add(Handleable* handleable) {
    _handleables.push_back(handleable);
}

void Handleable::Handler::remove(Handleable* handleable) {
    _handleables.erase(std::remove(_handleables.begin(), _handleables.end(), handleable), _handleables.end());
}

bool Handleable::Handler::contains(Handleable* handleable) {
    for (unsigned int i = 0; i < _handleables.size(); i++) {
        if (_handleables[i] == handleable) {
            return true;
        }
    }

    return false;
}

void Handleable::Handler::begin() {
    for(Handleable *h : _handleables) {
        h->begin();
    }
}

void Handleable::Handler::handle() {
    for(Handleable *h : _handleables) {
        h->handle();
    }
}

    
