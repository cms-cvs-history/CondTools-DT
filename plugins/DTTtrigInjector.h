
/*----------------------------------------------------------------------

Toy EDAnalyzer for testing purposes only.

----------------------------------------------------------------------*/

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class DTTtrigInjector : public edm::EDAnalyzer{
 public:
  explicit  DTTtrigInjector(edm::ParameterSet const& p);
  explicit  DTTtrigInjector(int i) ;
  virtual ~ DTTtrigInjector();
  virtual void analyze(const edm::Event& e, const edm::EventSetup& c);
 private:
};
