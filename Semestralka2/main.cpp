#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include "structures/heap_monitor.h"
#include "structures/table/unsorted_sequence_table.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "Krajina.h"
#include "Kraj.h"
#include "Okres.h"
#include "Obec.h"
#include "Obvod.h"
#include "PrehladavacStromuUJ.h"
#include "EnumNazov.h"
#include "KUzemnaJednotkaNazov.h"
#include "KUzemnaJednotkaTyp.h"
#include "KUzemnaJednotkaPrislusnost.h"
#include "FilterMaleFi.h"
#include "KUzemnaJednotkaUcast.h"
#include "KUzemnaJednotkaVolici.h"
#include "KUzemnaJednotkaZucastneniVolici.h"
#include "KUzemnaJednotkaOdovzdaneObalky.h"
#include "FUzemnaJednotkaNazov.h"
#include "FUzemnaJednotkaUcast.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "KUzemnaJednotkaPodielPlatnychHlasov.h"
#include "FUzemnaJednotkaVolici.h"
#include "FUzemnaJednotkaTyp.h"
#include "FUzemnaJednotkaPrislusnost.h"

using namespace structures;

UzemnaJednotka* slovensko_ = new Krajina(1, "Slovensko", nullptr);
UnsortedSequenceTable<int, UzemnaJednotka*>* vsetkyUJ_ = nullptr;
SortedSequenceTable<int, UzemnaJednotka*>* vsetkyUJSorted_ = new SortedSequenceTable<int, UzemnaJednotka*>();
int indexVsetkychUJ_ = 0;

void inicializujKonzolu()
{
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);
}

int dajPocetRiadkovVSubore(std::string nazovSuboru)
{
	std::string riadok;
	std::ifstream subor(nazovSuboru);
	int pocetRiadkov = 0;
	if (subor.is_open())
	{
		while (std::getline(subor, riadok))
		{
			pocetRiadkov++;
		}
		subor.close();
	}
	return pocetRiadkov;
}

void spracujZaznamUzemnejTabulky(Array<std::string*>& udaje)
{
	if (!slovensko_->getPatriaDonho()->containsKey(*udaje[1]))
	{
		Kraj* novyKraj = new Kraj(std::stoi(*udaje[0]), *udaje[1], slovensko_);
		slovensko_->pridajDonho(novyKraj);
		vsetkyUJSorted_->insert(++indexVsetkychUJ_, novyKraj);
	}

	UzemnaJednotka* kraj;
	slovensko_->getPatriaDonho()->tryFind(*udaje[1], kraj);
	if (!kraj->getPatriaDonho()->containsKey(*udaje[3]))
	{
		Obvod* novyObvod = new Obvod(std::stoi(*udaje[2]), *udaje[3], kraj);
		kraj->pridajDonho(novyObvod);
		vsetkyUJSorted_->insert(++indexVsetkychUJ_, novyObvod);
	}

	UzemnaJednotka* obvod;
	kraj->getPatriaDonho()->tryFind(*udaje[3], obvod);
	if (!obvod->getPatriaDonho()->containsKey(*udaje[5]))
	{
		Okres* novyOkres = new Okres(std::stoi(*udaje[4]), *udaje[5], obvod);
		obvod->pridajDonho(novyOkres);
		vsetkyUJSorted_->insert(++indexVsetkychUJ_, novyOkres);
	}

	UzemnaJednotka* okres;
	obvod->getPatriaDonho()->tryFind(*udaje[5], okres);
	if (!okres->getPatriaDonho()->containsKey(*udaje[7]))
	{
		Obec* novaObec = new Obec(std::stoi(*udaje[6]), *udaje[7], okres, static_cast<TypObce>(std::stoi(*udaje[8])), std::stoi(*udaje[9]));
		okres->pridajDonho(novaObec);
		vsetkyUJSorted_->insert(++indexVsetkychUJ_, novaObec);
		dynamic_cast<Krajina*>(slovensko_)->pridajObec(novaObec);
	}
}

void spracujZaznamUcastnejTabulky(Array<std::string*>& udaje)
{
	UzemnaJednotka* obec = nullptr;
	dynamic_cast<Krajina*>(slovensko_)->getVsetkyObceSorted()->tryFind(std::stoi(*udaje[0]), obec);

	VolebnaUcast* volebnaUcast = new VolebnaUcast();
	volebnaUcast->pocetZapisanych_ = std::stoi(*udaje[2]);
	volebnaUcast->pocetZucastnenych_ = std::stoi(*udaje[3]);
	volebnaUcast->pocetObalkovych_ = std::stoi(*udaje[5]);
	volebnaUcast->pocetZCudziny_ = std::stoi(*udaje[7]);
	volebnaUcast->pocetPlatnychSpolu_ = std::stoi(*udaje[9]);

	dynamic_cast<Obec*>(obec)->setVolebnaUcastOkrsku(std::stoi(*udaje[1]), volebnaUcast);
}

