#include "Tools.h"
#include "Utilities.h"
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include <string>

int main(int argc, char *argv[]) {
  std::string mFileName;
  std::string mConfigStr;
  if (argc == 2) {
    mFileName = argv[1];
    mConfigStr = "";
  } else if (argc > 2) {
    mFileName = argv[2];
    mConfigStr = argv[1];
  }

  std::string outName = "CheckEff_";
  if (mConfigStr == "--time" || mConfigStr == "-t") {
    const char *suffix = GenerateTimeSuffix();
    outName.append(suffix);
    outName.append(".root");
  } else {
    const char *suffix = GetNameSuffix(mFileName.c_str());
    outName.append(suffix);
    outName.append(".root");
  }

  TFile *inFile = OpenFile(mFileName.c_str());
  TTree *nominal = GetTTree("nominal_Loose", inFile);
  std::cout << "Start running..." << std::endl;
  CheckJetsMatchingEff(nominal, outName.c_str());
  return 0;
}
