/**********************************************************************
*               2016.10.28 @SDU C816                                  *
*       File Utilities.h -> Some auxiliary functions                  *
**********************************************************************/

#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <TFile.h>
#include <TKey.h>
#include <TLeaf.h>
#include <TTree.h>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

TFile *OpenFile(const char *FileName);
TFile *CreateNewFile(const char *FileName);
TTree *GetTTree(const char *fTreeName, TFile *fFile);
std::string GenerateTimeSuffix();
std::string GetNameSuffix(const char *fInputName);

template <typename T> T GetTreeValue(TTree *mTree, std::string fvar) {
  T *fValue = nullptr;
  TLeaf *fLeaf = mTree->GetLeaf(fvar.c_str());
  if (fLeaf != nullptr) {
    fValue = (T *)fLeaf->GetValuePointer();
  }
  if (fValue == nullptr)
    exit(-1);
  return *fValue;
}

// Combinations and permutations
std::vector<std::vector<int>> GetCombinations(int n, int r);
std::vector<std::vector<int>> GetPermutations(int n, int r);

// Read variables from TMVA xml file
void grabVariableList(TString WeightFile, std::vector<TString> &mVarialbes);

#endif // __UTILITIES_H
