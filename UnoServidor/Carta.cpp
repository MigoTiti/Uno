#include "Carta.h"
#include "stdafx.h"

Carta::Carta()
{

}

bool Carta::operator==(const Carta& carta) const
{
	return this->cor == carta.getCor() && this->numero == carta.getNumero();
}

Carta::Carta(int cor, int numero)
{
	this->cor = cor;
	this->numero = numero;
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