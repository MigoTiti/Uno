#pragma once

#include <WS2tcpip.h>
#include <string>
#include "Baralho.h"

class Partida
{
public:
	Partida();
	Partida(const SOCKET* primeiroJogador);
	Partida(const SOCKET* primeiroJogador, int id);
	void setId(int id);
	void adicionarConexao(const SOCKET* jogador);
	void broadcast(const std::string* mensagem);
	void definirJogadores();
	SOCKET* getConexoes();
	int getJogadoresConectados();
	int getId();
	void iniciarPartida();
	void distribuirCartas();

	int nJogadores = 2;
private:

	Baralho baralho;
	SOCKET conexoes[2];
	int jogadoresConectados;
	int id;
	int jogadorDaVez = 1;
};
