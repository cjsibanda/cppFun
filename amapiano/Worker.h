//For educational and testing purposes only
#ifndef SIBANDA_WORKER_H_
#define SIBANDA_WORKER_H_
namespace sibanda {
    class Worker {
        private:
          long workerID{};
          char workerFirstName[51]{};
          char workerLastName[51]{};
          int numberOfDaysWorked{};
          int* numberOfDaysWorked{};
        public: 
          //Constructors ()
          Worker();
          Worker(long);
          Worker(long, const char*, const char*, int, int*);
          Worker(const Worker&);
          const Worker& print() const;
          
          Worker& operator=(const Worker&);

          //Destructor
          ~Worker();
    };
}
#endif