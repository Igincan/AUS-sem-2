#pragma once

#include "UzemnaJednotka.h"

class Okres : public UzemnaJednotka
{
public:

	Okres(int kod, std::string nazov, UzemnaJednotka* patriDo);

};

