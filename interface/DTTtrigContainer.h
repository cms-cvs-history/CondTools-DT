
/*----------------------------------------------------------------------

Toy EDAnalyzer for testing purposes only.

----------------------------------------------------------------------*/

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
class DTTtrig;

class DTTtrigContainer : public edm::EDAnalyzer{
 public:
  static DTTtrig* dataPtr;
  static unsigned int validityStart;
  static unsigned int validityEnd;
  static unsigned int currentTime;
};
