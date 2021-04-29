#include "Obec.h"

Obec::Obec(int kod, std::string nazov, UzemnaJednotka* patriDo, TypObce typObce, int pocetOkrskov) :
UzemnaJednotka(kod, nazov, TypUzemnejJednotky::OBEC, patriDo),
typObce_(typObce),
pocetOkrskov_(pocetOkrskov),
volebneUcastiOkrskov_(new Array<VolebnaUcast*>(pocetOkrskov_))
{
}

Obec::~Obec()
{
	for (int i = 0; i < static_cast<size_t>(volebneUcastiOkrskov_->size()); i++)
	{
		if ((*volebneUcastiOkrskov_)[i] != nullptr)
		{
			delete (*volebneUcastiOkrskov_)[i];
		}
	}
	delete volebneUcastiOkrskov_;
}

TypObce Obec::getTypObce()
{
	return typObce_;
}

int Obec::getPocetOkrskov()
{
	return pocetOkrskov_;
}

void Obec::setVolebnaUcastOkrsku(int cisloOkrsku, VolebnaUcast* volebnaUcast)
{
	if ((*volebneUcastiOkrskov_)[cisloOkrsku - 1] == nullptr)
	{
		(*volebneUcastiOkrskov_)[cisloOkrsku - 1] = volebnaUcast;
	}
	else
	{
		throw std::logic_error("UzemnaJednotka::setVolebnaUcast: You can't set (*volebneUcastiOkrskov_)[index] twice!");
	}
}

VolebnaUcast* Obec::getVolebnaUcastOkrsku(int index)
{
	return (*volebneUcastiOkrskov_)[index - 1];
}
