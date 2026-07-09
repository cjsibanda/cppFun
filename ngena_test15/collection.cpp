#include "collection.h"

#include <sstream>


namespace seneca
{
    //Sets the name of the collection to the string
	Collection::Collection(const std::string& name)
		:
		m_name(name)
	{
	}
    
    //destructor
	Collection::~Collection()
	{
		std::for_each(
			m_items.begin(),
			m_items.end(),
			[](MediaItem* item)
			{
				delete item;
			});
	}

    // a query that returns the name of the collection
	const std::string& Collection::name() const
	{
		return m_name;
	}

    //// a query that returns the number of items in the collection
	size_t Collection::size() const
	{
		return m_items.size();
	}

    /*************************************************************
    * Stores the address of the callback function (observer)
    * into an attribute. This parameter is a pointer to a function
    * that returns void and accepts two parameters; a collection and 
    * an item that has just been added to the collection. This functio
    * is called when an item is added to the collection
    **************************************************************/
	void Collection::setObserver(
		void (*observer)(const Collection&, const MediaItem&)
	)
	{
		m_observer = observer;
	}


    /******************************************************************
    * adds the item to the collection, only if the collection doesn't 
    * contain an item with the same title. If item is already in the 
    * collection, this function deletes the parameter. If the item is
    * added to the collection and an observer has been registered, this
    * operator calls the observer function passing the current object 
    * (*this) and the new item as arguments.
    ******************************************************************/
	Collection& Collection::operator+=(MediaItem* item)
	{
		auto found = std::find_if(
			m_items.begin(),
			m_items.end(),
			[item](MediaItem* current)
			{
				return current->getTitle() == item->getTitle();
			});
		if (found != m_items.end())
		{
			delete item;
			return *this;
		}
		m_items.push_back(item);
		if (m_observer)
		{
			m_observer(*this, *item);
		}
		return *this;
	}


    /*************************************************************
    * retuns the item at index idx
    * if the index is out of range, this operator throws and exception
    * of type std::out_of_range with the message Bad index [IDX]
    * Collection has [SIZE] items
    * Use operator + to concatenate strings
    *************************************************************/
	MediaItem* Collection::operator[](size_t idx) const
	{
		if (idx >= m_items.size())
		{
			throw std::out_of_range(
				"Bad index [" +
				std::to_string(idx) +
				"]. Collection has " +
				std::to_string(m_items.size()) +
				" items."
			);
		}
		return m_items[idx];
	}



    //returns the address of the title "title"
    // if no such item exists, it will return nullptr
	MediaItem* Collection::operator[](const std::string& title) const
	{

		auto result = std::find_if(
			m_items.begin(),
			m_items.end(),
			[&title](MediaItem* item)
			{
				return item->getTitle() == title;
			});


		return result == m_items.end()
			? nullptr
			: *result;

	}



    //remove quotation marks from the beginning/end of the title
    //and summary
	void Collection::removeQuotes()
	{

		std::for_each(
			m_items.begin(),
			m_items.end(),
			[](MediaItem* item)
			{

				auto remove = [](std::string text)
				{

					if (!text.empty() &&
						text.front() == '"')
					{
						text.erase(0, 1);
					}


					if (!text.empty() &&
						text.back() == '"')
					{
						text.pop_back();
					}


					return text;
				};


				item->setTitle(
					remove(item->getTitle())
				);

				item->setSummary(
					remove(item->getSummary())
				);

			});

	}




    //sort in ascending order the collection
    //of items based on the field specified as parameter
	void Collection::sort(const std::string& field)
	{

		if (field == "title")
		{
			std::sort(
				m_items.begin(),
				m_items.end(),
				[](MediaItem* a, MediaItem* b)
				{
					return a->getTitle() < b->getTitle();
				});
		}

		else if (field == "year")
		{
			std::sort(
				m_items.begin(),
				m_items.end(),
				[](MediaItem* a, MediaItem* b)
				{
					return a->getYear() < b->getYear();
				});
		}

	}



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
	)
	{
		for (size_t i = 0; i < collection.size(); ++i)
		{
			out << *collection[i];
		}
		return out;
	}


}