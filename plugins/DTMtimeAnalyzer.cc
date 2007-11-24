/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007-11-07 15:48:54 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondTools/DT/plugins/DTMtimeAnalyzer.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondTools/DT/interface/DTMtimeHandler.h"

//---------------
// C++ Headers --
//---------------


//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTMtimeAnalyzer::DTMtimeAnalyzer( const edm::ParameterSet& ps ):
 popcon::PopConAnalyzer<DTMtime>( ps, "DTMtime" ),
 dataTag(  ps.getParameter<std::string> ( "tag" ) ),
 fileName( ps.getParameter<std::string> ( "file" ) ) {
}

//--------------
// Destructor --
//--------------
DTMtimeAnalyzer::~DTMtimeAnalyzer() {
}

//--------------
// Operations --
//--------------
void DTMtimeAnalyzer::initSource( const edm::Event& evt,
                                  const edm::EventSetup& est ) {
  m_handler_object = new DTMtimeHandler( "DTMtime",
                                         m_offline_connection,
                                         m_catalog, evt, est,
                                         dataTag,
                                         fileName );
  return;
}

  
DEFINE_FWK_MODULE(DTMtimeAnalyzer);

