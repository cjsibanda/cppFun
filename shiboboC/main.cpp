/***********************************************************************
 tester program
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "TagList.h"
#include "NameTag.h"
using namespace shibobo;
int noOfNames(FILE* fptr) {
   char ch;
   int recs = 0;
   rewind(fptr);
   while(fscanf(fptr, "%c", &ch) == 1) {
      recs += (ch == '\n');
   }
   rewind(fptr);
   return recs;
}
int main() {
   char name[51]{};
   FILE* fptr = fopen("simpsons.txt","r");
   NameTag nt;
   TagList tl(noOfNames(fptr));
   while(fscanf(fptr, "%[^\n]\n", name) == 1) {
      nt.set(name);
      tl.add(nt);
   }
   tl.print();
   fclose(fptr);
   return 0;
}
