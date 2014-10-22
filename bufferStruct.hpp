/*
 * =====================================================================================
 *
 *       Filename:  bufferStruct.hpp
 *
 *    Description:  structure of buffer
 *
 *        Version:  1.0
 *        Created:  Monday 20 October 2014 07:32:36  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  COGNIZANT
 *
 * =====================================================================================
 */
#ifndef _BUFFERSTRUCT_HPP_
#define _BUFFERSTRUCT_HPP_

typedef struct _storage storage;
struct _storage{
	std::string       ipAddress;
	long unsigned int noOfCount;
	long unsigned int dataSizeUpLink;
	long unsigned int dataSizeDownLink;
//	time_t            lastAccessTime;
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
typedef std::map < std::string , storage >_mappingIp ;

typedef struct _buffStruct buffStruct;
struct _buffStruct{
	bool isActive;
	_mappingIp mappedIp;
};

typedef std::map < int , bool > _indexStorage;
extern buffStruct *buffStructStorage;//[10]; // circular buffer storage

#endif
