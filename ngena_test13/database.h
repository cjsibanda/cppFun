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
        T m_numEntries;
        std::string m_keys[20]{};
        std::T m_values[20]{};
        std::string m_filename;
        //-------------------------------------------->
        // A class variable (a static attribute) 
        // that will store the address of the one-and-only
        //instance of type Database
        // why is std::sharedPtr used?
        // why is std::unique_ptr NOT a good choice?
        //<--------------------------------------------
        Database(std::sharedPtr);
        /****************************************************************
        * A private constructor to prevent client from instatiating class
        * Prints to the screen the address of the current instance and prototype
        * Opens file and reads the key/value paris into the attributes
        * Assumes the file is correct and exists
        * Replaces any underscore character (_) that appears
        * .. in the keys with a single space before storing it into attributes
        * decrypts the value loaded from the database file by calling the
        * encryptDecrypt() function and passing the value as a parameter
        ******************************************************************/
        Database(const std::string& filename) 
        {
            ///work on this...
            std::cout << "The Database file?"
            std::ifstream myfile(filename);
            if (myfile.is_open())
            {
                m_numEntries = 0;
                while(!myfile.eof() && numEntries < MAX_ENTRIES)
                {
                    //do something
                    //do something else
                    ++m_numEntries;
                }
                myfile.close();
            }
        }
        //empty body will specialize later
        void encryptDecrypt(T& value)
        {
            /* nothing */
        }
    public:
      /**************************************************
      *  A class function that will provide to the client
      * ... the one-and-only object of this type that is
      * allowed to exist
      * receives filename representing string as parameter
      * returbs static attribute if Database class instantiated
      * creates instance of type Database if NOT instatiated 
      ****************************************************/
      static std::shared_ptr<Databsase<T>> getInstance(const std::string& dbFileName)
      {
        // 
      }

      /*****************************************************
      * A query that searches in the array of keys
      * for the first parameter
      * if key is found return Err_Status::Err_Success
      * if key is not found, return Err_Status::Err_Notfound
      ******************************************************/
      Err_status GetValue(const std::string& key, T& value)
      { 
         //   
      }

      /*****************************************************************
      * A modifier that receives key & value as parameters
      * if there is space - the capacity of array not reached
      * if there is space, the key/value pair is added and
      * function returns Err_Success. Otherwise, it returns Err_OutOfMemory
      ******************************************************************/
      Err_Status SetValue(const std::string& key, const T& value) 
      {
        //
      }


     /*********************************************************
     * Destructor that...
     * Prints to the screen the address of the current instance
     * and the prototype of the destructor
     * iterates over the database content and creates a database
     * backup in a separate file.
     * The backup file name will be the input file name with
     * the string .bkp.txt appended to it
     * Before saving a value into a backup database file, call
     * the encryptDecrypt() function, passing the value as a parameter
     * --> the format of this file is:
     *     KEY -> ENCRYPTED_VALUE
     *     KEY -> ENCRYPTED_VALUE
     *     KEY -> ENCRYPTED_VALUE
     *     ...
     ***********************************************************/
      ~Database()
      {
        //YNWA
      }

      //specializations
      template<>
      inline void Database<std::string>::encryptDecrypt(std::string& value)
      {
        const char secret[]{ "secret encrytion key "};
        
        //fix this pseudo code
        foreach character C in the parameter
          foreach character K in the secret
            C = C ^ K
      }

      template<>
      inline void Database<long long>::encryptDecrypt(long long& value)
      {
        const char secret[]{ "super secret encryption key" };

        foreach byte B in the parameter
          foreach character K in the secret
             B = B ^ K 
      }

      template<typename T>
      std::shared_ptr<Database<T>> Database<T>::instance{};
    }
}
#endif

