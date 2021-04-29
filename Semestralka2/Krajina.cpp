#include "Krajina.h"

Krajina::Krajina(int kod, std::string nazov, UzemnaJednotka* patriDo) :
UzemnaJednotka(kod, nazov, TypUzemnejJednotky::KRAJINA, patriDo),
vsetkyObce_(nullptr),
vsetkyObceSorted_(new SortedSequenceTable<int, UzemnaJednotka*>())
{
}

Krajina::~Krajina()
{
	if (vsetkyObce_ != nullptr)
	{
		delete vsetkyObce_;
		vsetkyObce_ = nullptr;
	}
	delete vsetkyObceSorted_;
	vsetkyObceSorted_ = nullptr;
}

void Krajina::pridajObec(Obec* obec)
{
	vsetkyObceSorted_->insert(obec->getKod(), obec);
}

void Krajina::skopirujObceDoUnsorted()
{
	if (vsetkyObce_ == nullptr)
	{
		vsetkyObce_ = new UnsortedSequenceTable<int, UzemnaJednotka*>(*vsetkyObceSorted_);
	}
	else
	{
		throw std::logic_error("Krajina::skopirujObceDoUnsorted: Obce su uz skopirovane!");
	}
}

UnsortedSequenceTable<int, UzemnaJednotka*>* Krajina::getVsetkyObce()
{
	return vsetkyObce_;
}

SortedSequenceTable<int, UzemnaJednotka*>* Krajina::getVsetkyObceSorted()
{
	return vsetkyObceSorted_;
}
