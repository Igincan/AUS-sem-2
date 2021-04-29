#pragma once

#include "sort.h"

template <typename K, typename T, typename R>
class BubbleSort : public Sort<K, T, R>
{
private:

	void utried(UnsortedSequenceTable<K, T*>* tabulka, Kriterium<R, T>* kriterium, bool vzostupne) override;

};

template<typename K, typename T, typename R>
inline void BubbleSort<K, T, R>::utried(UnsortedSequenceTable<K, T*>* tabulka, Kriterium<R, T>* kriterium, bool vzostupne)
{
	bool change = false;
	do
	{
		change = false;
		for (int i = 0; i < static_cast<int>(tabulka->size()) - 1; i++)
		{
			if (this->porovnaj((*kriterium)(tabulka->getItemAtIndex(i).accessData()), (*kriterium)(tabulka->getItemAtIndex(i + 1).accessData()), vzostupne) > 0)
			{
				tabulka->swap(i, i + 1);
				change = true;
			}
		}
	} while (change);
}