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
DTTtrigPopConCollector::DTTtrigPopConCollector( std::string name,
                                std::string connect_string,
                                const edm::Event& evt,
                                const edm::EventSetup& est,
                                const std::string& tag ):
 popcon::PopConSourceHandler<DTTtrig>( name, connect_string,
                                       evt, est ),
 dataTag( tag ) {
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

  int irun = event.id().run();
  int ievt = event.id().event();
  std::cout << "================ "
            << irun << " " << ievt << std::endl;

  std::map<std::string, popcon::PayloadIOV> mp = getOfflineInfo();
  std::map<std::string, popcon::PayloadIOV>::iterator iter = mp.begin();
  std::map<std::string, popcon::PayloadIOV>::iterator iend = mp.end();
  std::cout << "list of all tags: " << std::endl;
  while ( iter != iend ) {
    std::cout << "Tag: "                       << iter->first
              << " , last object valid since " << iter->second.last_since
              << " to "                        << iter->second.last_till
              << std::endl;
    iter++;
  }

  std::cout << "look for tag " << dataTag << std::endl;
  std::map<std::string, popcon::PayloadIOV>::iterator itag =
    mp.find( dataTag );
  unsigned int last = itag->second.last_since;

  unsigned int runf = DTTtrigContainer::validityStart;
  std::cout << "check for payload valid since " << runf 
            << " / " << last << std::endl;
  // check if data already present in target DB
  if ( runf <= last ) return;
  std::cout << "write payload valid since "
            << DTTtrigContainer::currentTime << std::endl;

//  unsigned int runf = irun;
  unsigned int runl = 0xffffffff;
  popcon::IOVPair iop = { DTTtrigContainer::currentTime, runl };
  std::cout << "APPEND NEW OBJECT: "
            << runf << " " << runl << std::endl;
  m_to_transfer->push_back( std::make_pair( DTTtrigContainer::dataPtr, iop ) );

  return;

}


