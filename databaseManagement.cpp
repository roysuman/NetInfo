/*
 * =====================================================================================
 *
 *       Filename:  databaseManagement.cpp
 *
 *    Description:  see the header file for definetion
 *
 *        Version:  1.0
 *        Created:  Saturday 18 October 2014 02:56:17  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#include "databaseManagement.hpp"

database::DbManager::DbManager( void ){

	initDb = false;
}

bool database::DbManager::createDb( void ){
	int    flag;

	

	if ( sqlite3_open ( ( inputVar.databaseName).c_str() , &db ) != SQLITE_OK){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
			<<__FUNCTION__<<"] Line ["<<__LINE__
			<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<" DEb cant create\n";
		initDb = false;
	}
	else {
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
			<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
			Time ["<<__DATE__<<"_"<<__TIME__
			<<"]db created at path["<<inputVar.databasePath<<
			" ] database name :["<<inputVar.databaseName<<"]\n";;
		initDb = true;
	}
	return initDb;
}
	    
bool database::DbManager::closeDb ( ){

	bool   returnValue;

	if ( sqlite3_close( db ) != SQLITE_OK ) returnValue = false;
	else returnValue = true;

	return returnValue ;
}

bool database::DbManager::createTable( void ){
	bool           returnValue;
	std::string    sqlStatement;
	char           *zErrMsg;

	createDb();

	sqlStatement = "create table capturedData ( IP_ADDRESS TEXT PRIMARY KEY NOT NULL ,"\
			"SOURCE_PORT INTEGER NOT NULL ,"\
		       	"DUMMY_TCP_PACKET_COUNT INTEGER ,"\
			"ICMP_PACKET_COUNT INTEGER ,"\
			"GMP_PACKET_COUNT INTEGER ,"\
			"IPIP_PACKET_COUNT INTEGER,"\
			"TCP_PACKET_COUNT INTEGER,"\
			"EGP_PACKET_COUNT INTEGER ,"\
			"PUP_PACKET_COUNT INTEGER,"\
			"UDP_PACKET_COUNT INTEGER,"\
			"IDP_PACKET_COUNT INTEFER,"\
			"DCCP_PACKET_COUNT INTEGER,"\
			"RSVP_PACKET_COUNT INTEGER,"\
			"IPV6_PACKET_COUNT INTEGER,"\
			"ESP_PACKET_COUNT INTEGER,"\
			"AH_PACKET_COUNT INTEGER,"\
			"BEETPH_PACKET_COUNT INTEGER,"\
			"PIM_PACKET_COUNT INTEGER,"\
			"COMP_PACKET_COUNT INTEGER,"\
			"SCTP_PACKET_COUNT INTEGER,"\
			"UDPLITTLE_PACKET_COUNT INTEGER,"\
			"RAWIP_PACKET_COUNT INTEGER );";
	std::cout<<"\nSql Statement ["<<sqlStatement<<" ]\n";
	if ( sqlite3_exec( db , sqlStatement.c_str() ,callback, 0 ,&zErrMsg )  != SQLITE_OK ) {
		returnValue = false;
	}else{
		returnValue = true;
	}
	closeDb();

	return returnValue;
}






std::string database::DbManager::quotesql( const std::string &stringData){
	return std::string("\"" + stringData + std::string("\"") );
}


database::DbManager::~DbManager(){}

int database::callback( void *temp , int argc , char **argv , char **azColName ){
	std::cout<<"\n"<<__FUNCTION__<<std::endl;
	for ( int loop = 0 ; loop < argc ;loop ++ ){
		std::cout<<azColName[ loop ]<< ( argv[ loop ] ? argv [ loop ] : "NULL")<<std::endl;
	}
	return 0;
}

 
bool database::DbManager::insertData( buffStruct *currentBuffer ){
	//see whether ip already exist or not..
	_mappingIp::iterator    it;
	int                     res;
	int                     count;
	char                    *zErrMsg;
	storage                 structStore;
	bool                    returnValue;
	std::string             sqlStatement;
	sqlite3_stmt            *statement;

	count = 0;

	if ( currentBuffer->mappedIp.empty() ) returnValue = false;

	for ( it = currentBuffer->mappedIp.begin() ; it != currentBuffer->mappedIp.end() ;  ){
		structStore = (*it).second;
		std::cout<<__FUNCTION__<<"IP"<<(*it).first<<std::endl;
		createDb();

		sqlStatement=  "select count( *) from capturedData where IP_ADDRESS = '"+  (*it).first + "';";
		if ( sqlite3_prepare ( db , sqlStatement.c_str() , -1 , &statement , 0 ) == SQLITE_OK  ){
			if ( sqlite3_step ( statement ) != SQLITE_ROW ) count = 0;
			else count =  sqlite3_column_int ( statement , 0 ) ;

			std::cout<<"Count="<<count<<std::endl;

		}

		if ( count > 1 ){
			std::cerr<<"Multiple instance of the ip present--need to mearge\n";
			
		}else if ( count == 0 ){
			sqlStatement = "insert into capturedData ( IP_ADDRESS , SOURCE_PORT ,"\
					"DUMMY_TCP_PACKET_COUNT , ICMP_PACKET_COUNT ," \
					"GMP_PACKET_COUNT , IPIP_PACKET_COUNT , TCP_PACKET_COUNT ,"\
					"EGP_PACKET_COUNT , PUP_PACKET_COUNT , UDP_PACKET_COUNT ,"\
					"IDP_PACKET_COUNT , DCCP_PACKET_COUNT , RSVP_PACKET_COUNT," \
					"IPV6_PACKET_COUNT , ESP_PACKET_COUNT , AH_PACKET_COUNT,"\
					"BEETPH_PACKET_COUNT , PIM_PACKET_COUNT , COMP_PACKET_COUNT ,"\
					"SCTP_PACKET_COUNT , UDPLITTLE_PACKET_COUNT , RAWIP_PACKET_COUNT ) VALUES" \
					"('"+(*it).first+"',"
					+static_cast < std::ostringstream*> ( & (std::ostringstream ()<<(structStore.dummyTcpPacketCount)) )->str()+","
					+static_cast < std::ostringstream*>( & ( std::ostringstream() << (structStore.dummyTcpPacketCount)) )->str() + ","
					+static_cast < std::ostringstream*> ( &(std::ostringstream() << (structStore.icmpPacketCount)) )->str() +","
					+static_cast < std::ostringstream*> ( &(std::ostringstream ()<< (structStore.gmpPacketCount)) )->str()+","
					+static_cast < std::ostringstream*> ( & ( std::ostringstream()<< (structStore.ipipPacketCount)) )->str()+","
					+static_cast < std::ostringstream*> (&(std::ostringstream ()<< (structStore.tcpPacketCount)) )->str() +","
					+static_cast < std::ostringstream*>( &(std::ostringstream () << (structStore.egpPacketCount) ) )->str()+","
					+static_cast < std::ostringstream*>( &(std::ostringstream()<< (structStore.pupPacketCount )) )->str() +"," 
					+static_cast < std::ostringstream*> ( &(std::ostringstream()<<( structStore.udpPacketCpunt) ))->str()+","
					+static_cast < std::ostringstream*>( & ( std::ostringstream() << (structStore.idpPacketCount) ))->str()+","
					+static_cast < std::ostringstream*> ( & ( std::ostringstream()<< (structStore.dccpPacketCount) ) )->str()+","
					+static_cast < std::ostringstream*> ( & (std::ostringstream ()<< (structStore.rsvpPacketCount) ) )->str() +","
					+static_cast < std::ostringstream*> ( & (std::ostringstream()<< (structStore.ipv6PacketCount) ) )->str()+","
					+static_cast < std::ostringstream*> ( &(std::ostringstream()<< (structStore.espPacketCount) ) )->str() +","
					+static_cast < std::ostringstream*>( & (std::ostringstream() << ( structStore.ahPacketCount )) )->str() +","
					+static_cast < std::ostringstream*> ( &( std::ostringstream()<< ( structStore.beetphPacketCount ) ) )->str()+","
					+static_cast < std::ostringstream*> ( &( std::ostringstream()<< ( structStore.pimPacketCount) ) )->str()+ "," 
					+static_cast < std::ostringstream*>( &(std::ostringstream () << ( structStore.compPacketCount) ) )->str()  +","
					+static_cast < std::ostringstream*>( & ( std::ostringstream() <<( structStore.sctpPacketCount) ) )->str() +","
					+static_cast < std::ostringstream*> ( &( std::ostringstream()<< ( structStore.udpLitePacketCount) ) )->str()+","
					+static_cast < std::ostringstream*>( &(std::ostringstream()<< ( structStore.rawPacketCount) ) )->str() +");";
		}
		else{
			sqlStatement.clear();
			sqlStatement = "update capturedData set DUMMY_TCP_PACKET_COUNT = DUMMY_TCP_PACKET_COUNT + "
				+ static_cast < std::ostringstream*>( & ( std::ostringstream() << (structStore.dummyTcpPacketCount)) )->str() + ", ICMP_PACKET_COUNT = ICMP_PACKET_COUNT + "
				+ static_cast < std::ostringstream*> ( &(std::ostringstream() << (structStore.icmpPacketCount)) )->str() +", GMP_PACKET_COUNT = GMP_PACKET_COUNT + " 
				+static_cast < std::ostringstream*> ( &(std::ostringstream ()<< (structStore.gmpPacketCount)) )->str()+", IPIP_PACKET_COUNT = IPIP_PACKET_COUNT + " 
				+static_cast < std::ostringstream*> ( & ( std::ostringstream()<< (structStore.ipipPacketCount)) )->str()+", TCP_PACKET_COUNT = TCP_PACKET_COUNT + "
				+static_cast < std::ostringstream*> (&(std::ostringstream ()<< (structStore.tcpPacketCount)) )->str() +", EGP_PACKET_COUNT = EGP_PACKET_COUNT + "
				+static_cast < std::ostringstream*>( &(std::ostringstream () << (structStore.egpPacketCount) ) )->str()+", PUP_PACKET_COUNT = PUP_PACKET_COUNT + "
				+static_cast < std::ostringstream*>( &(std::ostringstream()<< (structStore.pupPacketCount )) )->str() +", UDP_PACKET_COUNT  = UDP_PACKET_COUNT + "
				+static_cast < std::ostringstream*> ( &(std::ostringstream()<<( structStore.udpPacketCpunt) ))->str()+", IDP_PACKET_COUNT = IDP_PACKET_COUNT + " 
				+static_cast < std::ostringstream*>( & ( std::ostringstream() << (structStore.idpPacketCount) ))->str()+", DCCP_PACKET_COUNT = DCCP_PACKET_COUNT + "
				+static_cast < std::ostringstream*> ( & ( std::ostringstream()<< (structStore.dccpPacketCount) ) )->str()+", RSVP_PACKET_COUNT = RSVP_PACKET_COUNT + "
				+static_cast < std::ostringstream*> ( & (std::ostringstream ()<< (structStore.rsvpPacketCount) ) )->str() +", IPV6_PACKET_COUNT = IPV6_PACKET_COUNT + "
				+static_cast < std::ostringstream*> ( & (std::ostringstream()<< (structStore.ipv6PacketCount) ) )->str()+", ESP_PACKET_COUNT = ESP_PACKET_COUNT + "
				+static_cast < std::ostringstream*> ( &(std::ostringstream()<< (structStore.espPacketCount) ) )->str() +", AH_PACKET_COUNT = AH_PACKET_COUNT + "
				+static_cast < std::ostringstream*>( & (std::ostringstream() << ( structStore.ahPacketCount )) )->str() +", BEETPH_PACKET_COUNT = BEETPH_PACKET_COUNT + "
				+static_cast < std::ostringstream*> ( &( std::ostringstream()<< ( structStore.beetphPacketCount ) ) )->str()+", PIM_PACKET_COUNT = PIM_PACKET_COUNT + "
				+static_cast < std::ostringstream*> ( &( std::ostringstream()<< ( structStore.pimPacketCount) ) )->str()+ ", COMP_PACKET_COUNT = COMP_PACKET_COUNT + "
				+static_cast < std::ostringstream*>( &(std::ostringstream () << ( structStore.compPacketCount) ) )->str()  +", SCTP_PACKET_COUNT = SCTP_PACKET_COUNT  + "
				+static_cast < std::ostringstream*>( & ( std::ostringstream() <<( structStore.sctpPacketCount) ) )->str() +", UDPLITTLE_PACKET_COUNT = UDPLITTLE_PACKET_COUNT + "
				+static_cast < std::ostringstream*> ( &( std::ostringstream()<< ( structStore.udpLitePacketCount) ) )->str()+", RAWIP_PACKET_COUNT = RAWIP_PACKET_COUNT + "
				+static_cast < std::ostringstream*>( &(std::ostringstream()<< ( structStore.rawPacketCount) ) )->str() +" WHERE IP_ADDRESS = '"+(*it).first +"' ;";
			//sql statement for update
			


		}
		std::cout<<"SQl statement ["<<sqlStatement<<" ] DB:{"<<db<<"}\n";
		if (  sqlite3_exec( db, sqlStatement.c_str() , callback, 0, &zErrMsg ) != SQLITE_OK ){

			std::cerr<<"error on execution\n";
		}

		returnValue = true;
		
	}
	closeDb();

	currentBuffer->mappedIp.clear();//clear the container

	return returnValue;
}
