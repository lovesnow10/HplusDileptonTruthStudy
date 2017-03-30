#include "Tools.h"
#include "Utilities.h"
#include <iostream>
#include <string>

#include "TFile.h"
#include "TTree.h"

int main(int argc, char const *argv[]) {
  std::string outName(argv[2]);

  TFile *inFile = OpenFile(argv[1]);
  TTree *nominal = GetTTree("nominal_Loose", inFile);
  std::cout << "Start running...PrepareBDTTrees" << std::endl;
  PrepareBDTTrees(nominal, outName);
  return 0;
}
