/*
 * =====================================================================================
 *
 *       Filename:  jsonFileRead.cpp
 *
 *    Description:  reffer the header file
 *
 *        Version:  1.0
 *        Created:  Saturday 18 October 2014 05:12:40  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  COGNIZANT
 *
 * =====================================================================================
 */
#include "jsonFileRead.hpp"

json::JsonInput::JsonInput(){
	Json::Value     root;
	Json::Reader    reader;
	std::string     fileName;
	Json::Value     nodeValue;
	std::ifstream   fileHandler;
	
	fileName = "CONFIG/inputVar.json";
	initJso = true;
	try{
		fileHandler.open( fileName.c_str() );
		if ( !fileHandler.is_open() ){
			std::cout<<"Cant able to open file for json handler\n";
			initJso = false;
		}
		if ( ! ( reader.parse( fileHandler , root ) ) ){
			std::cerr<<"Failed to parse Json input for variables\n";
			initJso = false;

		}

		nodeValue = root [ "databasePath" ];
		if ( not nodeValue.isNull() ){
			inputVar.databasePath = nodeValue.asString();
		}else initJso = false;
		nodeValue = root ["databaseName"];
		if ( not nodeValue.isNull() ){
			inputVar.databaseName = nodeValue.asString();
			
		}else initJso = false ;

		nodeValue = root ["timeIntervalInSeconds"];
		if ( nodeValue.isNull() ){
			inputVar.timeIntervalInSeconds =
				nodeValue.asString();
		}else initJso = false ;
		nodeValue = root [ "memorySizeInKb"];
		if ( nodeValue.isNull() ){
			inputVar.memorySizeInKb = 
				nodeValue.asString();
		}else initJso =false;
	}
	catch ( std::exception &e ){
		std::cerr<<"Exception received:"<<e.what()<<std::endl;
		initJso = false;
	}
}
	


