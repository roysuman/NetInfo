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
#ifndef _CAPTURE_HPP_
#define _CAPTURE_HPP_
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
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include "bufferPool.hpp"

#define MAX_DEVICE_NO 15
extern void processPacket( u_char * , const pcap_pkthdr * ,
			const u_char*);
extern int activeBufferIndex;
extern void signalCallbackHandler( int ); 
class Sniffing: public buffer::BufferPool{
	private:

	public:
        char **interfaceList;
        int   noOfInterface;
	boost::asio::io_service    io;
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
		void swapBufferIndex( const boost::system::error_code& , boost::asio::deadline_timer*  );
		
		
};
#endif
