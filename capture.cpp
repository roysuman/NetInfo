/*
 * =====================================================================================
 *
 *       Filename:  capture.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 October 2014 10:09:57  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#include"capture.hpp"

_mappingIp    mappingIp;

int           totalPacketCount = 0;
/* 
int    ahPacketCount= 0;
int    udpPacketCpunt = 0;
int    tcpPacketCount = 0;
int    gmpPacketCount = 0;
int    egpPacketCount = 0;
int    pupPacketCount = 0;
int    idpPacketCount = 0;
int    dccpPacketCount= 0;
int    grePacketCount = 0;
int    espPacketCount = 0;
int    pimPacketCount = 0;
int    rawPacketCount = 0;
int    compPacketCount = 0;
int    sctpPacketCount = 0;
int    ipv6PacketCount = 0;
int    rsvpPacketCount = 0;
int    icmpPacketCount = 0;
int    ipipPacketCount = 0;
int    totalPacketCount = 0;
int    othersPacketCount = 0;
int    beetphPacketCount = 0;
int    udpLitePacketCount = 0;
int    dummyTcpPacketCount = 0;
*/
void processPacket( u_char * , const pcap_pkthdr * ,
			const u_char*);

Sniffing::~Sniffing(){}
Sniffing::Sniffing( ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	char         errorBuffer[ 100 ] ;
	pcap_if_t    *pAlldevsp , *pDevice ;
    noOfInterface= 0;


	interfaceList = new char*[ MAX_DEVICE_NO ];
	if ( pcap_findalldevs ( &pAlldevsp , errorBuffer ) ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]Error finding devices \t "<<errorBuffer<<std::endl;
		exit ( 0 );
	}
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]---Searching Done \n";


	for ( pDevice = pAlldevsp  ; pDevice != NULL && noOfInterface < MAX_DEVICE_NO ; 
			pDevice=pDevice->next ){
		std::cout<<"Loop:"<<noOfInterface<<"Device Name:"<<pDevice->name<<std::endl;
		if ( pDevice->name != NULL ){
			interfaceList [ ++noOfInterface ] = new char [ sizeof ( pDevice->name ) + 1 ];
			strcpy( interfaceList[ noOfInterface ] , pDevice->name );
		}
	}
}

bool Sniffing::showInterface (  ){
	int  localCountNoOfInterface = noOfInterface;
	

	while ( localCountNoOfInterface >= 0  ){
		std::cout<<noOfInterface<<"InterFaceName:"<<interfaceList[ localCountNoOfInterface-- ]<<std::endl;

	}
	return true;

}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  startSniffing
 *  Description:  start capturing packet
 *              @std::string interFaceName - name of the interface to sniff
 * =====================================================================================
 */

