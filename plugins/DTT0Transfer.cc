#include "CondCore/PopCon/interface/PopConAnalyzer.h"
#include "CondTools/DT/interface/DTT0PopConCollector.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef popcon::PopConAnalyzer<DTT0PopConCollector> DTT0Transfer;


DEFINE_FWK_MODULE(DTT0Transfer);

