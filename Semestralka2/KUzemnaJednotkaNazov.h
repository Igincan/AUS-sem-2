#pragma once

#include "KriteriumUzemnejJednotky.h"

class KUzemnaJednotkaNazov : public KriteriumUzemnejJednotky<std::string>
{
public:
	
	std::string operator()(UzemnaJednotka* objekt) override;

};

