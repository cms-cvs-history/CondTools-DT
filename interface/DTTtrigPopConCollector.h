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
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CondFormats/DTObjects/interface/DTTtrig.h"

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
  DTTtrigPopConCollector( const edm::ParameterSet& ps );

  /** Destructor
   */
  virtual ~DTTtrigPopConCollector();

  /** Operations
   */
  /// 
  void getNewObjects();
  std::string id() const;

 private:

//  std::string offlTag;
  std::string dataTag;
  DTTtrig* dataPtr;
//  unsigned int validityStart;

};


#endif // DTTtrigPopConCollector_H






