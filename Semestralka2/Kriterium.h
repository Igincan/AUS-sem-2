#pragma once

template<typename R, typename O>
class Kriterium
{
public:
	
	virtual R operator()(O* objekt) = 0;

};
