#pragma once

#include "stdafx.h"
#include <vector>

using std::vector;

class Mao
{
public:
	Mao();
	void setCartas(vector<Carta> cartas);
	vector<Carta> getCartas();
private:
	vector<Carta> cartas;
};