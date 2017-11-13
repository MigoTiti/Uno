#pragma once

class Carta
{
public:
	Carta();
	Carta(int cor, int numero);
	int getCor() const;
	int getNumero() const;
	void setCor(int cor);
	void setNumero(int numero);

	friend std::ostream& operator<<(std::ostream& os, const Carta& carta);

	static const int COR_PRETA = 0;
	static const int COR_VERMELHA = 1;
	static const int COR_AMARELA = 2;
	static const int COR_AZUL = 3;
	static const int COR_VERDE = 4;
	static const int MAIS_DOIS = 10;
	static const int REVERTER = 11;
	static const int BLOQUEAR = 12;
	static const int MAIS_QUATRO = 13;
	static const int CORINGA = 14;
private:
	int numero;
	int cor;
};