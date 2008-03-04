/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007/12/10 19:46:20 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondTools/DT/plugins/DTTtrigTransfer.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondTools/DT/interface/DTTtrigPopConCollector.h"
#include "FWCore/Framework/interface/MakerMacros.h"

//---------------
// C++ Headers --
//---------------


//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTTtrigTransfer::DTTtrigTransfer( const edm::ParameterSet& ps ):
 popcon::PopConAnalyzer<DTTtrig>( ps, "DTTtrig" ),
 dataTag(  ps.getParameter<std::string> ( "onlTag" ) ) {
}

//--------------
// Destructor --
//--------------
DTTtrigTransfer::~DTTtrigTransfer() {
}

//--------------
// Operations --
//--------------
void DTTtrigTransfer::initSource( const edm::Event& evt,
                                        const edm::EventSetup& est ) {
  m_handler_object = new DTTtrigPopConCollector( "DTTtrig",
                                                 m_offline_connection,
                                                 evt, est, dataTag );
  return;
}

DEFINE_FWK_MODULE(DTTtrigTransfer);

