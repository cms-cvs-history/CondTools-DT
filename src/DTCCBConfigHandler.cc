/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007/11/24 12:29:54 $
 *  $Revision: 1.1.2.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondTools/DT/interface/DTCCBConfigHandler.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondTools/DT/interface/DTConfigHandler.h"
#include "CondTools/DT/interface/DTDBSession.h"
#include "CondTools/DT/interface/DTDBDataHandle.h"
#include "CondFormats/DTObjects/interface/DTCCBConfig.h"
#include "CondFormats/DTObjects/interface/DTConfigList.h"
#include "CondCore/DBCommon/interface/AuthenticationMethod.h"
#include "CondCore/DBCommon/interface/Exception.h"
#include "CondCore/DBCommon/interface/DBSession.h"
#include "CondCore/DBCommon/interface/Connection.h"
#include "CondCore/DBCommon/interface/CoralTransaction.h"
#include "CondCore/DBCommon/interface/SessionConfiguration.h"
#include "CondCore/DBCommon/interface/ConnectionConfiguration.h"
//#include "CondCore/DBCommon/interface/RelationalStorageManager.h"
#include "RelationalAccess/AccessMode.h"
#include "RelationalAccess/IRelationalService.h"
#include "RelationalAccess/RelationalServiceException.h"
#include "RelationalAccess/IRelationalDomain.h"
#include "RelationalAccess/SchemaException.h"
#include "RelationalAccess/ISession.h"
#include "RelationalAccess/ISessionProxy.h"
#include "RelationalAccess/ITransaction.h"
#include "RelationalAccess/ISchema.h"
#include "RelationalAccess/ITable.h"
#include "RelationalAccess/TableDescription.h"
#include "RelationalAccess/ITablePrivilegeManager.h"
#include "RelationalAccess/IPrimaryKey.h"
#include "RelationalAccess/ICursor.h"
#include "RelationalAccess/IQuery.h"
#include "RelationalAccess/ITableDataEditor.h"
#include "CoralBase/Exception.h"
#include "CoralBase/AttributeList.h"
#include "CoralBase/AttributeSpecification.h"
#include "CoralBase/Attribute.h"

//---------------
// C++ Headers --
//---------------


//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTCCBConfigHandler::DTCCBConfigHandler( std::string name,
                                        std::string connect_string,
                                        const edm::Event& evt,
                                        const edm::EventSetup& est,
                                        const std::string& tag,
                                        const std::string& onlineDB,
                                        const std::string& onlineAuthPath,
                                        const std::string& offlineAuthPath,
                                        const std::string& token ):
 popcon::PopConSourceHandler<DTCCBConfig>( name, connect_string,
                                           evt, est ),
 dataTag( tag ),
 onlineConnect( onlineDB ),
 onlineAuthentication( onlineAuthPath ),
 offlineAuthentication( offlineAuthPath ),
 offlineConnect( connect_string ),
 offlineCatalog( " " ),
 listToken( token ) {
}

//--------------
// Destructor --
//--------------
DTCCBConfigHandler::~DTCCBConfigHandler() {
}

