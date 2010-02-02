#ifndef DTDBPluginSession_H
#define DTDBPluginSession_H
/** \class DTDBPluginSession
 *
 *  Description: 
 *
 *  TEMPORARY TOOL TO HANDLE CONFIGURATIONS
 *  TO BE REMOVED IN FUTURE RELEASES
 *
 *
 *  $Date: 2010/01/15 09:30:00 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------
#include "CondFormats/DTObjects/interface/DTDBAbstractSession.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include <string>
#include <map>
namespace edm {
  class Event;
  class EventSetup;
  class ParameterSet;
}
namespace cond{
  class PoolTransaction;
  class Connection;
  class DBSession;
}

//---------------
// C++ Headers --
//---------------
#include <string>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTDBPluginSession: public DTDBAbstractSession {

 public:

  /** Constructor
   */
  DTDBPluginSession( const std::string& dbFile,
                     const std::string& dbCatalog,
                     const std::string& auth_path,
                     bool siteLocalConfig = false );

  /** Destructor
   */
  virtual ~DTDBPluginSession();

  /** Operations
   */
  /// get storage manager
  virtual cond::PoolTransaction* poolDB() const;

  /// start transaction
  virtual void connect( bool readOnly );
  /// end   transaction
  virtual void disconnect();

 private:

  cond::DBSession* m_session;
  cond::Connection* m_connection;
  cond::PoolTransaction* m_pooldb;

};


#endif // DTDBPluginSession_H






