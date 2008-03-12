
/*----------------------------------------------------------------------

Toy EDAnalyzer for testing purposes only.

----------------------------------------------------------------------*/

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
class DTT0;

class DTT0Container : public edm::EDAnalyzer{
 public:
  static DTT0* dataPtr;
  static unsigned int validityStart;
  static unsigned int validityEnd;
  static unsigned int currentTime;
};
