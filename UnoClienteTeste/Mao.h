#pragma once

#include "stdafx.h"
#include <vector>

using std::vector;

class Mao
{
public:
	Mao();
	void setCartas(vector<Carta> cartas);
	void removerCartaEmIndice(int indice);
	Carta getCartaEmIndice(int indice);
	vector<Carta> getCartas() const;
	void adicionarCarta(Carta& carta);

	friend std::ostream& operator<<(std::ostream& os, const Mao& mao);
private:
	vector<Carta> cartas;
};