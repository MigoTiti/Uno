#include "stdafx.h"

WSADATA inicializarSocket();
SOCKADDR_IN inicializarEnderecoSocket(const std::string& endereco);
void comunicar(SOCKET& conexao);
void enviarMensagem(std::string mensagem, const SOCKET& socket);
void limparTela();
void iniciarJogo(const SOCKET& conexao, Mao& maoDoJogador, Carta& cartaNaMesa);
Mao setNumeroJogadorECartas(const char* numero, Carta& cartaNaMesa);
void decodificarCartas(std::vector<std::string>& tokens, std::vector<Carta>& cartas);
bool isJogadaValida(Carta& cartaEscolhida, Carta& cartaNaMesa, bool correnteCompra);
std::string escolherEndereco();

static int nJogador;
static int vezDoJogador = 1;

static const int CRIAR_PARTIDA = 1;
static const int ENTRAR_EM_PARTIDA = 2;
static const int CONFIRMACAO_ENTRADA = 3;
static const int JOGADA = 4;
static const int COMPRAR_CARTA = 5;
static const int SEM_CARTAS_CORRENTE = 6;

int main()
{
	std::string endereco(escolherEndereco());

	WSAData wsaData = inicializarSocket();
	SOCKADDR_IN enderecoSocket = inicializarEnderecoSocket(endereco);

	SOCKET conexao = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(conexao, (SOCKADDR*)&enderecoSocket, sizeof(enderecoSocket)) != 0)
	{
		MessageBoxA(NULL, "Conexão falhou", "Erro", MB_OK | MB_ICONERROR);
		return 0;
	}

	char mensagem[256];
	recv(conexao, mensagem, sizeof(mensagem), NULL);
	std::cout << "Conectado \n";

	if (mensagem[0] == '1')
	{
		comunicar(conexao);
	}

	return 1;
}

void comunicar(SOCKET& conexao)
{
	std::string opcao;
	std::cout << "1 - criar partida; \n2 - Entrar em partida;\n";
	std::cin >> opcao;
	enviarMensagem(opcao, conexao);

	char mensagem[4096];
	recv(conexao, mensagem, sizeof(mensagem), NULL);

	limparTela();
	if ((mensagem[0] - '0') == CRIAR_PARTIDA)
	{
		std::cout << "Aguardando jogadores...";
		recv(conexao, mensagem, sizeof(mensagem), NULL);

		if ((mensagem[0] - '0') == CONFIRMACAO_ENTRADA)
		{
			limparTela();

			Carta cartaNaMesa;
			Mao maoDoJogador = setNumeroJogadorECartas(mensagem, cartaNaMesa);

			iniciarJogo(conexao, maoDoJogador, cartaNaMesa);
		}
	}
	else if ((mensagem[0] - '0') == ENTRAR_EM_PARTIDA)
	{
		std::string mensagemString(mensagem);
		mensagemString.erase(mensagemString.begin());

		std::vector<std::string> tokens;
		StringUtil::tokenize(mensagemString, tokens, "&");

		std::cout << tokens[0] << "\n" << "Escolha a partida:\n";

		tokens.clear();

		std::cin >> opcao;
		enviarMensagem(opcao, conexao);

		limparTela();

		recv(conexao, mensagem, sizeof(mensagem), NULL);
		if ((mensagem[0] - '0') == CRIAR_PARTIDA)
		{
			std::cout << "Aguardando jogadores...";
			recv(conexao, mensagem, sizeof(mensagem), NULL);

			if ((mensagem[0] - '0') == CONFIRMACAO_ENTRADA)
			{
				limparTela();

				Carta cartaNaMesa;
				Mao maoDoJogador = setNumeroJogadorECartas(mensagem, cartaNaMesa);

				iniciarJogo(conexao, maoDoJogador, cartaNaMesa);
			}
		}
		else if ((mensagem[0] - '0') == CONFIRMACAO_ENTRADA)
		{
			Carta cartaNaMesa;
			Mao maoDoJogador = setNumeroJogadorECartas(mensagem, cartaNaMesa);

			iniciarJogo(conexao, maoDoJogador, cartaNaMesa);
		}
	}
}

Mao setNumeroJogadorECartas(const char* numero, Carta& cartaNaMesa)
{
	char numeroJogador;
	numeroJogador = numero[1];
	nJogador = atoi(&numeroJogador);

	std::vector<std::string> tokens;

	StringUtil::tokenize(std::string(numero), tokens, "&");

	Mao maoDoJogador = Mao();
	std::vector<Carta> cartas;
	decodificarCartas(tokens, cartas);

	cartaNaMesa = cartas.back();
	cartas.pop_back();

	maoDoJogador.setCartas(cartas);
	return maoDoJogador;
}

