
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <list>
#include <string.h>
#include <algorithm> 
#include <locale>

using namespace std;

// trim from start (in place)
static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
	ltrim(s);
	rtrim(s);
}

bool is_Number(string s) {//2..12
	bool is_n = false;	  //01234
	int dot=0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '.') ++dot;
	}
	if (dot > 1) return is_n;
	for (int i = 0; i < s.length(); i++) { 
		if (s[0] == '.' || s[s.length() - 1] == '.') return false;
			if (i == 0) {
				if (s[i] == '-' || s[i] == '0' || s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9') {
					is_n = true;
				}else {
					is_n = false;
					return is_n;
				}
			}
			
			if (i >= 1 && i<(s.length() - 1)) {
				if (s[i] != ' ' && (s[i] == '.' || s[i] == '0' || s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9')) {
					is_n = true;
				}
				else {
					is_n = false;
					return is_n;
				}
			}
			if (i == (s.length() - 1)) {
				if (s[i] == '0' || s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9') {
					is_n = true;
				}
				else {
					is_n = false;
					return is_n;
				}
			}
		
	}
	return is_n;
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
	char buf1[50];
	while (1) {
		
		memset(buf, 0, sizeof(buf));
		list<string> lista;
		bool is_ok = false;
		string s1;
		int broj_kr=0;
		while (not is_ok) {
			cout << "Vnesete broj na kvadratni ravenki koi sakate da bidat reseni (ax^2 + bx + c = 0): ";
			getline(cin,s1);
			trim(s1);
			if (s1 == "stop") break;
			try {
				if (s1 == "") throw 1;
				broj_kr = stoi(s1);
				for (int i = 0; i < s1.length(); i++) {
					if (s1[i] == '0' || s1[i] == '1' || s1[i] == '2' || s1[i] == '3' || s1[i] == '4' || s1[i] == '5' || s1[i] == '6' || s1[i] == '7' || s1[i] == '8' || s1[i] == '9') {

					}
					else {
						throw 1;
					}
				}
				is_ok = true;
			}
			catch (...) { cout << "Vnesete validen broj ili 'stop' za prekin!\n"; }
		}
		cout << endl;
		if (s1 == "stop") {
			strcpy_s(buf, s1.c_str());
			send(Connection, buf, sizeof(buf), NULL);
			break;
		}
		strcpy_s(buf1, s1.c_str());
		for (int j = 1; j <= broj_kr; j++) {
			cout << "********** Kvadratna ravenka broj ["<<j<<"] **********\n";
			string a, b, c, abc;
			a:	cout << "Koeficient 'a' (a/=0): ";
			getline(cin, a);
			trim(a);
			if (!is_Number(a)) {
				cout << "Vnesete validen broj!\n";
				goto a;
			}
			if (stod(a) == 0) {
				cout << "Ova ne e kvadratna ravenka!" << endl;
				goto a;
			}
			b:	cout << "Koeficient 'b': ";
			 
			getline(cin, b);
			trim(b);
			if (!is_Number(b)) {
				cout << "Vnesete validen broj!\n";

				goto b;
			}
			c:	cout << "Koeficient 'c': ";
			getline(cin, c);
			trim(c);
			if (!is_Number(c)) {
				cout << "Vnesete validen broj!\n";
				goto c;
			}
			cout << "Kvadratna ravenka ["<<j<<"] "<<": (" << a << ")x^2 + (" << b << ")x + (" << c << ") = 0\n";

			abc = a + " " + b + " " + c;
			lista.push_back(abc);
			cout << endl;
		}
		int lista_size = lista.size();
		send(Connection, buf1, sizeof(buf1), NULL);
		while (!lista.empty()) {
			strcpy_s(buf, lista.front().c_str());
			lista.pop_front();
			send(Connection, buf, sizeof(buf), NULL);
		}
		for (int i = 0; i < lista_size; i++) {
			memset(buf, 0, sizeof(buf));
			recv(Connection, buf, sizeof(buf), NULL);
			cout << "Resenie na kvadratna ravenka ["<<i+1<<"] " <<": " << buf << endl<<endl;
		}

		cout << "*****************************##########*****************************\n";


	}
	closesocket(Connection);
	system("pause");
	return 0;
}
