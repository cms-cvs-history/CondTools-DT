#ifndef DTDBSession_H
#define DTDBSession_H
/** \class DTDBSession
 *
 *  Description: 
 *
 *
 *  $Date: 2007/06/22 14:02:17 $
 *  $Revision: 1.1.2.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "FWCore/ServiceRegistry/interface/ActivityRegistry.h"
#include "CondCore/DBCommon/interface/DBSession.h"
#include "CondCore/IOVService/interface/IOVService.h"
#include "CondCore/DBCommon/interface/AuthenticationMethod.h"
#include "CondCore/DBCommon/interface/PoolStorageManager.h"
#include "CondCore/DBCommon/interface/RelationalStorageManager.h"
#include "CondCore/DBCommon/interface/Ref.h"
#include "CondCore/DBCommon/interface/Time.h"
#include "CondCore/MetaDataService/interface/MetaData.h"
#include "CondCore/DBOutputService/interface/serviceCallbackRecord.h"
#include <string>
#include <map>
namespace edm{
  class Event;
  class EventSetup;
  class ParameterSet;
}

//---------------
// C++ Headers --
//---------------
#include <string>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTDBSession {

 public:

  /** Constructor
   */
  DTDBSession( const std::string& dbFile,
               const std::string& dbCatalog,
               const std::string& auth_path,
               bool siteLocalConfig = false );

  /** Destructor
   */
  virtual ~DTDBSession();

  /** Operations
   */
  /// get storage manager
  cond::PoolStorageManager* poolDB() const;

  /// start transaction
  void connect( bool readOnly );
  /// end   transaction
  void disconnect();

 private:

  cond::DBSession* m_session;
  cond::PoolStorageManager* m_pooldb;

};


#endif // DTDBSession_H






