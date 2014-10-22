/*
 * =====================================================================================
 *
 *       Filename:  jsonFileRead.hpp
 *
 *    Description:  read input parameters from a json file
 *
 *        Version:  1.0
 *        Created:  Saturday 18 October 2014 05:09:15  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  COGNIZANT
 *
 * =====================================================================================
 */
#ifndef _JSONFILEREAD_HPP_
#define _JSONFILEREAD_HPP_
#include <iostream>
#include <fstream>
#include "jsoncpp/json.h"
#include "jsoncpp/writer.h"
namespace json{
	typedef struct _inputJsonStruct inputJsonStruct;
	struct _inputJsonStruct{
		std::string    databasePath;
		std::string    databaseName;
		std::string    timeIntervalInSeconds;
		std::string    memorySizeInKb;
	};

	class JsonInput{
		public:
			bool initJso;
			inputJsonStruct    inputVar;
			JsonInput( void );
			~JsonInput( void ){}
				
	};

}
#endif
