#ifndef DTPerformanceHandler_H
#define DTPerformanceHandler_H
/** \class DTPerformanceHandler
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
class DTPerformance;

//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTPerformanceHandler: public popcon::PopConSourceHandler<DTPerformance> {

 public:

  /** Constructor
   */
  DTPerformanceHandler( std::string name,
                  std::string connect_string,
                  std::string catalog,
                  const edm::Event& evt,
                  const edm::EventSetup& est,
                  const std::string& tag,
                  const std::string& file );
  void getNewObjects();

  /** Destructor
   */
  virtual ~DTPerformanceHandler();

  /** Operations
   */
  /// 

 private:

  std::string dataTag;
  std::string fileName;

};


#endif // DTPerformanceHandler_H






