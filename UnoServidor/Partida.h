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
	void multicast(const std::string& mensagem);
	SOCKET* getConexoes();
	int getJogadoresConectados();
	int getId();
	void iniciarPartida();
	void distribuirCartas();
	void incrementarVezDoJogador(int valor, bool horario);

	int nJogadores = 2;

	static const int JOGADA = 4;
	static const int COMPRAR_CARTA = 5;
	static const int SEM_CARTAS_CORRENTE = 6;
	static const int RETORNO_JOGADA = 7;
	static const int RETORNO_COMPRA = 8;
private:
	Carta decodificarCarta(std::string& cartaString);

	Baralho baralho;
	SOCKET conexoes[2];
	int jogadoresConectados;
	int id;
	int jogadorDaVez = 1;
};
