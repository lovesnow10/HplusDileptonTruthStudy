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
#include <TMath.h>

#include <iostream>
#include <map>
#include <vector>

// fuctionalities
int GetLeptonPlusTruth(TTree *mEvent, TLorentzVector *LpVect);
int GetLeptonMinusTruth(TTree *mEvent, TLorentzVector *LmVect);
int GetLeptonPlusDetector(TTree *mEvent, TLorentzVector *LpVect);
int GetLeptonMinusDetector(TTree *mEvent, TLorentzVector *LmVect);
int GetJetDetector(TTree *mEvent, TLorentzVector *BxVect, ObjType _type);
int GetMetVector(TTree *mEvent, TLorentzVector *MetVect);
int CheckTrueDilepton(TTree *mEvent);
int FakeLeptonRemoval(TTree *mEvent);
int TauVeto(TTree *mEvent);
int HasNMatchJets(TTree *mEvent, int nMatch = 3);
int CheckCorrectMatch(TTree *mEvent, std::vector<int> mPermutation, int nMatch = 3);
std::map<std::string, bool> JetMatching(TTree *mEvent);
std::map<std::string, bool> LepMatching(TTree *mEvent);

std::map<std::string, float> GetBDTInputVars(DilepEvent *mHpEvent);
std::map<std::string, float> SolveLeptonDirectNeutrinos(DilepEvent *mHpEvent);

// main functions
int CheckJetsMatchingEff(TTree *fTree, std::string outName);
int CheckJetsWiLepMatchingEff(TTree *fTree, std::string outName);
int PrepareBDTTrees(TTree *fTree, std::string outName);

#endif /* ifndef __TOOLS_H */
