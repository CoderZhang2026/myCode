#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

SOCKET sock;
int keep_running = 1;

// 子线程：专门用来在后台默默收消息
unsigned __stdcall ThreadRecv(void* pParam) {
    char buf[128];
    while (keep_running) {
        int len = recv(sock, buf, sizeof(buf), 0);
        if (len > 0) {
            buf[len] = '\0';
            printf("[Server sent]: %s\n", buf);//收到服务端
        }
    }
    return 0;
}

int main() {
    // 1. 初始化网络
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    // 2. 创建套接字并连接
    sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = inet_addr("10.19.251.76");
    
    printf("Connecting to server...\n");
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed! Please check if the server is running.\n");
        return 1;
    }
    printf("Connected! (type 'quit' to exit)\n");
    
    // 3. 开启子线程去收消息
    HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadRecv, NULL, 0, NULL);
    
    // 4. 主线程死循环：你只管疯狂发消息，发完直接换下一句
    char send_buf[128];
    while (1) {
        printf("Input: ");
        fgets(send_buf, 128, stdin);
        send_buf[strcspn(send_buf, "\n")] = 0;
        
        if (strcmp(send_buf, "quit") == 0) {
            keep_running = 0;
            break;
        }
        send(sock, send_buf, strlen(send_buf), 0);
    }
    
    WaitForSingleObject(hThread, 1000);
    CloseHandle(hThread);
    closesocket(sock);
    WSACleanup();
    return 0;
}


//gcc win_client.c -o win_client.exe -lws2_32
//.\win_client.exe