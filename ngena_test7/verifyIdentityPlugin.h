#ifndef SENECA_VERIFYIDENTITYPLUGIN_H
#define SENECA_VERIFYIDENTITYPLUGIN_H
#include <string>
#include "plugin.h"

namespace seneca
{
   constexpr size_t CAPACITY = 10u;

   /****************************************
   * class is derived from plugin
   * -> representing a plugin that simulates
   * the verification of the sender as trusted person
   * the collection of trusted senders is loaded from a file
   ******************************************/
   class VerifyIdentityPlugin : public Plugin
   {
        //statically allocated array
        //collection of email addresses from file
        std::string m_users[CAPACITY];
    public:
        //loads the file specified as parameter
        VerifyIdentityPlugin(const  char* filename);
        //checks if email comes from trusted source
        void operator()(Message& msg) override;
        //prints the messege to the screen
        void showStats() const override;

   }
}
#