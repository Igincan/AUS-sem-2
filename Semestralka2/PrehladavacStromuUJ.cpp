#include "PrehladavacStromuUJ.h"

PrehladavacStromuUJ::PrehladavacStromuUJ(UzemnaJednotka* aktualneMiesto) :
aktualneMiesto_(aktualneMiesto)
{
}

bool PrehladavacStromuUJ::maVyssieho()
{
	return aktualneMiesto_->getPatriDo() != nullptr;
}

bool PrehladavacStromuUJ::maNizsich()
{
	if (aktualneMiesto_->getPatriaDonho() != nullptr)
	{
		return !aktualneMiesto_->getPatriaDonho()->isEmpty();
	}
	else
	{
		return false;
	}
}

bool PrehladavacStromuUJ::existujeNizsie(std::string nazov)
{
	return aktualneMiesto_->getPatriaDonho()->containsKey(nazov);
}

void PrehladavacStromuUJ::chodVyssie()
{
	if (aktualneMiesto_->getPatriDo() != nullptr)
	{
		aktualneMiesto_ = aktualneMiesto_->getPatriDo();
	}
	else
	{
		throw std::logic_error("PrehladavacStromuUJ::chodVyssie: Neexistuje vyssie!");
	}
}

void PrehladavacStromuUJ::chodNizsie(std::string nazov)
{
	aktualneMiesto_->getPatriaDonho()->tryFind(nazov, aktualneMiesto_);
}

std::string PrehladavacStromuUJ::dajNazovVyssieho()
{
	return aktualneMiesto_->getPatriDo()->getNazov();
}

Array<std::string*>* PrehladavacStromuUJ::dajNazvyNizsich()
{
	Array<std::string*>* result = new Array<std::string*>(aktualneMiesto_->getPatriaDonho()->size());
	int index = 0;
	for (auto item : *aktualneMiesto_->getPatriaDonho())
	{
		(*result)[index++] = new std::string(item->getKey());
	}
	return result;
}

std::string PrehladavacStromuUJ::dajNazovAktualneho()
{
	return aktualneMiesto_->getNazov();
}

TypUzemnejJednotky PrehladavacStromuUJ::dajTypUzemnejJednotkyAktualneho()
{
	return aktualneMiesto_->getTypUzemnejJednotky();
}

TypUzemnejJednotky PrehladavacStromuUJ::dajTypUzemnejJednotkyVyssieho()
{
	return aktualneMiesto_->getPatriDo()->getTypUzemnejJednotky();
}

UzemnaJednotka* PrehladavacStromuUJ::dajAktualnuUzemnuJednotku()
{
	return aktualneMiesto_;
}
