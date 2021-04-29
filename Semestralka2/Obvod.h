#pragma once

#include "UzemnaJednotka.h"

class Obvod : public UzemnaJednotka
{
public:

	Obvod(int kod, std::string nazov, UzemnaJednotka* patriDo);

};