void nacitajTabulku(int indexTabulky)
{
	std::string nazovSuboru;
	switch (indexTabulky)
	{
	case 0:
		nazovSuboru = "NRSR_2020_SK_tab0c.csv";
		break;
	case 1:
		nazovSuboru = "NRSR_2020_SK_tab02e.csv";
		break;
	default:
		throw std::logic_error("nacitajTabulku: Invalid table index.");
	}
	std::cout << u8"Načítavam data zo súboru '" << nazovSuboru << "'..." << std::endl;
	int pocetRiadkov = dajPocetRiadkovVSubore("data/" + nazovSuboru) - 1;
	std::string riadok;
	std::ifstream subor("data/" + nazovSuboru);
	if (subor.is_open())
	{
		std::getline(subor, riadok);
		int index = 0;

		while (std::getline(subor, riadok))
		{
			std::stringstream riadkovyStream(riadok);
			std::string udaj;
			Array<std::string*> udaje = Array<std::string*>(11);
			int indexUdaju = 0;

			while (std::getline(riadkovyStream, udaj, '|'))
			{
				udaje[indexUdaju] = new std::string(udaj);
				indexUdaju++;
			}

			switch (indexTabulky)
			{
			case 0:
				spracujZaznamUzemnejTabulky(udaje);
				break;
			case 1:
				spracujZaznamUcastnejTabulky(udaje);
				break;
			default:
				throw std::logic_error("nacitajTabulku: Invalid table index.");
			}

			for (int i = 0; i < static_cast<int>(udaje.size()); i++)
			{
				delete udaje[i];
			}
			if (index % (pocetRiadkov / 20) == 0)
			{
				std::cout << '\r' << (index / (pocetRiadkov / 20)) * 5 << '%' << std::flush;
			}
			index++;
		}
		switch (indexTabulky)
		{
		case 0:
			dynamic_cast<Krajina*>(slovensko_)->skopirujObceDoUnsorted();
			break;
		case 1:
			vsetkyUJ_ = new UnsortedSequenceTable<int, UzemnaJednotka*>(*vsetkyUJSorted_);
			break;
		}
		std::cout << std::endl;
		subor.close();
	}
}

void nacitajTabulky()
{
	nacitajTabulku(0);
	nacitajTabulku(1);
}

