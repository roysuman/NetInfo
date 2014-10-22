/*
 * =====================================================================================
 *
 *       Filename:  bufferPool.hpp
 *
 *    Description:  buffer pool
 *
 *        Version:  1.0
 *        Created:  Saturday 18 October 2014 04:18:17  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  COGNIZANT
 *
 * =====================================================================================
 */
#ifndef _BUFFER_POOL_HPP_
#define _BUFFER_POOL_HPP_
#define poolSize 10
#include <iostream>
#include <map>
#include "databaseManagement.hpp"
#include "jsonFileRead.hpp"
#include "bufferStruct.hpp"
namespace buffer{

	class BufferPool {
		private:
			_indexStorage indexStorage;
		public:
			bool initPool;
			BufferPool( );
			~BufferPool();
			bool getBuffer( int * );
			bool retBuffer( int buffId );
			
	};
}
#endif
