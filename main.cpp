#include "const.h"
#include <cstdlib>
#include <time.h>
#include <vector>
#include "vector2D.h"
#include "Photon.h"
#include <iostream>
#include "Muons.h"
#include "Material.h"

int main(int argc, char** argv)
{

    //Initialisation of the pseudo-random number generator.
    srand(time(0));


    //Creation of the material.
    Material Scint;

    //Creation of 10 muons passing throught the scintillator.
    for (int i = 0; i < 10; i++)
    {
        //Creation of a muon.
        Muons p;
        //Propagation of the muon.
        p.beam(Scint);
    }
    

    return 0;
}