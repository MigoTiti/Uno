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
	this->baralho.jogarCarta(this->baralho.getCartaNoTopo());

	//implementar lógica de jogo e troca de vez de jogador
	while (true)
	{
		char jogada[256];
		recv(conexoes[jogadorDaVez - 1], jogada, sizeof(jogada), NULL);

		std::string jogadaString(jogada);

		std::vector<std::string> tokens;
		StringUtil::tokenize(jogadaString, tokens, ";");
		jogadaString = tokens[0];

		tokens.clear();
		StringUtil::tokenize(jogadaString, tokens, "&");

		char comando = tokens[0][0];

		if (comando - '0' == Partida::JOGADA)
		{
			Carta cartaJogada = decodificarCarta(tokens[1]);
			this->baralho.jogarCarta(cartaJogada);
			//terminar implementação de jogada
		}
		else if (comando - '0' == Partida::COMPRAR_CARTA)
		{
			//implementar compra de carta
		}
		else if (comando - '0' == Partida::SEM_CARTAS_CORRENTE)
		{
			//implementar compra de carta acumulada
		}

		multicast(std::string(jogada));
	}
	
}

Carta Partida::decodificarCarta(std::string& cartaString)
{
	std::vector<std::string> tokens;
	StringUtil::tokenize(cartaString, tokens, ",");

	int cor = atoi(tokens[0].data());
	int numero = atoi(tokens[1].data());

	return Carta(cor, numero);
}

void Partida::distribuirCartas()
{
	this->baralho = Baralho();
	this->baralho.jogarCarta(this->baralho.getCartaNoTopo());

	Carta primeiraCarta = baralho.getCartaNaMesa();

	for (int i = 0; i < jogadoresConectados; i++)
	{
		std::string mensagem = "3" + std::to_string(i + 1);

		for (int j = 0; j < 7; j++)
		{
			Carta c = baralho.getCartaNoTopo();
			mensagem = mensagem + "&" + c.toString();
		}

		mensagem = mensagem + "&" + std::to_string(primeiraCarta.getCor()) + "," + std::to_string(primeiraCarta.getNumero()) + "&";
		std::cout << "\n" << mensagem << "\n";
		
		send(this->conexoes[i], mensagem.data(), static_cast<int>(mensagem.size()), NULL);
	}
}

void Partida::adicionarConexao(const SOCKET* jogador)
{
	if (jogadoresConectados < 4)
	{
		this->conexoes[this->jogadoresConectados++] = *jogador;
	}
}

void Partida::multicast(const std::string& mensagem)
{
	for (int i = 0; i < this->jogadoresConectados; i++)
	{
		send(this->conexoes[i], mensagem.data(), static_cast<int>(mensagem.size()), NULL);
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