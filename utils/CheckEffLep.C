#include "Tools.h"
#include "Utilities.h"
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include <string>

int main(int argc, char const *argv[]) {
  std::string mFileName;
  std::string mConfigStr;
  std::string suffix;
  if (argc == 2) {
    mFileName = argv[1];
    mConfigStr = "";
  } else if (argc > 2) {
    mFileName = argv[2];
    mConfigStr = argv[1];
  }

  std::string outName = "CheckEffLep_";
  if (mConfigStr == "--time" || mConfigStr == "-t") {
    suffix = GenerateTimeSuffix();
  } else {
    suffix = GetNameSuffix(mFileName.c_str());
  }
  outName = outName + suffix + ".root";

  TFile *inFile = OpenFile(mFileName.c_str());
  TTree *nominal = GetTTree("nominal_Loose", inFile);
  std::cout << "Start running" << std::endl;
  CheckJetsWiLepMatchingEff(nominal, outName.c_str());
  return 0;
}
