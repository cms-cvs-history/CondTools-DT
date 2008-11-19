touch test.db log.db xDump.txt xValidate.log
rm -f test.db log.db *Dump.txt *Validate.log
pool_build_object_relational_mapping              \
  -f ../xml/DTReadOutMapping-mapping-custom.xml   \
  -d CondFormatsDTObjects -c sqlite_file:test.db
pool_build_object_relational_mapping              \
  -f ../xml/DTT0-mapping-custom.xml               \
  -d CondFormatsDTObjects -c sqlite_file:test.db
pool_build_object_relational_mapping              \
  -f ../xml/DTTtrig-mapping-custom.xml            \
  -d CondFormatsDTObjects -c sqlite_file:test.db
pool_build_object_relational_mapping              \
  -f ../xml/DTMtime-mapping-custom.xml            \
  -d CondFormatsDTObjects -c sqlite_file:test.db
cmsRun validate_map_w.py
cmsRun validate_t0_w.py
cmsRun validate_tTrig_w.py
cmsRun validate_mTime_w.py
cmsRun validate_r.py
