#pragma once

#include "structures/table/sorted_sequence_table.h"
#include "Kriterium.h"

using namespace structures;

template<typename R, typename O, typename K>
class Filter
{
public:

	/// <returns> Smernik na tabulku. POZOR! Po pouziti treba vymazat! </returns>
	Table<K, O*>* operator()(Table<K, O*>* tabulka);

protected:
	
	Filter(Kriterium<R, O>* kriterium);

	virtual bool splnaFilter(O* objekt) = 0;

	Kriterium<R, O>* kriterium_;

};

template<typename R, typename O, typename K>
inline Table<K, O*>* Filter<R, O, K>::operator()(Table<K, O*>* tabulka)
{
	Table<K, O*>* result = new SortedSequenceTable<K, O*>();
	for (auto item : *tabulka)
	{
		if (splnaFilter(item->accessData()))
		{
			result->insert(item->getKey(), item->accessData());
		}
	}
	return result;
}

template<typename R, typename O, typename K>
inline Filter<R, O, K>::Filter(Kriterium<R, O>* kriterium) :
kriterium_(kriterium)
{
}
