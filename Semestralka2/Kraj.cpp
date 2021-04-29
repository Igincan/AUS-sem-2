#include "Kraj.h"

Kraj::Kraj(int kod, std::string nazov, UzemnaJednotka* patriDo) :
UzemnaJednotka(kod, nazov, TypUzemnejJednotky::KRAJ, patriDo)
{
}
