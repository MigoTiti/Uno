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

	os << "\n" << cartas.size() + 1 << " - Comprar carta (em uma corrente de compras, compra todas as cartas da corrente, e caso já tenha comprado, pula a jogada);\n";

	return os;
}

void Mao::adicionarCarta(Carta& carta)
{
	this->cartas.push_back(carta);
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