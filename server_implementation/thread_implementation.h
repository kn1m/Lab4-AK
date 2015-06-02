
#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>
#include <map>
#include <string>

namespace threading {
        class Thread {
            public:
                typedef void* (*threadFuncT)(void*);
                Thread(threadFuncT func, void* param = nullptr, std::string name = std::string(""));
                static std::string getCurrentThreadName();
                void join();
                void deatch();
                unsigned long getId();
                void setName (std::string name);
                Thread() = delete;
            private:
                static std::map<unsigned long,std::string> threadsIdName;
                pthread_t innerThread;
        };

        class Guard {
            public:
                virtual bool tryLock() = 0;
                virtual void unlock() = 0;
                virtual void lock() = 0;
                virtual ~Guard() { }
        };

        class MutexImpementation : public Guard {
            public:
                MutexImpementation(void);
                virtual ~MutexImpementation(void);
                virtual bool tryLock();
                virtual void unlock();
                virtual void lock();
                MutexImpementation(const MutexImpementation & ) = delete;
                MutexImpementation & operator=(const MutexImpementation & ) = delete;
            private:
                pthread_mutex_t Pmutex;
        };

        class Locker {
            public:
                Locker(Guard & whatToLock);
                ~Locker();
                Locker() = delete;
                Locker(const Locker & ) = delete;
                Locker operator=(const Locker & ) = delete;
            private:
                Guard * locker;
        };
}

#endif