/**********************************************************************
*               2016.10.28 @SDU C816                                  *
*       File Utilities.h -> Some auxiliary functions                  *
**********************************************************************/

#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <TFile.h>
#include <TTree.h>
#include <TKey.h>
#include <iostream>
#include <ctime>

TFile *OpenFile(const char* FileName);
TFile *CreateNewFile(const char* FileName);
TTree *GetTTree(const char* fTreeName, TFile* fFile);
const char* GenerateTimeSuffix();

#endif // __UTILITIES_H

