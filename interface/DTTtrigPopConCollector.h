#ifndef DTTtrigPopConCollector_H
#define DTTtrigPopConCollector_H
/** \class DTTtrigPopConCollector
 *
 *  Description: 
 *
 *
 *  $Date: 2007/12/07 15:12:32 $
 *  $Revision: 1.2 $
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

class DTTtrigPopConCollector: public popcon::PopConSourceHandler<DTTtrig> {

 public:

  /** Constructor
   */
  DTTtrigPopConCollector( std::string name,
                  std::string connect_string,
                  const edm::Event& evt,
                  const edm::EventSetup& est,
                  const std::string& tag );
  void getNewObjects();

  /** Destructor
   */
  virtual ~DTTtrigPopConCollector();

  /** Operations
   */
  /// 

 private:

  std::string dataTag;

};


#endif // DTTtrigPopConCollector_H






