#include "Partida.h"
#include "stdafx.h"

Partida::Partida()
{
	this->jogadoresConectados = 0;
}

Partida::Partida(const SOCKET* primeiroJogador)
{
	this->conexoes[0] = *primeiroJogador;
	this->jogadoresConectados = 1;
}

Partida::Partida(const SOCKET* primeiroJogador, int id) : Partida(primeiroJogador)
{
	this->id = id;
}

void Partida::iniciarPartida()
{
	bool sentidoHorario = true;
	while (true)
	{
		char jogada[256];
		recv(conexoes[jogadorDaVez - 1], jogada, sizeof(jogada), NULL);
		broadcast(&(std::string(jogada)));
	}
	
}

void Partida::distribuirCartas()
{
	this->baralho = Baralho();
	for (int i = 0; i < jogadoresConectados; i++)
	{
		std::string mensagem = "3" + std::to_string(nJogadores);

		for (int j = 0; j < 7; j++)
		{
			Carta c = baralho.getCartaNoTopo();
			int cor = c.getCor();
			int numero = c.getNumero();
			mensagem = mensagem + "&" + std::to_string(cor) + "," + std::to_string(numero);
		}

		std::cout << "\n" << mensagem << "\n";

		send(this->conexoes[i], mensagem.c_str(), strlen(mensagem.c_str()), NULL);
	}
}

void Partida::definirJogadores()
{
	for (int i = 0; i < this->jogadoresConectados - 1; i++)
	{
		std::string mensagem = std::to_string(i + 1);
		send(this->conexoes[i], mensagem.c_str(), strlen(mensagem.c_str()), NULL);
	}
}

void Partida::adicionarConexao(const SOCKET* jogador)
{
	if (jogadoresConectados < 4)
	{
		this->conexoes[this->jogadoresConectados++] = *jogador;
	}
}

void Partida::broadcast(const std::string* mensagem)
{
	for (int i = 0; i < this->jogadoresConectados; i++)
	{
		send(this->conexoes[i], (*mensagem).c_str(), strlen((*mensagem).c_str()), NULL);
	}
}

int Partida::getId()
{
	return this->id;
}

void Partida::setId(int id)
{
	this->id = id;
}

SOCKET* Partida::getConexoes()
{
	return this->conexoes;
}

int Partida::getJogadoresConectados()
{
	return this->jogadoresConectados;
}