
/*----------------------------------------------------------------------

Toy EDAnalyzer for testing purposes only.

----------------------------------------------------------------------*/

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <string>

namespace edmtest {
  class DTHVTest : public edm::EDAnalyzer
  {
  public:
    explicit  DTHVTest(edm::ParameterSet const& p);
    explicit  DTHVTest(int i) ;
    virtual ~ DTHVTest();
    virtual void analyze(const edm::Event& e, const edm::EventSetup& c);
  private:
  };
}
