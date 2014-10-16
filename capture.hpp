/*
 * =====================================================================================
 *
 *       Filename:  capture.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 October 2014 09:58:55  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  SELF
 *
 * =====================================================================================
 */
#include <iostream>
#include <map>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<net/ethernet.h>
#include<netinet/ip_icmp.h>
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>
#include <csignal>
#define MAX_DEVICE_NO 15
extern void processPacket( u_char * , const pcap_pkthdr * ,
			const u_char*);
typedef struct _storage storage;
struct _storage{
	std::string       ipAddress;
	long unsigned int noOfCount;
	long unsigned int dataSizeUpLink;
	long unsigned int dataSizeDownLink;
	time_t            lastAccessTime;
	int    ahPacketCount;
    //int    noOfInterface ;
	int    udpPacketCpunt ;
	int    tcpPacketCount ;
	int    gmpPacketCount ;
	int    egpPacketCount ;
	int    pupPacketCount ;
	int    idpPacketCount ;
	int    dccpPacketCount;
	int    grePacketCount ;
	int    espPacketCount ;
	int    pimPacketCount ;
	int    rawPacketCount ;
	int    compPacketCount ;
	int    sctpPacketCount ;
	int    ipv6PacketCount ;
	int    rsvpPacketCount ;
	int    icmpPacketCount ;
	int    ipipPacketCount ;
	int    othersPacketCount ;
	int    beetphPacketCount ;
	int    udpLitePacketCount ;
	int    dummyTcpPacketCount ;

};
extern int    totalPacketCount ;
typedef std::map < std::string , storage >_mappingIp ;
extern _mappingIp mappingIp;
//extern int  noOfInterface;
//protocol count variables
/* 
extern int  tcpPacketCount ;
extern int  udpPacketCpunt;
extern int  icmpPacketCount ;
extern int  othersPacketCount;
extern int  gmpPacketCount;
extern int  totalPacketCount;
extern int  ipipPacketCount;
extern int  egpPacketCount;
extern int  pupPacketCount;
extern int  idpPacketCount;
extern int  dccpPacketCount;
extern int  rsvpPacketCount;
extern int  grePacketCount;
extern int  ipv6PacketCount;
extern int  espPacketCount;
extern int  ahPacketCount;
extern int  beetphPacketCount;
extern int  pimPacketCount;
extern int  compPacketCount;
extern int  sctpPacketCount;
extern int  udpLitePacketCount;
extern int  rawPacketCount;
extern int  dummyTcpPacketCount;
*/

extern void signalCallbackHandler( int ); 
class Sniffing{
	public:
		friend class B;
        char **interfaceList;
        int   noOfInterface;
	private:

		pcap_t * pHandle;
	public:
		Sniffing();
		~Sniffing();
        void startSniffing( std::string );
		bool showInterface( void );
        void stopSniffing( );
		bool printStatistics(){
			//std::cout<<" TCP Count [ "<<tcpPacketCount<<" ] ICMP count [ "<<icmpPacketCount<<" ] GMP count [ "<<gmpPacketCount<<" ] oThers count [ "<<othersPacketCount<<" ] "<<std::endl;
			return true;

		}
		
};

