#include <iostream>
#include "Tools.h"
#include "Utilities.h"

#include "TFile.h"
#include "TTree.h"
#include <string>

int main(int argc, char const *argv[]) {
  std::string outName = "CheckEffLep_";
  const char* suffix = GenerateTimeSuffix();
  outName.append(suffix);
  outName.append(".root");

  TFile *inFile = OpenFile(argv[1]);
  TTree *nominal = GetTTree("nominal_Loose", inFile);
  std::cout << "Start running" << std::endl;
  CheckJetsWiLepMatchingEff(nominal, outName.c_str());
  return 0;
}
