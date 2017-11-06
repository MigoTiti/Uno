#include "stdafx.h"

Mao::Mao()
{

}

void Mao::setCartas(std::vector<Carta> cartas)
{
	this->cartas = cartas;
}

std::vector<Carta> Mao::getCartas()
{
	return this->cartas;
}