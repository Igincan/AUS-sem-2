#pragma once

#include <string>
#include <iostream>
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"
#include "TypUzemnejJednotky.h"
#include "EnumNazov.h"

using namespace structures;

class UzemnaJednotka
{
protected:

	UzemnaJednotka(int kod, std::string nazov, TypUzemnejJednotky typUzemnehoCelku, UzemnaJednotka* patriDo);

	int kod_;
	std::string nazov_;
	TypUzemnejJednotky typUzemnehoCelku_;
	UzemnaJednotka* patriDo_;
	SortedSequenceTable<std::string, UzemnaJednotka*>* patriaDonho_;
	UnsortedSequenceTable<int, UzemnaJednotka*>* patriaDonhoUnsorted_;

public:

	virtual ~UzemnaJednotka();

	void pridajDonho(UzemnaJednotka* UJ);
	std::string getNazov();
	int getKod();
	TypUzemnejJednotky getTypUzemnejJednotky();
	UzemnaJednotka* getPatriDo();
	SortedSequenceTable<std::string, UzemnaJednotka*>* getPatriaDonho();
	UnsortedSequenceTable<int, UzemnaJednotka*>* getPatriaDonhoUnsorted();

};

