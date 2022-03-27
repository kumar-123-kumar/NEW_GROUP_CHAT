#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include<iomanip>
#include<string>
#include<conio.h>
#pragma comment(lib, "Ws2_32.lib")
struct sockaddr_in srv;
#define PORT 9909
fd_set fr, fw, fe;
using namespace std;
int index;


class Chat
{
private:

	char message[50];
	char name[20];
	int left_side_colr_code;
	int message_colr_code;
public:
	Chat()//CONSTRUCTOR
	{

	}

	~Chat()//DESTRUCTOR
	{

	}
	void set_Name()
	{
		cout << "ENTER YOUR NAME : ";
		fflush(stdin);
		fgets(name, 20, stdin);
	}

	void set_Message()
	{
		cout << "MESSAGE : ";
		fflush(stdin);
		fgets(message, 50, stdin);
	}

	void set_Left_Color()
	{

	}

	void set_Message_Color()
	{

	}

	char* get_Message()
	{
		return message;
	}

	char* get_Name()
	{
		return name;
	}

	int get_Left_Color()
	{
		return left_side_colr_code;
	}

	int get_Message_Color()
	{
		return message_colr_code;
	}

};


int main()
{
	WSADATA ws;			/*WSA VARIABLES ENABLES THE SOCKET PROGRAMMING ENVIRONMENT IN THE WINDOWS */
						/*BEFORE CREATING THE SOCKETS WE NEED TO INITIALIZE THIS ENVIRONMENT*/
	int iresult = WSAStartup(MAKEWORD(2, 2), &ws);
	if (iresult < 0)
	{
		printf("WSA VARAIBLES ARE NOT CREATED\n");
	}
	else if (iresult == 0) {
		printf("WSA_VARIABLES ARE CREATED \n");
	}
	//for (index = 0; index < 11; index++)
	int client_soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	std::cout << "CLIENT_SOCKET ID  = " << client_soc << std::endl;
	//std::cout << "SOCKET ID " << client_soc << std::endl;
	if (client_soc > 0)
	{
		std::cout << "SOCKET CREATED SUCCESSFULLY" << std::endl;
	}
	else
	{
		std::cout << "SOCKET FUNCTION FAILED " << std::endl;
	}
	struct in_addr inaddr;
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	int r_Val = inet_addr("127.0.0.1");

	if (r_Val == 0)
	{
		std::cout << "NO CONNECTION" << std::endl;
	}
	else if (r_Val == -1)
	{
		std::cout << "INVALID" << std::endl;

	}
	else
	{
		std::cout << "IP ADDRESS SUCCESSFULLY CONVERTED TO BYTE ORDER" << std::endl;
	}
	srv.sin_addr.s_addr = inet_addr("127.0.0.1"); //IT WILL FIND MACHINE LOCAL IP AND ASSIGN TO THE SOCKET
	memset(&(srv.sin_zero), 0, 8);			//srv.sin_addri.s_addr = inet_addr() // on the argument we need to specify our ip addrss

	int nRet = 0;
	nRet = connect(client_soc, (struct sockaddr*)&srv, sizeof(srv));
	if (nRet < 0)
	{
		printf("connection is failed\n");
	}
	const int  buf_len = 4096;
	char buf[buf_len] = { 0 };
	/*while (true)
	{
		int res_obj_res = recv(client_soc , buf , 4096, 0);
		if (res_obj_res > 0)
		{
			cout << buf << endl;
		}
		else
		{
			std::cout << "FAILED WHILE RECEIVING THE MESSAGE : " << std::endl;
		}
	}*/

	int welcom_msg_status = recv(client_soc, buf, 4096, 0);
	if (welcom_msg_status < 0)
	{
		cout << "FAILED TO RECEIVE THE MESSAGE FROM THER SERVER : " << endl;
	}
	else
	{
		cout << setw(30) << buf << endl;
	}

	char* sender_name = nullptr;
	char* sender_msg = nullptr;
	bool loop_status = true;
	Chat receiver_obj;
	while (loop_status)
	{
		int obj_rec_status = recv(client_soc, (char*)&receiver_obj, sizeof(receiver_obj), 0);

		if (obj_rec_status < 0)
		{
			cout << "FAILURE WHILE RECEIVING THE OBJECT :" << endl;
			cout << "EXIT FROM THE LOOP" << endl;
			loop_status = false;
		}
		else
		{
			sender_name = receiver_obj.get_Name();
			int i = 0;
			while (sender_name[i] != '\0') {
				if (sender_name[i] == '\n')
				{
					//THERE IS PROBLEM WITH THIS NEW LINE CHAR BECAUSE OF THE SENDER NAME AND THE MESSAGE NAME ARE NOT APPEARED ON THESAME LINE SO NEED TO IGNORE THIS NEW LINE CHARACTERS 
				}
				else
				cout << sender_name[i];

				i++;
			}
			//cout << sender_name;
			sender_msg = receiver_obj.get_Message();
			cout << "     : " << sender_msg << endl;
		}
	}

	return 0;
}