bool retazecJeInt(std::string retazec)
{
	try
	{
		std::stoi(retazec);
		return true;
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
}

bool retazecJeDouble(std::string retazec)
{
	try
	{
		std::stod(retazec);
		return true;
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
}

void vymazNazvyNizzsich(Array<std::string*>* nazvyNizsich)
{
	if (nazvyNizsich != nullptr)
	{
		for (int i = 0; i < static_cast<int>(nazvyNizsich->size()); i++)
		{
			delete (*nazvyNizsich)[i];
		}
		delete nazvyNizsich;
	}
}

UzemnaJednotka* prehladavanieStromuUI()
{
	PrehladavacStromuUJ prehladavac = PrehladavacStromuUJ(slovensko_);
	std::string vstup;
	do
	{
		Array<std::string*>* nazvyNizsich = prehladavac.maNizsich() ? prehladavac.dajNazvyNizsich() : nullptr;

		std::cout << u8"Nachádzate sa v strome územných jednotiek." << std::endl;
		std::cout << u8"príkazy:" << std::endl;
		std::cout << u8"  [číslo]   - číslo územnehej jednotky do ktorej chcete vojsť" << std::endl;
		std::cout << u8"  hore      - posuniete sa v strome o jedno vyššie" << std::endl;
		std::cout << u8"  enter     - zvolí sa daná územná jednotka a ukončí sa prehľadávanie stromu" << std::endl;
		std::cout << u8"  undefined - zvolí sa undefined a ukončí sa prehľadávanie stromu" << std::endl;

		std::cout << u8"Aktuálna:" << std::endl;
		std::cout << u8"  typ: " << EnumNazov::daj(prehladavac.dajTypUzemnejJednotkyAktualneho()) << std::endl;
		std::cout << u8"  názov: " << prehladavac.dajNazovAktualneho() << std::endl;
		if (prehladavac.dajTypUzemnejJednotkyAktualneho() == TypUzemnejJednotky::OBEC)
		{
			Obec* obec = dynamic_cast<Obec*>(prehladavac.dajAktualnuUzemnuJednotku());
			std::cout << u8"  počet okrskov: " << obec->getPocetOkrskov() << std::endl;
		}
		if (prehladavac.maVyssieho())
		{
			std::cout << u8"Si pod:" << std::endl;
			std::cout << u8"  typ: " << EnumNazov::daj(prehladavac.dajTypUzemnejJednotkyVyssieho()) << std::endl;
			std::cout << u8"  názov: " << prehladavac.dajNazovVyssieho() << std::endl;
		}
		if (prehladavac.maNizsich())
		{
			std::cout << u8"Pod tebou sú:" << std::endl;
			for (int i = 0; i < static_cast<int>(nazvyNizsich->size()); i++)
			{
				std::cout << "  [" << i << "]: " << *(*nazvyNizsich)[i] << std::endl;
			}
		}
		std::cout << std::endl << "> ";
		std::getline(std::cin, vstup);
		if (retazecJeInt(vstup))
		{
			int intVstup = std::stoi(vstup);
			if (prehladavac.maNizsich())
			{
				if (intVstup >= 0 && intVstup < nazvyNizsich->size())
				{
					if (prehladavac.existujeNizsie(*(*nazvyNizsich)[std::stoi(vstup)]))
					{
						prehladavac.chodNizsie(*(*nazvyNizsich)[std::stoi(vstup)]);
					}
					else
					{
						std::cout << u8"Taký neexistuje!" << std::endl;
					}
				}
				else
				{
					std::cout << u8"Nevalidny index." << std::endl;
				}
			}
			else if (prehladavac.dajTypUzemnejJednotkyAktualneho() == TypUzemnejJednotky::OBEC)
			{
				Obec* obec = dynamic_cast<Obec*>(prehladavac.dajAktualnuUzemnuJednotku());
				if (intVstup > 0 && intVstup <= obec->getPocetOkrskov())
				{
					std::cout << obec->getVolebnaUcastOkrsku(intVstup)->toString() << std::endl;
				}
				else
				{
					std::cout << u8"Taký okrsok neexistuje." << std::endl;
				}
			}
		}
		else if (vstup == "hore")
		{
			prehladavac.chodVyssie();
		}
		else if (vstup == "enter")
		{
			vymazNazvyNizzsich(nazvyNizsich);
			return prehladavac.dajAktualnuUzemnuJednotku();
		}
		else if (vstup == "undefined")
		{
			vymazNazvyNizzsich(nazvyNizsich);
			return nullptr;
		}
		std::cout << std::endl;
		vymazNazvyNizzsich(nazvyNizsich);
	} while (true);
}

void otestujKriteria()
{
	PrehladavacStromuUJ prehladavac(slovensko_);

	KUzemnaJednotkaNazov* nazov = new KUzemnaJednotkaNazov();
	KUzemnaJednotkaTyp* typ = new KUzemnaJednotkaTyp();
	KUzemnaJednotkaPrislusnost* prislusnost = new KUzemnaJednotkaPrislusnost(slovensko_);
	KUzemnaJednotkaUcast* ucast = new KUzemnaJednotkaUcast();
	KUzemnaJednotkaVolici* volici = new KUzemnaJednotkaVolici();
	KUzemnaJednotkaZucastneniVolici* zucastneni = new KUzemnaJednotkaZucastneniVolici();
	KUzemnaJednotkaOdovzdaneObalky* obalky1 = new KUzemnaJednotkaOdovzdaneObalky(SposobOdovzdania::OSOBNE);
	KUzemnaJednotkaOdovzdaneObalky* obalky2 = new KUzemnaJednotkaOdovzdaneObalky(SposobOdovzdania::Z_CUDZINY);
	KUzemnaJednotkaOdovzdaneObalky* obalky3 = new KUzemnaJednotkaOdovzdaneObalky(SposobOdovzdania::SPOLU);

	int index = 0;
	while (prehladavac.maNizsich())
	{
		if (index != 0)
		{
			Array<std::string*>* nazvy = prehladavac.dajNazvyNizsich();
			prehladavac.chodNizsie(*(*nazvy)[rand() % nazvy->size()]);
			for (int i = 0; i < static_cast<int>(nazvy->size()); i++)
			{
				delete (*nazvy)[i];
			}
			delete nazvy;
		}
		std::cout << (*nazov)(prehladavac.dajAktualnuUzemnuJednotku()) << " | ";
		std::cout << EnumNazov::daj((*typ)(prehladavac.dajAktualnuUzemnuJednotku())) << " | ";
		//std::cout << "patriDoVyssiehoCelku(slovensko_) -> " << (*prislusnost)(prehladavac.dajAktualnuUzemnuJednotku()) << " | ";
		std::cout << u8"účasť[%]: " << (*ucast)(prehladavac.dajAktualnuUzemnuJednotku()) << " | ";
		std::cout << u8"voliči: " << (*volici)(prehladavac.dajAktualnuUzemnuJednotku()) << " | ";
		std::cout << u8"zúčastnení: " << (*zucastneni)(prehladavac.dajAktualnuUzemnuJednotku()) << " | ";
		std::cout << u8"obálky[osobne]: " << (*obalky1)(prehladavac.dajAktualnuUzemnuJednotku()) << " | ";
		std::cout << u8"obálky[z cudziny]: " << (*obalky2)(prehladavac.dajAktualnuUzemnuJednotku()) << " | ";
		std::cout << u8"obálky[spolu]: " << (*obalky3)(prehladavac.dajAktualnuUzemnuJednotku()) << " | ";
		std::cout << std::endl;
		index++;
	}
	delete nazov;
}

void otestujFiltre()
{
	std::cout << u8"Stará tabuľka:" << std::endl;
	Table<std::string, UzemnaJednotka*>* tabulka = slovensko_->getPatriaDonho();
	for (auto item : *tabulka)
	{
		std::cout << "  " << item->getKey() << ": " << item->accessData()->getNazov() << std::endl;
	}
	std::cout << std::endl;

	FUzemnaJednotkaUcast<std::string>* filter = new FUzemnaJednotkaUcast<std::string>(60, 70);

	Table<std::string, UzemnaJednotka*>* novaTabulka = (*filter)(tabulka);

	std::cout << u8"Nová tabuľka:" << std::endl;
	for (auto item : *novaTabulka)
	{
		std::cout << "  " << item->getKey() << ": " << item->accessData()->getNazov() << std::endl;
	}
	std::cout << std::endl;

	for (auto item : *tabulka)
	{
		delete item->accessData();
	}
	delete tabulka;
	delete novaTabulka;
	delete filter;
}

void otestujSorty()
{
	UnsortedSequenceTable<int, UzemnaJednotka*>* tabulka = dynamic_cast<Krajina*>(slovensko_)->getVsetkyObce();
	MergeSort<int, UzemnaJednotka, double> sort;
	KUzemnaJednotkaUcast sortKriterium;
	KUzemnaJednotkaNazov nazov;
	std::cout << "Unsorted:" << std::endl;
	for (auto item : *tabulka)
	{
		std::cout << nazov(item->accessData()) << ": " << sortKriterium(item->accessData()) << std::endl;
	}
	std::cout << "Triedim..." << std::endl;
	sort(tabulka, &sortKriterium, true);
	std::cout << "Sorted:" << std::endl;
	for (auto item : *tabulka)
	{
		std::cout << nazov(item->accessData()) << ": " << sortKriterium(item->accessData()) << std::endl;
	}
}

char dajPismenoFiltraUI(std::string hlavicka)
{
	std::string vstup;
	char pismeno = 0;
	do
	{
		std::cout << hlavicka << std::endl;
		std::cout << u8"  'a' - podľa názvu" << std::endl;
		std::cout << u8"  'b' - podľa počtu voličov" << std::endl;
		std::cout << u8"  'c' - podľa účasti v %" << std::endl;
		std::getline(std::cin, vstup);
		if (vstup.size() > 0)
		{
			pismeno = vstup.at(0);
		}
	} while (!(vstup.size() > 0 && (pismeno == 'a' || pismeno == 'b' || pismeno == 'c')));
	return pismeno;
}

void pouziFUzemnaJednotkaTypUI(Table<int, UzemnaJednotka*>*& tabulka)
{
	std::string vstup;
	int vstupInt = 0;
	do
	{
		std::cout << u8"Filter podľa typu územnej jednotky." << std::endl;
		std::cout << u8"Zadajte parameter (typ) pre filter:" << std::endl;
		std::cout << u8"  '1' - Krajina" << std::endl;
		std::cout << u8"  '2' - Kraj" << std::endl;
		std::cout << u8"  '3' - Obvod" << std::endl;
		std::cout << u8"  '4' - Okres" << std::endl;
		std::cout << u8"  '5' - Obec" << std::endl;
		std::getline(std::cin, vstup);
		if (retazecJeInt(vstup))
		{
			vstupInt = std::stoi(vstup);
		}
	} while (!((retazecJeInt(vstup) && 1 <= vstupInt && vstupInt <= 5) || vstup == "undefined"));
	if (vstup != "undefined")
	{
		TypUzemnejJednotky typ = TypUzemnejJednotky::KRAJINA;
		switch (vstupInt)
		{
		case 1:
			typ = TypUzemnejJednotky::KRAJINA;
			break;
		case 2:
			typ = TypUzemnejJednotky::KRAJ;
			break;
		case 3:
			typ = TypUzemnejJednotky::OBVOD;
			break;
		case 4:
			typ = TypUzemnejJednotky::OKRES;
			break;
		case 5:
			typ = TypUzemnejJednotky::OBEC;
			break;
		}
		FUzemnaJednotkaTyp<int> filter(typ);
		Table<int, UzemnaJednotka*>* pomocnaTabulka = tabulka;
		tabulka = filter(tabulka);
		delete pomocnaTabulka;
		pomocnaTabulka = nullptr;
	}
}

void pouziFUzemnaJednotkaNazovUI(Table<int, UzemnaJednotka*>*& tabulka)
{
	std::string vstup;
	do
	{
		std::cout << u8"Filter podľa názvu územnej jednotky." << std::endl;
		std::cout << u8"Zadajte parameter (názov obce) pre filter: ";
		std::getline(std::cin, vstup);
	} while (!(vstup.size() > 0));
	if (vstup != "undefined")
	{
		FUzemnaJednotkaNazov<int> filter(vstup);

		Table<int, UzemnaJednotka*>* pomocnaTabulka = tabulka;
		tabulka = filter(tabulka);
		delete pomocnaTabulka;
		pomocnaTabulka = nullptr;
	}
}

void pouziFUzemnaJednotkaPrislusnostUI(Table<int, UzemnaJednotka*>*& tabulka)
{
	std::string vstup;
	std::cout << u8"Filter podľa vyššej územnej jednotky." << std::endl;
	std::cout << u8"Zadajte parameter (územna jednotka) pre filter:" << std::endl;
	UzemnaJednotka* vstupnaUJ = prehladavanieStromuUI();
	do
	{
		std::cout << u8"Zadajte parameter (alpha) pre filter:" << std::endl;
		std::cout << u8"  'true'  - vrátane" << std::endl;
		std::cout << u8"  'false' - všetky okrem zvolenej" << std::endl;
		std::getline(std::cin, vstup);
	} while (!(vstup == "true" || vstup == "false" || vstup == "undefined"));
	if (vstupnaUJ != nullptr && vstup != "undefined")
	{
		bool alpha = false;
		if (vstup == "true")
		{
			alpha = true;
		}
		else if (vstup == "false")
		{
			alpha = false;
		}
		FUzemnaJednotkaPrislusnost<int> filter(alpha, vstupnaUJ);
		Table<int, UzemnaJednotka*>* pomocnaTabulka = tabulka;
		tabulka = filter(tabulka);
		delete pomocnaTabulka;
		pomocnaTabulka = nullptr;
	}
}

void pouziFUzemnaJednotkaVoliciUI(Table<int, UzemnaJednotka*>*& tabulka)
{
	std::string alphaString;
	std::string betaString;
	int alpha = 0;
	int beta = 0;
	do
	{
		std::cout << u8"Zadajte parameter alpha (minimum zap. voličov) pre filter: ";
		std::getline(std::cin, alphaString);
		if (retazecJeInt(alphaString))
		{
			alpha = std::stoi(alphaString);
		}
	} while (!(retazecJeInt(alphaString) || alphaString == "undefined"));
	do
	{
		std::cout << u8"Zadajte parameter beta (maximum zap.voličov) pre filter: ";
		std::getline(std::cin, betaString);
		if (retazecJeInt(betaString))
		{
			beta = std::stoi(betaString);
		}
	} while (!(retazecJeInt(betaString) || alphaString == "undefined"));
	if (alphaString != "undefined" && betaString != "undefined")
	{
		FUzemnaJednotkaVolici<int> filter(alpha, beta);

		Table<int, UzemnaJednotka*>* pomocnaTabulka = tabulka;
		tabulka = filter(tabulka);
		delete pomocnaTabulka;
		pomocnaTabulka = nullptr;
	}
}

void pouziFUzemnaJednotkaUcastUI(Table<int, UzemnaJednotka*>*& tabulka)
{
	std::string alphaString;
	std::string betaString;
	double alpha = 0;
	double beta = 0;
	do
	{
		std::cout << u8"Zadajte parameter alpha (minimálna účasť) pre filter: ";
		std::getline(std::cin, alphaString);
		if (retazecJeDouble(alphaString))
		{
			alpha = std::stod(alphaString);
		}
	} while (!(retazecJeDouble(alphaString) || alphaString == "undefined"));
	do
	{
		std::cout << u8"Zadajte parameter beta (maximalna účasť) pre filter: ";
		std::getline(std::cin, betaString);
		if (retazecJeDouble(betaString))
		{
			beta = std::stod(betaString);
		}
	} while (!(retazecJeDouble(betaString) || betaString == "undefined"));
	if (alphaString != "undefined" && betaString != "undefined")
	{
		FUzemnaJednotkaUcast<int> filter(alpha, beta);

		Table<int, UzemnaJednotka*>* pomocnaTabulka = tabulka;
		tabulka = filter(tabulka);
		delete pomocnaTabulka;
		pomocnaTabulka = nullptr;
	}
}

void vystup1()
{
	Table<int, UzemnaJednotka*>* tabulka = dynamic_cast<Table<int, UzemnaJednotka*>*>(dynamic_cast<Krajina*>(slovensko_)->getVsetkyObce()->clone());

	char pismeno = dajPismenoFiltraUI(u8"Zadajte kritérium pre filter:");

	switch (pismeno)
	{
	case 'a':
		pouziFUzemnaJednotkaNazovUI(tabulka);
		break;
	case 'b':
		pouziFUzemnaJednotkaVoliciUI(tabulka);
		break;
	case 'c':
		pouziFUzemnaJednotkaUcastUI(tabulka);
		break;
	}
	KUzemnaJednotkaNazov nazov;
	KUzemnaJednotkaUcast ucast;
	KUzemnaJednotkaVolici volici;
	KUzemnaJednotkaZucastneniVolici zucastneniVolici;
	KUzemnaJednotkaOdovzdaneObalky odovzdaneObalkyOsobne(SposobOdovzdania::OSOBNE);
	KUzemnaJednotkaOdovzdaneObalky odovzdaneObalkyZCudziny(SposobOdovzdania::Z_CUDZINY);
	KUzemnaJednotkaOdovzdaneObalky odovzdaneObalkySpolu(SposobOdovzdania::SPOLU);
	KUzemnaJednotkaPodielPlatnychHlasov podielPlatnychHlasov;

	for (auto item : *tabulka)
	{
		UzemnaJednotka* UJ = item->accessData();
		UzemnaJednotka* vyssiaUJ = UJ->getPatriDo();
		std::cout << nazov(UJ) << " (" << nazov(vyssiaUJ);
		while ((vyssiaUJ = vyssiaUJ->getPatriDo()) != nullptr)
		{
			std::cout << ", " << nazov(vyssiaUJ);
		}
		std::cout << ')' << std::endl;
		std::cout << u8"Účasť: " << ucast(UJ) << ", ";
		std::cout << u8"Voliči: " << volici(UJ) << ", ";
		std::cout << u8"Zúcastnení voliči: " << zucastneniVolici(UJ) << ", ";
		std::cout << u8"Odovzdané obálky osobne: " << odovzdaneObalkyOsobne(UJ) << ", ";
		std::cout << u8"Odovzdané obálky z cudziny: " << odovzdaneObalkyZCudziny(UJ) << ", ";
		std::cout << u8"Odovzdané obálky spolu: " << odovzdaneObalkySpolu(UJ) << ", ";
		std::cout << u8"Podiel platných hlasov: " << podielPlatnychHlasov(UJ) << std::endl << std::endl;
	}

	delete tabulka;
}

void vystup2()
{
	UnsortedSequenceTable<int, UzemnaJednotka*>* tabulka = dynamic_cast<UnsortedSequenceTable<int, UzemnaJednotka*>*>(dynamic_cast<Krajina*>(slovensko_)->getVsetkyObce()->clone());

	std::string vstup;
	std::cout << "Obce:" << std::endl;
	char pismeno = dajPismenoFiltraUI(u8"Zadajte kritérium pre triedenie:");

	switch (pismeno)
	{
	case 'a':
	{
		MergeSort<int, UzemnaJednotka, std::string> sort;
		KUzemnaJednotkaNazov kriterium;
		std::cout << "Triedim..." << std::endl;
		sort(tabulka, &kriterium, true);
		std::cout << "Vzostupne:" << std::endl;
		for (auto item : *tabulka)
		{
			std::cout << kriterium(item->accessData()) << u8" - názov: " << kriterium(item->accessData()) << std::endl;
		}
		std::cout << std::endl << u8"Stlač enter pre pokračovanie..." << std::endl;
		std::cin.ignore();
		std::cout << "Triedim..." << std::endl;
		sort(tabulka, &kriterium, false);
		std::cout << "Zostupne:" << std::endl;
		for (auto item : *tabulka)
		{
			std::cout << kriterium(item->accessData()) << u8" - názov: " << kriterium(item->accessData()) << std::endl;
		}
	}
	break;
	case 'b':
	{
		MergeSort<int, UzemnaJednotka, int> sort;
		KUzemnaJednotkaVolici kriterium;
		KUzemnaJednotkaNazov nazov;
		std::cout << "Triedim..." << std::endl;
		sort(tabulka, &kriterium, true);
		std::cout << "Vzostupne:" << std::endl;
		for (auto item : *tabulka)
		{
			std::cout << nazov(item->accessData()) << u8" - voliči: " << kriterium(item->accessData()) << std::endl;
		}
		std::cout << std::endl << u8"Stlač enter pre pokračovanie..." << std::endl;
		std::cin.ignore();
		std::cout << "Triedim..." << std::endl;
		sort(tabulka, &kriterium, false);
		std::cout << "Zostupne:" << std::endl;
		for (auto item : *tabulka)
		{
			std::cout << nazov(item->accessData()) << u8" - voliči: " << kriterium(item->accessData()) << std::endl;
		}
	}
	break;
	case 'c':
	{
		MergeSort<int, UzemnaJednotka, double> sort;
		KUzemnaJednotkaUcast kriterium;
		KUzemnaJednotkaNazov nazov;
		std::cout << "Triedim..." << std::endl;
		sort(tabulka, &kriterium, true);
		std::cout << "Vzostupne:" << std::endl;
		for (auto item : *tabulka)
		{
			std::cout << nazov(item->accessData()) << u8" - účasť: " << kriterium(item->accessData()) << std::endl;
		}
		std::cout << std::endl << u8"Stlač enter pre pokračovanie..." << std::endl;
		std::cin.ignore();
		std::cout << "Triedim..." << std::endl;
		sort(tabulka, &kriterium, false);
		std::cout << "Zostupne:" << std::endl;
		for (auto item : *tabulka)
		{
			std::cout << nazov(item->accessData()) << u8" - účasť: " << kriterium(item->accessData()) << std::endl;
		}
	}
	break;
	}

	delete tabulka;
}

void vystup3()
{
	Table<int, UzemnaJednotka*>* tabulka = dynamic_cast<Table<int, UzemnaJednotka*>*>(vsetkyUJSorted_->clone());

	std::cout << u8"Územné jednotky:" << std::endl;
	std::cout << u8"Zadajte 'undefined' pre preskočenie filtra." << std::endl;

	std::string vstup;
	int vstupInt = 0;

	pouziFUzemnaJednotkaTypUI(tabulka);
	
	pouziFUzemnaJednotkaPrislusnostUI(tabulka);

	char pismeno = dajPismenoFiltraUI(u8"Zadajte kritérium pre filter:");

	switch (pismeno)
	{
	case 'a':
		pouziFUzemnaJednotkaNazovUI(tabulka);
		break;
	case 'b':
		pouziFUzemnaJednotkaVoliciUI(tabulka);
		break;
	case 'c':
		pouziFUzemnaJednotkaUcastUI(tabulka);
		break;
	}
	
	KUzemnaJednotkaNazov nazov;
	KUzemnaJednotkaUcast ucast;
	KUzemnaJednotkaVolici volici;
	KUzemnaJednotkaZucastneniVolici zucastneniVolici;
	KUzemnaJednotkaOdovzdaneObalky odovzdaneObalkyOsobne(SposobOdovzdania::OSOBNE);
	KUzemnaJednotkaOdovzdaneObalky odovzdaneObalkyZCudziny(SposobOdovzdania::Z_CUDZINY);
	KUzemnaJednotkaOdovzdaneObalky odovzdaneObalkySpolu(SposobOdovzdania::SPOLU);
	KUzemnaJednotkaPodielPlatnychHlasov podielPlatnychHlasov;

	for (auto item : *tabulka)
	{
		UzemnaJednotka* UJ = item->accessData();
		UzemnaJednotka* vyssiaUJ = UJ->getPatriDo();
		std::cout << nazov(UJ) << " (" << nazov(vyssiaUJ);
		while ((vyssiaUJ = vyssiaUJ->getPatriDo()) != nullptr)
		{
			std::cout << ", " << nazov(vyssiaUJ);
		}
		std::cout << ')' << std::endl;
		std::cout << u8"Účasť: " << ucast(UJ) << ", ";
		std::cout << u8"Voliči: " << volici(UJ) << ", ";
		std::cout << u8"Zúcastnení voliči: " << zucastneniVolici(UJ) << ", ";
		std::cout << u8"Odovzdané obálky osobne: " << odovzdaneObalkyOsobne(UJ) << ", ";
		std::cout << u8"Odovzdané obálky z cudziny: " << odovzdaneObalkyZCudziny(UJ) << ", ";
		std::cout << u8"Odovzdané obálky spolu: " << odovzdaneObalkySpolu(UJ) << ", ";
		std::cout << u8"Podiel platných hlasov: " << podielPlatnychHlasov(UJ) << std::endl;
	}

	delete tabulka;
}

void vystup4()
{
	Table<int, UzemnaJednotka*>* tabulka = dynamic_cast<Table<int, UzemnaJednotka*>*>(vsetkyUJ_->clone());

	pouziFUzemnaJednotkaTypUI(tabulka);

	pouziFUzemnaJednotkaPrislusnostUI(tabulka);

	pouziFUzemnaJednotkaUcastUI(tabulka);

	pouziFUzemnaJednotkaVoliciUI(tabulka);

	char pismeno = dajPismenoFiltraUI(u8"Zadajte kritérium pre triedenie:");

	switch (pismeno)
	{
	case 'a':
	{
		UnsortedSequenceTable<int, UzemnaJednotka*>* neutriedenaTabulka = new UnsortedSequenceTable<int, UzemnaJednotka*>(*dynamic_cast<SortedSequenceTable<int, UzemnaJednotka*>*>(tabulka));
		MergeSort<int, UzemnaJednotka, std::string> sort;
		KUzemnaJednotkaNazov kriterium;
		std::cout << "Triedim..." << std::endl;
		sort(neutriedenaTabulka, &kriterium, true);
		std::cout << "Vzostupne:" << std::endl;
		for (auto item : *neutriedenaTabulka)
		{
			std::cout << kriterium(item->accessData()) << u8" - názov: " << kriterium(item->accessData()) << std::endl;
		}
		std::cout << std::endl << u8"Stlač enter pre pokračovanie..." << std::endl;
		std::cin.ignore();
		std::cout << "Triedim..." << std::endl;
		sort(neutriedenaTabulka, &kriterium, false);
		std::cout << "Zostupne:" << std::endl;
		for (auto item : *neutriedenaTabulka)
		{
			std::cout << kriterium(item->accessData()) << u8" - názov: " << kriterium(item->accessData()) << std::endl;
		}

		delete neutriedenaTabulka;
	}
	break;
	case 'b':
	{
		UnsortedSequenceTable<int, UzemnaJednotka*>* neutriedenaTabulka = new UnsortedSequenceTable<int, UzemnaJednotka*>(*dynamic_cast<UnsortedSequenceTable<int, UzemnaJednotka*>*>(tabulka));
		MergeSort<int, UzemnaJednotka, int> sort;
		KUzemnaJednotkaVolici kriterium;
		KUzemnaJednotkaNazov nazov;
		std::cout << "Triedim..." << std::endl;
		sort(neutriedenaTabulka, &kriterium, true);
		std::cout << "Vzostupne:" << std::endl;
		for (auto item : *neutriedenaTabulka)
		{
			std::cout << nazov(item->accessData()) << u8" - voliči: " << kriterium(item->accessData()) << std::endl;
		}
		std::cout << std::endl << u8"Stlač enter pre pokračovanie..." << std::endl;
		std::cin.ignore();
		std::cout << "Triedim..." << std::endl;
		sort(neutriedenaTabulka, &kriterium, false);
		std::cout << "Zostupne:" << std::endl;
		for (auto item : *neutriedenaTabulka)
		{
			std::cout << nazov(item->accessData()) << u8" - voliči: " << kriterium(item->accessData()) << std::endl;
		}
	}
	break;
	case 'c':
	{
		UnsortedSequenceTable<int, UzemnaJednotka*>* neutriedenaTabulka = new UnsortedSequenceTable<int, UzemnaJednotka*>(*dynamic_cast<UnsortedSequenceTable<int, UzemnaJednotka*>*>(tabulka));
		MergeSort<int, UzemnaJednotka, double> sort;
		KUzemnaJednotkaUcast kriterium;
		KUzemnaJednotkaNazov nazov;
		std::cout << "Triedim..." << std::endl;
		sort(neutriedenaTabulka, &kriterium, true);
		std::cout << "Vzostupne:" << std::endl;
		for (auto item : *neutriedenaTabulka)
		{
			std::cout << nazov(item->accessData()) << u8" - účasť: " << kriterium(item->accessData()) << std::endl;
		}
		std::cout << std::endl << u8"Stlač enter pre pokračovanie..." << std::endl;
		std::cin.ignore();
		std::cout << "Triedim..." << std::endl;
		sort(neutriedenaTabulka, &kriterium, false);
		std::cout << "Zostupne:" << std::endl;
		for (auto item : *neutriedenaTabulka)
		{
			std::cout << nazov(item->accessData()) << u8" - účasť: " << kriterium(item->accessData()) << std::endl;
		}
	}
	break;
	}

	delete tabulka;
}

void vystupy()
{
	std::string vstup;
	int intVstup = 0;
	do
	{
		do
		{
			std::cout << u8"Zadajte číslo výstupu [1-4]: ";
			std::getline(std::cin, vstup);
			if (retazecJeInt(vstup))
			{
				intVstup = std::stoi(vstup);
			}
		} while (!(retazecJeInt(vstup) && 1 <= intVstup && intVstup <= 4));

		switch (intVstup)
		{
		case 1:
			vystup1();
			break;
		case 2:
			vystup2();
			break;
		case 3:
			vystup3();
			break;
		case 4:
			vystup4();
			break;
		}
		do
		{
			std::cout << u8"Chcete pokračovat? (ano/nie): ";
			std::getline(std::cin, vstup);
		} while (!(vstup == "ano" || vstup == "nie"));
	} while (vstup == "ano");
}

void uvolniPamet()
{
	delete slovensko_;
	slovensko_ = nullptr;
	if (vsetkyUJ_ != nullptr)
	{
		delete vsetkyUJ_;
		vsetkyUJ_ = nullptr;
	}
	delete vsetkyUJSorted_;
	vsetkyUJSorted_ = nullptr;
}

int main()
{
	initHeapMonitor();
	inicializujKonzolu();
	srand(static_cast<int>(time(nullptr)));

	nacitajTabulky();

	//prehladavanieStromuUI();

	//otestujKriteria();
	//otestujFiltre();
	//otestujSorty();

	vystupy();

	uvolniPamet();

	return 0;
}