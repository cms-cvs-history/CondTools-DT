#!/bin/csh
pool_build_object_relational_mapping -f ../xml/DTCCBConfig-mapping-custom.xml -d CondFormatsDTObjectsCapabilities -c oracle://cms_orcon_prod/CMS_COND_21X_DT -u "CMS_COND_21X_DT" -p "GEBL51TMB4IV"
pool_build_object_relational_mapping -f ../xml/DTConfigData-mapping-custom.xml -d CondFormatsDTObjectsCapabilities -c oracle://cms_orcon_prod/CMS_COND_21X_DT -u "CMS_COND_21X_DT" -p "GEBL51TMB4IV"
pool_build_object_relational_mapping -f ../xml/DTConfigList-mapping-custom.xml -d CondFormatsDTObjectsCapabilities -c oracle://cms_orcon_prod/CMS_COND_21X_DT -u "CMS_COND_21X_DT" -p "GEBL51TMB4IV"

