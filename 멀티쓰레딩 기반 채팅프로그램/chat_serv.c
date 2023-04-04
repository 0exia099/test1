#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 100
#define MAX_CLNT 256
#define NAME_SIZE 20

void * handle_clnt(void * arg); //hendle client socket function(클라이언트 소켓을 다루기 위한 함수)
void send_msg(char * msg, int len, int sock); //check message and send function(메세지를 확인하고 보내는 함수)
void now_mem(int id);	//print out the information in the chat room with the member now. with connect message(채팅 방 정보와 현재 사용자들의 이름을 출력하는 함수. 접속 메세지도 함께보냄)
void now_mem_2(int id);	//print out the information in the chat room with the member now(채팅 방 정보와 현재 사용자들의 이름을 출력하는 함수. 접속 메세지 보내지 않음)
void make_room(int sock);	//create room function(채팅 방을 만드는 함수)
void join_room(int roomNum, int sock);	//join room function(채팅방에 들어가는 함수)
void get_out_room(int sock);	//exit chat room function(채팅방에서 나가는 동작을 처리하는 함수)
void error_handling(char * msg);

struct clnt	//client information structure(클라이언트 정보를 가지는 구조체)
{
	char name[NAME_SIZE]; //client name(클라이언트 이름)
	int name_sock;	//socket(클라이언트와 연결된 소켓 번호)
	char ip[16];	//ip(클라이언트의 ip)
	int room_num;	//the room number in which the client is participating.(클라이언트가 들어간 채팅방 번호)
	//-1 if not participating(대기실에 있다면 -1)
};
struct room	//room information structure(채팅방의 정보를 가지는 구조체)
{
	int member_cnt;	//count of member(채팅 방안의 멤버수)
	int member[10];	//member's socket(채팅 방안의 멤버의 소켓번호)
};
int room_cnt = 0;	//chat room count(아래 chat_room의 현재 수)
int clnt_cnt=0;		//client count(아래 clnt_socks의 현재 수)
struct clnt clnt_socks[MAX_CLNT];	//client(현재 접속된 클라이언트 정보가지는 배열)
struct room chat_room[MAX_CLNT];	//chat room(현재 생성된 방을 가지는 배열)
int wait_socks[MAX_CLNT];	//client in waiting room(대기실에 대기중인 클라이언트 소켓을 가지는 배열)
int wait_cnt=0;	//client in waiting room count(wait_socks의 현재 수)
pthread_mutex_t mutx;	//mutex

int main(int argc, char *argv[])
{
	char ip[16]="";
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
  	//set mutex
	pthread_mutex_init(&mutx, NULL);
	//create socket(소켓 생성)
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	//set socket(소켓 바인딩에 사용할 정보 입력)
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET; 
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	//binding
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	//listen
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	while(1)
	{
		char name[NAME_SIZE]="";
		clnt_adr_sz=sizeof(clnt_adr);
		//accept
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);
		strcpy(ip, inet_ntoa(clnt_adr.sin_addr));

		pthread_mutex_lock(&mutx);
		read(clnt_sock, name, sizeof(name));
		strcpy(clnt_socks[clnt_cnt].name, name);	//set client name
		strcpy(clnt_socks[clnt_cnt].ip, ip);		//set client ip
		clnt_socks[clnt_cnt].room_num = -1;		//set room num
		clnt_socks[clnt_cnt++].name_sock=clnt_sock;	//set client socket
		wait_socks[wait_cnt++] = *((int*)&clnt_sock);	//add wait_socks
		pthread_mutex_unlock(&mutx);
		//start a thread dealing with a socket that is connected to a client(accept한 소켓으로 쓰레드 생성, 실행)
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
		pthread_detach(t_id);
		//print client
		printf("Connected client\n IP: %s \n", ip);
		printf(" NAME: %s \n", name);
	}
	close(serv_sock);
	return 0;
}
	
