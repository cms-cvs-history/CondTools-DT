import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

process.PoolDBESSource = cms.ESSource("PoolDBESSource",
    loadAll = cms.bool(True),
    timetype = cms.string('runnumber'),
    toGet = cms.VPSet(
                cms.PSet( record = cms.string('DTReadOutMappingRcd'),
                          tag = cms.string('map_test') ),
                cms.PSet( record = cms.string('DTT0Rcd'),
                          tag = cms.string('t0_test') ),
                cms.PSet( record = cms.string('DTTtrigRcd'),
                          tag = cms.string('tTrig_test') ),
                cms.PSet( record = cms.string('DTMtimeRcd'),
                          tag = cms.string('mTime_test') )
    ),
    connect = cms.string('sqlite_file:test.db'),
    DBParameters = cms.PSet(
        messageLevel = cms.untracked.int32(0),
        authenticationPath = cms.untracked.string('.')
    )
)

process.source = cms.Source("EmptyIOVSource",
    timetype = cms.string('runnumber'),
    firstValue = cms.uint64(1),
    lastValue  = cms.uint64(5),
    interval = cms.uint64(1)
)

process.map   = cms.EDAnalyzer("DTROMapValidateDBRead",
    chkFile = cms.string('mapDump.txt'),
    logFile = cms.string('mapValidate.log')
)

process.t0    = cms.EDAnalyzer("DTT0ValidateDBRead",
    chkFile = cms.string('t0Dump.txt'),
    logFile = cms.string('t0Validate.log')
)

process.tTrig = cms.EDAnalyzer("DTTtrigValidateDBRead",
    chkFile = cms.string('tTrigDump.txt'),
    logFile = cms.string('tTrigValidate.log')
)

process.mTime = cms.EDAnalyzer("DTMtimeValidateDBRead",
    chkFile = cms.string('mTimeDump.txt'),
    logFile = cms.string('mTimeValidate.log')
)

process.p = cms.Path(process.map+
                     process.t0+
                     process.tTrig+
                     process.mTime)
