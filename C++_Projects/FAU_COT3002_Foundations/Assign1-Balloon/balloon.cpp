#include <iostream>
using namespace std;
#include "balloon.h"

// implementation of balloon autopilot class
// modified 1/9/94

const int ALT_CHANGE = 10;        // altitude change in Vent/Burn
const int JUMP_SIZE =  5;         // random fluctuation when flying

Balloon::Balloon()
// initialize balloon to be at zero altitude, no cruising forward
{
    myAltitude = 0;
    myCruiseSteps = 0;
}

void Balloon::Ascend(int height)
// precondition: height >= 0
// postcondition: balloon has ascended to altitude >= height
//                using minimum number of burns     
{
    cout << endl;
    cout << "***** (Height = " << myAltitude << ") ";
    cout << "Ascending to " << height << " meters ";
    cout << "*****" << endl << endl;
    
    while (myAltitude < height)
    {
        AltitudeMessage();
        Burn(); 
        cout << endl;
    }
}

void Balloon::Descend(int height)
// precondition: height >= 0
// postcondition: balloon has descended to altitude <= height
//                using minimum number of vents
{
    cout << endl;
    cout << "***** (Height = " << myAltitude << ") ";
    cout << "Descending to " << height << " meters ";
    cout << "*****" << endl << endl;
    
    while (myAltitude > height)
    {
        AltitudeMessage();              
        Vent();
        cout << endl;
    }
}

void Balloon::Cruise(int duration)
// precondition: 0 <= duration
// postcondition: cruise for duration time steps
//                (random altitude fluctuations possible)
{
    const int START = myAltitude;
    const int MARGIN = 5;

    cout << endl;
    cout << "***** Cruising at " << START << " meters " << endl;
    cout << "***** with margin +/- " << MARGIN << endl;
    cout << "****  for " << duration << " time-steps" << endl << endl;

    int k;
    for(k=0; k < duration; k+= 1)
    {
        AltitudeMessage();
	myCruiseSteps += 1;
	
        cout << "(time step " << k << ") ";
        AdjustAltitude();
        
        if (myAltitude > (START + MARGIN)){      // too high, let air out
            cout << " too high! ";
            Vent();
        }
        else if (myAltitude < (START - MARGIN)){ // too low, burn
            cout << " too low! ";
            Burn();
        }
        cout << endl;
    }
}

int Balloon::GetAltitude()
// postcondition: returns altitude of balloon
{
    return myAltitude;
}

int Balloon::GetLocation()
// postcondition: returns # of time-steps cruised forward     
{
    return myCruiseSteps;
}

void Balloon::AdjustAltitude()
// fly for one time-step, adjust altitude randomly (flip coin)
// precondition: altitude = t
// postcondition: altitude in range [t-JUMP_SIZE,t+JUMP_SIZE]
// exceptions: altitude cannot be below 0     
{
    
    if (myRand.RandInt(0,1) == 1){       // adjust on "coin-flip"

            // add random number in range [-JUMP_SIZE,JUMP_SIZE]
        
        int change = myRand.RandInt(-JUMP_SIZE,JUMP_SIZE);

        if (change > 0) {
            cout << "wind-shear +" << change << " m.";
        }
        else if (change < 0) {
            cout << "wind-shear -" << -1*change << " m.";
        }
        
        myAltitude += change;

        if (myAltitude < 0){            // keep balloon above ground
            myAltitude = 0;           
        }
    }
}

void Balloon::Burn()
// put air in balloon
// precondition: altitude = t
// postcondition: altitude = t + ALT_CHANGE     
{
    myAltitude += ALT_CHANGE;
    BurnMessage();
}

void Balloon::Vent()
// release air from balloon
// precondition: altitude = t     
// postcondition: altitude = t - ALT_CHANGE
// exception:     altitude cannot be below 0
{
    myAltitude -= ALT_CHANGE;
    if (myAltitude < 0) {
        myAltitude = 0;   
    } 
    VentMessage();    
}

void Balloon::BurnMessage()
// message printed when balloon filled with air (Burn called)
{
    cout << " Burn!";
}

void Balloon::VentMessage()
// message printed when air is let out of balloon (Vent called)     
{
    cout << " Woosh!";
}

void Balloon::AltitudeMessage()
// print current altitude
{
    cout << myAltitude << " meters ";
}
    
