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
        T m_numEntries{0};
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
        inline static std::shared_ptr<Database<T>> m_instance{nullptr};

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
            std::cout << "[" this << "] Database(const std::string&)\n";
            m_filename = filename;

            std::ifstream file(filename);
            if (file.is_open())
            {
              std::string key;
              T value;
              while (m_numeEntries < 20 && file >> key >> value)
              {
                 //Replace underscores with single spaces
                 std::replace(key.begin(), key.end(), '_', ' ');

                 //Decrypt the value inline
                 encryptDecrypt(value);

                 m_keys[m_numEntries] = key;
                 m_values[m_numEntries] = values;
                 ++m_n_numEntries;
              }
              file.close();
            }

        }


        //empty body will specialize later
        void encryptDecrypt(T& value)
        {
            /* nothing */
        }
    public:
      //Disable copy and move ops?
      Database(const Database&) = delete;
      Database& operator=(const Database&) = delete;
      Database(Database&&) = delete;
      Database& operator=(Database&&) = delete;

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
        if (!m_instance)
        {
          //std::make_shared cannot access private constructor directly
          // can pass a custom token
          struct AllocatorToken : public Database<T> {
            AllocatorToken(const std::string& file) : Database<T>(file) {}
          };
          m_instance = std::make_shared<AllocatorToken>(dbFileName); 
        }
        return m_instance;
      }

      /*****************************************************
      * A query that searches in the array of keys
      * for the first parameter
      * if key is found return Err_Status::Err_Success
      * if key is not found, return Err_Status::Err_Notfound
      ******************************************************/
      Err_status GetValue(const std::string& key, T& value) const
      { 
         for (size_t i = 0; i < m_numEntries; ++i)
         {
          if (m_keys[i] == key)
          {
            value = m_values[i];
            return Err_Status::Err_Success;
          }
         }
         return Err_Status::Err_NotFound;
      }

      /*****************************************************************
      * A modifier that receives key & value as parameters
      * if there is space - the capacity of array not reached
      * if there is space, the key/value pair is added and
      * function returns Err_Success. Otherwise, it returns Err_OutOfMemory
      ******************************************************************/
      Err_Status SetValue(const std::string& key, const T& value) 
      {
        if (m_numEntries >= 20)
        {
          return Err_Status::Err_OutOfMemory;
        }

        m_keys[m_numEntries] = key;
        m_values[m_numEntries] = value;
        ++m_numEntries;
        return Err_Status::Err_Success;
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
        std::cout << "[" << this << "] ~Database()\n";

        std::ofstream bkpFile(m_filename + ".bkp.txt");
        if (bkpFile.is_open())
        {
          for (size_t i = 0; i < m_numEntries; ++i)
          {
            T encryptedVal = m_values[i];
            encryptDecrypt(encryptedVal); //RE-encrypt for storage

            bkpFile << std::left << std::setw(25) << m_keys[i]
                    << " -> " << encryptedVal << "\n";
          }
          bkpFile.close();
        }
      }
    };

      //Generic base implementation
      template<typename T>
      void Database<T>::encryptDecrypt(T& value) {/*YNWA*/}

      //specializations
      template<>
      inline void Database<std::string>::encryptDecrypt(std::string& value)
      {
        /**********************************
        fix this pseudo code
        * [foreach character C in the parameter
        *  foreach character K in the secret
        *   C = C ^ K
        ***********************************/
        const char secret[]{ "secret encrytion key "};
        const size_t secretLen = sizeof(secret) - 1;

        for (char& c : value)
        {
          for (size_t i = 0; i < secretLen; ++i)
          {
            c ^= secret[i];
          }

        }

        
      }

      template<>
      inline void Database<long long>::encryptDecrypt(long long& value)
      {
        const char secret[]{ "super secret encryption key" };
        const size_t secretLen = sizeof(secret) - 1;
        char* bytes = reinterpret_cast<char*>(&value);

        /**********************************
        * Fix this pseudo code
        * foreach byte B in the parameter
        *   foreach character K in the secret
        *      B = B ^ K 
        **************************************/
       for (size_t b = 0; b < sizeof(long long); ++b)
       {
          for (size_t i = 0; i < secretLen; ++i)
          {
            bytes[b] ^= secret[i];
          }
        
      }

      
    }
}
#endif

