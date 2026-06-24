#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <string>

namespace seneca
{

    /**********************************************
    * Enumeration to be added to the model
    * It will be used to signal that operation finished
    * ... with success, or some error occured
    ***********************************************/
    enum class Err_Status
    {
        Err_Sucess,
        Err_NotFound,
        Err_OutOfMemory
    };

    /*************************************************************
    * Define a class Database that manages two parrallel arrays
    * ...of keys and an array of values
    * Database class is templated
    * It has one template parameter T representing the type of value
    * 
    **************************************************************/
    template<typename T>
    class Database
    {

        //private members
        //-> a variable representing number of entries in database
        //->statically-allocated of strings representing keys. Size of array is 20
        //->statically-allocated array of objects of type T represinting the value
        //->string representing database file name
        //-> static class variable that will store static
        //->
    public:
      static std::shared_ptr<Databsase<T>>
      {

      }

      //YNWA

      ~Database()
      {
        //YNWA
      }

      template<>
      inline void Database<std::string>::encryptDecrypt(std::string& value)
      {
        const char secret[]{ "secret encrytion key "};

        //encoding & decoding
        //for loop(s)?
      }

      template<>
      inline void Database<long long>::encryptDecrypt(long long& value)
      {
        //YNWA
      }

      template<typename T>
      std::shared_ptr<Database<T>> Database<T>::instance{};
    }
}
#endif

