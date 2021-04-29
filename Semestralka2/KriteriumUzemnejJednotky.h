#pragma once

#include "Kriterium.h"
#include "UzemnaJednotka.h"

template<typename R>
class KriteriumUzemnejJednotky : public Kriterium<R, UzemnaJednotka>
{
public:

	virtual R operator()(UzemnaJednotka* objekt) override = 0;

};
