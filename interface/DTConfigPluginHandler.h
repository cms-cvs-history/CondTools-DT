#ifndef DTConfigPluginHandler_H
#define DTConfigPluginHandler_H
/** \class DTConfigPluginHandler
 *
 *  Description:
 *       Class to hold configuration identifier for chambers
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
#include "CondFormats/DTObjects/interface/DTConfigAbstractHandler.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "CondFormats/DTObjects/interface/DTConfigList.h"
#include "CondFormats/DTObjects/interface/DTConfigData.h"

namespace cond{
  template <typename T> class TypedRef;
}
class DTDBPluginSession;

//---------------
// C++ Headers --
//---------------
#include <string>
#include <map>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTConfigPluginHandler: public DTConfigAbstractHandler {

 public:

  /** Constructor
   */
  // fake constructor, only to set "instance"
  DTConfigPluginHandler();

  /** Operations
   */
  /// get content
  virtual const DTConfigList* getContainer();
  virtual int get( int cfgId, DTConfigData*& obj );

  virtual void getData( int cfgId, std::vector<const std::string*>& list );

  virtual int set( int cfgId, const std::string& token );
  /// Access methods to data
  typedef std::map< int, cond::TypedRef<DTConfigData>* >::const_iterator
                                                          const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

  /// purge db copy
  virtual void purge();

  /// copy to other DB
  /// newToken : empty string to create a new copy from scratch
  ///            existing token to update an existing copy
  /// listContainer : container name for the DTConfigList object
  /// dataContainer : container name for the DTConfigData object
  virtual std::string clone( DTDBAbstractSession* newSession,
                             const std::string& newToken,
                             const std::string& listContainer,
                             const std::string& dataContainer );

 private:

  /** Constructor
   */
  /// create a configuration handler, private to force use of
  ///        the static "create" function
  /// session : DB session to be used
  /// token : token of the DTConfigList object
  DTConfigPluginHandler( DTDBAbstractSession* session,
                         const std::string& token );
  /// constructor not to be used 
  DTConfigPluginHandler( const DTConfigPluginHandler& x );
  const DTConfigPluginHandler& operator=( const DTConfigPluginHandler& x );

  /** Destructor
   */
  virtual ~DTConfigPluginHandler();

  virtual DTConfigAbstractHandler* build( DTDBAbstractSession* session,
                                          const std::string& token );
  virtual void destroy( const DTDBAbstractSession* session );
  virtual void destroy( const DTConfigAbstractHandler* handler );

  /// copy to other DB, from scratch
  std::string clone( DTDBAbstractSession* newSession,
                     const std::string& listContainer,
                     const std::string& dataContainer );

  static std::string compToken( const std::string& token, int id );
  static int         compToken( const std::string& token );

  DTDBAbstractSession* dbSession;
  std::string objToken;
  cond::TypedRef<DTConfigList>* refSet;

  int cachedBrickNumber;
  int cachedStringNumber;
  int cachedByteNumber;

  typedef std::map<const DTDBAbstractSession*,DTConfigAbstractHandler*>
          handler_map;
  typedef handler_map::const_iterator c_map_iter;
  typedef handler_map::iterator         map_iter;
  static handler_map handlerMap;

};


#endif // DTConfigPluginHandler_H






