/*
-Retrieving records from a file using input file stream object
-Move and Copy Semantics: Protein Sequence
-Copy Semantics for a class with resource
-Move semantics for a class with a resource
-std::chrono
--> Question: Why is there big difference between copy and move ops
*/
////// FIX //////////////

#include <iostream>
#include <iomanip>
#include <utility>
#include <string>
#include "ProteinDatabase.h"
#include "ProteinDatabase.h"
#include "TimedTask.h"
#include "TimedTask.h"

//check if header guards exist and follow convention
#ifndef SIBANDA_PROTEINTDATABASE_H
   #error "Header guard from 'ProteinDatabase.h' doesn't follow the conventions!"
#endif
#ifndef SIBANDA_TIMEDTASK_H
   #error "The header guard for 'TimedTask.h' doesn't follow the convention!"
#endif

enum ExitCode
{
    SUCCESS,
    ERROR_NO_INPUT_FILE
    ERROR_TOO_MANY_ARGUMENTS,
};

int cout = ExitCode::SUCCESS; //won't compile if headers don't follow conventions

using ArrayOf5_t = size_t[5];

//From notes
void printDatabase(std::string&& lbl, seneca::ProteinDatabase& db, ArrayOf5_t&& indices)
{
	for (auto& idx : indices)
	{
		std::cout << std::setw(40) << lbl << " Protein " << std::setw(5) << idx      << ": ["
		          <<  db.getUID(idx)                                                  << "]["
		          <<  db[idx].size()                                                  << "]["
		          << (db[idx].size() ? db[idx].substr(0, 20) : db[idx])               << "]["
		          << (db[idx].size() ? db[idx].substr(db[idx].size() - 20) : db[idx]) << "]\n";
	}
	std::cout << '\n';
}


int main(int argc, char** argv)
{
    std::cout << "Command Line:\n";
    std::cout << "-----------------\n";
    for (int i = 0; i < argc; ++i)
        std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
    std::cout << "-----------------\n\n";

    if (argc == 1)
    {
        std::cerr << "ERROR: Missing file name!\n";
        return ExitCode::ERROR_NO_INPUT_FILE;
    }
    else if (argc != 2)
    {
        std::cerr << "ERROR: Too many arguments!\n";
        return ExitCode::ERROR_TOO_MANY_ARGUMENTS;
    }

    //redo
    sibanda::TimedTask t;
    {
        t.startClock();
        sibanda::ProteinDatabase protein_DBA;
        t.stopClock();
        t.addTask(" 0-arg Constructor");
        std::cout << " 0-arg Constructor - protein_DBA.size = "
            << std::setw(7) << protein_DBA.size() << " Proteins -> \n";
        printDatabase("(a)", protein_DBA, {0u, 99u, 999u, 9999u, 99999u});

        t.startClock();
        sibanda::ProteinDatabase protein_DBB(argv[1]);
        t.stopClock();
        t.addTask(" 0-arg Constructor");
        std::cout << " 0-arg Constructor - protein_DBA.size = "
             << std::setw(7) << protein_DBA.size() << " Protein -> \n";
        printDatabase("(a)", protein_DBA, {0u, 99u, 999u, 9999u});
        
        t.startClock();
        sibanda::ProteinDatabase protein_DBB(argv[1]);
        t.stopClock();
        t.addTask(" 1-arg constructor");
        std::cout << " 1-arg Constructor - protein_DBB.size = "
                  << std::setw(7) << protein_DBB.size() << " PRoteins -> \n";
        printDatabase("(b)", protein_DBB, {0u, 99u, 999u, protein_DBB.size() - 1u, protein_DBB.size() });

        
        t.startClock();
		sibanda::ProteinDatabase protein_DBC{ protein_DBB };
		t.stopClock();
		t.addTask("  Copy Constructor");
		std::cout << "  Copy Constructor  - protein_DBC.size = "
		          << std::setw(7) << protein_DBC.size() << " Proteins -> \n";
		printDatabase("(c)", protein_DBC, { 0u, 99u, 999u, protein_DBC.size() - 1u, protein_DBC.size() });



		t.startClock();
		protein_DBA = protein_DBB;
		t.stopClock();
		t.addTask("  Copy Assignment");
		std::cout << "  Copy Assignment   - protein_DBA.size = "
			<< std::setw(7) << protein_DBA.size() << " Proteins -> \n";
		printDatabase("(a)", protein_DBA, { 0u, 99u, 999u, protein_DBA.size() - 1u, protein_DBA.size() });



		// if self-assignment is not handled right-> it will crash
		protein_DBA = protein_DBA;

		t.startClock();
		sibanda::ProteinDatabase protein_DBD = std::move(protein_DBA);
		t.stopClock();
		t.addTask("  Move Constructor");
		std::cout << "  Move Constructor  - protein_DBD.size = "
			<< std::setw(7) << protein_DBD.size() << " Proteins -> \n";
		printDatabase("(a)", protein_DBA, { 0u, 99u, 999u, 23011u, 23012u });
		printDatabase("(d)", protein_DBD, { 0u, 99u, 999u, protein_DBD.size() - 1u, protein_DBD.size() });



		{
			// if self-assignment not  handled right -> this will crash
			auto& sameProtein = protein_DBD;
			sameProtein = std::move(protein_DBD);
		}

		t.startClock();
		protein_DBA = std::move(protein_DBD);
		t.stopClock();
		t.addTask("  Move Assignment");
		std::cout << "  Move Assignment   - protein_DBA.size = "
		          << std::setw(7) << protein_DBA.size() << " Proteins -> \n";
		printDatabase("(a)", protein_DBA, { 0u, 99u, 999u, protein_DBA.size() - 1u, protein_DBA.size() });
		printDatabase("(d)", protein_DBD, { 0u, 99u, 999u, 23011u, 23012u });


		
		protein_DBB = {};
		protein_DBC = {};

		t.startClock();
	}
	t.stopClock();
	t.addTask("  Destructor");

	std::cout << t;

	return cout;
    }
}