/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007-11-07 15:08:40 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondTools/DT/interface/DTRangeT0Handler.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondFormats/DTObjects/interface/DTRangeT0.h"

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
DTRangeT0Handler::DTRangeT0Handler( std::string name,
                                    std::string connect_string,
                                    std::string catalog,
                                    const edm::Event& evt,
                                    const edm::EventSetup& est,
                                    const std::string& tag,
                                    const std::string& file ):
 popcon::PopConSourceHandler<DTRangeT0>( name, connect_string, catalog,
                                         evt, est ),
 dataTag( tag ),
 fileName( file ) {
}

//--------------
// Destructor --
//--------------
DTRangeT0Handler::~DTRangeT0Handler() {
}

//--------------
// Operations --
//--------------
void DTRangeT0Handler::getNewObjects() {

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

  DTRangeT0* t0Range = new DTRangeT0( dataTag );

  int status = 0;
  std::ifstream ifile( fileName.c_str() );
  int whe;
  int sta;
  int sec;
  int qua;
  int t0min;
  int t0max;
  while ( ifile >> whe
                >> sta
                >> sec
                >> qua
                >> t0min
                >> t0max ) {
    status = t0Range->set( whe, sta, sec, qua, t0min, t0max );
    std::cout << whe << " "
              << sta << " "
              << sec << " "
              << qua << " "
              << t0min << " "
              << t0max << "  -> ";                
    std::cout << "insert status: " << status << std::endl;
  }

  unsigned int runf = irun;
  unsigned int runl = 0xffffffff;
  popcon::IOVPair iop = { runf, runl };
  std::cout << "APPEND NEW OBJECT: "
            << runf << " " << runl << " " << t0Range << std::endl;
  m_to_transfer->push_back( std::make_pair( t0Range, iop ) );

  return;

}

