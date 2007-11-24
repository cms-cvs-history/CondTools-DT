#ifndef DTTtrigHandler_H
#define DTTtrigHandler_H
/** \class DTTtrigHandler
 *
 *  Description: 
 *
 *
 *  $Date: 2007-11-07 15:08:40 $
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
class DTTtrig;

//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTTtrigHandler: public popcon::PopConSourceHandler<DTTtrig> {

 public:

  /** Constructor
   */
  DTTtrigHandler( std::string name,
                  std::string connect_string,
                  std::string catalog,
                  const edm::Event& evt,
                  const edm::EventSetup& est,
                  const std::string& tag,
                  const std::string& file );
  void getNewObjects();

  /** Destructor
   */
  virtual ~DTTtrigHandler();

  /** Operations
   */
  /// 

 private:

  std::string dataTag;
  std::string fileName;

};


#endif // DTTtrigHandler_H






