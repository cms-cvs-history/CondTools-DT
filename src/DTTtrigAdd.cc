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
#include "CondTools/DT/interface/DTTtrigAdd.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondFormats/DTObjects/interface/DTTtrig.h"
#include "CondFormats/DataRecord/interface/DTTtrigRcd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

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
DTTtrigAdd::DTTtrigAdd( std::string name,
                        std::string connect_string,
                        std::string catalog,
                        const edm::Event& evt,
                        const edm::EventSetup& est,
                        const std::string& tag,
                        const std::string& file ):
 popcon::PopConSourceHandler<DTTtrig>( name, connect_string, catalog,
                                       evt, est ),
 dataTag( tag ),
 fileName( file ),
 context( est ) {
}

//--------------
// Destructor --
//--------------
DTTtrigAdd::~DTTtrigAdd() {
}

//--------------
// Operations --
//--------------
void DTTtrigAdd::getNewObjects() {

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

  edm::ESHandle<DTTtrig> oldtTrig;
  context.get<DTTtrigRcd>().get(oldtTrig);

  DTTtrig* tTrig = new DTTtrig( *oldtTrig );
  tTrig->version() = oldtTrig->version() + "new";

  int status = 0;

  DTTtrig::const_iterator oldIter = tTrig->begin();
  DTTtrig::const_iterator oldIend = tTrig->end();
  while ( oldIter != oldIend ) {
    const DTTtrigId&   trigId   = oldIter->first;
    const DTTtrigData& trigData = oldIter->second;
    float trigTime;
    float trigTrms;
    tTrig->get( trigId.wheelId,
                trigId.stationId,
                trigId.sectorId,
                trigId.slId,
                trigId.layerId,
                trigId.cellId,
                trigTime, trigTrms );
    std::cout << trigId.wheelId   << " "
              << trigId.stationId << " "
              << trigId.sectorId  << " "
              << trigId.slId      << " -> "
              << trigId.layerId   << " -> "
              << trigId.cellId    << " -> "
              << trigData.tTrig    << " "
              << trigData.tTrms    << " -> "
              << trigTime          << " "
              << trigTrms          << std::endl;
    trigTime += irun * 10;
    trigTrms += irun * 10;
    status = tTrig->set( trigId.wheelId,
                         trigId.stationId,
                         trigId.sectorId,
                         trigId.slId,
                         trigId.layerId,
                         trigId.cellId,
                         trigTime, trigTrms );
    tTrig->get( trigId.wheelId,
                trigId.stationId,
                trigId.sectorId,
                trigId.slId,
                trigId.layerId,
                trigId.cellId,
                trigTime, trigTrms );
    std::cout << trigId.wheelId   << " "
              << trigId.stationId << " "
              << trigId.sectorId  << " "
              << trigId.slId      << " -> "
              << trigId.layerId   << " -> "
              << trigId.cellId    << " -> "
              << trigData.tTrig    << " "
              << trigData.tTrms    << " -> "
              << trigTime          << " "
              << trigTrms          << std::endl;
   oldIter++;
  }

  unsigned int runf = irun;
  unsigned int runl = 0xffffffff;
  popcon::IOVPair iop = { runf, runl };
  std::cout << "APPEND NEW OBJECT: "
            << runf << " " << runl << " " << tTrig << std::endl;
  m_to_transfer->push_back( std::make_pair( tTrig, iop ) );

  return;

}


