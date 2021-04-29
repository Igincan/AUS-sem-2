#pragma once

#include <iostream>
#include "UzemnaJednotka.h"
#include "TypObce.h"
#include "VolebnaUcast.h"

class Obec : public UzemnaJednotka
{
public:

	Obec(int kod, std::string nazov, UzemnaJednotka* patriDo, TypObce typObce, int pocetOkrskov);
	~Obec();

	TypObce getTypObce();
	int getPocetOkrskov();

	/// <param name = "index"> POZOR! Indexuje sa od 1! </param>
	void setVolebnaUcastOkrsku(int index, VolebnaUcast* volebnaUcast);
	/// <param name = "index"> POZOR! Indexuje sa od 1! </param>
	VolebnaUcast* getVolebnaUcastOkrsku(int index);

private:
	
	TypObce typObce_;
	int pocetOkrskov_;
	Array<VolebnaUcast*>* volebneUcastiOkrskov_;

};

