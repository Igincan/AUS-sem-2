#pragma once

#include "UzemnaJednotka.h"

class Kraj : public UzemnaJednotka
{
public:
	
	Kraj(int kod, std::string nazov, UzemnaJednotka* patriDo);

};

