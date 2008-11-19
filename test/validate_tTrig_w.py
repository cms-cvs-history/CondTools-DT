import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.load("CondCore.DBCommon.CondDBCommon_cfi")

process.CondDBCommon.connect = 'sqlite_file:test.db'
process.CondDBCommon.DBParameters.authenticationPath = '.'

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDBCommon,
    logconnect = cms.untracked.string('sqlite_file:log.db'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('DTTtrigRcd'),
        tag = cms.string('tTrig_test')
    ))
)

process.source = cms.Source("EmptyIOVSource",
    timetype   = cms.string('runnumber'),
    firstValue = cms.uint64(1),
    lastValue  = cms.uint64(2),
    interval   = cms.uint64(1)
)

process.tTrig = cms.EDAnalyzer("DTTtrigValidateDBWrite",
    name = cms.untracked.string('DTTtrig'),
    record = cms.string('DTTtrigRcd'),
    Source = cms.PSet(
        version = cms.string('tTrig_test'),
        outFile = cms.string('tTrigDump.txt'),
        logFile = cms.string('tTrigValidate.log'),
        debug = cms.bool(False),
        firstRun = cms.uint32(1),
         lastRun = cms.uint32(5)
    ),
    SinceAppendMode = cms.bool(True)
)

process.p = cms.Path(process.tTrig)

