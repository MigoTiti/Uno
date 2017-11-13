#include "Carta.h"
#include "stdafx.h"

Carta::Carta()
{

}

Carta::Carta(int cor, int numero)
{
	this->cor = cor;
	this->numero = numero;
}

std::ostream& operator<<(std::ostream& os, const Carta& carta)
{
	std::string cartaString;
	int cor = carta.getCor();
	int numero = carta.getNumero();
	switch (cor)
	{
	case Carta::COR_PRETA:
		if (numero == Carta::CORINGA)
			cartaString = "Coringa (troca cor)";
		else if (numero == Carta::MAIS_QUATRO)
			cartaString = "Coringa (+4)";
		break;
	case Carta::COR_VERMELHA:
		switch (numero)
		{
		case Carta::MAIS_DOIS:
			cartaString = "+2 vermelho";
			break;
		case Carta::REVERTER:
			cartaString = "Reverter vermelho";
			break;
		case Carta::BLOQUEAR:
			cartaString = "Bloquear vermelho";
			break;
		case Carta::CORINGA:
			cartaString = "Coringa vermelho";
			break;
		default:
			cartaString = std::to_string(numero) + " vermelho";
			break;
		}
		break;
	case Carta::COR_AMARELA:
		switch (numero)
		{
		case Carta::MAIS_DOIS:
			cartaString = "+2 amarelo";
			break;
		case Carta::REVERTER:
			cartaString = "Reverter amarelo";
			break;
		case Carta::BLOQUEAR:
			cartaString = "Bloquear amarelo";
			break;
		case Carta::CORINGA:
			cartaString = "Coringa amarelo";
			break;
		default:
			cartaString = std::to_string(numero) + " amarelo";
			break;
		}
		break;
	case Carta::COR_AZUL:
		switch (numero)
		{
		case Carta::MAIS_DOIS:
			cartaString = "+2 azul";
			break;
		case Carta::REVERTER:
			cartaString = "Reverter azul";
			break;
		case Carta::BLOQUEAR:
			cartaString = "Bloquear azul";
			break;
		case Carta::CORINGA:
			cartaString = "Coringa azul";
			break;
		default:
			cartaString = std::to_string(numero) + " azul";
			break;
		}
		break;
	case Carta::COR_VERDE:
		switch (numero)
		{
		case Carta::MAIS_DOIS:
			cartaString = "+2 verde";
			break;
		case Carta::REVERTER:
			cartaString = "Reverter verde";
			break;
		case Carta::BLOQUEAR:
			cartaString = "Bloquear verde";
			break;
		case Carta::CORINGA:
			cartaString = "Coringa verde";
			break;
		default:
			cartaString = std::to_string(numero) + " verde";
			break;
		}
		break;
	}

	os << cartaString;
	return os;
}

int Carta::getCor() const
{
	return this->cor;
}

int Carta::getNumero() const
{
	return this->numero;
}

void Carta::setCor(int cor)
{
	this->cor = cor;
}

void Carta::setNumero(int numero)
{
	this->numero = numero;
}