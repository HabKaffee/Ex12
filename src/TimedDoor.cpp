//  Copyright 2021 Nikita Naumov

#include "TimedDoor.h"

void Timer::sleep(int sleepFor) {
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepFor*1000));
}
void Timer::tregister(int sleepFor, TimerClient * id) {
    this->client = id;
    this->sleep(sleepFor);
}
int TimedDoor::getTime() {
    return this->iTimeout;
}
DoorTimerAdapter::DoorTimerAdapter(TimedDoor &door) : door(door) {
    this->door = door;
}
void DoorTimerAdapter::Timeout() {
    Timer timer;
    timer.tregister(this->door.getTime(), this);
    this->door.DoorTimeOut();
}

TimedDoor::TimedDoor(int timeout) : iTimeout(timeout), opened(false),
                            adapter(new DoorTimerAdapter(*this)) {};

void TimedDoor::lock() {
    this->opened = false;
}

void TimedDoor::unlock() {
    this->opened = true;
    this->adapter->Timeout();

}

bool TimedDoor::isDoorOpened() {
    if (this->opened) {
        return true;
    }
    return false;
}

void TimedDoor::DoorTimeOut() {
    throw static_cast<std::string>("close the door!");
}

void TimedDoor::throwState() {
    if(this->opened) {
        throw static_cast<std::string>("the door is opened");
    }
    if (!(this->opened)) {
        throw static_cast<std::string>("the door is closed!");
    }
}


