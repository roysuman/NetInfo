/*
 * =====================================================================================
 *
 *       Filename:  bufferPool.cpp
 *
 *    Description:  see the header file
 *
 *        Version:  1.0
 *        Created:  Saturday 18 October 2014 04:39:53  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  COGNIZANT
 *
 * =====================================================================================
 */
#include "bufferPool.hpp"
//using namespace buffer;
buffStruct    *buffStructStorage ;//= new buffer::buffStruct[10];//[10]; // circular buffer storage
buffer::BufferPool::BufferPool(  ){
	try{
		buffStructStorage = new buffStruct [ poolSize ];
		initPool = true;
	}
	catch ( std::exception &e ){
		std::cerr<<"Exception occured duringcreating pool"<<e.what()<<std::endl;
		initPool = false;
	}
      for ( int loop = 0 ; loop < poolSize ; ++loop ){
	      indexStorage.insert ( std::pair < int , bool > ( loop , false ) );
	      
	      buffStructStorage[ loop ].isActive = false;

      }

}

buffer::BufferPool::~BufferPool(){
	//dissector
	try{
		delete []buffStructStorage;
	}
	catch( std::exception &e ){
		std::cerr<<"Exception occured during returning memory\
			at buffer pool"<<e.what()<<std::endl;
	}
}

bool buffer::BufferPool::getBuffer( int *poolIndex ){

	_indexStorage::iterator    it; 
	bool                       returnValue;

	it = indexStorage.begin();
	if ( it != indexStorage.end() ){
		*poolIndex = (*it).first;
		indexStorage.erase( it );

		//_mappingIp it2 = buffStructStorage [ *poolIndex ].mappedIp;

//		(*it).second.ahPacketCount = (*it).second.udpPacketCpunt = ( *it).second.tcpPacketCount = 0;

		//init count = 0;
		returnValue = true;

	}else{
		*poolIndex = -1;
		returnValue =false;
	}

	return returnValue;

}

bool buffer::BufferPool::retBuffer(int buffId ){

	bool          retValue;

	try{
		//perform the db insert/update operation then insert
		//the free buffer
		database::DbManager dbInstance;
		dbInstance.insertData( &buffStructStorage[ buffId] );

		indexStorage.insert ( std::pair < int , bool > ( buffId   , true ) );
		retValue = true;
	}
	catch ( std::exception &e ){
		std::cerr<<"Exception received "<<e.what()<<std::endl;
		retValue = false;
	}
	return retValue;
}
