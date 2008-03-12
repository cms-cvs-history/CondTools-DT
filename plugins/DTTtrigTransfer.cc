#include "CondCore/PopCon/interface/PopConAnalyzer.h"
#include "CondTools/DT/interface/DTTtrigPopConCollector.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef popcon::PopConAnalyzer<DTTtrigPopConCollector> DTTtrigTransfer;


DEFINE_FWK_MODULE(DTTtrigTransfer);

