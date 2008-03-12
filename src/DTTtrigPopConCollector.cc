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
#include "CondTools/DT/interface/DTTtrigPopConCollector.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondTools/DT/plugins/DTTtrigInjector.h"
#include "CondTools/DT/interface/DTTtrigContainer.h"
#include "CondFormats/DTObjects/interface/DTTtrig.h"

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
DTTtrigPopConCollector::DTTtrigPopConCollector( const edm::ParameterSet& ps ):
 dataTag(       ps.getParameter<std::string>  (  "onlTag" ) ) {
}

//--------------
// Destructor --
//--------------
DTTtrigPopConCollector::~DTTtrigPopConCollector() {
}

//--------------
// Operations --
//--------------
void DTTtrigPopConCollector::getNewObjects() {

  //to access the information on the tag inside the offline database:
  cond::TagInfo const & ti = tagInfo();
  unsigned int last = ti.lastInterval.first;

  //to access the information on last successful log entry for this tag:
//  cond::LogDBEntry const & lde = logDBEntry();     

  //to access the lastest payload (Ref is a smart pointer)
//  Ref payload = lastPayload();

  unsigned int runf = DTTtrigContainer::validityStart;
//  unsigned int runl = 0xffffffff;

  std::cout << "check for payload valid since " << runf 
            << " / " << last << std::endl;
  // check if data already present in target DB
  if ( runf <= last ) return;
  cond::Time_t snc = DTTtrigContainer::currentTime;
  std::cout << "write payload valid since " << snc << std::endl;
  m_to_transfer.push_back( std::make_pair( 
                                DTTtrigContainer::dataPtr, snc ) );

  return;

}

std::string DTTtrigPopConCollector::id() const {
  return dataTag;
}



