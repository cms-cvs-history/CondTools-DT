import FWCore.ParameterSet.Config as cms

process = cms.Process("DTDBINIT")
process.source = cms.Source("EmptyIOVSource",
    lastRun = cms.untracked.uint32(1),
    timetype = cms.string('runnumber'),
    firstRun = cms.untracked.uint32(1),
    interval = cms.uint32(1)
)

process.conf_init = cms.EDFilter("DTConfigDBInit",
    catalog = cms.string('file:testcatalog.xml'),
    contact = cms.string('sqlite_file:testconf.db'),
    name = cms.string('list_conf'),
    authPath = cms.string('.')
)

process.p = cms.Path(process.conf_init)

