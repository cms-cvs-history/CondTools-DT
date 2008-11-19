import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.load("CondCore.DBCommon.CondDBCommon_cfi")

process.CondDBCommon.connect = 'sqlite_file:test.db'
process.CondDBCommon.DBParameters.authenticationPath = '.'

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDBCommon,
    logconnect = cms.untracked.string('sqlite_file:log.db'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('DTMtimeRcd'),
        tag = cms.string('mTime_test')
    ))
)

process.source = cms.Source("EmptyIOVSource",
    timetype   = cms.string('runnumber'),
    firstValue = cms.uint64(1),
    lastValue  = cms.uint64(2),
    interval   = cms.uint64(1)
)

process.mTime = cms.EDAnalyzer("DTMtimeValidateDBWrite",
    name = cms.untracked.string('DTMtime'),
    record = cms.string('DTMtimeRcd'),
    Source = cms.PSet(
        version = cms.string('mTime_test'),
        outFile = cms.string('mTimeDump.txt'),
        logFile = cms.string('mTimeValidate.log'),
        debug = cms.bool(False),
        firstRun = cms.uint32(1),
         lastRun = cms.uint32(5)
    ),
    SinceAppendMode = cms.bool(True)
)

process.p = cms.Path(process.mTime)

