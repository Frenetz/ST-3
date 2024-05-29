// Copyright 2024 Khodyrev Fedor

#include <stdexcept>
#include <thread> // NOLINT [build/c++11]
#include <chrono> // NOLINT [build/c++11]

#include "TimedDoor.h"

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& door_) : door(door_) {}

void DoorTimerAdapter::Timeout() {
    if (door.isDoorOpened()) {
        throw std::runtime_error("Time's up!");
    }
}

TimedDoor::TimedDoor(int timeout_) : iTimeout(timeout_), isOpened(false), adapter(new DoorTimerAdapter(*this)) {}

bool TimedDoor::isDoorOpened() {
    return isOpened;
}

void TimedDoor::unlock() {
    if (isOpened) {
        throw std::logic_error("Door is already opened");
    }
    isOpened = true;
}

void TimedDoor::lock() {
    if (!isOpened) {
        throw std::logic_error("Door is already closed");
    }
    isOpened = false;
}

int TimedDoor::getTimeOut() const {
    return iTimeout;
}

void TimedDoor::throwState() {
    adapter->Timeout();
}

void Timer::sleep(int duration) {
    std::this_thread::sleep_for(std::chrono::seconds(duration));
}

void Timer::tregister(int duration, TimerClient* client_) {
    client = client_;
    sleep(duration);
    client_->Timeout();
}
