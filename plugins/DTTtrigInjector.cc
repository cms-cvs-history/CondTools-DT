
/*----------------------------------------------------------------------

Toy EDAnalyzer for testing purposes only.

----------------------------------------------------------------------*/

#include <stdexcept>
#include <string>
#include <iostream>
#include <map>
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ValidityInterval.h"


#include "CondTools/DT/plugins/DTTtrigInjector.h"
#include "CondTools/DT/interface/DTTtrigContainer.h"
#include "CondFormats/DTObjects/interface/DTTtrig.h"
#include "CondFormats/DataRecord/interface/DTTtrigRcd.h"

DTTtrigInjector::DTTtrigInjector(edm::ParameterSet const& p) {
}

DTTtrigInjector::DTTtrigInjector(int i) {
}

DTTtrigInjector::~DTTtrigInjector() {
}

void DTTtrigInjector::analyze(const edm::Event& e,
                        const edm::EventSetup& context) {

  using namespace edm::eventsetup;

  // get payload for current run
  std::cout <<" I AM IN RUN NUMBER "<<e.id().run() <<std::endl;
  std::cout <<" ---EVENT NUMBER "<<e.id().event() <<std::endl;
  edm::ESHandle<DTTtrig> tTrig;
  context.get<DTTtrigRcd>().get(tTrig);
  edm::ValidityInterval iov( context.get<DTTtrigRcd>().validityInterval() );
  unsigned int currValidityStart = iov.first().eventID().run();
  unsigned int currValidityEnd   = iov.last( ).eventID().run();
  DTTtrigContainer::currentTime   = e.id().run();

  // check if changed
  if ( currValidityEnd <= DTTtrigContainer::validityEnd ) return;

  // create a copy
  delete DTTtrigContainer::dataPtr;
  DTTtrigContainer::dataPtr = new DTTtrig( tTrig->version() );
  std::cout << tTrig->version() << std::endl;
  std::cout << std::distance( tTrig->begin(), tTrig->end() )
            << " data in the container" << std::endl;
  std::cout << "valid since "
            << currValidityStart << " to "
            << currValidityEnd   << std::endl;
  DTTtrig::const_iterator iter = tTrig->begin();
  DTTtrig::const_iterator iend = tTrig->end();
  while ( iter != iend ) {
    const DTTtrigId&   trigId   = iter->first;
    const DTTtrigData& trigData = iter->second;
    DTTtrigContainer::dataPtr->set( trigId.wheelId,
                                    trigId.stationId,
                                    trigId.sectorId,
                                    trigId.slId,
                                    trigId.layerId,
                                    trigId.cellId,
                                    trigData.tTrig,
                                    trigData.tTrms );
    iter++;
  }

  DTTtrigContainer::validityStart = currValidityStart;
  DTTtrigContainer::validityEnd   = currValidityEnd;
  return;
}
DEFINE_FWK_MODULE(DTTtrigInjector);
