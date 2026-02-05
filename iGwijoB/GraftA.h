//ref 12
#ifndef IGWIJO_GRAFTA_
#define IGWIJO_GRAFTA_
namespace igwijo {
    class Graft {
      private:
        long workerID{};
        char workerFirstName[41]{};
        char workerLastName[41]{};
      public:
        void set(long, const char*, const char*);
        void print() const;
    };

    void printTheWorker(const Graft&);
    
    void setTheWorker(Graft&, long, const char*, const char*);
}

#endif // !IGWIJO_GRAFTA_

