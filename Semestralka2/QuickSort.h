#pragma once

#include "sort.h"

template <typename K, typename T, typename R>
class QuickSort : public Sort<K, T, R>
{
private:

	void utried(UnsortedSequenceTable<K, T*>* tabulka, Kriterium<R, T>* kriterium, bool vzostupne) override;
	void quick(int min, int max);

	UnsortedSequenceTable<K, T*>* tabulka_;
	Kriterium<R, T>* kriterium_;
	bool vzostupne_;

};

template<typename K, typename T, typename R>
inline void QuickSort<K, T, R>::utried(UnsortedSequenceTable<K, T*>* tabulka, Kriterium<R, T>* kriterium, bool vzostupne)
{
	tabulka_ = tabulka;
	kriterium_ = kriterium;
	vzostupne_ = vzostupne;

	quick(0, tabulka->size() - 1);
}

template<typename K, typename T, typename R>
inline void QuickSort<K, T, R>::quick(int min, int max)
{
	R pivot = (*kriterium_)(tabulka_->getItemAtIndex((min + max) / 2).accessData());
	int lavy = min;
	int pravy = max;
	do
	{
		//while (this->porovnaj((*kriterium_)(tabulka_->getItemAtIndex(lavy).accessData()), pivot, vzostupne_) < 0)
		while (tabulka_->getItemAtIndex(lavy).getKey() < pivot)
		{
			lavy++;
		}
		//while (this->porovnaj((*kriterium_)(tabulka_->getItemAtIndex(pravy).accessData()), pivot, vzostupne_) > 0)
		while (tabulka_->getItemAtIndex(lavy).getKey() > pivot)
		{
			pravy--;
		}
		if (lavy <= pravy)
		{
			tabulka_->swap(lavy, pravy);
			lavy++;
			pravy++;
		}
	} while (lavy <= pravy);
	if (min < pravy)
	{
		quick(min, pravy);
	}
	if (lavy < max)
	{
		quick(lavy, max);
	}
}
