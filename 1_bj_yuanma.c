// 全局变量
int client_sock = -1;    // 全局变量，存储与客户端通信的套接字描述符，初始化为 -1 表示无效
int keep_running = 1;    // 全局标志位，控制程序运行状态，1 表示继续运行，0 表示退出

// 【子线程函数】：专门负责在后台死循环等待键盘输入，发给客户端
void* ThreadSend(void* arg) {          // 线程函数，参数为 void* 类型（此处未使用），返回值为 void*
    char send_buf[128] = {0};          // 定义一个 128 字节的发送缓冲区，并初始化为全 0
    while (keep_running) {             // 当 keep_running 为 1 时，持续循环
        // 获取键盘输入
        fgets(send_buf, 128, stdin);   // 从标准输入（键盘）读取一行数据，最多读取 127 个字符，存入 send_buf
        
        if (strcmp(send_buf, "quit\n") == 0) {  // 判断用户输入的是否为 "quit"（fgets 会保留末尾的换行符 \n）
            keep_running = 0;          // 将全局标志位设为 0，通知所有线程准备退出
            break;                     // 跳出 while 循环，结束子线程
        }

        // 1. 发送数据给客户端
        send(client_sock, send_buf, strlen(send_buf), 0);  // 通过 client_sock 套接字，将 send_buf 中的数据发送给客户端，发送长度为字符串实际长度

        // 2. 打印发送日志（带清屏指令，防止终端文字重复/重叠）
        // \033[A 光标上移一行 -> \033[2K 清除当前整行 -> \r 光标移至行首
        printf("\033[A\033[2K\r[服务端] 发送了: %s", send_buf);  // 使用 ANSI 转义序列将光标移回上一行并清除，然后打印发送日志，避免与主线程的接收日志重叠

        // 3. 清空发送缓冲区，防止脏数据
        memset(send_buf, 0, 128);      // 将 send_buf 缓冲区全部置为 0，防止残留上次的数据
    }
    return NULL;                       // 线程函数返回 NULL，结束子线程
}