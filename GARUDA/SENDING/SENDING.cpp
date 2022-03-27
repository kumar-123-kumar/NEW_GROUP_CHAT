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
const int buf_len = 4096;
char buf[buf_len] = { 0, };



class Chat
{
private:

    char message[50];
    char name[20];
    int left_side_colr_code;
    int message_colr_code;
public:
    Chat()
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


    int rec_status = recv(client_soc, buf, 4096, 0);


    if (rec_status < 0)
    {
        cout << "FAILED WHILE RECEIVING THE WELCOME MESSAGE FROMT THE SERVER " << endl;
        return 0;
    }
    else
    {
        cout << setw(30) << buf << endl;
    }

    //CREATING THE OBJECT FOR THE CHAT CLASS
    Chat sending_client;
    sending_client.set_Name();

    while (true)
    {
        sending_client.set_Message();//HERE CONTINUEOUSLY SENDING THE MESSAGE 

        int sending_status = send(client_soc, (char*)&sending_client, sizeof(sending_client), 0);

        if (sending_status < 0)
        {
            cout << "FAILED TO SEND THE  MESSAGE TO THE SERVER " << endl;
        }
        else
        {

        }

    }//while loop end

    return 0;
}