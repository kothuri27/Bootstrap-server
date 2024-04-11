#include <sys/socket.h>
#include <string>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
#include<tuple>
using namespace std;
int size=1024;
void recieve(string lastname,int socketfid)
{
  char *recv_buffer;
  char len_buff[40];
  memset(&len_buff, '\0',40);
  FILE *f;
  f = fopen(lastname.c_str(), "wb");
  int count;
  count = recv(socketfid,len_buff,sizeof(len_buff),0);
  long totarecv_bufferlength = atoi(len_buff);
  //cout << totarecv_bufferlength;
  //total buffer recived cout>>"recived";
  recv_buffer = new char[totarecv_bufferlength];
  //memset(&recv_buffer, '\0',totarecv_bufferlength);
  int bytes_sent = 0;
  int bytes_left = totarecv_bufferlength;
  while(totarecv_bufferlength> bytes_sent){
    count = recv(socketfid,recv_buffer+bytes_sent,bytes_left,0);
    //cout << count << endl;
    bytes_sent+=count;
    bytes_left-=count;
    
    /*char msg[90];
  printf("enter the filename send to be send to server:\n");
  scanf("%s",msg);
  bzero(buffer,1024);
  strcpy(buffer,msg);*/
  }
  //cout << recv_buffer;
  fwrite(recv_buffer,1,totarecv_bufferlength,f);
  fclose(f);
  return;
}
void transer(int socketfid, string pathname)
{
    string lastname = "recieved.   ";
    for(int start=0;start<pathname.length();start++)
    {
      if(pathname[start]=='.')
      {
        int m = 0;
        int i=start+1;
        for(int j=start+1;j<pathname.length();j++)
        {
        lastname[8+m] = pathname[i];
        m++;
        }
        break;
      }
    }
    cout << lastname;
    recieve(lastname,socketfid);
  }
int main()
{
	//string buffer;
	int u_port=9899;//boots port 
	int P_port=8888;
	int udpsocketid;
    struct sockaddr_in udp_serverAddr, client_server;
    char buffer[1024];
  	socklen_t addr_size;
	udpsocketid = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  	memset(&udp_serverAddr, '\0',  sizeof(udp_serverAddr));
	udp_serverAddr.sin_family = AF_INET;
	udp_serverAddr.sin_port = htons(u_port);
  	udp_serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    string ip_of_server =   "127.0.0.8";
    string port_of_server = "9813";
    string data1 = "MessageType : DISCOVERY";
    sendto(udpsocketid, data1.c_str(), data1.size(), 0, (struct sockaddr*)&udp_serverAddr, sizeof(udp_serverAddr));//sending through udp
    string x;
   cout<<"enter the server you want to connect"<<endl;
   cout<<" TEXTSERVER OR VEDIOSERVER OR IMAGAGESERVER OR PDFSERVER"<<endl;
   cout<<"enter as mentioned above"<<endl;
   cin>>x;
   data1=x;
   sendto(udpsocketid, x.c_str(), x.size(), 0, (struct sockaddr*)&udp_serverAddr, sizeof(udp_serverAddr));//sending through abut the server he need
    char rcv[1024];
    socklen_t siz = sizeof(client_server);
    recvfrom(udpsocketid,rcv, sizeof(rcv),0,(struct sockaddr*)&client_server, &siz);
    //cout<<"needed recived_ from boots"<<endl;
    cout<<rcv<<endl;
    string str(rcv);
    vector<string>temp;
    string word = "";
	for (auto x : str)
	{
		if (x == ' ')
		{
		//cout << word << endl;
            temp.push_back(word);
			word = "";
		}
		else {
			word = word + x;
		}
	}
	//cout << word << endl;
    temp.push_back(word);
    string serverIpAddr=temp[0];
    cout<<serverIpAddr<<endl;
    string port_no1=temp[1];
    string token =temp[2];
    string type=temp[3];
    cout<<port_no1<<endl;
    cout<<"YOUR(client) CONNECTED to the "+type+ "OF IPADDRESS :"<<serverIpAddr<<"  and THE PORT NUMBER IS :"<<port_no1<<"token :"<<token<<endl;
    int tcpPort = stoi(port_no1);
     struct sockaddr_in server_addr,si_other;
     int tcpSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(tcpSocketFd ==-1)
        { cout<<"Error creating TCP socket"<<endl; exit(1); } 
   else { cout<<"TCP socket created successfully  WITH BOOTSRAP. . . \n"; }

   struct sockaddr_in tcpSockAddressInfo;
   tcpSockAddressInfo.sin_family = AF_INET;
   tcpSockAddressInfo.sin_port = htons(tcpPort);
   inet_pton(AF_INET, serverIpAddr.c_str(), &(tcpSockAddressInfo.sin_addr));
   memset(&(tcpSockAddressInfo.sin_zero), '\0', 8);
   
   int check = connect(tcpSocketFd, (struct sockaddr *)&tcpSockAddressInfo, sizeof(struct sockaddr));
   if (check == -1)
     { cout<<"Error with file server connection "<<endl;                                                       
     }
   else { cout<<"B_CLIENT connected with FILE SERVER . . .\n"; }
   
   //addr_size = sizeof(si_other);
   //send(tcpSocketFd, x.c_str(),x.size(),0);
   cout<<"verifying token with fileserver"<<endl;
   send(tcpSocketFd, token.c_str(),token.size(),0);//send token to 
   char len_buff[40];
   memset(&len_buff, '\0',40);
   recv(tcpSocketFd,len_buff,sizeof(len_buff),0);//tcpsocket from boots
   string s(len_buff);
   //cout<<"authentication message from the server is           "<<s<<endl;
   if(s=="passed")
  {
   cout<<"AUTHENTICATION_DONE"<<endl; 
   cout<<"enter the name of the file which is stored in the same local location"<<endl;
   string data;
   cin>>data;
   send(tcpSocketFd, data.c_str(),data.size(),0);//sendind data to fileserver//filename
   cout<<"data reciving started"<<endl;
   transer(tcpSocketFd,data);
  cout<<"********** data RECVIED successfully.\n*******";
	cout<<"********* connection closed .\n*********";
  exit(0);
  }
  else
  {
    cout<<"AUTHENTICATION FAILED"<<endl;
    exit(0);
  }
  

  

}