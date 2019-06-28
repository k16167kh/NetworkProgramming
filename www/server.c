#include<sys/socket.h> 
#include<unistd.h> 
#include<arpa/inet.h> 
#include<stdio.h>//printf���g������K�v 
#define BUF_SIZE 256 
#include<string.h>//strlen�g������ 
#include<stdlib.h>

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}



//���b�Z�[�W����M���ĕ\������R�[�h 
void commun(int sock) { 
	char buf[BUF_SIZE]; 
	int len_r;//��M������ 
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
	sprintf(response,"�l�b�g���[�N�v���O���~���O��web�T�C�g");
	if(send(sock, response, strlen(response), 0) != strlen) 
		DieWithError("send()sent a message of unexpected bytes"); 
	sprintf(response,"</text></head><body>�l�b�g���[�N�_�C�X�L</body></html>");
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
	//clisok:�ق��̂Ƃ��ł���Ă˂��Ă�� 
	//servsock:�҂��󂯐�p 
	int cliSock; 
	int servSock = socket(PF_INET, SOCK_STREAM, 0); 
	struct sockaddr_in servAddress; 
	struct sockaddr_in clientAddress; 
	unsigned int szClientAddr; 
	 
	servAddress.sin_family = AF_INET; 
	servAddress.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY:�C���^�[�l�b�g�̃A�h���X��������Ȃ�ł����� 
	servAddress.sin_port = htons(80);//80�ԃ|�[�g���ڑ����Ă�����Ή����� 
	bind(servSock, (struct sockaddr *)&servAddress, sizeof(servAddress)); 
	listen(servSock, 5);//���ԑ҂��ł���N���C�A���g��(�ڑ��҂���) 
	while(1){ 
		szClientAddr = sizeof(clientAddress); 
		cliSock = accept(servSock, (struct sockaddr *)&clientAddress, &szClientAddr); 
		commun(cliSock); 
	} 
	 
	close(servSock); 
	return 0; 
} 