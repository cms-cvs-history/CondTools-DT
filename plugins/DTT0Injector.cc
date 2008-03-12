
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


#include "CondTools/DT/plugins/DTT0Injector.h"
#include "CondTools/DT/interface/DTT0Container.h"
#include "CondFormats/DTObjects/interface/DTT0.h"
#include "CondFormats/DataRecord/interface/DTT0Rcd.h"

DTT0Injector::DTT0Injector(edm::ParameterSet const& p) {
}

DTT0Injector::DTT0Injector(int i) {
}

DTT0Injector::~DTT0Injector() {
}

void DTT0Injector::analyze(const edm::Event& e,
                        const edm::EventSetup& context) {

  using namespace edm::eventsetup;

  // get payload for current run
  std::cout <<" I AM IN RUN NUMBER "<<e.id().run() <<std::endl;
  std::cout <<" ---EVENT NUMBER "<<e.id().event() <<std::endl;
  edm::ESHandle<DTT0> t0;
  context.get<DTT0Rcd>().get(t0);
  edm::ValidityInterval iov( context.get<DTT0Rcd>().validityInterval() );
  unsigned int currValidityStart = iov.first().eventID().run();
  unsigned int currValidityEnd   = iov.last( ).eventID().run();
  DTT0Container::currentTime   = e.id().run();

  // check if changed
  if ( currValidityEnd <= DTT0Container::validityEnd ) return;

  // create a copy
  delete DTT0Container::dataPtr;
  DTT0Container::dataPtr = new DTT0( t0->version() );
  std::cout << t0->version() << std::endl;
  std::cout << std::distance( t0->begin(), t0->end() )
            << " data in the container" << std::endl;
  std::cout << "valid since "
            << currValidityStart << " to "
            << currValidityEnd   << std::endl;
  DTT0::const_iterator iter = t0->begin();
  DTT0::const_iterator iend = t0->end();
  while ( iter != iend ) {
    const DTT0Id&   t0Id   = iter->first;
    const DTT0Data& t0Data = iter->second;
    DTT0Container::dataPtr->set( t0Id.wheelId,
                                 t0Id.stationId,
                                 t0Id.sectorId,
                                 t0Id.slId,
                                 t0Id.layerId,
                                 t0Id.cellId,
                                 t0Data.t0mean,
                                 t0Data.t0rms );
    iter++;
  }

  DTT0Container::validityStart = currValidityStart;
  DTT0Container::validityEnd   = currValidityEnd;
  return;
}
DEFINE_FWK_MODULE(DTT0Injector);
