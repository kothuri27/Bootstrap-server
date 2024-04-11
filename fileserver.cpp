
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
#include<tuple>
using namespace std;
int size=1024;
const int backLog = 3;
int main()
{
	//string buffer;
	int u_port=9899;
	int P_port=8888;
	int udpsocketid;

    struct sockaddr_in udp_serverAddr, server, client_server;
	socklen_t sinSize = sizeof(struct sockaddr_in);
    char buffer[1024];
  	socklen_t addr_size;
	int tcpsocket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
	if(tcpsocket == -1){
		cout<<"Error creating socket"<<endl;
	}
	else{
		cout<<"Socket created sucessfully"<<endl;
	}
	string ip_of_server = "127.0.0.2";
	cout<<"Enter IP of server"<<endl;
	cin>>ip_of_server;
	string port_no;
	cout<<"enter port number"<<endl;
	cin>>port_no;
	cout<<"ENTER THE TYPE OF SERVER YOU WANT TO MAKE   *****DISCLAIMER DONT USE SAME NAME FOR DIFFERENT SERVER*****"<<endl;
  cout<<" TEXTSERVER OR VEDIOSERVER OR IMAGAGESERVER or PDFSERVER"<<endl;
  cout<<"enter as mentioned above"<<endl;
	string type;
	cin>>type;
	server.sin_family = AF_INET;
	
	P_port = stoi(port_no);
	server.sin_port = htons(P_port);
	inet_pton(AF_INET,ip_of_server.c_str(),&(server.sin_addr));
	memset(&(server.sin_zero), '\0', 8);
	int bindID = bind(tcpsocket,(struct sockaddr *)&server, sizeof(struct sockaddr));
  	if(bindID != -1)
  	{
  	cout<<"binded registering to bootsrap server "<<endl;
  	}
  	else
  	{
  	cout<<"error"<<endl;
  	}
	udpsocketid = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  	memset(&udp_serverAddr, '\0', sizeof(udp_serverAddr));
	udp_serverAddr.sin_family = AF_INET;
	udp_serverAddr.sin_port = htons(u_port);
	string ip_of_bootsr = "127.0.0.1";
  	udp_serverAddr.sin_addr.s_addr = inet_addr(ip_of_bootsr.c_str());
	
  
  string port_of_server = "9803";
  //string data = "MessageType : REGESTRATION , Ipaddress : "+ip_of_server+" , Port : "+ port_of_server;//text
  string data="servicename: "+type+" servicetype: TEXT, IP_Address: "+ip_of_server+" , Port_number: "+ port_of_server+" ,service_access_token: abcd"+" :bjkl";
  sendto(udpsocketid, data.c_str(), data.size(), 0, (struct sockaddr*)&udp_serverAddr, sizeof(udp_serverAddr));//sending data to boots
  char rcv[1024];
  socklen_t siz = sizeof(client_server);
  //recvfrom(udpsocketid,rcv, sizeof(rcv),0,(struct sockaddr*)&client_server, &siz);
  //cout<<inet_ntoa(client_server.sin_addr)<<endl;
  //cout<<ntohs(client_server.sin_port)<<endl;
  //cout<<rcv<<endl;

//connecting client

 

  int tcpSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  cout<<"in file waiting for client"<<endl;
   if(!tcpSocketFd)
        { cout<<"Error creating TCP socket"<<endl; exit(1); } 
   else { cout<<"TCP socket created successfully . . . \n"; }

   struct sockaddr_in tcpSockAddressInfo;
   tcpSockAddressInfo.sin_family = AF_INET;
   tcpSockAddressInfo.sin_port = htons(stoi(port_of_server));
   inet_pton(AF_INET, ip_of_server.c_str(), &(tcpSockAddressInfo.sin_addr));
   memset(&(tcpSockAddressInfo.sin_zero), '\0', 8);

   int check = bind(tcpSocketFd, (struct sockaddr *)&tcpSockAddressInfo, sizeof(struct sockaddr)); 
   if(check == -1)
     { cout<<"Error binding TCP socket ! ! ! \n"<<endl;
       close(tcpSocketFd);   exit(1);}
   else { cout<<"TCP Binding Successful . . .\n\n"; }




   while(1)
  {

    check = listen(tcpSocketFd, backLog);  // start listining for new connections
    if(check == -1)
      { cout<<"Error listening on TCP socket"<<endl;
        close(tcpSocketFd); exit(1); }
    else {cout<<"Listining for client to connect and ask for files. . .\n\n";} 

     int B_ClientFd = accept(tcpSocketFd, (struct sockaddr *)&client_server, &sinSize);////b_client is used to recive and pass
     if (B_ClientFd == -1)
     {
        cout<<"Error with new file server connection :"<<endl;
        close(tcpSocketFd);
        exit(1);
     }
    cout<<"connected with CLIENT  * \n"<<endl;


    


  char token[1024];
  memset(&token,'\0',1024);;
  recv(B_ClientFd,token, size,0);
  string s(token);
  string code;
  code="abcd"+ip_of_server;
  if(s==code)
  {
    string p="passed";
    send(B_ClientFd,p.c_str(),p.size(),0);
	char pathname[1024];
	memset(&pathname,'\0',1024);
  socklen_t siz1 = sizeof(tcpSockAddressInfo);
	int len = recv(B_ClientFd,pathname, size,0);

	//cout<<pathname<<endl;
  cout<<"the file client is asking is "<<pathname<<endl;
  cout<<"TRANSMISSION STARTED"<<endl;
	
  int n;
  //cout << n;
  cout<<("%s",pathname)<<endl;
  FILE *f;
  f = fopen(pathname, "rb");
  char *temp;
  long filelength;
  fseek(f, 0, SEEK_END);
  filelength = ftell(f);
  char lenbuff[30];
  memset(&lenbuff,'\0',30);
  sprintf(lenbuff,"%ld",filelength);
  send(B_ClientFd,lenbuff,sizeof(lenbuff),0);
  rewind(f);
  temp = new char[filelength]; 
  while(fread(temp, filelength, 1, f) != NULL); 
  cout << temp;
  fclose(f);
  int n1 = send(B_ClientFd,temp,filelength,0);
  cout << n1 << endl;
	cout<<"at last"<<endl;

  cout<<"***********************FILE SENT TO CLIENT*******************"<<endl;
  }
  else{
    string p1="failed";
    cout<<p1<<endl;
    send(B_ClientFd,p1.c_str(),p1.size(),0);
    cout<<"unauthorized users"<<endl;
  }
  }
   
  return 0;
  }
	
	
	