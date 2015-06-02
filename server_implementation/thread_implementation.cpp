//
// Created by m3sc4 on 15.05.15.
//

#include "thread_implementation.h"
#include <sstream>

namespace threading {

    Thread::Thread(threadFuncT func, void* param, std::string name) {
        pthread_create(&innerThread, nullptr, func, param);
        if (name.length() != 0)
            threadsIdName[(unsigned long) innerThread] = name;
        else {
            std::ostringstream autoThreadName("thread", std::ios_base::app);
            autoThreadName << (unsigned long) innerThread;
            threadsIdName[(unsigned long) innerThread] = autoThreadName.str();
        }
    }

    void Thread::join() {
        pthread_join(innerThread, nullptr);
    }

    void Thread::deatch() {
        pthread_detach(innerThread);
    }

    unsigned long Thread::getId() {
        return (unsigned long) innerThread;
    }

    void Thread::setName (std::string name) {
        threadsIdName[this->getId()] = name;
    }

    std::string Thread::getCurrentThreadName() {
        try {
            return threadsIdName.at((unsigned long) pthread_self());
        } catch (std::out_of_range) {
            return std::string("Undefined thread.");
        }
    }

    Locker::Locker(Guard & whatToLock) {
        locker = &whatToLock;
        locker->lock();
    }

    Locker::~Locker() {
        locker->unlock();
    }

    MutexImpementation::MutexImpementation(void) {
        pthread_mutex_init(&Pmutex, nullptr);
    }

    MutexImpementation::~MutexImpementation(void) {
        pthread_mutex_destroy(&Pmutex);
    }

    bool MutexImpementation::tryLock() {
        return pthread_mutex_trylock(&Pmutex) == 0;
    }

    void MutexImpementation::unlock() {
        pthread_mutex_unlock(&Pmutex);
    }

    void MutexImpementation::lock() {
        pthread_mutex_lock(&Pmutex);
    }

    std::map<unsigned long, std::string> threading::Thread::threadsIdName;
}

