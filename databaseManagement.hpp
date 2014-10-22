/*
 * =====================================================================================
 *
 *       Filename:  databaseManagement.hpp
 *
 *    Description:  push and pull data from sqlite3 database
 *
 *        Version:  1.0
 *        Created:  Saturday 18 October 2014 02:52:02  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  SUMAN
 *
 * =====================================================================================
 */
#ifndef _DATABASEMANAGEMENT_HPP_
#define _DATABASEMANAGEMENT_HPP_
#include <iostream>
#include <sstream>
#include <sqlite3.h>
#include <stdlib.h>
#include "jsonFileRead.hpp" 
#include "bufferPool.hpp"
#include "bufferStruct.hpp"
namespace database{
extern int callback ( void * , int , char** , char**);
	class DbManager: public json::JsonInput {
		private:
			sqlite3        *db;
			bool           initDb;
		public:
			DbManager( void );
			~DbManager(void );
			bool closeDb( void );
			bool createDb( void );
			bool createTable( void );
			std::string quotesql( const std::string& );

			/*-----------------------------------------------------------------------------
			 *  insert the captured packet value into database
			 *-----------------------------------------------------------------------------*/
			bool insertData ( buffStruct * ); 

	};

}
#endif
