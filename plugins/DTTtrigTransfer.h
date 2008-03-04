#ifndef DTTtrigTransfer_H
#define DTTtrigTransfer_H
/** \class DTTtrigTransfer
 *
 *  Description: 
 *
 *
 *  $Date: 2007/12/10 19:46:20 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------
#include "CondCore/PopCon/interface/PopConAnalyzer.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "CondFormats/DTObjects/interface/DTTtrig.h"

//---------------
// C++ Headers --
//---------------
#include <string>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTTtrigTransfer: public popcon::PopConAnalyzer<DTTtrig> {

 public:

  /** Constructor
   */
  DTTtrigTransfer( const edm::ParameterSet& ps );

  /** Destructor
   */
  virtual ~DTTtrigTransfer();

  /** Operations
   */
  /// 
  void initSource( const edm::Event& evt, const edm::EventSetup& est );

 private:

  std::string dataTag;

};


#endif // DTTtrigTransfer_H






