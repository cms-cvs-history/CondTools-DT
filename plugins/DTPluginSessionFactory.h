#ifndef DTPluginSessionFactory_H
#define DTPluginSessionFactory_H
/** \class DTPluginSessionFactory
 *
 *  Description: 
 *
 *
 *  $Date: 2010-01-14 23:18:12 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------
#include "CondFormats/DTObjects/interface/DTAbstractSessionFactory.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
namespace edm{
  class ParameterSet;
  class ActivityRegistry;
}


//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

namespace cond { namespace service {
class DTPluginSessionFactory: public DTAbstractSessionFactory {

 public:

  /** Constructor
   */
  DTPluginSessionFactory();
  DTPluginSessionFactory( const edm::ParameterSet & iConfig,
                          edm::ActivityRegistry & iAR );

  /** Destructor
   */
  virtual ~DTPluginSessionFactory();

  /** Operations
   */
  /// create DB session pointer
  virtual DTDBAbstractSession* createSession( const std::string& dbFile,
                                              const std::string& dbCatalog,
                                              const std::string& auth_path,
                                              bool siteLocalConfig = false );

 private:


};

} }

#endif // DTPluginSessionFactory_H






