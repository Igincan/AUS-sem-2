#pragma once

#include "structures/table/table.h"
#include "Kriterium.h"

using namespace structures;

template<typename R, typename O>
class VyberoveKriterium
{
public:

	virtual O* operator()(Table<int, O*>* tabulka) = 0;

protected:

	VyberoveKriterium(Kriterium<R, O>* kriterium);

	Kriterium<R, O>* kriterium_;

};

template<typename R, typename O>
inline VyberoveKriterium<R, O>::VyberoveKriterium(Kriterium<R, O>* kriterium) :
kriterium_(kriterium)
{
}
