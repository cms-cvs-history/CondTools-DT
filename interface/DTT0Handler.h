#ifndef DTT0Handler_H
#define DTT0Handler_H
/** \class DTT0Handler
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
class DTT0;

//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTT0Handler: public popcon::PopConSourceHandler<DTT0> {

 public:

  /** Constructor
   */
  DTT0Handler( std::string name,
               std::string connect_string,
               std::string catalog,
               const edm::Event& evt,
               const edm::EventSetup& est,
               const std::string& tag,
               const std::string& file );
  void getNewObjects();

  /** Destructor
   */
  virtual ~DTT0Handler();

  /** Operations
   */
  /// 

 private:

  std::string dataTag;
  std::string fileName;

};


#endif // DTT0Handler_H






