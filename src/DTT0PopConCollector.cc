/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007/12/07 15:13:59 $
 *  $Revision: 1.2 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondTools/DT/interface/DTT0PopConCollector.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondTools/DT/plugins/DTT0Injector.h"
#include "CondTools/DT/interface/DTT0Container.h"
#include "CondFormats/DTObjects/interface/DTT0.h"

//---------------
// C++ Headers --
//---------------
#include <iostream>
#include <fstream>

//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTT0PopConCollector::DTT0PopConCollector( const edm::ParameterSet& ps ):
 dataTag(       ps.getParameter<std::string>  (  "onlTag" ) ) {
}

//--------------
// Destructor --
//--------------
DTT0PopConCollector::~DTT0PopConCollector() {
}

//--------------
// Operations --
//--------------
void DTT0PopConCollector::getNewObjects() {

  //to access the information on the tag inside the offline database:
  cond::TagInfo const & ti = tagInfo();
  unsigned int last = ti.lastInterval.first;

  //to access the information on last successful log entry for this tag:
//  cond::LogDBEntry const & lde = logDBEntry();     

  //to access the lastest payload (Ref is a smart pointer)
//  Ref payload = lastPayload();

  unsigned int runf = DTT0Container::validityStart;
//  unsigned int runl = 0xffffffff;

  std::cout << "check for payload valid since " << runf 
            << " / " << last << std::endl;
  // check if data already present in target DB
  if ( runf <= last ) return;
  cond::Time_t snc = DTT0Container::currentTime;
  std::cout << "write payload valid since " << snc << std::endl;
  m_to_transfer.push_back( std::make_pair( 
                                DTT0Container::dataPtr, snc ) );

  return;

}

std::string DTT0PopConCollector::id() const {
  return dataTag;
}



