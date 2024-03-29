#include "stdafx.h"

using std::cout;
using std::string;
using std::stringstream;

Partida partidas[100];
int contagemPartidas = 0;

WSADATA inicializarSocket();
SOCKADDR_IN inicializarEnderecoSocket(const std::string& endereco);
void comunicar(SOCKET);
void enviarMensagem(string mensagem, const SOCKET* socket);
std::string escolherEndereco();

int main()
{
	std::string endereco(escolherEndereco());

	WSAData wsaData = inicializarSocket();
	SOCKADDR_IN enderecoSocket = inicializarEnderecoSocket(endereco);

	SOCKET escutadorSocket = socket(AF_INET, SOCK_STREAM, NULL);
	bind(escutadorSocket, (SOCKADDR*)&enderecoSocket, sizeof(enderecoSocket));
	listen(escutadorSocket, SOMAXCONN);

	int tamanhoEndereco = sizeof(enderecoSocket);

	SOCKET conexoes[10];

	for (int i = 0; i < 10; i++)
	{
		cout << "Esperando \n";
		conexoes[i] = accept(escutadorSocket, (SOCKADDR*)&enderecoSocket, &tamanhoEndereco);
		if (conexoes[i] == 0)
		{
			cout << "Nao aceitou a conexao \n";
		}
		else
		{
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)comunicar, (LPVOID)(conexoes[i]), NULL, NULL);
		}
	}

	return 0;
}

void comunicar(SOCKET socket)
{
	enviarMensagem("1", &socket);

	char mensagem[256];
	recv(socket, mensagem, sizeof(mensagem), NULL);

	if (mensagem[0] == '1')
	{
		partidas[contagemPartidas] = Partida(&socket, contagemPartidas);
		cout << "Criou partida " << contagemPartidas++ << "\n";
		enviarMensagem("1", &socket);
	}
	else if (mensagem[0] == '2')
	{
		string retorno = "2Partidas disponiveis: \n";
		for (int i = 0; i < contagemPartidas; i++)
		{
			int id = partidas[contagemPartidas].getId();
			retorno = retorno + std::to_string(id);
			retorno += ";\n";
		}
		
		retorno = retorno + "&";

		enviarMensagem(retorno, &socket);

		recv(socket, mensagem, sizeof(mensagem), NULL);

		string partida(mensagem);
		stringstream str(partida);
		int idPartida;
		str >> idPartida;

		partidas[idPartida].adicionarConexao(&socket);

		if (partidas[idPartida].getJogadoresConectados() == partidas[idPartida].nJogadores)
		{
			partidas[idPartida].distribuirCartas();
			partidas[idPartida].iniciarPartida();
		}
		else 
		{
			enviarMensagem("1", &socket);
		}
	}
}

void enviarMensagem(std::string mensagem, const SOCKET* socket)
{
	send(*socket, mensagem.data(), static_cast<int>(mensagem.size()), NULL);
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
	std::cout << "Digite a opcao de endereco IP: \n1 - 192.168.1.4\n2 - 10.1.4.243\n3 - 10.16.4.73\n4 - IP personalizado\n";
	char opcaoEndereco;
	std::cin >> opcaoEndereco;

	std::string endereco;

	if (opcaoEndereco == '1')
		endereco = "192.168.1.4";
	else if (opcaoEndereco == '2')
		endereco = "10.1.4.243";
	else if (opcaoEndereco == '3')
		endereco = "10.16.4.73";
	else
	{
		system("cls");
		std::cout << "Digite o endereco IP a ser usado: \n";
		std::cin >> endereco;
	}

	system("cls");
	return endereco;
}