#pragma once

#include "KriteriumUzemnejJednotky.h"

class KUzemnaJednotkaTyp : public KriteriumUzemnejJednotky<TypUzemnejJednotky>
{
public:

	TypUzemnejJednotky operator()(UzemnaJednotka* objekt) override;

};

