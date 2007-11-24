#ifndef DTTtrigAnalyzer_H
#define DTTtrigAnalyzer_H
/** \class DTTtrigAnalyzer
 *
 *  Description: 
 *
 *
 *  $Date: 2007-11-07 15:48:54 $
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

class DTTtrigAnalyzer: public popcon::PopConAnalyzer<DTTtrig> {

 public:

  /** Constructor
   */
  DTTtrigAnalyzer( const edm::ParameterSet& ps );

  /** Destructor
   */
  virtual ~DTTtrigAnalyzer();

  /** Operations
   */
  /// 
  void initSource( const edm::Event& evt, const edm::EventSetup& est );

 private:

  std::string dataTag;
  std::string fileName;

};


#endif // DTTtrigAnalyzer_H