void decodificarCartas(std::vector<std::string>& tokens, std::vector<Carta>& cartas)
{
	for (int i = 1; i <= 8; i++)
	{
		std::string cartaString(tokens[i]);
		std::vector<std::string> tokensCarta;

		StringUtil::tokenize(cartaString, tokensCarta, ",");
		cartas.push_back(Carta(atoi(tokensCarta[0].data()), atoi(tokensCarta[1].data())));
	}
}

void iniciarJogo(const SOCKET& conexao, Mao& maoDoJogador, Carta& cartaNaMesa)
{
	bool sentidoHorario = true;
	bool correnteCompra = false;
	int contagemCorrente = 0;

	while (true)
	{
		limparTela();
		std::cout << "Carta na mesa: " << cartaNaMesa << "\n" << maoDoJogador;
		std::cout << "\nVoce e o jogador numero: " << nJogador << "\n";
		std::string opcao;

		if (nJogador == vezDoJogador)
		{
			std::cout << "\nEscolha uma carta para jogar\n";
			std::cin >> opcao;

			int jogada = atoi(opcao.data());
			if (jogada < maoDoJogador.getCartas().size() && jogada >= 0)
			{
				Carta cartaEscolhida = maoDoJogador.getCartaEmIndice(atoi(opcao.data()));

				if (isJogadaValida(cartaEscolhida, cartaNaMesa, false))
				{
					std::string jogadaCompleta = std::to_string(JOGADA) + "&" + cartaEscolhida.toString() + ";";
					enviarMensagem(jogadaCompleta, conexao);
					char mensagem[1000];
					recv(conexao, mensagem, sizeof(mensagem), NULL);

					std::string resposta(mensagem);
					std::vector<std::string> tokens;

					StringUtil::tokenize(resposta, tokens, "&");

					//processamento da resposta
				}
				else
				{
					std::cout << "\nJogada invalida, tente novamente\nAperte qualquer botao para continuar\n";
					std::cin >> opcao;
				}
			}
			else if (jogada == maoDoJogador.getCartas().size())
			{
				//comprar carta
			}
			else 
			{
				//jogada inválida
			}
		}
		else
		{
			std::cout << "Vez do jogador " << vezDoJogador << "\n";
			char mensagem[1000];
			recv(conexao, mensagem, sizeof(mensagem), NULL);

			std::string resposta(mensagem);
			std::vector<std::string> tokens;

			StringUtil::tokenize(resposta, tokens, "&");
			
			//processamento da resposta
		}
	}
}

bool isJogadaValida(Carta& cartaEscolhida, Carta& cartaNaMesa, bool correnteCompra)
{
	int corCartaEscolhida = cartaEscolhida.getCor();
	int numeroCartaEscolhida = cartaEscolhida.getNumero();
	int corCartaNaMesa = cartaNaMesa.getCor();
	int numeroCartaNaMesa = cartaNaMesa.getNumero();

	if ((numeroCartaNaMesa == Carta::MAIS_DOIS || numeroCartaNaMesa == Carta::MAIS_QUATRO) && correnteCompra)
	{
		if (numeroCartaEscolhida == Carta::MAIS_DOIS || numeroCartaEscolhida == Carta::MAIS_QUATRO)
			return true;
		else
			return false;
	}

	if (numeroCartaEscolhida == Carta::MAIS_QUATRO || numeroCartaEscolhida == Carta::CORINGA)
		return true;

	return corCartaEscolhida == corCartaNaMesa || numeroCartaEscolhida == numeroCartaNaMesa;
}

void limparTela()
{
	system("cls");
}

void enviarMensagem(std::string mensagem, const SOCKET& socket)
{
	send(socket, mensagem.data(), static_cast<int>(mensagem.size()), NULL);
}

SOCKADDR_IN inicializarEnderecoSocket(const std::string& endereco)
{
	SOCKADDR_IN enderecoSocket;
	int tamanhoEndereco = sizeof(enderecoSocket);

	enderecoSocket.sin_port = htons(12345);
	enderecoSocket.sin_family = AF_INET;
	inet_pton(AF_INET, endereco.data(), &enderecoSocket.sin_addr.S_un.S_addr);

	return enderecoSocket;
}

WSADATA inicializarSocket()
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Erro na inicializacao do socket", "Erro", MB_OK | MB_ICONERROR);
		exit(1);
	}

	return wsaData;
}

std::string escolherEndereco()
{
	std::cout << "Digite a opcao de endereco IP: \n1 - 192.168.1.4\n2 - 10.1.4.243\n3 - IP personalizado\n";
	char opcaoEndereco;
	std::cin >> opcaoEndereco;

	std::string endereco;

	if (opcaoEndereco == '1')
		endereco = "192.168.1.4";
	else if (opcaoEndereco == '2')
		endereco = "10.1.4.243";
	else
	{
		limparTela();
		std::cout << "Digite o endereco IP a ser usado: \n";
		std::cin >> endereco;
	}

	limparTela();
	return endereco;
}