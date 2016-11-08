/************************************************************************
*                        2016.10.28 @SDU C816                           *
*                   File Tools.h -> Some main working horse             *
* **********************************************************************/

#ifndef __TOOLS_H
#define __TOOLS_H

#include "Utilities.h"

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1F.h>
#include <TString.h>

#include <iostream>
#include <vector>
#include <map>

int CheckJetsMatchingEff(TTree *fTree, const char* outName);

#endif /* ifndef __TOOLS_H */
