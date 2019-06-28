#include<sys/socket.h> 
#include<unistd.h> 
#include<arpa/inet.h> 
#include<stdio.h>//printfを使うから必要 
#define BUF_SIZE 256 
#include<string.h>//strlen使うから 
#include<stdlib.h>

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}



//メッセージを受信して表示するコード 
void commun(int sock) { 
	char buf[BUF_SIZE]; 
	int len_r;//受信文字数 
	char response[BUF_SIZE]; 
	while((len_r =recv(sock,buf,BUF_SIZE,0)) > 0){
		buf[len_r] =  '/0';
		
		printf("%s/n",buf);
		
		if(strstr(buf, "/r/n/r/n")){
			break;
		}
	}
	if(len_r < 0);
	DiewithError("received() failed");
	
	printf("received HTTP Request./n");
	sprintf(response, "HTTP/1.1 200 ok/r/n");
	
	if(send(sock, response, strlen(response), 0) != strlen) 
		DieWithError("send()sent a message of unexpected bytes"); 
	sprintf(response, "Content-Type : text/html;char");
	
	if(send(sock, response, strlen(response), 0) != strlen) 
		DieWithError("send()sent a message of unexpected bytes"); 
	sprintf(response,"/r/n");
	if(send(sock, response, strlen(response), 0) != strlen) 
		DieWithError("send()sent a message of unexpected bytes"); 
	sprintf(response,"ネットワークプログラミングのwebサイト");
	if(send(sock, response, strlen(response), 0) != strlen) 
		DieWithError("send()sent a message of unexpected bytes"); 
	sprintf(response,"</text></head><body>ネットワークダイスキ</body></html>");
	if(send(sock, response, strlen(response), 0) != strlen) 
		DieWithError("send()sent a message of unexpected bytes"); 
	
	if((len_r = recv(sock, buf, BUF_SIZE, 0)) <= 0) 
		DieWithError("recv() failed"); 
	buf[len_r] = '\0'; 
	printf("%s\n", buf); 
	if(send(sock, buf, strlen(buf), 0) != strlen(buf)) 
	DieWithError("send() sent a message of unexpected bytes"); 
} 


int main(int argc, char **argv) { 
	//clisok:ほかのとこでやってねってやつ 
	//servsock:待ち受け専用 
	int cliSock; 
	int servSock = socket(PF_INET, SOCK_STREAM, 0); 
	struct sockaddr_in servAddress; 
	struct sockaddr_in clientAddress; 
	unsigned int szClientAddr; 
	 
	servAddress.sin_family = AF_INET; 
	servAddress.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY:インターネットのアドレスだったらなんでもいい 
	servAddress.sin_port = htons(80);//80番ポートも接続してきたら対応する 
	bind(servSock, (struct sockaddr *)&servAddress, sizeof(servAddress)); 
	listen(servSock, 5);//順番待ちできるクライアント数(接続待ち数) 
	while(1){ 
		szClientAddr = sizeof(clientAddress); 
		cliSock = accept(servSock, (struct sockaddr *)&clientAddress, &szClientAddr); 
		commun(cliSock); 
	} 
	 
	close(servSock); 
	return 0; 
} 