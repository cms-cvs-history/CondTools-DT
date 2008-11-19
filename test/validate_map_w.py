import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.load("CondCore.DBCommon.CondDBCommon_cfi")

process.CondDBCommon.connect = 'sqlite_file:test.db'
process.CondDBCommon.DBParameters.authenticationPath = '.'

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDBCommon,
    logconnect = cms.untracked.string('sqlite_file:log.db'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('DTReadOutMappingRcd'),
        tag = cms.string('map_test')
    ))
)

process.source = cms.Source("EmptyIOVSource",
    timetype   = cms.string('runnumber'),
    firstValue = cms.uint64(1),
    lastValue  = cms.uint64(2),
    interval   = cms.uint64(1)
)

process.map = cms.EDAnalyzer("DTROMapValidateDBWrite",
    name = cms.untracked.string('DTReadOutMapping'),
    record = cms.string('DTReadOutMappingRcd'),
    Source = cms.PSet(
        version = cms.string('map_test'),
        outFile = cms.string('mapDump.txt'),
        logFile = cms.string('mapValidate.log'),
        debug = cms.bool(False)
    ),
    SinceAppendMode = cms.bool(True)
)

process.p = cms.Path(process.map)

