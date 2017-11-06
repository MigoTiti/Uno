#include "stdafx.h"

using std::cout;
using std::string;
using std::cin;
using std::getline;

WSADATA inicializarSocket();
SOCKADDR_IN inicializarEnderecoSocket(const string* endereco);
void comunicar(SOCKET conexao);
void enviarMensagem(string mensagem, const SOCKET* socket);
void limparTela();
void iniciarJogo(const SOCKET* conexao);

static int nJogador;
static int vezDoJogador = 1;

int main()
{
	string endereco("192.168.1.4");
	//cout << "Digite o ip do servidor: \n";
	//cin >> endereco;

	WSAData wsaData = inicializarSocket();
	SOCKADDR_IN enderecoSocket = inicializarEnderecoSocket(&endereco);

	SOCKET conexao = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(conexao, (SOCKADDR*)&enderecoSocket, sizeof(enderecoSocket)) != 0)
	{
		MessageBoxA(NULL, "Conexão falhou", "Erro", MB_OK | MB_ICONERROR);
		return 0;
	}

	char mensagem[256];
	recv(conexao, mensagem, sizeof(mensagem), NULL);
	cout << "Conectado \n";

	if (mensagem[0] == '1')
	{
		comunicar(conexao);
	}

	return 1;
}

void comunicar(SOCKET conexao)
{
	string opcao;
	cout << "1 - criar partida; \n2 - Entrar em partida;\n";
	cin >> opcao;
	send(conexao, opcao.c_str(), sizeof(opcao), NULL);

	char mensagem[4096];
	recv(conexao, mensagem, sizeof(mensagem), NULL);

	limparTela();
	if (mensagem[0] == '1')
	{
		cout << "Aguardando jogadores...";
		recv(conexao, mensagem, sizeof(mensagem), NULL);

		if (mensagem[0] == '3')
		{
			limparTela();

			//Distribuir cartas
			//TODO
			string maoString = string(mensagem);
			Mao maoDoJogador = Mao();

			recv(conexao, mensagem, sizeof(mensagem), NULL);
			string nJogadorString(mensagem);
			std::stringstream str(nJogadorString);
			str >> nJogador;

			iniciarJogo(&conexao);
		}
	}
	else if (mensagem[0] == '2')
	{
		cout << "\n" << mensagem << "\n" << "Escolha a partida:\n";
		cin >> opcao;
		send(conexao, opcao.c_str(), sizeof(opcao), NULL);

		limparTela();

		recv(conexao, mensagem, sizeof(mensagem), NULL);
		if (mensagem[0] == '1')
		{
			cout << "Aguardando jogadores...";
			recv(conexao, mensagem, sizeof(mensagem), NULL);

			if (mensagem[0] == '3')
			{
				limparTela();

				//Distribuir cartas

				recv(conexao, mensagem, sizeof(mensagem), NULL);
				string nJogadorString(mensagem);
				std::stringstream str(nJogadorString);
				str >> nJogador;

				iniciarJogo(&conexao);
			}
		}
		else if (mensagem[0] == '3')
		{
			//Distribuir cartas
			char numeroJogador[1];
			numeroJogador[0] = mensagem[1];
			string nJogadorString(numeroJogador);
			std::stringstream str(nJogadorString);
			str >> nJogador;

			iniciarJogo(&conexao);
		}
	}
}

void iniciarJogo(const SOCKET* conexao)
{
	while (true)
	{
		limparTela();
		cout << "Voce e o jogador numero: " << nJogador << "\n";
		string opcao;

		if (nJogador == vezDoJogador)
		{
			cout << "\nSua vez\n";
			cin >> opcao;
			enviarMensagem(opcao, conexao);
			char mensagem[1000];
			recv(*conexao, mensagem, sizeof(mensagem), NULL);
			cout << "\n" << mensagem;
		}
		else
		{
			cout << "Vez do jogador 1\n";
			char mensagem[1000];
			recv(*conexao, mensagem, sizeof(mensagem), NULL);
			cout << "\n" << mensagem;
		}
	}
}

void limparTela()
{
	system("cls");
}

void enviarMensagem(string mensagem, const SOCKET* socket)
{
	send(*socket, mensagem.c_str(), sizeof(mensagem), NULL);
}

SOCKADDR_IN inicializarEnderecoSocket(const string* endereco)
{
	SOCKADDR_IN enderecoSocket;
	int tamanhoEndereco = sizeof(enderecoSocket);

	enderecoSocket.sin_port = htons(12345);
	enderecoSocket.sin_family = AF_INET;
	inet_pton(AF_INET, const_cast<char*>((*endereco).c_str()), &enderecoSocket.sin_addr.S_un.S_addr);

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

