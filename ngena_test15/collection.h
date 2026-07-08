#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "mediaItem.h"


namespace seneca
{

    /**********************************************************************************
    * Purpose of collection module is to manage collection of media items
    * Class will take ownership of ALL MediaItem objects provided by the client
    * and becomes responsible to manage their life.
    * It is assumed that, all pointers received from the client store the address
    * of dynamically allocated objects.
    * When a new item is added, this class informs the client using a callback function
    ************************************************************************************/

	class Collection
	{
		std::string m_name{}; //name of collection

		std::vector<MediaItem*> m_items{}; //an STL container to store media items

        //pointer to function the returns void
        //receives two parameters of type const Collection& and const MediaItem& in that order
        // This is the observer function
		void (*m_observer)(const Collection&, const MediaItem&) { nullptr };


	public:
        //Sets the name of the collection to the string
		Collection(const std::string& name);

        //destructor
		~Collection();

        //<-------------------------------------
        //This class does NOT support copy/move ops
        // delete all of them
        //------------------------------------>>
		Collection(const Collection&) = delete;
		Collection& operator=(const Collection&) = delete;

		Collection(Collection&&) = delete;
		Collection& operator=(Collection&&) = delete;


        // a query that returns the name of the collection
		const std::string& name() const;

        // a query that returns the number of items in the collection
		size_t size() const;

        /*************************************************************
        * Stores the address of the callback function (observer)
        * into an attribute. This parameter is a pointer to a function
        * that returns void and accepts two parameters; a collection and 
        * an item that has just been added to the collection. This functio
        * is called when an item is added to the collection
        **************************************************************/
		void setObserver(
			void (*observer)(const Collection&, const MediaItem&)
		);

        /******************************************************************
        * adds the item to the collection, only if the collection doesn't 
        * contain an item with the same title. If item is already in the 
        * collection, this function deletes the parameter. If the item is
        * added to the collection and an observer has been registered, this
        * operator calls the observer function passing the current object 
        * (*this) and the new item as arguments.
        ******************************************************************/
		Collection& operator+=(MediaItem* item);


        /*************************************************************
        * retuns the item at index idx
        * if the index is out of range, this operator throws and exception
        * of type std::out_of_range with the message Bad index [IDX]
        * Collection has [SIZE] items
        * Use operator + to concatenate strings
        *************************************************************/
		MediaItem* operator[](size_t idx) const;


        //returns the address of the title "title"
        // if no such item exists, it will return nullptr
		MediaItem* operator[](const std::string& title) const;

       //remove quotation marks from the beginning/end of the title
       //and summary
		void removeQuotes();

       //sort in ascending order the collection
       //of items based on the field specified as parameter
		void sort(const std::string& field);



	};

    /****************************************************
    *overload the insertion operator to insert the content
    * of a Collection object into an ostream object. Iterate
    *  over all elements in the collection and insert each 
    *  one into the ostream object (do not add newlines).
    ****
    * Important: The class Collection should have no
    *  knowledge of the custom types you have defined: 
    * Book, Movie, TvShow, SpellChecker, and Settings.
    *****************************************************/
	std::ostream& operator<<(
		std::ostream& out,
		const Collection& collection
	);


}

#endif