#pragma once

#include <sstream>

struct VolebnaUcast
{
public:

	int		pocetZapisanych_;
	int		pocetZucastnenych_;
	int		pocetObalkovych_;
	int		pocetZCudziny_;
	int		pocetPlatnychSpolu_;

	std::string toString()
	{
		std::stringstream sstream;
		sstream 
			<< "Pocet opravnenych volicov:     " << pocetZapisanych_ << std::endl
			<< "Pocet zucastnenych volicov:    " << pocetZucastnenych_ << std::endl
			<< "Pocet obalkovych volicov:      " << pocetObalkovych_ << std::endl
			<< "Pocet z cudziny:               " << pocetZCudziny_ << std::endl
			<< "Pocet platnych spolu:          " << pocetPlatnychSpolu_;
		return sstream.str();
	}
};