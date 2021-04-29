#pragma once

#include "Filter.h"

template<typename R, typename O, typename K>
class FilterMaleFi : public Filter<R, O, K>
{
public:

	FilterMaleFi(Kriterium<R, O>* kriterium, R alpha);

private:

	bool splnaFilter(O* objekt) override;

	R alpha_;

};

template<typename R, typename O, typename K>
inline FilterMaleFi<R, O, K>::FilterMaleFi(Kriterium<R, O>* kriterium, R alpha) :
Filter<R, O, K>(kriterium),
alpha_(alpha)
{
}

template<typename R, typename O, typename K>
inline bool FilterMaleFi<R, O, K>::splnaFilter(O* objekt)
{
	return alpha_ == (*this->kriterium_)(objekt);
}