//--------------
// Operations --
//--------------
void DTCCBConfigHandler::getNewObjects() {

  cond::DBSession* coralSession;
  cond::Connection* m_connection;
  cond::CoralTransaction* m_coraldb;

  coralSession = new cond::DBSession();
  // to get the username/passwd from $CORAL_AUTH_PATH/authentication.xml
  coralSession->configuration().setAuthenticationMethod( cond::XML );
  coralSession->configuration().setAuthenticationPath( onlineAuthentication );
  // set message level to Error or Debug
  coralSession->configuration().setMessageLevel( cond::Error );
//  coralSession->connectionConfiguration().setConnectionRetrialTimeOut( 60 );
  coralSession->open();

  m_connection = new cond::Connection( onlineConnect );
  m_connection->connect( coralSession );
  m_coraldb = &( m_connection->coralTransaction() );
  m_coraldb->start( true );

  std::cout << "get session proxy... " << std::endl;
  isession = &( m_coraldb->coralSessionProxy() );
  std::cout << "session proxy got" << std::endl;
  m_coraldb->start( true );
//  m_coraldb = new cond::RelationalStorageManager( onlineConnect,
//                                                  coralSession );
//  isession =
//  m_coraldb->connect( cond::ReadOnly );
//  m_coraldb->startTransaction( true );

  chkConfigList();
  std::cout << "get run config..." << std::endl;

  std::map<std::string, popcon::PayloadIOV> mp = getOfflineInfo();
  std::cout << "tag map got..." << std::endl;
  std::map<std::string, popcon::PayloadIOV>::iterator iter = mp.begin();
  std::map<std::string, popcon::PayloadIOV>::iterator iend = mp.end();
  while ( iter != iend ) {
    std::cout << "Tag: "                       << iter->first
              << " , last object valid since " << iter->second.last_since
              << " to "                        << iter->second.last_till
              << std::endl;
    iter++;
  }
  std::cout << "loop over tags done..." << std::endl;

  coral::AttributeList emptyBindVariableList;

  unsigned lastRun = 0;
  std::map<std::string, popcon::PayloadIOV>::iterator itag =
    mp.find( dataTag );
  if ( itag != mp.end() ) lastRun = itag->second.last_since;
  else                    std::cout << "tag " << dataTag
                                    << " not found" << std::endl;

  std::cout << "last run found..." << std::endl;

    std::cout << "LAST RUN: " << lastRun << std::endl;
    std::map<int,int> cfgMap;

    std::cout << "get table handle... " << std::endl;
    coral::ITable& runConfigTable =
      isession->nominalSchema().tableHandle( "TBRUN" );
    std::cout << "table handle got " << std::endl;
    std::auto_ptr<coral::IQuery>
      runConfigQuery( runConfigTable.newQuery() );
    runConfigQuery->addToOutputList( "RUN" );
    runConfigQuery->addToOutputList( "CONFKEY" );

    coral::ICursor& runConfigCursor = runConfigQuery->execute();
    while( runConfigCursor.next() ) {
      const coral::AttributeList& row = runConfigCursor.currentRow();
      int runConfigId = row["CONFKEY"].data<int>();
      int runId       = row[    "RUN"].data<int>();
      if ( static_cast<unsigned>( runId ) > lastRun ) 
           cfgMap.insert( std::pair<int,int>( runId,
                                              runConfigId ) );
    }
    std::map<int,int>::const_iterator runIter = cfgMap.begin();
    std::map<int,int>::const_iterator runIend = cfgMap.end();
    char confKeyString[20];
    char brickIdString[20];
    while ( runIter != runIend ) {
      const std::pair<int,int>& runEntry = *runIter++;
      std::cout << "run "          << runEntry.first
                << " ---> config " << runEntry.second << std::endl;
      DTCCBConfig* fullConf = new DTCCBConfig( dataTag );
      fullConf->setFullKey( runEntry.second );
      fullConf->setStamp(   runEntry.first );
      std::vector< std::pair<DTCCBId,int> > ccbMap;
      std::auto_ptr<coral::IQuery>
           ccbDataQuery( isession->nominalSchema().newQuery() );
      ccbDataQuery->addToTableList( "CCBRELATIONS" );
      ccbDataQuery->addToTableList( "CCBMAP" );
      ccbDataQuery->addToOutputList( "CCBMAP.WHEEL" );
      ccbDataQuery->addToOutputList( "CCBMAP.SECTOR" );
      ccbDataQuery->addToOutputList( "CCBMAP.STATION" );
      ccbDataQuery->addToOutputList( "CCBRELATIONS.CONFCCBKEY" );
      sprintf( confKeyString, "%i", runEntry.second );
      std::string
      ccbDataCondition  =      "CCBRELATIONS.CCBID = CCBMAP.CCBID";
      ccbDataCondition += " and CCBRELATIONS.CONFKEY = ";
      ccbDataCondition += confKeyString;
      ccbDataQuery->setCondition( ccbDataCondition, emptyBindVariableList );
      std::cout << ccbDataCondition << std::endl;
      coral::ICursor& ccbDataCursor = ccbDataQuery->execute();
      while( ccbDataCursor.next() ) {
        const coral::AttributeList& row = ccbDataCursor.currentRow();
        int wheel   = row["CCBMAP.WHEEL"  ].data<int>();
        int sector  = row["CCBMAP.SECTOR" ].data<int>();
        int station = row["CCBMAP.STATION"].data<int>();
        int ccbConf = row["CCBRELATIONS.CONFCCBKEY"].data<int>();
        DTCCBId ccbId;
        ccbId.  wheelId =   wheel;
        ccbId.stationId = station;
        ccbId. sectorId =  sector;
        ccbMap.push_back( std::pair<DTCCBId,int>( ccbId, ccbConf ) );
      }

      std::vector< std::pair<DTCCBId,int> >::const_iterator ccbIter
                                                          = ccbMap.begin();
      std::vector< std::pair<DTCCBId,int> >::const_iterator ccbIend
                                                          = ccbMap.end();
      while ( ccbIter != ccbIend ) {
        std::pair<DTCCBId,int> ccbEntry = *ccbIter++;
        DTCCBId& ccbId = ccbEntry.first;
        int ccbConfId  = ccbEntry.second;
        int   wheel = ccbId.  wheelId;
        int station = ccbId.stationId;
        int  sector = ccbId. sectorId;
        std::vector<int> ccbConf;
        coral::ITable& confBrickTable =
          isession->nominalSchema().tableHandle( "CFG2BRKREL" );
        std::auto_ptr<coral::IQuery>
          confBrickQuery( confBrickTable.newQuery() );
        confBrickQuery->addToOutputList( "BRKID" );
        sprintf( brickIdString, "%i", ccbConfId );
        std::string
        confBrickCondition  = "CONFID = ";
        confBrickCondition += brickIdString;
        std::cout << confBrickCondition << std::endl;
        confBrickQuery->setCondition( confBrickCondition,
                                      emptyBindVariableList );
        coral::ICursor& confBrickCursor = confBrickQuery->execute();
        while( confBrickCursor.next() ) {
          const coral::AttributeList& row = confBrickCursor.currentRow();
          int confBrickId = row["BRKID"].data<int>();
          ccbConf.push_back( confBrickId );
        }
        fullConf->setConfigKey( wheel, station, sector, ccbConf );
      }
      popcon::IOVPair iop = { runEntry.first, 0xffffffff };
      std::cout << "APPEND NEW OBJECT: "
                << runEntry.first << " " << fullConf << std::endl;
      m_to_transfer->push_back( std::make_pair( fullConf, iop ) );
    }

  delete m_connection;
  delete coralSession;

  return;
}


