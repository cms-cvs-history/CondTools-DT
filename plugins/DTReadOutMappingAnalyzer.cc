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
#include "CondTools/DT/plugins/DTReadOutMappingAnalyzer.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondTools/DT/interface/DTReadOutMappingHandler.h"

//---------------
// C++ Headers --
//---------------


//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTReadOutMappingAnalyzer::DTReadOutMappingAnalyzer( const edm::ParameterSet& ps ):
 popcon::PopConAnalyzer<DTReadOutMapping>( ps, "DTReadOutMapping" ),
 dataTag(  ps.getParameter<std::string> ( "tag" ) ),
 fileName( ps.getParameter<std::string> ( "file" ) ) {
}

//--------------
// Destructor --
//--------------
DTReadOutMappingAnalyzer::~DTReadOutMappingAnalyzer() {
}

//--------------
// Operations --
//--------------
void DTReadOutMappingAnalyzer::initSource( const edm::Event& evt,
                                  const edm::EventSetup& est ) {
  m_handler_object = new DTReadOutMappingHandler( "DTReadOutMapping",
                                         m_offline_connection,
                                         m_catalog, evt, est,
                                         dataTag,
                                         fileName );
  return;
}

  
DEFINE_FWK_MODULE(DTReadOutMappingAnalyzer);

