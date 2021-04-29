#include "UzemnaJednotka.h"

UzemnaJednotka::UzemnaJednotka(int kod, std::string nazov, TypUzemnejJednotky typUzemnehoCelku, UzemnaJednotka* patriDo) :
kod_(kod),
nazov_(nazov),
typUzemnehoCelku_(typUzemnehoCelku),
patriDo_(patriDo),
patriaDonho_(new SortedSequenceTable<std::string, UzemnaJednotka*>()),
patriaDonhoUnsorted_(new UnsortedSequenceTable<int, UzemnaJednotka*>())
{
}

UzemnaJednotka::~UzemnaJednotka()
{
	for (auto item : *patriaDonho_)
	{
		delete item->accessData();
	}
	delete patriaDonho_;
	patriaDonho_ = nullptr;
	delete patriaDonhoUnsorted_;
	patriaDonhoUnsorted_ = nullptr;
}

void UzemnaJednotka::pridajDonho(UzemnaJednotka* UJ)
{
	patriaDonho_->insert(UJ->getNazov(), UJ);
	patriaDonhoUnsorted_->insert(UJ->getKod(), UJ);
}

std::string UzemnaJednotka::getNazov()
{
	return nazov_;
}

int UzemnaJednotka::getKod()
{
	return kod_;
}

TypUzemnejJednotky UzemnaJednotka::getTypUzemnejJednotky()
{
	return typUzemnehoCelku_;
}

UzemnaJednotka* UzemnaJednotka::getPatriDo()
{
	return patriDo_;
}

SortedSequenceTable<std::string, UzemnaJednotka*>* UzemnaJednotka::getPatriaDonho()
{
	return patriaDonho_;
}

UnsortedSequenceTable<int, UzemnaJednotka*>* UzemnaJednotka::getPatriaDonhoUnsorted()
{
	return patriaDonhoUnsorted_;
}
