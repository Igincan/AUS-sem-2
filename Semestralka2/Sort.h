#pragma once

#include "structures/table/unsorted_sequence_table.h"
#include "Kriterium.h"

using namespace structures;

template <typename K, typename T, typename R>
class Sort
{
public:

	void operator()(UnsortedSequenceTable<K, T*>* tabulka, Kriterium<R, T>* kriterium, bool vzostupne);

protected:

	virtual void utried(UnsortedSequenceTable<K, T*>* tabulka, Kriterium<R, T>* kriterium, bool vzostupne) = 0;
	int porovnaj(R hodnota1, R hodnota2, bool vzostupne);

};

template<typename K, typename T, typename R>
inline void Sort<K, T, R>::operator()(UnsortedSequenceTable<K, T*>* tabulka, Kriterium<R, T>* kriterium, bool vzostupne)
{
	utried(tabulka, kriterium, vzostupne);
}

template<typename K, typename T, typename R>
inline int Sort<K, T, R>::porovnaj(R hodnota1, R hodnota2, bool vzostupne)
{
	if (vzostupne)
	{
		return hodnota1 > hodnota2 ? 1 : hodnota1 < hodnota2 ? -1 : 0;
	}
	else
	{
		return hodnota1 > hodnota2 ? -1 : hodnota1 < hodnota2 ? 1 : 0;
	}
}
