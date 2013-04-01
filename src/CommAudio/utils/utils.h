#ifndef UTILS_H
#define UTILS_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <cassert>
#include <libzplay.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libzplay.lib")

#define BUFLEN 1024
#define RECV_MAX 2048
//This struct will be assigned to the OVerlapped struct 
//hEvent parameter for use in the Completion Routine.
typedef struct recvData
{
	bool bQuit;
	char recvBuffer[RECV_MAX];
	SOCKET *sock;
	sockaddr* dest;
} RECVDATA, *PRECVDATA;

SOCKET NewUDPSocket();
SOCKET NewTCPSocket();
SOCKADDR_IN SetDestinationAddr(std::string address, int port);
int JoinMulticast(SOCKET *socketfd, std::string achMcAddr);
int BindSocket(SOCKET *socketfd, char* hostname, int port);
int ReadFromFile(HANDLE hFile, char* buffer);
void CALLBACK UDPRoutine(DWORD dwError, DWORD dwTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
void UDPSend(SOCKET s, char* buf, const struct sockaddr *dest, OVERLAPPED *sendOv);
void UDPRead(OVERLAPPED *recvOv);
int SetReuseAddr(SOCKET* socketfd);

void StartMicSession(SOCKET socketfd);
int SendMicSessionRequest(SOCKET socketfd);
int SendAudioData(SOCKET s);
int __stdcall PlaybackRoutine(void* instance, void *user_data, libZPlay::TCallbackMessage message, unsigned int param1, unsigned int param2);

DWORD WINAPI ListenForPackets(LPVOID lpParameter);
DWORD WINAPI MonitorMicInput(LPVOID lpParameter);

#endif