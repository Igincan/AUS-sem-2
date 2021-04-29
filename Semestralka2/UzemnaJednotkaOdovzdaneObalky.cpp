#include "KUzemnaJednotkaOdovzdaneObalky.h"

KUzemnaJednotkaOdovzdaneObalky::KUzemnaJednotkaOdovzdaneObalky(SposobOdovzdania sposobOdovzdania) :
sposobOdovzdania_(sposobOdovzdania)
{
}

int KUzemnaJednotkaOdovzdaneObalky::operator()(UzemnaJednotka* objekt)
{
	int pocetOdovzdanychObalok = 0;
	zrataj(objekt, pocetOdovzdanychObalok);
	return pocetOdovzdanychObalok;
}

void KUzemnaJednotkaOdovzdaneObalky::zrataj(UzemnaJednotka* UJ, int& pocetOdovzdanychObalok)
{
	if (UJ->getTypUzemnejJednotky() == TypUzemnejJednotky::OBEC)
	{
		Obec* obec = dynamic_cast<Obec*>(UJ);
		for (int i = 1; i <= obec->getPocetOkrskov(); i++)
		{
			switch (sposobOdovzdania_)
			{
			case SposobOdovzdania::OSOBNE:
				pocetOdovzdanychObalok += obec->getVolebnaUcastOkrsku(i)->pocetObalkovych_;
				break;
			case SposobOdovzdania::Z_CUDZINY:
				pocetOdovzdanychObalok += obec->getVolebnaUcastOkrsku(i)->pocetZCudziny_;
				break;
			case SposobOdovzdania::SPOLU:
				pocetOdovzdanychObalok += obec->getVolebnaUcastOkrsku(i)->pocetPlatnychSpolu_;
				break;
			}
		}
	}
	else
	{
		for (auto item : *UJ->getPatriaDonho())
		{
			zrataj(item->accessData(), pocetOdovzdanychObalok);
		}
	}
}
