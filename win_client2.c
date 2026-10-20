// win_client.c 只管发送测试版
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = inet_addr("10.19.251.76");
    
    printf("正在连接...\n");
    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("连接成功！开始疯狂发送消息...\n");
    
    char buf[128] = {0};
    while (1) {
        printf("请输入发送: ");
        fgets(buf, 128, stdin);
        buf[strcspn(buf, "\n")] = '\0';
        if(strcmp(buf, "quit") == 0) break;
        
        send(sock, buf, strlen(buf), 0);
        // 注意：这里没有 recv 了！发完直接跳出循环让你继续输入！
    }
    
    closesocket(sock);
    WSACleanup();
    return 0;
}