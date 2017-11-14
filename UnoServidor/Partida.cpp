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
	bool correnteCompra = false;
	int contagemCorrente = 0;
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

			//sintaxe retorno de jogada = CÓDIGO DE JOGADA & CARTA JOGADA & SENTIDO HORÁRIO & PRÓXIMO JOGADOR A JOGAR & CORRENTE DE COMPRA (LIGADO OU DESLIGADO) & CONTADOR DE CORENTE (SE LIGADO) &
			int numero = cartaJogada.getNumero();

			std::string retorno(std::to_string(Partida::RETORNO_JOGADA) + "&" + cartaJogada.toString() + "&");

			if (numero == Carta::MAIS_DOIS || numero == Carta::MAIS_QUATRO)
			{
				numero == Carta::MAIS_DOIS ? contagemCorrente += 2 : contagemCorrente += 4;
				correnteCompra = true;
				incrementarVezDoJogador(1, sentidoHorario);

				retorno = retorno + (sentidoHorario ? "1" : "0") + "&" + std::to_string(jogadorDaVez) + "&1&" + std::to_string(contagemCorrente) + "&";
			}
			else if (numero == Carta::BLOQUEAR)
			{
				incrementarVezDoJogador(2, sentidoHorario);
				retorno = retorno + (sentidoHorario ? "1" : "0") + "&" + std::to_string(jogadorDaVez) + "&0&";
			}
			else if (numero == Carta::REVERTER)
			{
				sentidoHorario = !sentidoHorario;
				incrementarVezDoJogador(1, sentidoHorario);
				retorno = retorno + (sentidoHorario ? "1" : "0") + "&" + std::to_string(jogadorDaVez) + "&0&";
			}
			else 
			{
				incrementarVezDoJogador(1, sentidoHorario);
				retorno = retorno + (sentidoHorario ? "1" : "0") + "&" + std::to_string(jogadorDaVez) + "&0&";
			}
				
			multicast(retorno);
		}
		else if (comando - '0' == Partida::COMPRAR_CARTA)
		{
			if (correnteCompra)
			{

			}
			else
			{

			}
			//implementar compra de carta
		}
		else if (comando - '0' == Partida::PULAR_JOGADA)
		{
			//implementar compra de carta acumulada
		}
	}

}

void Partida::incrementarVezDoJogador(int valor, bool horario)
{
	if (horario)
		for (int i = 1; i <= valor; i++)
			jogadorDaVez == nJogadores ? jogadorDaVez = 1 : jogadorDaVez++;
	else
	{
		for (int i = 1; i <= valor; i++)
			jogadorDaVez == 1 ? jogadorDaVez = nJogadores : jogadorDaVez--;
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