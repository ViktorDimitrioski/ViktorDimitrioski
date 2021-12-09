
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <list>
#include <string.h>
#include <vector>
#include <cmath>
#include <string>


using namespace std;

vector<string> tokenize(string s, char delimiter) {
	string str;
	vector<string> v;
	for (size_t i = 0; i < s.size(); i++) {
		if (i != s.size() - 1) {
			/* If the i-th character is not a delimiter
			   then add it to the string str */
			if (s[i] != delimiter) {
				str = str + s[i];
			}
			else {
				/* If the i-th character is a delimiter
				   and the string str is not empty then
				   push str into the vector containing
				   tokens.Also make the string str empty
				   after pushing it into the vector*/
				if (str != "") {
					v.push_back(str);
					str = "";
				}
			}
		}
		else {
			/* If the i-th character is the last character
			   of the string and it is not a delimiter
			   then add it to the string str */
			if (s[i] != delimiter) {
				str = str + s[i];
			}
			/* As there are no characters left, if the string
			   str is not empty then push it into the vector */
			if (str != "") {
				v.push_back(str);
			}
		}
	}
	return v;
}

int main(void)
{
	
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		printf("Neuspesna inicijalizacija\n");
		return 0;
	}

	SOCKADDR_IN addr; 
	int addrlen = sizeof(addr); 
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	addr.sin_port = htons(54555); 
	addr.sin_family = AF_INET;
	
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); 
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); 
	listen(sListen, 4); 

	SOCKET newConnection; 
	
	
		
		char buf[500];
		while (1) {
			newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen);
			if (newConnection == 0)
			{
				cout << "Nastana greska pri prifakanje na konekcija. Obidete se povtorno!" << endl;
				break;
			}
			cout << "Uspesno prifatena konekcija" << endl;
			while (1) {
				list<string> lista;
				memset(buf, 0, sizeof(buf));
				recv(newConnection, buf, sizeof(buf), NULL);
				string str(buf);
				if (str == "stop") {
					closesocket(newConnection);
					break;
				}
				int broj_kr = stoi(str);
				for (int i = 1; i <= broj_kr; i++) {
					recv(newConnection, buf, sizeof(buf), NULL);
					lista.push_back(buf);

				}
				while (!lista.empty()) {
					strcpy_s(buf, lista.front().c_str());
					lista.pop_front();
					string s(buf);

					vector<string> v = tokenize(s, ' ');
					double a = stod(v[0]);
					double b = stod(v[1]);
					double c = stod(v[2]);
					double x,x1,x2,d,sqrt_d_p,sqrt_d_n;
					string x1_s,x2_s;

					d = ((b * b) - (4 * a * c));
					if (d > 0) { // dve realni resenija
						sqrt_d_p = sqrt(d);
						x1 = (-b + sqrt_d_p) / (2*a);
						x2 = (-b - sqrt_d_p) / (2*a);
						x1_s ="x1= " + to_string(x1);
						x2_s ="x2= " + to_string(x2);
						string x1_x2 = x1_s + "    " + x2_s;
						memset(buf, 0, sizeof(buf));
						strcpy_s(buf, x1_x2.c_str());
						send(newConnection, buf, sizeof(buf), NULL);
						


					}
					if (d < 0) { // dve complexni resenija
						//x1 = (-b/2) + (sqrt(-d)/2);
						sqrt_d_n = (sqrt(-d));

						string s_b = to_string(-b/(2*a));
						string s_d = to_string(sqrt_d_n/(2*a)) + "i";
						string x1_i ="x1= " + s_b + " + " + s_d;

						//x2 = (-b - d) / 2;
						string x2_i ="x2= " + s_b + " - " + s_d;

						string x1_x2_i = x1_i + "    " + x2_i;
						memset(buf, 0, sizeof(buf));
						strcpy_s(buf, x1_x2_i.c_str());
						send(newConnection, buf, sizeof(buf), NULL);


					}
					if (d == 0) {//edno resenie
						x = (-b) / (2 * a);
						string x_eqzero ="x= " + to_string(x);

						memset(buf, 0, sizeof(buf));
						strcpy_s(buf, x_eqzero.c_str());
						send(newConnection, buf, sizeof(buf), NULL);
					}
					

					cout << a << "\t\t\t" << b << "\t\t\t" << c <<endl;
					for (size_t i = 0; i < v.size(); i++) {
						//cout << v[i] << "  ";
					}
				}
				//ax^2+bx+c=0

				//memset(buf, 0, sizeof(buf));
				//send(newConnection, buf, sizeof(buf), NULL);
			}
		}
	closesocket(sListen);
	closesocket(newConnection);
	system("pause");
	return 0;
}