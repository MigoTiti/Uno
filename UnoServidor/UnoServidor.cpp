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

	SOCKET escutadorSocket = socket(AF_INET, SOCK_STREAM, NULL);
	bind(escutadorSocket, (SOCKADDR*)&enderecoSocket, sizeof(enderecoSocket));
	listen(escutadorSocket, SOMAXCONN);

	cout << "Esperando \n";

	SOCKET novaConexao = accept(escutadorSocket, (SOCKADDR*)&enderecoSocket, &tamanhoEndereco);
	if (novaConexao == 0)
	{
		cout << "N aceitou esta merda \n";
	}
	else
	{
		cout << "Aceitou hein \n";
		char retorno[256] = "FALA SEU BABACA";
		send(novaConexao, retorno, sizeof(retorno), NULL);
	}

	char mensagem[256];
	recv(novaConexao, mensagem, sizeof(mensagem), NULL);
	cout << "Resposta: " << mensagem << "\n";

	system("pause");

	return 0;
}

