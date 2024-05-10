#include "Packet_Ninja.h"
#include "Core.h"
#include "Log.h"
#include <future>

namespace Core
{
	static WSADATA	wsaData_winRef;
	static int		iResult_win;

	static SOCKET ListenSocket_win;
	static SOCKET ClientSocket_win;

	static struct addrinfo* result_winRef;
	static struct addrinfo	hints_win;

	static int iSendResult_win;
	static char recvbuf_win[DEFAULT_BUFLEN];
	static int recvbuflen_win;

	static std::future<mint> listen_thread;

	mint Packet_Ninja::Init()
	{
		INFOc("Creating Network Socket in port: {}", DEFAULT_PORT);

		
		ListenSocket_win = INVALID_SOCKET;
		ClientSocket_win = INVALID_SOCKET;

		result_winRef = NULL;
		recvbuflen_win = DEFAULT_BUFLEN;

		// Initialize Winsock
		iResult_win = WSAStartup(MAKEWORD(2, 2), &wsaData_winRef);
		if (iResult_win != 0)
		{
			ERRORc("Packet Ninja Failed to make a windows WSA socket, returned code {}", iResult_win);
			return (mint)iResult_win;
		}

		ZeroMemory(&hints_win, sizeof(hints_win));
		hints_win.ai_family = AF_INET;
		hints_win.ai_socktype = SOCK_STREAM;
		hints_win.ai_protocol = IPPROTO_TCP;
		hints_win.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		iResult_win = getaddrinfo(NULL, DEFAULT_PORT, &hints_win, &result_winRef);
		if (iResult_win != 0) {
			ERRORc("Packet Ninja getaddrinfo step failed with error: {}", iResult_win);
			WSACleanup();
			return 1;
		}

		// Create a SOCKET for the server to listen for client connections.
		ListenSocket_win = socket(result_winRef->ai_family, result_winRef->ai_socktype, result_winRef->ai_protocol);
		if (ListenSocket_win == INVALID_SOCKET) {
			ERRORc("Packet Ninja socket creation failed with error: {}", WSAGetLastError());
			freeaddrinfo(result_winRef);
			WSACleanup();
			return 1;
		}

		freeaddrinfo(result_winRef);
		
		listen_thread = std::async(Wait_For_Connection);
		

		return 0;
	}

	mint Packet_Ninja::Wait_For_Connection()
	{
		// Setup the TCP listening socket
		iResult_win = bind(ListenSocket_win, result_winRef->ai_addr, (int)result_winRef->ai_addrlen);
		if (iResult_win == SOCKET_ERROR) {
			ERRORc("Packet Ninja TCP bind failed with error: {}", WSAGetLastError());
			freeaddrinfo(result_winRef);
			closesocket(ListenSocket_win);
			WSACleanup();
			return 1;
		}

		iResult_win = listen(ListenSocket_win, SOMAXCONN);
		if (iResult_win == SOCKET_ERROR) {
			ERRORc("Packet Ninja TCP listen failed with error: {}", WSAGetLastError());
			closesocket(ListenSocket_win);
			WSACleanup();
			return 1;
		}

		// Accept a client socket
		ClientSocket_win = accept(ListenSocket_win, NULL, NULL);
		if (ClientSocket_win == INVALID_SOCKET) {
			ERRORc("Packet Ninja TCP Client Accept failed with error: {}", WSAGetLastError());
			closesocket(ListenSocket_win);
			WSACleanup();
			return 1;
		}

		return 0;
	}

	mint Packet_Ninja::Test_Send_Packets() 
	{
		// Receive until the peer shuts down the connection
		do {

			iResult_win = recv(ClientSocket_win, recvbuf_win, recvbuflen_win, 0);
			if (iResult_win > 0) {
				INFOc("Packet Ninja Bytes received: {}", iResult_win);

				// Echo the buffer back to the sender
				iSendResult_win = send(ClientSocket_win, recvbuf_win, iResult_win, 0);
				if (iSendResult_win == SOCKET_ERROR) {
					WARNc("Packet Ninja Test send failed with error: {}", WSAGetLastError());
					closesocket(ClientSocket_win);
					WSACleanup();
					return 1;
				}
				INFOc("Packet Ninja Test Bytes sent: {}", iSendResult_win);
			}
			else if (iResult_win == 0)
				INFOc("Packet Ninja Test Connection closing...");
			else {
				WARNc("Packet Ninja Test recv failed with error: {}", WSAGetLastError());
				closesocket(ClientSocket_win);
				WSACleanup();
				return 1;
			}

		} while (iResult_win > 0);

		// cleanup
		closesocket(ClientSocket_win);
		WSACleanup();

	}
}