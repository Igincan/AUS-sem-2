#pragma once

#include "UzemnaJednotka.h"
#include "Obec.h"

class Krajina : public UzemnaJednotka
{
public:

	Krajina(int kod, std::string nazov, UzemnaJednotka* patriDo);
	~Krajina();

	void pridajObec(Obec* obec);
	void skopirujObceDoUnsorted();
	UnsortedSequenceTable<int, UzemnaJednotka*>* getVsetkyObce();
	SortedSequenceTable<int, UzemnaJednotka*>* getVsetkyObceSorted();

private:

	UnsortedSequenceTable<int, UzemnaJednotka*>* vsetkyObce_;
	SortedSequenceTable<int, UzemnaJednotka*>* vsetkyObceSorted_;

};

