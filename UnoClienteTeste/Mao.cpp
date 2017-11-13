#include "stdafx.h"

Mao::Mao()
{

}

std::ostream& operator<<(std::ostream& os, const Mao& mao)
{
	std::vector<Carta> cartas = mao.getCartas();

	os << "Cartas na mao: \n";

	for (int i = 0; i < cartas.size(); i++)
	{
		os << i + 1 << " - " << cartas[i] << ";\n";
	}

	os << cartas.size() + 1 << " - Comprar carta;\n";

	return os;
}

Carta Mao::getCartaEmIndice(int indice)
{
	Carta carta = this->cartas[indice - 1];
	return carta;
}

void Mao::removerCartaEmIndice(int indice)
{
	this->cartas.erase(cartas.begin() + indice - 1);
}

void Mao::setCartas(std::vector<Carta> cartas)
{
	this->cartas = cartas;
}

std::vector<Carta> Mao::getCartas() const
{
	return this->cartas;
}