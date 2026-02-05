// 10 -> 17
// 10 -> 17
#ifndef IGWIJO_GRAFT_
#define IGWIJO_GRAFT_
namespace igwijo {
  //graft struture definition
  struct Graft {
    long workerID{};
    char workerFirstName[41]{};
    char workerLastName[41]{};
    //Function prototypes
    void set(long, const char*, const char*);
    void print() const;
  };

  
} 

#endif // !IGWIJO_GRAFT_

