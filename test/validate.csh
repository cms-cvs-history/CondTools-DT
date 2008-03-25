rm -f test.db log.db *Dump.txt *Validate.log
pool_build_object_relational_mapping -f ../xml/DTT0-mapping-custom.xml -d CondFormatsDTObjectsCapabilities -c sqlite_file:test.db
pool_build_object_relational_mapping -f ../xml/DTTtrig-mapping-custom.xml -d CondFormatsDTObjectsCapabilities -c sqlite_file:test.db
pool_build_object_relational_mapping -f ../xml/DTMtime-mapping-custom.xml -d CondFormatsDTObjectsCapabilities -c sqlite_file:test.db
cmsRun validate_map_w.cfg
cmsRun validate_t0_w.cfg
cmsRun validate_tTrig_w.cfg
cmsRun validate_mTime_w.cfg
cmsRun validate_r.cfg
#cmsRun validate_t0r.cfg
#cmsRun validate_tTrigr.cfg
