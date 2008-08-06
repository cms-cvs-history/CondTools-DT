import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.load("CondCore.DBCommon.CondDBCommon_cfi")

process.CondDBCommon.connect = 'oracle://cms_orcon_prod/CMS_COND_21X_DT'
process.CondDBCommon.DBParameters.authenticationPath = '.'

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDBCommon,
    logconnect = cms.untracked.string('oracle://cms_orcon_prod/CMS_COND_21X_POPCONLOG'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('DTCCBConfigRcd'),
        tag = cms.string('conf_test')
    ))
)

process.source = cms.Source("EmptyIOVSource",
    lastRun = cms.untracked.uint32(1),
    timetype = cms.string('runnumber'),
    firstRun = cms.untracked.uint32(1),
    interval = cms.uint32(1)
)

process.conf_o2o = cms.EDAnalyzer("DTCCBConfigPopConAnalyzer",
    name = cms.untracked.string('DTCCBConfig'),
    Source = cms.PSet(
        DBParameters = cms.PSet(
            messageLevel = cms.untracked.int32(0),
            authenticationPath = cms.untracked.string('.')
        ),
        onlineDB = cms.string('oracle://cms_omds_lb/CMS_DT_ELEC_CONF'),

        offlineDB = cms.string('oracle://cms_orcon_prod/CMS_COND_21X_DT'),
        tag = cms.string('conf_test'),
        token = cms.string('[DB=00000000-0000-0000-0000-000000000000][CNT=DTConfigList][CLID=9CB14BE8-30A2-DB11-9935-000E0C5CE283][TECH=00000B01][OID=00000004-00000000]'),
        onlineAuthentication = cms.string('.')
    ),
    SinceAppendMode = cms.bool(True),
    record = cms.string('DTCCBConfigRcd'),
    loggingOn = cms.untracked.bool(True),
    debug = cms.bool(False)
)

process.p = cms.Path(process.conf_o2o)

