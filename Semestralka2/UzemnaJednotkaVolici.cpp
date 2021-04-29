#include "KUzemnaJednotkaVolici.h"

int KUzemnaJednotkaVolici::operator()(UzemnaJednotka* objekt)
{
	int pocetZapisanych = 0;
	zrataj(objekt, pocetZapisanych);
	return pocetZapisanych;
}

void KUzemnaJednotkaVolici::zrataj(UzemnaJednotka* UJ, int& pocetZapisanych)
{
	if (UJ->getTypUzemnejJednotky() == TypUzemnejJednotky::OBEC)
	{
		Obec* obec = dynamic_cast<Obec*>(UJ);
		for (int i = 1; i <= obec->getPocetOkrskov(); i++)
		{
			pocetZapisanych += obec->getVolebnaUcastOkrsku(i)->pocetZapisanych_;
		}
	}
	else
	{
		for (auto item : *UJ->getPatriaDonho())
		{
			zrataj(item->accessData(), pocetZapisanych);
		}
	}
}
