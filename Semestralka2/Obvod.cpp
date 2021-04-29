#include "Obvod.h"

Obvod::Obvod(int kod, std::string nazov, UzemnaJednotka* patriDo) :
UzemnaJednotka(kod, nazov, TypUzemnejJednotky::OBVOD, patriDo)
{
}
