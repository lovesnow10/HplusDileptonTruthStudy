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
/*  TTree *mTree = GetTTree("nominal_Loose", inFile);

  // setup TMVA reader
  std::vector<TString> variables;
  //  variables.push_back("dR_B1_B2");
  //  variables.push_back("dR_B2_B3");
  //  variables.push_back("dR_B1_B3");
  //  variables.push_back("Pse_dR_ttbar");
  //  variables.push_back("PseTbar_Mass_NoNu");
  //  variables.push_back("PseHplus_Mass_NoNu");
  //  variables.push_back("Pse_dR_Hp_tbar_NoNu");
  //  variables.push_back("PseTbar_Mass_Lep");
  //  variables.push_back("PseHplus_Mass_Lep");

  std::map<TString, float> mVarialbes;
  const int toMatch = 3;

  TString MethodName("RecoBDT_Dilepton");
  TString WeightFile(argv[2]);

  grabVariableList(WeightFile, variables);

  TMVA::Reader *mReader = new TMVA::Reader("!Color:!Silent");

  for (auto _var : variables) {
    mReader->AddVariable(_var, &mVarialbes[_var]);
  }
  mReader->BookMVA(MethodName, WeightFile);

  // Define histogram
  TString histname = MethodName + "_" + TString(argv[3]);
  TH1F *hist_out = new TH1F(histname, histname, 20, -1, 1);

  long nentries = mTree->GetEntries();

  for (long i = 0; i < nentries; ++i) {
    if (i % 500 == 0)
      std::cout << "Processing " << i << std::endl;
    mTree->GetEntry(i);

    if (TauVeto(mTree) || FakeLeptonRemoval(mTree))
      continue;

    int nJets = GetTreeValue<int>(mTree, "nJets");
    int nBTags = GetTreeValue<int>(mTree, "nBTags");

    if (!(nJets >= 3 && nBTags > 0))
      continue;

    TLorentzVector *LpVect = new TLorentzVector();
    TLorentzVector *LmVect = new TLorentzVector();
    TLorentzVector *MetVect = new TLorentzVector();
    TLorentzVector *B1Vect = new TLorentzVector();
    TLorentzVector *B2Vect = new TLorentzVector();
    TLorentzVector *B3Vect = new TLorentzVector();

    GetLeptonPlusDetector(mTree, LpVect);
    GetLeptonMinusDetector(mTree, LmVect);
    GetMetVector(mTree, MetVect);

    std::vector<float> jet_pt =
        GetTreeValue<std::vector<float>>(mTree, "jet_pt");
    std::vector<float> jet_eta =
        GetTreeValue<std::vector<float>>(mTree, "jet_eta");
    std::vector<float> jet_phi =
        GetTreeValue<std::vector<float>>(mTree, "jet_phi");
    std::vector<float> jet_e = GetTreeValue<std::vector<float>>(mTree, "jet_e");

    float mMaxBDTScore = -9999.0;

    // Get jets permutation and loop them
    std::vector<std::vector<int>> mPermutations =
        GetPermutations(nJets, toMatch);
    for (auto mPerm : mPermutations) {
      B1Vect->SetPtEtaPhiE(jet_pt.at(mPerm.at(0)), jet_eta.at(mPerm.at(0)),
                           jet_phi.at(mPerm.at(0)), jet_e.at(mPerm.at(0)));
      B2Vect->SetPtEtaPhiE(jet_pt.at(mPerm.at(1)), jet_eta.at(mPerm.at(1)),
                           jet_phi.at(mPerm.at(1)), jet_e.at(mPerm.at(1)));
      B3Vect->SetPtEtaPhiE(jet_pt.at(mPerm.at(2)), jet_eta.at(mPerm.at(2)),
                           jet_phi.at(mPerm.at(2)), jet_e.at(mPerm.at(2)));
      DilepEvent *event = new DilepEvent();
      event->SetVector(ObjType::B1, B1Vect);
      event->SetVector(ObjType::B2, B2Vect);
      event->SetVector(ObjType::B3, B3Vect);
      event->SetVector(ObjType::Lp, LpVect);
      event->SetVector(ObjType::Lm, LmVect);
      event->SetVector(ObjType::MET, MetVect);

      std::map<std::string, float> tmpVariables = GetBDTInputVars(event);
      //mVarialbes.clear();
      for (auto _var : variables) {
        mVarialbes.at(_var) = tmpVariables.at(_var.Data());
      }
      float tmpBDTscore = mReader->EvaluateMVA(MethodName);

      mMaxBDTScore = (tmpBDTscore > mMaxBDTScore) ? tmpBDTscore : mMaxBDTScore;
    }
    hist_out->Fill(mMaxBDTScore);
  }
*/
  inFile->Close();
  outFile->Close();
  return 0;
}
