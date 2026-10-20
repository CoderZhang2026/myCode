int client_sock = -1;
int keep_running = 1;

void ThreadSend(void* arg){
	
	char send_buf[128] = {0};
	
	while (keep_running){
		fgets(send_buf, 128, stdin);

		if (strcmp(send_buf, "quit\n") == 0){
			keep_running = 0;
			break;
		}
		send(client_sock, send_buf, strlen(send_buf),0);

		printf("\033[A\033[2k\r[server]send: %s" send_buf);

		memset(send_buf, 0, 128);
	}
	return NULL;
}