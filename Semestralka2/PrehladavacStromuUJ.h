#pragma once

#include "UzemnaJednotka.h"

class PrehladavacStromuUJ
{
public:

	PrehladavacStromuUJ(UzemnaJednotka* aktualneMiesto);
	
	bool maVyssieho();
	bool maNizsich();
	bool existujeNizsie(std::string nazov);
	void chodVyssie();
	void chodNizsie(std::string nazov);
	std::string dajNazovVyssieho();
	Array<std::string*>* dajNazvyNizsich();
	std::string dajNazovAktualneho();
	TypUzemnejJednotky dajTypUzemnejJednotkyAktualneho();
	TypUzemnejJednotky dajTypUzemnejJednotkyVyssieho();
	UzemnaJednotka* dajAktualnuUzemnuJednotku();

private:

	UzemnaJednotka* aktualneMiesto_;

};

