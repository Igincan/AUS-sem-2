#include "Okres.h"

Okres::Okres(int kod, std::string nazov, UzemnaJednotka* patriDo) :
UzemnaJednotka(kod, nazov, TypUzemnejJednotky::OKRES, patriDo)
{
}
