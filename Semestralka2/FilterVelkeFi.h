#pragma once

#include "Filter.h"

template<typename R, typename O, typename K>
class FilterVelkeFi : public Filter<R, O, K>
{
public:

	FilterVelkeFi(Kriterium<R, O>* kriterium, R alpha, R beta);

private:

	bool splnaFilter(O* objekt) override;

	R alpha_;
	R beta_;

};

template<typename R, typename O, typename K>
inline FilterVelkeFi<R, O, K>::FilterVelkeFi(Kriterium<R, O>* kriterium, R alpha, R beta) :
	Filter<R, O, K>(kriterium),
	alpha_(alpha),
	beta_(beta)
{
}

template<typename R, typename O, typename K>
inline bool FilterVelkeFi<R, O, K>::splnaFilter(O* objekt)
{
	R hodnota = (*this->kriterium_)(objekt);
	return alpha_ <= hodnota && hodnota <= beta_;
}
