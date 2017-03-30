#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "TFile.h"
#include "TH1F.h"
#include "TMVA/Reader.h"
#include "TString.h"
#include "TTree.h"

#include "Tools.h"
#include "Utilities.h"

int main(int argc, char const *argv[]) {
  if (argc < 5) {
    std::cout << "No enough args, exit..." << std::endl;
    return -1;
  }
  // open file and get trees
  TFile *inFile = OpenFile(argv[1]);
  TFile *outFile = CreateNewFile(argv[4]);
  TString WeightFile(argv[2]);
  TString SampleName(argv[3]);
  ApplyRecoBDT(inFile, WeightFile, SampleName, outFile);

  inFile->Close();
  outFile->Close();
  return 0;
}
