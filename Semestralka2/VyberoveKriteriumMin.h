#pragma once

#include "VyberoveKriterium.h"

template<typename R, typename O>
class VyberoveKriteriumMin : public VyberoveKriterium<R, O>
{
public:

	O* operator()(Table<int, O*>* tabulka) override;

};

template<typename R, typename O>
inline O* VyberoveKriteriumMin<R, O>::operator()(Table<int, O*>* tabulka)
{
	R min;
	bool isFirstIteration = true;
	for (auto item : *tabulka)
	{
		if (isFirstIteration)
		{
			min = (*kriterium_)(item->accessData());
			isFirstIteration = false;
		}
		else
		{
			R novaHodnota = (*kriterium_)(item->accessData());
			if (min > novaHodnota)
			{
				min = novaHodnota;
			}
		}
	}
}
