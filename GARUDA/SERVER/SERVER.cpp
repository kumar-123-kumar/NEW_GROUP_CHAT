#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include<iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include<string>
#include<iomanip>
#pragma comment(lib, "Ws2_32.lib")
struct sockaddr_in srv;
#define PORT 9909
fd_set fr, fw, fe;
#define INADDR "127.0.0.1"
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

    WSADATA ws;
    int iresult = WSAStartup(MAKEWORD(2, 2), &ws);
    if (iresult < 0)
    {
        cout << "WSA VARAIBLES ARE CREATED SUCCESSFULLY : " << endl;
        return 0;
    }
    else
    {
        cout << "WSA VARAIBLES ARE CREATED SUCCESSFULLY : " << endl;
    }
    SOCKET MAIN_SOC;
    MAIN_SOC = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (MAIN_SOC == INVALID_SOCKET)
    {
        cout << "SOCKET IS NOT CREATED SUCCESSFULLY : " << endl;
        return 0;
    }
    else
    {
        cout << "SOCKET CREATED SUCCESSFULLY :" << endl;
    }

    struct in_addr inaddr;
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = INADDR_ANY;
    srv.sin_port = htons(PORT);
    memset(&(srv.sin_zero), 0, 8);



    int OptVal = 0;
    int OptSize = sizeof(OptVal);
    int set_sock_res = setsockopt(MAIN_SOC, SOL_SOCKET, SO_REUSEADDR, (char*)&OptVal, OptSize);
    if (set_sock_res == 0)
    {
        std::cout << "SOCKET OPT FUNCTION SUCCESS" << std::endl;
    }
    else
    {
        std::cout << "THE SOCKET OPT FUNCTION CALL IS NOT SUCCESSFUL" << std::endl;
    }

    int bind_res = bind(MAIN_SOC, (sockaddr*)&srv, sizeof(sockaddr));

    if (bind_res < 0)
    {
        cout << "BINDING IS UN SUCCESSFUL" << endl;
        return 0;
    }
    else
    {
        cout << "BINDING THE SOCKET SUCCESSFUL" << endl;
    }


    listen(MAIN_SOC, SOMAXCONN);

    fd_set master;
    FD_ZERO(&master);

    FD_SET(MAIN_SOC, &master);

    bool server_status = true;

    int addr_len;

    char* temp_name = nullptr;
    char* temp_msg = nullptr;
    Chat send_to_all_obj;
    while (server_status)
    {

        fd_set copy = master;

        int select_count = select(0, &copy, nullptr, nullptr, nullptr);

        for (int i = 0; i < select_count; i++)
        {
            SOCKET temp_soc = copy.fd_array[i];
            if (temp_soc == MAIN_SOC)
            {
                addr_len = sizeof(struct sockaddr);
                SOCKET new_client = accept(MAIN_SOC, NULL, &addr_len);
                if (new_client != INVALID_SOCKET)
                {
                    cout << "NEW CLIENT " << endl;
                }
                FD_SET(new_client, &master);
                char welcome_msg[] = "  ***********          WELCOME TO THE CHAT ROOM           ****************   ";
                int wel_msg_len = sizeof(welcome_msg) / sizeof(welcome_msg[0]);
                int temp_res = send(new_client, welcome_msg, wel_msg_len, 0);
                if (temp_res > 0)
                {
                    cout << "welcome message sent successfully : " << endl;
                }
            }
            else
            {

                //ZeroMemory(buf, 4096);


               // int rec_bytes = recv(temp_soc, buf, 4096, 0);
                int rec_bytes = recv(temp_soc, (char*)&send_to_all_obj, sizeof(send_to_all_obj), 0);
                temp_msg = send_to_all_obj.get_Message();
                cout << " client message : " << temp_msg << endl;
                if (rec_bytes <= 0)
                {
                    cout << " " << MAIN_SOC << "  :" << "DISCONNECTED " << endl;
                    closesocket(temp_soc);
                    FD_CLR(temp_soc, &master);
                }
                else
                {
                    //Send_Over_The_Netword(master);

                    for (int i = 0; i < master.fd_count; i++)
                    {
                        SOCKET out_soc = master.fd_array[i];
                        if (out_soc != temp_soc and out_soc != MAIN_SOC)
                        {


                            //int sending_status = send(out_soc, buf, 4096, 0);
                            int sending_status = send(out_soc, (char*)&send_to_all_obj, sizeof(send_to_all_obj), 0);
                            if (sending_status < 0)
                            {
                                cout << "SENDING FAILURE " << endl;
                            }
                            else
                            {
                                cout << "MESSAGE SENT SUCCESSFULLY :" << endl;
                            }
                        }
                    }
                }
            }
        }
    }


    return 0;
}