

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>


using namespace std;

bool is_digits(const std::string& str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

void sifriraj(char& buf, int len) {
	
	char *buf1 = &buf;
	for (int i = 0; i < len; i++) {
		if (isalpha(buf1[i])) {
			switch (buf1[i]) {
			case 'a': buf1[i] = 'z'; break;
			case 'b': buf1[i] = 'y'; break;
			case 'c': buf1[i] = 'x'; break;
			case 'd': buf1[i] = 'w'; break;
			case 'e': buf1[i] = 'v'; break; 
			case 'f': buf1[i] = 'u'; break;
			case 'g': buf1[i] = 't'; break;
			case 'h': buf1[i] = 's'; break;
			case 'i': buf1[i] = 'r'; break;
			case 'j': buf1[i] = 'q'; break;
			case 'k': buf1[i] = 'p'; break;
			case 'l': buf1[i] = 'o'; break;
			case 'm': buf1[i] = 'n'; break;
			case 'n': buf1[i] = 'm'; break;
			case 'o': buf1[i] = 'l'; break;
			case 'p': buf1[i] = 'k'; break;
			case 'q': buf1[i] = 'j'; break;
			case 'r': buf1[i] = 'i'; break;
			case 's': buf1[i] = 'h'; break;
			case 't': buf1[i] = 'g'; break;
			case 'u': buf1[i] = 'f'; break;
			case 'v': buf1[i] = 'e'; break;
			case 'w': buf1[i] = 'd'; break;
			case 'x': buf1[i] = 'c'; break;
			case 'y': buf1[i] = 'b'; break;
			case 'z': buf1[i] = 'a'; break;
			default:break;
			}
		}
	}
}


int main()
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &wsaData) != 0) 
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	SOCKADDR_IN addr; 
	int sizeofaddr = sizeof(addr); 
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	addr.sin_port = htons(54555);
	addr.sin_family = AF_INET; 

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL); 
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) 
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return 0; 
	}
	cout << "Uspesno vospostavena konekcija so serverot" << std::endl;
	char buf[500];
	while (1) {

		memset(buf, 0, sizeof(buf));
		cout << "Prati: ";
		cin.getline(buf, sizeof(buf));
		string str(buf); 
		if (is_digits(str)) {
			cout << "Ve molime vnesete nova poraka\n";
			continue;
		}
		int i = 0;
		char c;
		while (buf[i])
		{
			c = buf[i];
			buf[i] = tolower(c);
			i++;
		}
		str=buf;
		sifriraj(*buf, strlen(buf));
		send(Connection, buf, sizeof(buf), NULL); 
		if (str == "kraj") break;
		memset(buf, 0, sizeof(buf));
		recv(Connection, buf, sizeof(buf), NULL); 
		cout << "Primeno: " << buf << endl;

	}
	closesocket(Connection);
	system("pause");
}
