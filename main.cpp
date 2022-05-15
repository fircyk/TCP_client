#include <iostream>
#include <string>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
    WSAData wsData;
    sockaddr_in servAddress;
    int wsStart = WSAStartup((2,2), &wsData);
    if(wsStart != 0){
        cout << "winsock error" << endl;
        return 0;
    }

    string ipAddress = "127.0.0.1";
    int port = 54000;

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == INVALID_SOCKET){
        cout << "socket creation error" << endl;
        WSACleanup();
    }

    servAddress.sin_family = AF_INET;
    servAddress.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &servAddress.sin_addr);



    int connnectionResult = connect(clientSocket, (sockaddr*)&servAddress, sizeof(servAddress));
    if(connnectionResult == SOCKET_ERROR){
        cout << "cant connect to server" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 0;
    }

    char buffer[2048];
    string input;

    do{
        cout << "# ";
        getline(cin, input);
        if(input.size()>0){
            int textResult = send(clientSocket, input.c_str(), input.size()+1, 0);
            if(textResult != SOCKET_ERROR){
                int bytesReceived = recv(clientSocket, buffer, 2048, 0);
                if(bytesReceived > 0){
                    cout << "SERVER: " << string(buffer, 0, bytesReceived) << endl;

                }
            }
        }

    }while(input.size()>0);

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
