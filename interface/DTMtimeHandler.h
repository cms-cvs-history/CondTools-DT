#ifndef DTMtimeHandler_H
#define DTMtimeHandler_H
/** \class DTMtimeHandler
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
class DTMtime;

//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTMtimeHandler: public popcon::PopConSourceHandler<DTMtime> {

 public:

  /** Constructor
   */
  DTMtimeHandler( std::string name,
                  std::string connect_string,
                  std::string catalog,
                  const edm::Event& evt,
                  const edm::EventSetup& est,
                  const std::string& tag,
                  const std::string& file );
  void getNewObjects();

  /** Destructor
   */
  virtual ~DTMtimeHandler();

  /** Operations
   */
  /// 

 private:

  std::string dataTag;
  std::string fileName;

};


#endif // DTMtimeHandler_H






