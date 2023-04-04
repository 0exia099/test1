#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
	
#define BUF_SIZE 100
#define NAME_SIZE 20
	
void * send_msg(void * arg);
void * recv_msg(void * arg);
void error_handling(char * msg);
	
char name[NAME_SIZE]="[DEFAULT]";
char msg[BUF_SIZE];
	
int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	pthread_t snd_thread, rcv_thread;
	void * thread_return;
	if(argc!=4) {
		printf("Usage : %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	 }
	
	sprintf(name, "[%s]", argv[3]);
	//create socket
	sock=socket(PF_INET, SOCK_STREAM, 0);
	//set socket information(connect에 사용할 소켓정보 입력)
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	 //connect
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("connect() error");
	//screen clear(대기실 화면으로 초기화)
	system("clear");
	fputs("====================================================================\n", stdout);
	fputs("\t\t\tWaiting Room\n", stdout);
	fputs("\t#mkRoom : Create a chat room\n", stdout);
	fputs("\t#jRoom (number) : Enter the room with that (number).\n", stdout);
	fputs("\tq : exit\n", stdout);
	fputs("\t(message) : Send (message)s to the people in the waiting room or chat room\n", stdout);
	fputs("\t@all (message) : Send (message)s to all people on the server\n", stdout);
	fputs("\t@(name) (message)r : Send a (message) only to people with that (name)\n", stdout);
	fputs("\tdon't use +, - at the beginning of a message\n", stdout);
	fputs("====================================================================\n", stdout);
	write(sock, argv[3], strlen(argv[3]));
	//thread start
	pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
	pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
	//thread join
	pthread_join(snd_thread, &thread_return);
	pthread_join(rcv_thread, &thread_return);
	close(sock);  
	return 0;
}
	
void * send_msg(void * arg)   // send thread main
{
	int sock=*((int*)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	int in_room = 0;//variables that determine if this is a chat room(채팅방인지 대기실인지 나타내는 변수. 0이면 대기실, 1이면 채팅방)
	char command[10];
	int i;

	while(1) 
	{
		fgets(msg, BUF_SIZE, stdin);
		strncpy(command, msg, 6);
		command[6] = '\0';
		//the message that goes into the chat room(채팅방에 들어가는 명령어(메시지)인 경우)
		if(!strcmp(msg,"#mkRoom\n") || !strcmp(command,"#jRoom"))
		{
			system("clear");//set screen chat room(채팅방 화면으로 초기화)
			fputs("********************************************************************\n", stdout);
			fputs("\t\t\tROOM\n", stdout);
			fputs("q : exit\n", stdout);
			fputs("(message) : Send (message)s to the people in the waiting room or chat room\n", stdout);
			fputs("@all (message) : Send (message)s to all people on the server\n", stdout);
			fputs("@(name) (message)r : Send a (message) only to people with that (name)\n", stdout);
			fputs("********************************************************************\n", stdout);
			in_room = 1;//chat room
			sprintf(name_msg,"%s %s", name, msg);
			write(sock, name_msg, strlen(name_msg));//send command(명령어 전송)
			sprintf(name_msg,"+%s is join the room+\n", name);
			write(sock, name_msg, strlen(name_msg));//send join message(채팅방 참가 메시지 전송)
		}
		else if(!strcmp(msg,"q\n")||!strcmp(msg,"Q\n")) 
		{
			if(in_room==0)//if not chat room(대기실에서 q)
			{
				sprintf(name_msg,"-%s is disconnected-\n", name);
				write(sock, name_msg, strlen(name_msg));//disconnect message(연결 종료 메시지 전송)
				close(sock);
				exit(0);
			}
			else//chat room->waiting room(채팅방에서 q)
			{
				system("clear");//(대기실 화면으로 초기화)
				fputs("====================================================================\n", stdout);
				fputs("\t\t\tWaiting Room\n", stdout);
				fputs("\t#mkRoom : Create a chat room\n", stdout);
				fputs("\t#jRoom (number) : Enter the room with that (number).\n", stdout);
				fputs("\tq : exit\n", stdout);
				fputs("\t(message) : Send (message)s to the people in the waiting room or chat room\n", stdout);
				fputs("\t@all (message) : Send (message)s to all people on the server\n", stdout);
				fputs("\t@(name) (message)r : Send a (message) only to people with that (name)\n", stdout);
				fputs("\tdon't use +, - at the beginning of a message\n", stdout);
				fputs("====================================================================\n", stdout);
				sprintf(name_msg,"-%s is get out the room-\n", name);
				write(sock, name_msg, strlen(name_msg));//exit message(채팅방에서 나가는 메세지 전송)
				in_room = 0;//waiting room
			}
		}
		else//다 아니면 메시지 전송
		{
			sprintf(name_msg,"%s %s", name, msg);
			write(sock, name_msg, strlen(name_msg));
		}
		
	}
	return NULL;
}
	
void * recv_msg(void * arg)   // read thread main
{
	int sock=*((int*)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	int str_len;

	while(1)
	{
		sprintf(name_msg, " ");
		str_len=read(sock, name_msg, NAME_SIZE+BUF_SIZE-1);
		if(str_len==-1) 
			return (void*)-1;
		name_msg[str_len]=0;
		if(name_msg[0] == '|')//receive clear message(화면 초기화 메세지 받으면)
		{
			system("clear");//대기실 화면 초기화
			fputs("====================================================================\n", stdout);
			fputs("\t\t\tWaiting Room\n", stdout);
			fputs("\t#mkRoom : Create a chat room\n", stdout);
			fputs("\t#jRoom (number) : Enter the room with that (number).\n", stdout);
			fputs("\tq : exit\n", stdout);
			fputs("\t(message) : Send (message)s to the people in the waiting room or chat room\n", stdout);
			fputs("\t@all (message) : Send (message)s to all people on the server\n", stdout);
			fputs("\t@(name) (message)r : Send a (message) only to people with that (name)\n", stdout);
			fputs("\tdon't use +, - at the beginning of a message\n", stdout);
			fputs("====================================================================\n", stdout);
		}
		else
		{
			fputs(name_msg, stdout);
		}
	}
	return NULL;
}
	
void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
