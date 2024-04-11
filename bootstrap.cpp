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
int main()
{
	struct sockaddr_in si_me, si_other;
  char buffer[1024];
  //string buffer;
  socklen_t addr_size;
  int udp_port=9899;
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  string ipAddr = "127.0.0.1";
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(udp_port);
  inet_pton(AF_INET,ipAddr.c_str(),&(si_me.sin_addr));
  memset(&(si_me.sin_zero), '\0', 8);
  int check= bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));
  if(check != -1)
  	{
  	cout<<"******* BINDING DONE ON BOOTSTRAP ******* "<<endl;
  	}
  else
  {
	cout<<"error"<<endl;
  }
  cout<<"WAITING FOR FILE_SERVER TO CONNECT"<<endl;
  vector<vector<string> > vec;
  addr_size = sizeof(si_other);
  memset(&(buffer), '\0', 1024);
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);//registations for texrserver
  cout<<"REGISTERING USING UDP"<<endl;
  string s(buffer);
  stringstream st(s);
  vector<string>temp;
  string word;
  while(st>> word){
    //cout<<word<<endl;
    if(word!=":")
    temp.push_back(word);
  }
  /*for(int i=0;i<temp.size();i++)
  {
    cout<<temp[i]<<endl;
  }*/
  vec.push_back(temp);
  //cout<<"THE TYPE IS STORED IS      "<<vec[0][1]<<endl;
  cout<<"REGISTRATION DONE FOR   " <<vec[0][1]<<endl;
  cout<<"***********************************************************"<<endl;
   cout<<"BIND ANOTHER SERVER"<<endl;
   memset(&(buffer), '\0', 1024);
   recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);//registations of image server
   cout<<"REGISTERING USING UDP"<<endl;
  vector<string>temp2;
   string s2(buffer);
  stringstream img(s2);
  string word1;
  while(img>> word1){
    //cout<<word<<endl;
    if(word1!=":")
    temp2.push_back(word1);
  }
  /*for(int i=0;i<temp.size();i++)
  {
    cout<<temp2[i]<<endl;
  }/*/
  vec.push_back(temp2);
  //cout<<"registration for image server done"<<endl;
  //cout<<"THE TYPE IS STORED IS      "<<vec[1][1]<<endl;
  cout<<"REGISTRATION DONE FOR   " <<vec[1][1]<<endl;
  cout<<"***********************************************************"<<endl;
   cout<<"BIND ANOTHER SERVER"<<endl;



recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);//registations of vedio server
cout<<"REGISTERING USING UDP"<<endl;
  vector<string>temp3;
   string s3(buffer);
  stringstream ved(s3);
  string word2;
  while(ved>> word2){
    //cout<<word<<endl;
    if(word!=":")
    temp3.push_back(word2);
  }
  vec.push_back(temp3);
  cout<<"REGISTRATION DONE FOR   " <<vec[2][1]<<endl;
  cout<<"***********************************************************"<<endl;
   cout<<"BIND ANOTHER SERVER"<<endl;

  /*/
  /*cout<<"*****************************"<<endl;
   for(int i=0;i<vec.size();i++)
  {
    cout<<vec[i][1]<<endl;
  }
  /*for(int i=0;i<vec.size();i++)
  {
    for(int j=0;j<vec[i].size();j++)
    {
      cout<<vec[i][j]<<endl;
    }
    
  }/*/
  //the type of server is stored in vec[i][1]
  //the ip in vec[i][5]
  //the port in v[i][8]
  //THE TPKEN IN V[I][10]/*/
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);//registations of PDF server
  cout<<"REGISTERING USING UDP"<<endl;
  vector<string>temp4;
   string s4(buffer);
  stringstream pdf(s4);
  string word3;
  while(pdf>> word3){
    //cout<<word<<endl;
    if(word!=":")
    temp4.push_back(word3);
  }
  vec.push_back(temp4);
  cout<<"REGISTRATION DONE FOR   " <<vec[3][1]<<endl;
  cout<<"BINDING ALL THE SERVERS IS DONE"<<endl;

  
  while(1)
  {
    cout<<"***********************************************************"<<endl;

    cout<<"STRAT THE CLIENT PROGRAM"<<endl;
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);//message from clinet//registration done from client
  
  cout<<"MessageType : DISCOVERY"<<endl;
  cout<<"DISCOVERY IS DONE USING UDP"<<endl;
   memset(&(buffer), '\0', 1024);
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);//choice of the client
  cout<<"the choice of the client is "<<buffer<<endl;
  string choice(buffer);
  int m;
  for(int i=0;i<vec.size();i++)
  {
    if(choice==vec[i][1])
    {
      m=i;
      break;
    }

  }
  /*for(int i=0;i<vec.size();i++)
  {
    cout<<"stored values are :"<<vec[i][1];
  }*/
  string type=vec[m][1];
  string ip=vec[m][5];
  string port=vec[m][8];
  string token=vec[m][10]+ip;
  string x=ip+" "+port+" "+token+" "+type+" cnxu";
  cout<<"connected is  client token is shared"<<endl;
  sendto(sockfd,x.c_str(),x.size(),0,(struct sockaddr*)& si_other, addr_size);
  cout<<"DATA SEND TO CLIENT USING TCP"<<endl;
  }

  return 0;
}