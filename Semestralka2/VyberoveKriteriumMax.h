#pragma once

#include "VyberoveKriterium.h"

template<typename R, typename O>
class VyberoveKriteriumMax : public VyberoveKriterium<R, O>
{
public:

	O* operator()(Table<int, O*>* tabulka) override;

};

template<typename R, typename O>
inline O* VyberoveKriteriumMax<R, O>::operator()(Table<int, O*>* tabulka)
{
	R max;
	bool isFirstIteration = true;
	for (auto item : *tabulka)
	{
		if (isFirstIteration)
		{
			max = (*kriterium_)(item->accessData());
			isFirstIteration = false;
		}
		else
		{
			R novaHodnota = (*kriterium_)(item->accessData());
			if (max < novaHodnota)
			{
				max = novaHodnota;
			}
		}
	}
}