void Sniffing::startSniffing( std::string interFaceName ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	char    errorBuff [ 100 ];

	 if ( !( pHandle= pcap_open_live ( interFaceName.c_str() , 65536 , 1 , 0 , errorBuff ) ) ){
		 std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			 <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			 <<__TIME__<<"]"<<"Failed to open InterFace\t"<<interFaceName<<" Error:"<<errorBuff<<std::endl;
		 exit ( 0 );
	 }
	 signal ( SIGINT , signalCallbackHandler );

	 pcap_loop ( pHandle ,-1 ,  processPacket , NULL );

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  processPacket
 *  Description:  after capturing a packet from the network layer, this method take care
 *                further processes.
 * =====================================================================================
 */

void processPacket(  u_char * ucArgs ,const pcap_pkthdr *pHeader ,
		const u_char * ucBuffer ){

	std::cout<<"File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	int            iSize;
	struct iphdr   *stIpHeader;

	iSize = pHeader->len;

	/*-----------------------------------------------------------------------------
	 *  get the ip header part of this incoming packet, excluding the ethernet
	 *  header
	 *-----------------------------------------------------------------------------*/
	stIpHeader= ( struct iphdr * ) ( ucBuffer + sizeof ( struct ethhdr ) );
	char           s[20];
	char       s2[20];
	unsigned short usIphdrlen ;
	struct sockaddr_in stSource;
	struct sockaddr_in stDest;
	std::string ip1 , ip2;
	_mappingIp::iterator it ;
	storage  value;
	bool newIp;

	newIp = false;
	std::string    machineIp ="192.168.1.7";
	


	usIphdrlen =stIpHeader->ihl * 4 ;
	memset ( &stSource , 0 , sizeof ( stSource ) );
	stSource.sin_addr.s_addr = stIpHeader->saddr ;
	memset ( &stDest , 0 , sizeof ( stDest ) );
	stDest.sin_addr.s_addr = stIpHeader->daddr;
	inet_ntop(AF_INET, &(stSource.sin_addr), s, 100);
	inet_ntop(AF_INET, &(stDest.sin_addr), s2, 100);
	ip1.assign(s);// assign 
	ip2.assign(s2);
	if ( ip1 == machineIp ){
		ip1 = ip2;//ip1 is the external ip
		it = mappingIp.find ( ip2 );
	}
	else it = mappingIp.find( ip1 );
	if ( it == mappingIp.end() ){ // this is a new IP
		newIp = true;
	}
	else{
		value = it->second;
	}

	std::cout<<"SIZE of Packet is:"<<ntohs ( stIpHeader->tot_len )<<std::endl;


	++ totalPacketCount;
	switch ( stIpHeader->protocol ) // check the protocol and take action depending on protocol
		{
			case 0:
				++(value.dummyTcpPacketCount);
				break;
			case 1: //ICMP protocol
				++ value.icmpPacketCount;
				break;

				
			case 2: // IGMP protocol
				++ value.gmpPacketCount;
				break;
			case 4:
				++value.ipipPacketCount;
				break;

			case 6: //TCP protocol , this protocol we need to sniff for database port
				++ value.tcpPacketCount;
				break;
			case 8:
				++value.egpPacketCount;
				break;
			case 12:
				++value.pupPacketCount;
				break;
								
			case 17: // UDP protocol
				++value.udpPacketCpunt;
				break;
			case 22:
				++value.idpPacketCount;
				break;
			case 33:
				++value.dccpPacketCount;
				break;
			case 46:
				++value.rsvpPacketCount;
				break;
			case 47:
				++value.grePacketCount;
				break;
			case 41:
				++value.ipv6PacketCount;
				break;
			case 50:
				++value.espPacketCount;
				break;
			case 51:
				++value.ahPacketCount;
				break;
			case 94:
				++value.beetphPacketCount;
				break;
			case 103:
				++value.pimPacketCount;
				break;
			case 108:
				++value.compPacketCount;
				break;
			case 132:
				++value.sctpPacketCount;
				break;
			case 136:
				++value.udpLitePacketCount;
				break;
			case 255:
				++value.rawPacketCount;
				break;

				
			default: // some other protocol like ARP etc..
				++ value.othersPacketCount;
				break;
		}
	  
//	std::cout<<"Dummy Protocol for Tcp"<<value.dummyTcpPacketCount<<"Internet Control Message Protocol:"<<value.icmpPacketCount<<"Internet Group Management Protocol"<<value.gmpPacketCount<<"IPIP tunnel"<<value.ipipPacketCount<<"Transmission Control Protocol"<<value.tcpPacketCount<<"Exterior Gateway Protocol"<<value.egpPacketCount<<"PUP protocol"<<value.pupPacketCount<<"User Datagram Protocol(UDP)"<<value.udpPacketCpunt<<"XNS IDP Protocol"<<value.idpPacketCount<<"Datagram Congestion COntrol Protocol"<<value.dccpPacketCount<<"RSVP Protocol"<<value.rsvpPacketCount<<"Cisco GRE tunnels"<<value.grePacketCount<<"IPv6-in-IPv4 tunnelling"<<value.ipv6PacketCount<<"Encapsulation Security Payload Protocol"<<value.espPacketCount<<"Authentication Header protocol"<<value.ahPacketCount<<"IP option pseudo header for BEET"<<value.beetphPacketCount<<"Protocol Independent Multicast"<<value.pimPacketCount<<"Compression Header protocol"<<value.compPacketCount<<"Stream Control Transport Protocol"<<value.sctpPacketCount<<"UDP - Lite ( RFC 3828 )"<<value.udpLitePacketCount<<"Raw IP packets"<<value.rawPacketCount<<std::endl;
	if( newIp ){
		mappingIp.insert( std::pair < std::string, storage >( ip1 , value ) );
	}
	
}

void Sniffing::stopSniffing( ){

	std::cout<<"File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	
	try {
		pcap_close( pHandle );
	}
	catch ( std::exception &e ){
		std::cerr<<"File Name [ "<<__FILE__<<"] Function [ "<<__FUNCTION__<<"] Line [ "<<__LINE__<<"] DateTime [ "<<__DATE__<<"-"<<__TIME__<<"] Exception:"<<e.what()<<std::endl;
        exit(-1);

	}

}	


void signalCallbackHandler ( int sigNum ){
	std::cout<<"Signal received"<<sigNum<<std::endl;
	exit ( sigNum );
}
