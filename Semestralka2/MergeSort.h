#pragma once

#include "sort.h"
#include "structures/queue/explicit_queue.h"

template <typename K, typename T, typename R>
class MergeSort : public Sort<K, T, R>
{
public:

	MergeSort();
	~MergeSort();

private:

	void utried(UnsortedSequenceTable<K, T*>* tabulka, Kriterium<R, T>* kriterium, bool vzostupne) override;

	void rozdel(int n);
	void spoj(int n);

	Kriterium<R, T>* kriterium_;
	bool vzostupne_;
	Queue<TableItem<K, T*>*>* frontRozdel1_;
	Queue<TableItem<K, T*>*>* frontRozdel2_;
	Queue<TableItem<K, T*>*>* frontSpoj_;

};

template<typename K, typename T, typename R>
inline MergeSort<K, T, R>::MergeSort() :
kriterium_(nullptr),
vzostupne_(false),
frontRozdel1_(new ExplicitQueue<TableItem<K, T*>*>()),
frontRozdel2_(new ExplicitQueue<TableItem<K, T*>*>()),
frontSpoj_(new ExplicitQueue<TableItem<K, T*>*>())
{
}

template<typename K, typename T, typename R>
inline MergeSort<K, T, R>::~MergeSort()
{
	delete frontRozdel1_;
	frontRozdel1_ = nullptr;
	delete frontRozdel2_;
	frontRozdel2_ = nullptr;
	delete frontSpoj_;
	frontSpoj_ = nullptr;
}

template<typename K, typename T, typename R>
inline void MergeSort<K, T, R>::utried(UnsortedSequenceTable<K, T*>* tabulka, Kriterium<R, T>* kriterium, bool vzostupne)
{
	kriterium_ = kriterium;
	vzostupne_ = vzostupne;
	for (auto item : *tabulka)
	{
		frontSpoj_->push(new TableItem<K, T*>(item->getKey(), item->accessData()));
	}
	int i = 1;
	while (i < tabulka->size())
	{
		rozdel(i);
		spoj(i);
		i *= 2;
	}
	rozdel(i);
	spoj(i);
	tabulka->clear();
	while (!frontSpoj_->isEmpty())
	{
		TableItem<K, T*>* item = frontSpoj_->pop();
		tabulka->insert(item->getKey(), item->accessData());
		delete item;
	}
}

template<typename K, typename T, typename R>
inline void MergeSort<K, T, R>::rozdel(int n)
{
	int pocet = 0;
	bool prvy = true;
	while (!frontSpoj_->isEmpty())
	{
		if (pocet % n == 0)
		{
			pocet = 0;
			prvy = !prvy;
		}
		if (prvy)
		{
			frontRozdel1_->push(frontSpoj_->pop());
		}
		else
		{
			frontRozdel2_->push(frontSpoj_->pop());
		}
		pocet++;
	}
}

template<typename K, typename T, typename R>
inline void MergeSort<K, T, R>::spoj(int n)
{
	int prvych = 0;
	int druhych = 0;
	do
	{
		if (prvych == 0 && druhych == 0)
		{
			prvych = n <= static_cast<int>(frontRozdel1_->size()) ? n : static_cast<int>(frontRozdel1_->size());
			druhych = n <= static_cast<int>(frontRozdel2_->size()) ? n : static_cast<int>(frontRozdel2_->size());
		}
		R hodnota1;
		bool hodnota1JeNull = true;
		if (prvych > 0)
		{
			hodnota1 = (*kriterium_)(frontRozdel1_->peek()->accessData());
			hodnota1JeNull = false;
		}
		R hodnota2;
		bool hodnota2JeNull = true;
		if (druhych > 0)
		{
			hodnota2 = (*kriterium_)(frontRozdel2_->peek()->accessData());
			hodnota2JeNull = false;
		}
		if (!hodnota1JeNull && !hodnota2JeNull)
		{
			if (this->porovnaj(hodnota1, hodnota2, vzostupne_) < 0)
			{
				prvych--;
				frontSpoj_->push(frontRozdel1_->pop());
			}
			else
			{
				druhych--;
				frontSpoj_->push(frontRozdel2_->pop());
			}
		}
		else
		{
			if (!hodnota1JeNull)
			{
				prvych--;
				frontSpoj_->push(frontRozdel1_->pop());
			}
			else if (!hodnota2JeNull)
			{
				druhych--;
				frontSpoj_->push(frontRozdel2_->pop());
			}
		}
	} while ((!frontRozdel1_->isEmpty()) || (!frontRozdel2_->isEmpty()));
}
