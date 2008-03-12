#ifndef DTT0PopConCollector_H
#define DTT0PopConCollector_H
/** \class DTT0PopConCollector
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
#include "CondFormats/DTObjects/interface/DTT0.h"

//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTT0PopConCollector: public popcon::PopConSourceHandler<DTT0> {

 public:

  /** Constructor
   */
  DTT0PopConCollector( const edm::ParameterSet& ps );

  /** Destructor
   */
  virtual ~DTT0PopConCollector();

  /** Operations
   */
  /// 
  void getNewObjects();
  std::string id() const;

 private:

//  std::string offlTag;
  std::string dataTag;
  DTT0* dataPtr;
//  unsigned int validityStart;

};


#endif // DTT0PopConCollector_H