void DTCCBConfigHandler::chkConfigList() {
  std::cout << "create session: "
            << offlineConnect << " , "
            << offlineCatalog << " , "
            << offlineAuthentication << std::endl;

  DTDBSession* session = new DTDBSession( offlineConnect, offlineCatalog,
                                          offlineAuthentication );
  session->connect( false );
  const DTConfigList* rs;
  std::cout << "read full list: " << listToken << std::endl;
  DTConfigHandler* ri = DTConfigHandler::create( session, listToken );
  rs = ri->getContainer();
  DTConfigList::const_iterator iter = rs->begin();
  DTConfigList::const_iterator iend = rs->end();
  while ( iter != iend ) {
    int id = iter->first;
    std::cout << "brick " << id
              << " -> "   << iter->second.ref << std::endl;
    std::cout << "========> " << std::endl;
    iter++;
  }

  coral::ITable& fullConfigTable =
    isession->nominalSchema().tableHandle( "CONFIGSETS" );
  std::auto_ptr<coral::IQuery>
    fullConfigQuery( fullConfigTable.newQuery() );
  fullConfigQuery->addToOutputList( "CONFKEY" );
  fullConfigQuery->addToOutputList( "NAME" );
  coral::ICursor& fullConfigCursor = fullConfigQuery->execute();
  while( fullConfigCursor.next() ) {
    const coral::AttributeList& row = fullConfigCursor.currentRow();
    int fullConfigId = row["CONFKEY"].data<int>();
    std::string fullConfigName = row["NAME"].data<std::string>();
    std::cout << "config " << fullConfigId
              << " : "     << fullConfigName << std::endl;
  }

  std::cout << " ===============" << std::endl;

  coral::AttributeList emptyBindVariableList;
  coral::ITable& brickConfigTable =
    isession->nominalSchema().tableHandle( "CFGBRICKS" );
  std::auto_ptr<coral::IQuery>
    brickConfigQuery( brickConfigTable.newQuery() );
  brickConfigQuery->addToOutputList( "BRKID" );
  brickConfigQuery->addToOutputList( "BRKNAME" );
  coral::ICursor& brickConfigCursor = brickConfigQuery->execute();
  DTConfigData* brickData = 0;
  char brickIdString[20];
  std::vector<int> missingList;
  while( brickConfigCursor.next() ) {
    const coral::AttributeList& row = brickConfigCursor.currentRow();
    int brickConfigId = row["BRKID"].data<int>();
    std::string brickConfigName = row["BRKNAME"].data<std::string>();
    std::cout << "brick " << brickConfigId
              << " : "    << brickConfigName << std::endl;
    ri->get( brickConfigId, brickData );
    if ( brickData == 0 ) {
      std::cout << "brick missing, copy request" << std::endl;
      missingList.push_back( brickConfigId );
      break; // REMOVE
    }
  }
  std::vector<int>::const_iterator brickIter = missingList.begin();
  std::vector<int>::const_iterator brickIend = missingList.end();
  while ( brickIter != brickIend ) {
    int brickConfigId = *brickIter++;
      std::auto_ptr<coral::IQuery>
           brickDataQuery( isession->nominalSchema().newQuery() );
      brickDataQuery->addToTableList( "CFGRELATIONS" );
      brickDataQuery->addToTableList( "CONFIGCMDS" );
      sprintf( brickIdString, "%i", brickConfigId );
      std::string
      brickCondition  =      "CONFIGCMDS.CMDID=CFGRELATIONS.CMDID";
      brickCondition += " and CFGRELATIONS.BRKID=";
      brickCondition += brickIdString;
      std::cout << "+++" << brickCondition << "+++" << std::endl;
      brickDataQuery->addToOutputList( "CFGRELATIONS.BRKID" );
      brickDataQuery->addToOutputList( "CONFIGCMDS.CONFDATA" );
      brickDataQuery->setCondition( brickCondition, emptyBindVariableList );
      coral::ICursor& brickDataCursor = brickDataQuery->execute();
      brickData = new DTConfigData();
      brickData->setId( brickConfigId );
      while( brickDataCursor.next() ) {
        const coral::AttributeList& row = brickDataCursor.currentRow();
        for ( coral::AttributeList::const_iterator iColumn = row.begin();
              iColumn != row.end(); ++iColumn ) {
          std::cout << iColumn->specification().name() << " : ";
          iColumn->toOutputStream( std::cout, false ) << "\t";
          std::cout << std::endl;
          if ( iColumn->specification().name() == "CONFIGCMDS.CONFDATA" )
          std::cout << "add : " << iColumn->data<std::string>()
                      << std::endl;
        }
        std::cout << "add : "
                  << row["CONFIGCMDS.CONFDATA"].data<std::string>()
                  << std::endl;
        brickData->add( row["CONFIGCMDS.CONFDATA"].data<std::string>() );
      }
      cond::TypedRef<DTConfigData> brickRef( *session->poolDB(), brickData );
      brickRef.markWrite( "DTConfigData" );
      ri->set( brickConfigId, brickRef.token() );
  }

  std::cout << "disconnect session..." << std::endl;
  session->disconnect();
  std::cout << "delete session..." << std::endl;
  delete session;
  std::cout << "list updated..." << std::endl;

  return;

}


