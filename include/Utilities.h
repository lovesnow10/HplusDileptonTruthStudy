/**********************************************************************
*               2016.10.28 @SDU C816                                  *
*       File Utilities.h -> Some auxiliary functions                  *
**********************************************************************/

#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <TFile.h>
#include <TTree.h>
#include <TKey.h>
#include <TLeaf.h>
#include <iostream>
#include <ctime>
#include <string>

TFile *OpenFile(const char* FileName);
TFile *CreateNewFile(const char* FileName);
TTree *GetTTree(const char* fTreeName, TFile* fFile);
std::string GenerateTimeSuffix();
std::string GetNameSuffix(const char* fInputName);

template <typename T> T GetTreeValue(TTree* mTree, std::string fvar)
{
  T *fValue = nullptr;
  TLeaf *fLeaf = mTree->GetLeaf(fvar.c_str());
  if (fLeaf != nullptr)
  {
    fValue = (T *)fLeaf->GetValuePointer();
  }
  if (fValue == nullptr) exit(-1);
  return *fValue;
}

#endif // __UTILITIES_H
