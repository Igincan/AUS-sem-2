#include "KUzemnaJednotkaUcast.h"

double KUzemnaJednotkaUcast::operator()(UzemnaJednotka* objekt)
{
	int pocetZapisanych = 0;
	int pocetZucastnenych = 0;

	zrataj(objekt, pocetZapisanych, pocetZucastnenych);

	if (pocetZapisanych > 0)
	{
		return (static_cast<double>(pocetZucastnenych) / pocetZapisanych) * 100;
	}
	else
	{
		return -1;
	}
}

void KUzemnaJednotkaUcast::zrataj(UzemnaJednotka* UJ, int& pocetZapisanych, int& pocetZucastnenych)
{
	if (UJ->getTypUzemnejJednotky() == TypUzemnejJednotky::OBEC)
	{
		Obec* obec = dynamic_cast<Obec*>(UJ);
		for (int i = 1; i <= obec->getPocetOkrskov(); i++)
		{
			pocetZapisanych += obec->getVolebnaUcastOkrsku(i)->pocetZapisanych_;
			pocetZucastnenych += obec->getVolebnaUcastOkrsku(i)->pocetZucastnenych_;
		}
	}
	else
	{
		for (auto item : *UJ->getPatriaDonho())
		{
			zrataj(item->accessData(), pocetZapisanych, pocetZucastnenych);
		}
	}
}
