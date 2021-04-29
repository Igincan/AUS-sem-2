#include "EnumNazov.h"

std::string EnumNazov::daj(TypUzemnejJednotky typ)
{
	switch (typ)
	{
    case TypUzemnejJednotky::KRAJINA:
        return "Krajina";
    case TypUzemnejJednotky::KRAJ:
        return "Kraj";
    case TypUzemnejJednotky::OBVOD:
        return "Obvod";
    case TypUzemnejJednotky::OKRES:
        return "Okres";
    case TypUzemnejJednotky::OBEC:
        return "Obec";
    default:
        throw std::logic_error("EnumNazov::daj: Impossible!");
	}
}
