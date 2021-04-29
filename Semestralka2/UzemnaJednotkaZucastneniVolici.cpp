#include "KUzemnaJednotkaZucastneniVolici.h"

int KUzemnaJednotkaZucastneniVolici::operator()(UzemnaJednotka* objekt)
{
	int pocetZucastnenych = 0;
	zrataj(objekt, pocetZucastnenych);
	return pocetZucastnenych;
}

void KUzemnaJednotkaZucastneniVolici::zrataj(UzemnaJednotka* UJ, int& pocetZucastnenych)
{
	if (UJ->getTypUzemnejJednotky() == TypUzemnejJednotky::OBEC)
	{
		Obec* obec = dynamic_cast<Obec*>(UJ);
		for (int i = 1; i <= obec->getPocetOkrskov(); i++)
		{
			pocetZucastnenych += obec->getVolebnaUcastOkrsku(i)->pocetZucastnenych_;
		}
	}
	else
	{
		for (auto item : *UJ->getPatriaDonho())
		{
			zrataj(item->accessData(), pocetZucastnenych);
		}
	}
}
