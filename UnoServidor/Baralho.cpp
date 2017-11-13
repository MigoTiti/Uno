#include "stdafx.h"

Baralho::Baralho()
{
	for (int i = 0; i <= 12; i++)
	{
		if (i == 0)
		{
			this->cartas.push_back(Carta(Carta::COR_VERMELHA, 0));
			this->cartas.push_back(Carta(Carta::COR_AMARELA, 0));
			this->cartas.push_back(Carta(Carta::COR_AZUL, 0));
			this->cartas.push_back(Carta(Carta::COR_VERDE, 0));
		}
		else
		{
			this->cartas.push_back(Carta(Carta::COR_VERMELHA, i));
			this->cartas.push_back(Carta(Carta::COR_VERMELHA, i));
			this->cartas.push_back(Carta(Carta::COR_AMARELA, i));
			this->cartas.push_back(Carta(Carta::COR_AMARELA, i));
			this->cartas.push_back(Carta(Carta::COR_AZUL, i));
			this->cartas.push_back(Carta(Carta::COR_AZUL, i));
			this->cartas.push_back(Carta(Carta::COR_VERDE, i));
			this->cartas.push_back(Carta(Carta::COR_VERDE, i));
		}
	}

	this->cartas.push_back(Carta(Carta::COR_PRETA, Carta::CORINGA));
	this->cartas.push_back(Carta(Carta::COR_PRETA, Carta::CORINGA));
	this->cartas.push_back(Carta(Carta::COR_PRETA, Carta::CORINGA));
	this->cartas.push_back(Carta(Carta::COR_PRETA, Carta::CORINGA));
	this->cartas.push_back(Carta(Carta::COR_PRETA, Carta::MAIS_QUATRO));
	this->cartas.push_back(Carta(Carta::COR_PRETA, Carta::MAIS_QUATRO));
	this->cartas.push_back(Carta(Carta::COR_PRETA, Carta::MAIS_QUATRO));
	this->cartas.push_back(Carta(Carta::COR_PRETA, Carta::MAIS_QUATRO));

	std::srand(static_cast<int>(time(0)));
	std::random_shuffle(this->cartas.begin(), this->cartas.end());
}

void Baralho::jogarCarta(const Carta& carta)
{
	cartasJogadas.push_back(cartaNaMesa);
	cartaNaMesa = carta;
}

Carta Baralho::getCartaNaMesa() const
{
	return this->cartaNaMesa;
}

vector<Carta> Baralho::getCartas()
{
	return this->cartas;
}

Carta Baralho::getCartaNoTopo()
{
	Carta c = cartas.back();
	cartas.pop_back();
	return c;
}