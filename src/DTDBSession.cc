/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007-01-23 14:52:04 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondTools/DT/interface/DTDBSession.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include "DataFormats/Provenance/interface/EventID.h"
#include "DataFormats/Provenance/interface/Timestamp.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Catalog/interface/SiteLocalConfig.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CondCore/MetaDataService/interface/MetaData.h"
#include "CondCore/DBCommon/interface/PoolStorageManager.h"
#include "CondCore/DBCommon/interface/RelationalStorageManager.h"
#include "CondCore/IOVService/interface/IOVService.h"
#include "CondCore/IOVService/interface/IOVEditor.h"
#include "CondCore/IOVService/interface/IOVNames.h"
#include "CondCore/DBCommon/interface/AuthenticationMethod.h"
#include "CondCore/DBCommon/interface/ConnectMode.h"
#include "CondCore/DBCommon/interface/MessageLevel.h"
#include "CondCore/DBCommon/interface/Exception.h"
#include "CondCore/DBCommon/interface/ConfigSessionFromParameterSet.h"
#include "CondCore/DBCommon/src/ServiceLoader.h"
#include "CondCore/DBOutputService/interface/Exception.h"
#include "CondCore/DBCommon/interface/ObjectRelationalMappingUtility.h"
#include "CondCore/DBOutputService/src/serviceCallbackToken.h"
//#include "RelationalAccess/IConnectionService.h"
//#include "RelationalAccess/IWebCacheControl.h"
#include <vector>

#include "CondCore/DBCommon/interface/SessionConfiguration.h"
#include "CondCore/DBCommon/interface/ConnectionConfiguration.h"



//---------------
// C++ Headers --
//---------------


//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTDBSession::DTDBSession( const std::string& dbFile,
                          const std::string& dbCatalog,
                          const std::string& auth_path,
                          bool siteLocalConfig ):
  m_session( 0 ),
  m_pooldb( 0 ) {
//                          const cond::AuthenticationMethod& auth_mode,

   std::string connect( dbFile );
   std::string catconnect( dbCatalog );
   int connectionTimeOut = 600;
   int connectionRetrialPeriod = 30;
   int connectionRetrialTimeOut = 180;
   m_session = new cond::DBSession( true );
//   m_session->sessionConfiguration().setAuthenticationMethod( auth_mode );
   if ( auth_path.empty() ) {
     m_session->sessionConfiguration().setAuthenticationMethod( cond::Env );
   }
   else {
     m_session->sessionConfiguration().setAuthenticationMethod( cond::XML );
     m_session->sessionConfiguration().setAuthenticationPath( auth_path );
   }
   m_session->sessionConfiguration().setMessageLevel( cond::Error );
   m_session->connectionConfiguration().enableConnectionSharing();
   m_session->connectionConfiguration().setConnectionTimeOut(
                                           connectionTimeOut );
   m_session->connectionConfiguration().
              enableReadOnlySessionOnUpdateConnections();
   m_session->connectionConfiguration().setConnectionRetrialPeriod(
                                           connectionRetrialPeriod);
   m_session->connectionConfiguration().setConnectionRetrialTimeOut(
                                           connectionRetrialTimeOut );

   m_session->open();
   if ( siteLocalConfig ) {
    edm::Service<edm::SiteLocalConfig> localconfservice;
    if( !localconfservice.isAvailable() ){
      throw cms::Exception("edm::SiteLocalConfigService is not available");       
    }
    connect=localconfservice->lookupCalibConnect(connect);
//    catconnect=iConfig.getUntrackedParameter<std::string>("catalog","");
    if(catconnect.empty()){
//      std::string tmpcatalog;
      catconnect=localconfservice->calibCatalog();
//      catconnect = tmpcatalog;
//    }else{
//      tmpcatalog=catconnect;
    }
    std::string logicalconnect=localconfservice->calibLogicalServer();

/*
    //get handle to IConnectionService
    seal::IHandle<coral::IConnectionService>
      connSvc = m_session->serviceLoader().context()->query<coral::IConnectionService>( "CORAL/Services/ConnectionService" );
    //get handle to webCacheControl()
    connSvc->webCacheControl().refreshTable( logicalconnect,cond::IOVNames::iovTableName() );
    connSvc->webCacheControl().refreshTable( logicalconnect,cond::IOVNames::iovDataTableName() );
*/
   }
   m_pooldb = new cond::PoolStorageManager( connect, catconnect, m_session );

}

//--------------
// Destructor --
//--------------
DTDBSession::~DTDBSession() {
  delete m_session;
}

//--------------
// Operations --
//--------------
/// get storage manager
cond::PoolStorageManager* DTDBSession::poolDB() const {
  return m_pooldb;
}


/// start transaction
void DTDBSession::connect( bool readOnly ) {
  m_pooldb->connect();
  m_pooldb->startTransaction( readOnly );
  return;
}


/// end   transaction
void DTDBSession::disconnect() {
  m_pooldb->commit();
  m_pooldb->disconnect();	
  return;
}
