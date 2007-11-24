#ifndef DTCCBConfigHandler_H
#define DTCCBConfigHandler_H
/** \class DTCCBConfigHandler
 *
 *  Description: 
 *
 *
 *  $Date: 2007-08-17 15:08:40 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------
#include "CondCore/PopCon/interface/PopConSourceHandler.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
class DTCCBConfig;
namespace coral {
  class ISessionProxy;
}

//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTCCBConfigHandler: public popcon::PopConSourceHandler<DTCCBConfig> {

 public:

  /** Constructor
   */
  DTCCBConfigHandler( std::string name,
                      std::string connect_string,
                      std::string catalog,
                      const edm::Event& evt,
                      const edm::EventSetup& est,
                      const std::string& tag,
                      const std::string& onlineDB,
                      const std::string& onlineAuthPath,
                      const std::string& offlineAuthPath,
                      const std::string& token );
  void getNewObjects();

  /** Destructor
   */
  virtual ~DTCCBConfigHandler();

  /** Operations
   */
  /// 

 private:

  std::string dataTag;
  std::string onlineConnect;
  std::string onlineAuthentication;
  std::string offlineAuthentication;
  std::string offlineConnect;
  std::string offlineCatalog;
  std::string listToken;
  DTCCBConfig* ccbConfig;

  coral::ISessionProxy* isession;
  void chkConfigList();

};


#endif // DTCCBConfigHandler_H






