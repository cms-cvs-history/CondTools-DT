/*
 *  See header file for a description of this class.
 *
 *  TEMPORARY TOOL TO HANDLE CONFIGURATIONS
 *  TO BE REMOVED IN FUTURE RELEASES
 *
 *
 *  $Date: 2010/01/15 09:30:00 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondTools/DT/interface/DTDBPluginSession.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include "CondCore/DBCommon/interface/DBSession.h"
#include "CondCore/DBCommon/interface/AuthenticationMethod.h"
#include "CondCore/DBCommon/interface/Connection.h"
#include "CondCore/DBCommon/interface/TypedRef.h"
#include "CondCore/DBCommon/interface/Time.h"

#include "FWCore/Catalog/interface/SiteLocalConfig.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CondCore/DBCommon/interface/ConnectionHandler.h"
#include "CondCore/DBCommon/interface/PoolTransaction.h"
#include "CondCore/DBCommon/interface/MessageLevel.h"
#include <vector>

#include "CondCore/DBCommon/interface/SessionConfiguration.h"


//---------------
// C++ Headers --
//---------------
#include <iostream>

//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTDBPluginSession::DTDBPluginSession( const std::string& dbFile,
                                      const std::string& dbCatalog,
                                      const std::string& auth_path,
                                      bool siteLocalConfig ):
  m_session( 0 ),
  m_pooldb( 0 ) {
  std::cout << "DTDBPluginSession::DTDBPluginSession(...)" << std::endl;

   std::string connect( dbFile );
   std::string catconnect( dbCatalog );
   m_session = new cond::DBSession();
   if ( auth_path.empty() ) {
     m_session->configuration().setAuthenticationMethod( cond::Env );
   }
   else {
     m_session->configuration().setAuthenticationMethod( cond::XML );
     m_session->configuration().setAuthenticationPath( auth_path );
   }
   m_session->configuration().setMessageLevel( cond::Error );
   m_session->open();

   // still necessary ????
   if ( siteLocalConfig ) {
    edm::Service<edm::SiteLocalConfig> localconfservice;
    if( !localconfservice.isAvailable() ){
      throw cms::Exception("edm::SiteLocalConfigService is not available");
    }
   }
   if ( cond::ConnectionHandler::Instance().getConnection(connect) == 0 ) {
     std::cout << "register " << connect << std::endl;
     cond::ConnectionHandler::Instance().registerConnection(connect,*m_session,0);
   }
   else {
     std::cout << "already registered " << connect << std::endl;
   }
   m_connection = cond::ConnectionHandler::Instance().getConnection(connect);

  instance = this;
  std::cout << "DTDBPluginSession created" << std::endl;

}

//--------------
// Destructor --
//--------------
DTDBPluginSession::~DTDBPluginSession() {
  delete m_session;
}

//--------------
// Operations --
//--------------
/// get storage manager
cond::PoolTransaction* DTDBPluginSession::poolDB() const {
  return m_pooldb;
}


/// start transaction
void DTDBPluginSession::connect( bool readOnly ) {
  m_connection->connect( m_session );
  m_pooldb = &( m_connection->poolTransaction() );
  m_pooldb->start( readOnly );
  return;
}


/// end   transaction
void DTDBPluginSession::disconnect() {
  m_pooldb->commit();
  m_connection->disconnect();
  return;
}
