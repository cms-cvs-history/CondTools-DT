import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.load("CondCore.DBCommon.CondDBCommon_cfi")

process.CondDBCommon.connect = 'sqlite_file:test.db'
process.CondDBCommon.DBParameters.authenticationPath = '.'

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDBCommon,
    logconnect = cms.untracked.string('sqlite_file:log.db'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('DTTPGParametersRcd'),
        tag = cms.string('tpg_test')
    ))
)

process.source = cms.Source("EmptyIOVSource",
    timetype   = cms.string('runnumber'),
    firstValue = cms.uint64(1),
    lastValue  = cms.uint64(2),
    interval   = cms.uint64(1)
)

process.tpg = cms.EDAnalyzer("DTTPGParametersPopConAnalyzer",
    name = cms.untracked.string('DTTPGParameters'),
    record = cms.string('DTTPGParametersRcd'),
    Source = cms.PSet(
        tag = cms.string('tpg_test'),
        file = cms.string('tpg.txt'),
        run = cms.uint32(1)
    ),
    SinceAppendMode = cms.bool(True)
)

process.p = cms.Path(process.tpg)

