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

int Carta::getCor()
{
	return this->cor;
}

int Carta::getNumero()
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