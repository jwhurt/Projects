#ifndef _BALLOON_H
#define _BALLOON_H

// class for balloon manipulation using simulated auto pilot
// written: 8/29/93  (based on an idea of Dave Reed)
// modified: 8/30/94, 12/29/94, 11/3/95

// member function explanation:
//
// Ascend: balloon ascends to height specified by parameter
//         in a sequence of burns.  Each burn raises the
//         altitude by 10 meters
//
// Cruise: balloon cruises at current altitude for a number of time
//         steps specified by parameter.  Random wind-shear can cause
//         balloon to rise and fall, but vents and burns keep the
//         balloon within +/- 5 meters of the altitude at which cruising
//         starts

// Descend:   balloon descends to height specified by parameter in a
//            sequence of vents.  Each vent drops the balloon 10 meters,
//            or to the ground (if less than 10 meters to the ground)
//
//
// int GetAltitude: returns altitude (in meters)
//
// int GetLocation: returns how many time steps taken
    
#include "randgen.h"    

class Balloon
{
  public:
    Balloon();                     // constructor

        // change where balloon is (up,down,"forward")
            
    void Ascend(int);              // ascend so altitude >= parameter
    void Descend(int);             // descend so altitude <= parameter
    void Cruise(int);              // cruise for parameter time-steps

        // retrieve balloon's location

    int GetAltitude();              // returns height above ground
    int GetLocation();              // returns how cruise "steps" taken

  private:

    int myAltitude;                // altitude (height) of balloon
    int myCruiseSteps;             // number of time-steps cruised
    RandGen myRand;                // random number generator

    void Burn();                   // go up (some amount)
    void Vent();                   // go down (some amount)
    void BurnMessage();            // message printed when burning
    void VentMessage();            // message printed when venting
    void AltitudeMessage();        // message to print current altitude
    void AdjustAltitude();         // adjust altitude randomly
};

#endif   // _BALLOON_H defined 
