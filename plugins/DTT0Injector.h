
/*----------------------------------------------------------------------

Toy EDAnalyzer for testing purposes only.

----------------------------------------------------------------------*/

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class DTT0Injector : public edm::EDAnalyzer{
 public:
  explicit  DTT0Injector(edm::ParameterSet const& p);
  explicit  DTT0Injector(int i) ;
  virtual ~ DTT0Injector();
  virtual void analyze(const edm::Event& e, const edm::EventSetup& c);
 private:
};
