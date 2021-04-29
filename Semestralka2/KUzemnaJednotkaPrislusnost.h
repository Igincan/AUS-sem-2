#pragma once

#include "KriteriumUzemnejJednotky.h"

class KUzemnaJednotkaPrislusnost : public KriteriumUzemnejJednotky<bool>
{
public:

	KUzemnaJednotkaPrislusnost(UzemnaJednotka* vyssiCelok);

	bool operator()(UzemnaJednotka* objekt) override;

private:

	UzemnaJednotka* vyssiCelok_;

};

