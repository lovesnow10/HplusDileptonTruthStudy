/************************************************************************
*                        2016.10.28 @SDU C816                           *
*                   File Tools.h -> Some main working horse             *
* **********************************************************************/

#ifndef __TOOLS_H
#define __TOOLS_H

#include "HplusDileptonEvent.h"
#include "Utilities.h"

#include <TBranch.h>
#include <TFile.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TString.h>
#include <TTree.h>

#include <iostream>
#include <map>
#include <vector>

// fuctionalities
int GetLeptonPlusTruth(TTree *mEvent, TLorentzVector *LpVect);
int GetLeptonMinusTruth(TTree *mEvent, TLorentzVector *LmVect);
int GetLeptonPlusDetector(TTree *mEvent, TLorentzVector *LpVect);
int GetLeptonMinusDetector(TTree *mEvent, TLorentzVector *LmVect);
int GetJetDetector(TTree *mEvent, TLorentzVector *BxVect, ObjType _type);
int CheckTrueDilepton(TTree *mEvent);
int FakeLeptonRemoval(TTree *mEvent);
int TauVeto(TTree *mEvent);
std::map<std::string, bool> JetMatching(TTree *mEvent);
std::map<std::string, bool> LepMatching(TTree *mEvent);

// main functions
int CheckJetsMatchingEff(TTree *fTree, std::string outName);
int CheckJetsWiLepMatchingEff(TTree *fTree, std::string outName);

#endif /* ifndef __TOOLS_H */
