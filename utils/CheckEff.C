#include <iostream>
#include "Tools.h"
#include "Utilities.h"

#include "TFile.h"
#include "TTree.h"
#include <string>

int main(int argc, char *argv[])
{
    std::string outName = "CheckEff_";
    const char* suffix = GenerateTimeSuffix();
    outName.append(suffix);
    outName.append(".root");
    
    TFile *inFile = OpenFile(argv[1]);
    TTree *nominal = GetTTree("nominal_Loose", inFile);
    std::cout<<"Start running..."<<std::endl;
    CheckJetsMatchingEff(nominal, outName.c_str());
    return 0;
}
