#pragma once

#include <vector>
#include "Carta.h"

using std::vector;

class Baralho
{
public:
	Baralho();
	Carta getCartaNoTopo();
	Carta getCartaNaMesa() const;
	vector<Carta> getCartas();
	void jogarCarta(const Carta& carta);
private:
	Carta cartaNaMesa;
	vector<Carta> cartasJogadas;
	vector<Carta> cartas;
};