void * handle_clnt(void * arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0, i;
	char msg[BUF_SIZE];

	now_mem(clnt_sock);	//print waiting room members, chat room information(현재 사용자들 이름, 채팅방 정보 출력 및 연결 메시지 전송)
	
	//receive untill connection ends(연결 종료 시 까지 메시지를 받는다)
	while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
		send_msg(msg, str_len, clnt_sock);	//forward current client socket
	
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)   //remove disconnected client
	{
		if(clnt_sock==clnt_socks[i].name_sock)
		{
			strcpy(msg,"[");
			strcat(msg, clnt_socks[i].name);
			strcat(msg, "] is disconnected");
			//print disconnected client
			printf("Disconnected client\n IP: %s \n", clnt_socks[i].ip);
			printf(" NAME: %s \n", clnt_socks[i].name);
			while(i <clnt_cnt-1)
			{
				strcpy(clnt_socks[i].name, clnt_socks[i+1].name);
				strcpy(clnt_socks[i].ip, clnt_socks[i+1].ip);
				clnt_socks[i]=clnt_socks[i+1];
				i++;
			}

			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);
	return NULL;
}
void send_msg(char * msg, int len, int sock)
{
	int i;
	int count=0;
	int sender_len;
	char command[10];
	char roomNumber[4];
	char res_name[NAME_SIZE];
	char room_info[BUF_SIZE];
	int room_num;

	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)
	{
		if(sock==clnt_socks[i].name_sock)
		{
			room_num = clnt_socks[i].room_num;	//find current client's room num(클라이언트가 들어간 방 번호 찾는다)
		}
	}
	pthread_mutex_unlock(&mutx);
	
	for(i = 0; msg[i]!=']';i++)
		;
	sender_len = i+1;	//message content start point(보내는 사람 이름 다음까지)

	if(msg[0] == '+' || msg[0] == '-')//connect, disconnect, join chat room, exit chat room message
	{
		if(msg[0] == '+')
		{
			if(room_num == -1)//connect message
			{
				//this is send from now_mem function(now_mem 함수에서 연결 메시지 보냄)
			}
			else//join chat room message
			{
				pthread_mutex_lock(&mutx);
				//send join message to same chat room member(채팅방 들어갈때 메시지 채팅방 전원에게 보냄)
				for(i=0; i<chat_room[room_num].member_cnt; i++)
					write(chat_room[room_num].member[i], msg, len);
				pthread_mutex_unlock(&mutx);
			}
		}
		if(msg[0] == '-')
		{
			if(room_num != -1)//exit chat room message
			{
				pthread_mutex_lock(&mutx);
				//send exit message to same chat room member
				for(i=0; i<chat_room[room_num].member_cnt; i++)
					write(chat_room[room_num].member[i], msg, len);
				pthread_mutex_unlock(&mutx);
				get_out_room(sock);	//exit chat room
				room_num = -1;
				now_mem_2(sock);	//display all user, chat room information
			}
			else	//disconnect message
			{
				pthread_mutex_lock(&mutx);
				//send disconnect message to all user
				for(i=0; i<clnt_cnt; i++)
					write(clnt_socks[i].name_sock, msg, len);

				for(i=0; i<wait_cnt; i++) //remove disconnected client from wait_socks
				{
					if(sock==wait_socks[i])
					{
						while(i <wait_cnt-1)
						{
							wait_socks[i]=wait_socks[i+1];
							i++;
						}
						break;
					}
				}
				wait_cnt--;
				pthread_mutex_unlock(&mutx);
				return;
			}
		}
	}
	else if(msg[sender_len + 1] == '#')//#mkRoom(create chat room) or #jRoom(join chat room)
	{
		int temp;
		
		for(i=sender_len+2; msg[i]!=' '&&i<sender_len+8; i++)
			command[count++] = msg[i];
		command[count] = '\0';
		temp = i + 1;
		count = 0;
		if(strcmp(command, "mkRoom")==0) //cheack command
		{
			make_room(sock);//create room
		}
		else if(strcmp(command, "jRoom")==0)
		{
			for(i=temp; i<temp+4; i++)
				roomNumber[count++] = msg[i];
			roomNumber[count]='\0';
			join_room(atoi(roomNumber), sock);//join room
		}
	}
	else if(msg[sender_len + 1] != '@')// default message
	{
		if(room_num == -1)// if not in chat room
		{
			pthread_mutex_lock(&mutx);
			//send message to waiting room member
			for(i=0; i<wait_cnt; i++)
				write(wait_socks[i], msg, len);
			pthread_mutex_unlock(&mutx);
		}
		else// if in chat room
		{
			pthread_mutex_lock(&mutx);
			//send message to chat room member
			for(i=0; i<chat_room[room_num].member_cnt; i++)
				write(chat_room[room_num].member[i], msg, len);
			pthread_mutex_unlock(&mutx);
		}
	}
	else
	{
		for(i=sender_len+1;msg[i]!=' ';i++)
		{
			res_name[count++] = msg[i];
	
		}
		res_name[count] = '\0';//receive user name

		if(strcmp(res_name, "@all") == 0 || strcmp(res_name, "@ALL") == 0)// send all user
		{
			pthread_mutex_lock(&mutx);
			for(i=0; i<clnt_cnt; i++)
				write(clnt_socks[i].name_sock, msg, len);
			pthread_mutex_unlock(&mutx);
		}
		else	//send to receive user
		{
			pthread_mutex_lock(&mutx);
			for(i=0; i<clnt_cnt; i++)
			{
				if(strcmp(res_name, clnt_socks[i].name)==0)
				{
					write(clnt_socks[i].name_sock, msg, len);
				}
			}
			pthread_mutex_unlock(&mutx);
		}
	}
	
}
void now_mem(int id) //this function is used at the first connection
{
	int i, j;
	char mem_msg[NAME_SIZE+BUF_SIZE];
	char name[NAME_SIZE];
	char room_info[BUF_SIZE];
	
	pthread_mutex_lock(&mutx);
	//print room information
	for(j=0;j<room_cnt;j++)
	{	
		sprintf(room_info, "***server*** room number : %d / member [%d/10]\n", j, chat_room[j].member_cnt);
		write(id, room_info, strlen(room_info));
	}
	//print all user
	for(i = 0; i < clnt_cnt; i++)
	{
		
		sprintf(mem_msg,"  member : %s\n", clnt_socks[i].name);
		write(id, mem_msg, strlen(mem_msg));
		//send connect message
		if(id==clnt_socks[i].name_sock)
		{
			sprintf(name,"%s", clnt_socks[i].name);
			sprintf(mem_msg,"+%s is connected+\n", name);
			for(j=0; j<clnt_cnt; j++)
				write(clnt_socks[j].name_sock, mem_msg, strlen(mem_msg));
			break;
		}
	}
	pthread_mutex_unlock(&mutx);
}
void now_mem_2(int id) //this function is used for display all user, room information
{
	int i, j;
	char mem_msg[NAME_SIZE+BUF_SIZE];
	char name[NAME_SIZE];
	char room_info[BUF_SIZE];
	
	pthread_mutex_lock(&mutx);
	//display room information
	for(j=0;j<room_cnt;j++)
	{	
		sprintf(room_info, "***server*** room number : %d / member [%d/10]\n", j, chat_room[j].member_cnt);
		write(id, room_info, strlen(room_info));
	}
	//display all user
	for(i = 0; i < clnt_cnt; i++)
	{
		sprintf(mem_msg,"  member : %s\n", clnt_socks[i].name);
		write(id, mem_msg, strlen(mem_msg));
	}
	pthread_mutex_unlock(&mutx);
}
void make_room(int sock)
{
	int i, j;
	int copy_wait_socks[MAX_CLNT];
	int cnt;
	char room_info[BUF_SIZE];
	pthread_mutex_lock(&mutx);
	//set room information
	chat_room[room_cnt].member_cnt = 1;	
	chat_room[room_cnt].member[0] = sock;
	for(i=0; i<wait_cnt; i++) //remove client form wait_socks
	{
		if(sock==wait_socks[i])
		{
			while(i <wait_cnt-1)
			{
				wait_socks[i]=wait_socks[i+1];
				i++;
			}

			break;
		}
	}
	wait_cnt--;
	for(i=0; i<clnt_cnt; i++)
	{
		if(sock==clnt_socks[i].name_sock)
		{
			clnt_socks[i].room_num = room_cnt;	//set client's room num
		}
	}
	room_cnt++;
	char clear_msg[5] = "|";	//clear message to clean up the client screen
	cnt = wait_cnt;
	for(i=0; i<wait_cnt; i++)
	{
		write(wait_socks[i], clear_msg, strlen(clear_msg));//send clear message to waiting room member
		copy_wait_socks[i] = wait_socks[i];
	}
	pthread_mutex_unlock(&mutx);
	sleep(1);	//wait for client to clear
	//display room information, all user to waiting room member
	for(i=0;i<cnt;i++)
		now_mem_2(copy_wait_socks[i]);
}
void join_room(int roomNum, int sock)
{
	int i;
	char mem_msg[BUF_SIZE];

	pthread_mutex_lock(&mutx);
	//set room information
	chat_room[roomNum].member_cnt++;
	chat_room[roomNum].member[chat_room[roomNum].member_cnt-1] = sock;
	for(i=0; i<wait_cnt; i++)	//remove client form wait_socks
	{
		if(sock==wait_socks[i])
		{
			while(i <wait_cnt-1)
			{
				wait_socks[i]=wait_socks[i+1];
				i++;
			}

			break;
		}
	}
	wait_cnt--;
	for(i=0; i<clnt_cnt; i++)
	{
		if(sock==clnt_socks[i].name_sock)
		{
			clnt_socks[i].room_num = roomNum;//set client's room num
		}
		if(roomNum == clnt_socks[i].room_num)
		{
			//display room member
			sprintf(mem_msg,"  member : %s\n", clnt_socks[i].name);
			write(sock, mem_msg, strlen(mem_msg));
		}
	}
	pthread_mutex_unlock(&mutx);
}
void get_out_room(int sock)
{
	int i, roomNum;
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)
	{
		if(sock==clnt_socks[i].name_sock)
		{
			roomNum = clnt_socks[i].room_num;
			clnt_socks[i].room_num = -1;//set client's room num
		}
	}

	wait_socks[wait_cnt++] = sock;//add client to wait_socks
	//set room information
	for(i=0; i<chat_room[roomNum].member_cnt; i++)
	{
		if(sock==chat_room[roomNum].member[i])
		{
			while(i <chat_room[roomNum].member_cnt-1)
			{
				chat_room[roomNum].member[i]=chat_room[roomNum].member[i+1];
				i++;
			}

			break;
		}
	}
	chat_room[roomNum].member_cnt--;
	pthread_mutex_unlock(&mutx);
}
void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
