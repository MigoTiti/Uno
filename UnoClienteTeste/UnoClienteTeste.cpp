// UnoClienteTeste.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"

using std::cout;

int main()
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Erro na inicializacao do socket", "Erro", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN enderecoSocket;
	int tamanhoEndereco = sizeof(enderecoSocket);

	enderecoSocket.sin_port = htons(12345);
	enderecoSocket.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &enderecoSocket.sin_addr.S_un.S_addr);

	SOCKET conexao = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(conexao, (SOCKADDR*)&enderecoSocket, tamanhoEndereco) != 0)
	{
		MessageBoxA(NULL, "Conexão falhou", "Erro", MB_OK | MB_ICONERROR);
		return 0;
	}

	cout << "Conectado \n";

	char mensagem[256];
	recv(conexao, mensagem, sizeof(mensagem), NULL);
	cout << "Resposta: " << mensagem << "\n";

	char resposta[256] = "FALA TU MEU PARSA";
	send(conexao, resposta, sizeof(resposta), NULL);

	system("pause");

	return 1;
}

