/*
 *  See header file for a description of this class.
 *
 *  $Date: 2010-01-14 23:18:12 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondTools/DT/plugins/DTPluginSessionFactory.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondTools/DT/interface/DTDBPluginSession.h"
#include "CondTools/DT/interface/DTConfigPluginHandler.h"
#include "FWCore/ServiceRegistry/interface/ServiceMaker.h"

//---------------
// C++ Headers --
//---------------
#include <iostream>

namespace cond { namespace service {

//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTPluginSessionFactory::DTPluginSessionFactory() {
  std::cout << "DTPluginSessionFactory::DTPluginSessionFactory "
            << this << std::endl;
  if ( instance == 0 ) instance = this;
  new DTConfigPluginHandler;
}

DTPluginSessionFactory::DTPluginSessionFactory(
                        const edm::ParameterSet & iConfig,
                        edm::ActivityRegistry & iAR ) {
  std::cout << "DTPluginSessionFactory::DTPluginSessionFactory(...) "
            << this << std::endl;
  if ( instance == 0 ) instance = this;
  new DTConfigPluginHandler;
}

//--------------
// Destructor --
//--------------
DTPluginSessionFactory::~DTPluginSessionFactory() {
}

//--------------
// Operations --
//--------------
DTDBAbstractSession* DTPluginSessionFactory::createSession( 
                                             const std::string& dbFile,
                                             const std::string& dbCatalog,
                                             const std::string& auth_path,
                                             bool siteLocalConfig ) {
  return new DTDBPluginSession( dbFile, dbCatalog, auth_path,
                                siteLocalConfig );
}

DEFINE_SEAL_MODULE();
DEFINE_ANOTHER_FWK_SERVICE( DTPluginSessionFactory );
} }

