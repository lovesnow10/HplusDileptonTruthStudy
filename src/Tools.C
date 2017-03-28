#include "TMVA/Reader.h"
#include "TRandom3.h"
#include "Tools.h"
#include <TMath.h>
#include <TROOT.h>

int GetLeptonPlusTruth(TTree *mEvent, TLorentzVector *LpVect) {
  std::vector<int> pdgid =
      GetTreeValue<std::vector<int>>(mEvent, "truth_pdgid");
  std::vector<float> truth_pt =
      GetTreeValue<std::vector<float>>(mEvent, "truth_pt");
  std::vector<float> truth_eta =
      GetTreeValue<std::vector<float>>(mEvent, "truth_eta");
  std::vector<float> truth_phi =
      GetTreeValue<std::vector<float>>(mEvent, "truth_phi");
  std::vector<float> truth_m =
      GetTreeValue<std::vector<float>>(mEvent, "truth_m");

  size_t nParticles = pdgid.size();
  int returnID = 0;

  for (size_t i = 0; i < nParticles; i++) {
    int id = pdgid.at(i);
    if (id == -11 || id == -13) {
      LpVect->SetPtEtaPhiM(truth_pt.at(i), truth_eta.at(i), truth_phi.at(i),
                           truth_m.at(i));
      returnID = id;
      break;
    }
  }
  return returnID;
}

int GetLeptonMinusTruth(TTree *mEvent, TLorentzVector *LmVect) {
  std::vector<int> pdgid =
      GetTreeValue<std::vector<int>>(mEvent, "truth_pdgid");
  std::vector<float> truth_pt =
      GetTreeValue<std::vector<float>>(mEvent, "truth_pt");
  std::vector<float> truth_eta =
      GetTreeValue<std::vector<float>>(mEvent, "truth_eta");
  std::vector<float> truth_phi =
      GetTreeValue<std::vector<float>>(mEvent, "truth_phi");
  std::vector<float> truth_m =
      GetTreeValue<std::vector<float>>(mEvent, "truth_m");

  size_t nParticles = pdgid.size();
  int returnID = 0;

  for (size_t i = 0; i < nParticles; i++) {
    int id = pdgid.at(i);
    if (id == 11 || id == 13) {
      LmVect->SetPtEtaPhiM(truth_pt.at(i), truth_eta.at(i), truth_phi.at(i),
                           truth_m.at(i));
      returnID = id;
      break;
    }
  }
  return returnID;
}

int GetLeptonPlusDetector(TTree *mEvent, TLorentzVector *LpVect) {
  std::vector<float> el_pt = GetTreeValue<std::vector<float>>(mEvent, "el_pt");
  std::vector<float> el_eta =
      GetTreeValue<std::vector<float>>(mEvent, "el_eta");
  std::vector<float> el_phi =
      GetTreeValue<std::vector<float>>(mEvent, "el_phi");
  std::vector<float> el_e = GetTreeValue<std::vector<float>>(mEvent, "el_e");
  std::vector<float> mu_pt = GetTreeValue<std::vector<float>>(mEvent, "mu_pt");
  std::vector<float> mu_eta =
      GetTreeValue<std::vector<float>>(mEvent, "mu_eta");
  std::vector<float> mu_phi =
      GetTreeValue<std::vector<float>>(mEvent, "mu_phi");
  std::vector<float> mu_e = GetTreeValue<std::vector<float>>(mEvent, "mu_e");
  std::vector<float> el_charge =
      GetTreeValue<std::vector<float>>(mEvent, "el_charge");
  std::vector<float> mu_charge =
      GetTreeValue<std::vector<float>>(mEvent, "mu_charge");

  int nElectrons = GetTreeValue<int>(mEvent, "nElectrons");
  int nMuons = GetTreeValue<int>(mEvent, "nMuons");

  int returnID =
      0; // this indicate leading or sub-leading lepton, only for ee and mumu
  // for emu, it indicates el:1 or mu:2

  int nDilType = nElectrons - nMuons; // 2:ee,0:emu,-2:mumu

  if (nDilType == 2) {
    if (el_charge.at(0) == 1)
      returnID = 1;
    else
      returnID = 2;
    LpVect->SetPtEtaPhiE(el_pt.at(returnID - 1), el_eta.at(returnID - 1),
                         el_phi.at(returnID - 1), el_e.at(returnID - 1));
  } else if (nDilType == -2) {
    if (mu_charge.at(0) == 1)
      returnID = 1;
    else
      returnID = 2;
    LpVect->SetPtEtaPhiE(mu_pt.at(returnID - 1), mu_eta.at(returnID - 1),
                         mu_phi.at(returnID - 1), mu_e.at(returnID - 1));
  } else if (nDilType == 0) {
    if (el_charge.at(0) == 1)
      returnID = 1;
    else
      returnID = 2;
    if (returnID == 1)
      LpVect->SetPtEtaPhiE(el_pt.at(0), el_eta.at(0), el_phi.at(0), el_e.at(0));
    else
      LpVect->SetPtEtaPhiE(mu_pt.at(0), mu_eta.at(0), mu_phi.at(0), mu_e.at(0));
  }
  return returnID;
}

int GetLeptonMinusDetector(TTree *mEvent, TLorentzVector *LpVect) {
  std::vector<float> el_pt = GetTreeValue<std::vector<float>>(mEvent, "el_pt");
  std::vector<float> el_eta =
      GetTreeValue<std::vector<float>>(mEvent, "el_eta");
  std::vector<float> el_phi =
      GetTreeValue<std::vector<float>>(mEvent, "el_phi");
  std::vector<float> el_e = GetTreeValue<std::vector<float>>(mEvent, "el_e");
  std::vector<float> mu_pt = GetTreeValue<std::vector<float>>(mEvent, "mu_pt");
  std::vector<float> mu_eta =
      GetTreeValue<std::vector<float>>(mEvent, "mu_eta");
  std::vector<float> mu_phi =
      GetTreeValue<std::vector<float>>(mEvent, "mu_phi");
  std::vector<float> mu_e = GetTreeValue<std::vector<float>>(mEvent, "mu_e");
  std::vector<float> el_charge =
      GetTreeValue<std::vector<float>>(mEvent, "el_charge");
  std::vector<float> mu_charge =
      GetTreeValue<std::vector<float>>(mEvent, "mu_charge");

  int nElectrons = GetTreeValue<int>(mEvent, "nElectrons");
  int nMuons = GetTreeValue<int>(mEvent, "nMuons");

  int returnID =
      0; // this indicate leading or sub-leading lepton, only for ee and mumu
  // for emu, it indicates el:1 or mu:2

  int nDilType = nElectrons - nMuons; // 2:ee,0:emu,-2:mumu

  if (nDilType == 2) {
    if (el_charge.at(0) == -1)
      returnID = 1;
    else
      returnID = 2;
    LpVect->SetPtEtaPhiE(el_pt.at(returnID - 1), el_eta.at(returnID - 1),
                         el_phi.at(returnID - 1), el_e.at(returnID - 1));
  } else if (nDilType == -2) {
    if (mu_charge.at(0) == -1)
      returnID = 1;
    else
      returnID = 2;
    LpVect->SetPtEtaPhiE(mu_pt.at(returnID - 1), mu_eta.at(returnID - 1),
                         mu_phi.at(returnID - 1), mu_e.at(returnID - 1));
  } else if (nDilType == 0) {
    if (el_charge.at(0) == -1)
      returnID = 1;
    else
      returnID = 2;
    if (returnID == 1)
      LpVect->SetPtEtaPhiE(el_pt.at(0), el_eta.at(0), el_phi.at(0), el_e.at(0));
    else
      LpVect->SetPtEtaPhiE(mu_pt.at(0), mu_eta.at(0), mu_phi.at(0), mu_e.at(0));
  }
  return returnID;
}

int GetJetDetector(TTree *mEvent, TLorentzVector *BxVect, ObjType _type) {
  std::vector<int> jet_truthmatch =
      GetTreeValue<std::vector<int>>(mEvent, "jet_truthmatch");
  std::vector<float> jet_pt =
      GetTreeValue<std::vector<float>>(mEvent, "jet_pt");
  std::vector<float> jet_eta =
      GetTreeValue<std::vector<float>>(mEvent, "jet_eta");
  std::vector<float> jet_phi =
      GetTreeValue<std::vector<float>>(mEvent, "jet_phi");
  std::vector<float> jet_e = GetTreeValue<std::vector<float>>(mEvent, "jet_e");

  int returnID = 0;
  size_t nJets = jet_truthmatch.size();

  int _bit = 0;
  switch (_type) {
  case ObjType::B0:
    _bit = 10;
    break;
  case ObjType::B1:
    _bit = 12;
    break;
  case ObjType::B2:
    _bit = 11;
    break;
  case ObjType::B3:
    _bit = 13;
    break;
  default:
    break;
  }
  for (size_t i = 0; i < nJets; i++) {
    int Jet_bit = int(TMath::Log2(jet_truthmatch.at(i)));
    if (Jet_bit == _bit && Jet_bit != 0) {
      returnID = Jet_bit;
      BxVect->SetPtEtaPhiE(jet_pt.at(i), jet_eta.at(i), jet_phi.at(i),
                           jet_e.at(i));
      break;
    }
  }
  return returnID;
}

int GetMetVector(TTree *mEvent, TLorentzVector *MetVect) {
  float met_met = GetTreeValue<float>(mEvent, "met_met");
  float met_phi = GetTreeValue<float>(mEvent, "met_phi");

  MetVect->SetPtEtaPhiM(met_met, 0, met_phi, 0);
  return 1;
}

int HasNMatchJets(TTree *mEvent, int nMatch) {
  int isMatch = 0;
  std::map<std::string, bool> mMatchingResults = JetMatching(mEvent);
  if (nMatch == 4) {
    if (mMatchingResults["B0"] && mMatchingResults["B1"] &&
        mMatchingResults["B2"] && mMatchingResults["B3"])
      isMatch = 1;
  } else {
    if (nMatch != 3)
      std::cout << "Wrong Match Number Gived, Using Default Value 3"
                << std::endl;
    if (mMatchingResults["B1"] && mMatchingResults["B2"] &&
        mMatchingResults["B3"])
      isMatch = 1;
  }
  return isMatch;
}

int CheckCorrectMatch(TTree *mEvent, std::vector<int> mPermutation,
                      int nMatch) {
  int isCorrect = 0;
  std::vector<int> jet_truthmatch =
      GetTreeValue<std::vector<int>>(mEvent, "jet_truthmatch");
  int tmpB0 = 0;
  int tmpB1 = 0;
  int tmpB2 = 0;
  int tmpB3 = 0;

  if (nMatch == 4) {
    tmpB0 = jet_truthmatch.at(mPermutation.at(0));
    tmpB1 = jet_truthmatch.at(mPermutation.at(1));
    tmpB2 = jet_truthmatch.at(mPermutation.at(2));
    tmpB3 = jet_truthmatch.at(mPermutation.at(3));

    tmpB0 = int(TMath::Log2(tmpB0));
    tmpB1 = int(TMath::Log2(tmpB1));
    tmpB2 = int(TMath::Log2(tmpB2));
    tmpB3 = int(TMath::Log2(tmpB3));

    if (tmpB0 == 10 && tmpB1 == 12 && tmpB2 == 11 && tmpB3 == 13)
      isCorrect = 1;
  } else {
    if (nMatch != 3)
      std::cout << "Wrong Match Number Gived, Using Default Value 3"
                << std::endl;
    tmpB1 = jet_truthmatch.at(mPermutation.at(0));
    tmpB2 = jet_truthmatch.at(mPermutation.at(1));
    tmpB3 = jet_truthmatch.at(mPermutation.at(2));

    tmpB1 = int(TMath::Log2(tmpB1));
    tmpB2 = int(TMath::Log2(tmpB2));
    tmpB3 = int(TMath::Log2(tmpB3));

    if (tmpB1 == 12 && tmpB2 == 11 && tmpB3 == 13)
      isCorrect = 1;
  }

  return isCorrect;
}

std::map<std::string, bool> JetMatching(TTree *mEvent) {
  const int BIT_B0 = 10;
  const int BIT_B1 = 12;
  const int BIT_B2 = 11;
  const int BIT_B3 = 13;

  std::map<std::string, bool> results;
  results.clear();

  // read stuff from tree
  std::vector<int> jet_truthmatch =
      GetTreeValue<std::vector<int>>(mEvent, "jet_truthmatch");
  int nJets = GetTreeValue<int>(mEvent, "nJets");

  results["B0"] = false;
  results["B1"] = false;
  results["B2"] = false;
  results["B3"] = false;

  for (size_t iJet = 0; iJet < nJets; iJet++) {
    int bit = int(TMath::Log2(jet_truthmatch.at(iJet)));
    switch (bit) {
    case BIT_B0:
      results["B0"] = true;
      break;
    case BIT_B1:
      results["B1"] = true;
      break;
    case BIT_B2:
      results["B2"] = true;
      break;
    case BIT_B3:
      results["B3"] = true;
      break;
    default:
      break;
    }
  }
  return results;
}

std::map<std::string, bool> LepMatching(TTree *mEvent) {
  std::map<std::string, bool> results;
  results.clear();
  results["Lp"] = false;
  results["Lm"] = false;

  const float DR_CUT = 0.4;
  // const float PT_CUT = 5.0;

  TLorentzVector LpTruth(0, 0, 0, 0);
  TLorentzVector LmTruth(0, 0, 0, 0);
  TLorentzVector LpDetector(0, 0, 0, 0);
  TLorentzVector LmDetector(0, 0, 0, 0);

  GetLeptonPlusTruth(mEvent, &LpTruth);
  GetLeptonMinusTruth(mEvent, &LmTruth);
  GetLeptonPlusDetector(mEvent, &LpDetector);
  GetLeptonMinusDetector(mEvent, &LmDetector);

  float dR_Lp = LpDetector.DeltaR(LpTruth);
  float dR_Lm = LmDetector.DeltaR(LmTruth);

  if (dR_Lp < DR_CUT)
    results["Lp"] = true;
  if (dR_Lm < DR_CUT)
    results["Lm"] = true;

  return results;
}

int CheckTrueDilepton(TTree *mEvent) {
  std::vector<int> pdgid =
      GetTreeValue<std::vector<int>>(mEvent, "truth_pdgid");
  int nLep = 0;
  for (auto _id : pdgid) {
    if (abs(_id) == 11 || abs(_id) == 13)
      nLep++;
  }
  if (nLep == 2)
    return 1;
  else
    return 0;
}

int FakeLeptonRemoval(TTree *mEvent) {
  int isFake = 1;
  bool pass = false;

  int nElectrons = GetTreeValue<int>(mEvent, "nElectrons");
  int nMuons = GetTreeValue<int>(mEvent, "nMuons");

  std::vector<int> el_true_type =
      GetTreeValue<std::vector<int>>(mEvent, "el_true_type");
  std::vector<int> mu_true_type =
      GetTreeValue<std::vector<int>>(mEvent, "mu_true_type");
  std::vector<int> el_true_origin =
      GetTreeValue<std::vector<int>>(mEvent, "el_true_origin");
  std::vector<int> mu_true_origin =
      GetTreeValue<std::vector<int>>(mEvent, "mu_true_origin");
  std::vector<int> el_true_originbkg =
      GetTreeValue<std::vector<int>>(mEvent, "el_true_originbkg");

  int nDilType = nElectrons - nMuons;

  int lt1 = -1;
  int lt2 = -1;
  int lo1 = -1;
  int lo2 = -1;
  int lb1 = -1;
  int lb2 = -1;
  if (nDilType == 2) {
    lt1 = el_true_type.at(0);
    lt2 = el_true_type.at(1);
    lo1 = el_true_origin.at(0);
    lo2 = el_true_origin.at(1);
    lb1 = el_true_originbkg.at(0);
    lb2 = el_true_originbkg.at(1);

    pass = (lt1 == 2 && (lo1 == 10 || lo1 == 12 || lo1 == 13 || lo1 == 14)) ||
           (lt1 == 4 && lo1 == 5 &&
            (lb1 == 10 || lb1 == 12 || lb1 == 13 || lb1 == 14));
    pass = pass &&
           ((lt2 == 2 && (lo2 == 10 || lo2 == 12 || lo2 == 13 || lo2 == 14)) ||
            (lt2 == 4 && lt2 == 5 &&
             (lb2 == 10 || lb2 == 12 || lb2 == 13 || lb2 == 14)));
  } else if (nDilType == -2) {
    lt1 = mu_true_type.at(0);
    lt2 = mu_true_type.at(1);
    lo1 = mu_true_origin.at(0);
    lo2 = mu_true_origin.at(1);

    pass = lt1 == 6 && lt2 == 6 &&
           (lo1 == 10 || lo1 == 12 || lo1 == 13 || lo1 == 14) &&
           (lo2 == 10 || lo2 == 12 || lo2 == 13 || lo2 == 14);
  } else if (nDilType == 0) {
    lt1 = el_true_type.at(0);
    lt2 = mu_true_type.at(0);
    lo1 = el_true_origin.at(0);
    lo2 = mu_true_origin.at(0);
    lb1 = el_true_originbkg.at(0);

    pass = lt2 == 6 && (lo2 == 10 || lo2 == 12 || lo2 == 13 || lo2 == 14);
    pass = pass &&
           ((lt1 == 2 && (lo1 == 10 || lo1 == 12 || lo1 == 13 || lo1 == 14)) ||
            (lt1 == 4 && lo1 == 5 &&
             (lb1 == 10 || lb1 == 12 || lb1 == 13 || lb1 == 14)));
  }

  if (pass)
    isFake = 0;
  return isFake;
}

int TauVeto(TTree *mEvent) {
  std::vector<int> pdgid =
      GetTreeValue<std::vector<int>>(mEvent, "truth_pdgid");
  int nTau = 0;
  for (auto id : pdgid) {
    if (abs(id) == 15)
      nTau = 1;
  }
  return nTau;
}

std::map<std::string, float> GetBDTInputVars(DilepEvent *mHpEvent) {
  std::map<std::string, float> mVariables;
  std::map<std::string, float> mNu_Lepton =
      SolveLeptonDirectNeutrinos(mHpEvent);
  mVariables.clear();
  TLorentzVector PseWp = *(mHpEvent->GetVector(ObjType::Lp)) +
                         *(mHpEvent->GetVector(ObjType::MET)) * 0.5;
  TLorentzVector PseWm = *(mHpEvent->GetVector(ObjType::Lm)) +
                         *(mHpEvent->GetVector(ObjType::MET)) * 0.5;
  TLorentzVector PseTop = *(mHpEvent->GetVector(ObjType::B1)) + PseWp;
  TLorentzVector PseTbar = *(mHpEvent->GetVector(ObjType::B3)) + PseWm;
  TLorentzVector PseHplus = *(mHpEvent->GetVector(ObjType::B2)) + PseTop;

  TLorentzVector PseTop_NoNu =
      *(mHpEvent->GetVector(ObjType::B1)) + *(mHpEvent->GetVector(ObjType::Lp));
  TLorentzVector PseTbar_NoNu =
      *(mHpEvent->GetVector(ObjType::B3)) + *(mHpEvent->GetVector(ObjType::Lm));
  TLorentzVector PseHplus_NoNu =
      *(mHpEvent->GetVector(ObjType::B2)) + PseTop_NoNu;

  TLorentzVector Nu_Lp, Nu_Lm;
  Nu_Lp.SetPtEtaPhiM(mNu_Lepton["Lp"], mHpEvent->GetVector(ObjType::Lp)->Eta(),
                     mHpEvent->GetVector(ObjType::Lp)->Phi(), 0);
  Nu_Lm.SetPtEtaPhiM(mNu_Lepton["Lm"], mHpEvent->GetVector(ObjType::Lm)->Eta(),
                     mHpEvent->GetVector(ObjType::Lm)->Phi(), 0);

  TLorentzVector PseWp_Lep = *(mHpEvent->GetVector(ObjType::Lp)) + Nu_Lp;
  TLorentzVector PseWm_Lep = *(mHpEvent->GetVector(ObjType::Lm)) + Nu_Lm;

  TLorentzVector PseTop_Lep = *(mHpEvent->GetVector(ObjType::B1)) + PseWp_Lep;
  TLorentzVector PseTbar_Lep = *(mHpEvent->GetVector(ObjType::B3)) + PseWm_Lep;
  TLorentzVector PseHplus_Lep =
      *(mHpEvent->GetVector(ObjType::B2)) + PseTop_Lep;

  mVariables["PseWp_Mass"] = PseWp.M();
  mVariables["PseWm_Mass"] = PseWm.M();
  mVariables["PseTop_Mass"] = PseTop.M();
  mVariables["PseTbar_Mass"] = PseTbar.M();
  //mVariables["PseHplus_Mass"] = PseHplus.M();

  //mVariables["dR_Lp_Lm"] = mHpEvent->GetVector(ObjType::Lp)
  //                             ->DeltaR(*(mHpEvent->GetVector(ObjType::Lm)));
  mVariables["dR_B1_B2"] = mHpEvent->GetVector(ObjType::B1)
                               ->DeltaR(*(mHpEvent->GetVector(ObjType::B2)));
  mVariables["dR_B1_B3"] = mHpEvent->GetVector(ObjType::B3)
                               ->DeltaR(*(mHpEvent->GetVector(ObjType::B1)));
  mVariables["dR_B2_B3"] = mHpEvent->GetVector(ObjType::B2)
                               ->DeltaR(*(mHpEvent->GetVector(ObjType::B3)));

  //mVariables["Pse_dR_Wp_Wm"] = PseWp.DeltaR(PseWm);
  mVariables["Pse_dR_ttbar"] = PseTop.DeltaR(PseTbar);
  //mVariables["Pse_dR_Hp_tbar"] = PseHplus.DeltaR(PseTbar);

  //mVariables["PseWp_Mass_NoNu"] = mHpEvent->GetVector(ObjType::Lp)->M();
  //mVariables["PseWm_Mass_NoNu"] = mHpEvent->GetVector(ObjType::Lm)->M();
  mVariables["PseTop_Mass_NoNu"] = PseTop_NoNu.M();
  mVariables["PseTbar_Mass_NoNu"] = PseTbar_NoNu.M();
  //mVariables["PseHplus_Mass_NoNu"] = PseHplus_NoNu.M();
  mVariables["Pse_dR_ttbar_NoNu"] = PseTop_NoNu.DeltaR(PseTbar_NoNu);
  //mVariables["Pse_dR_Hp_tbar_NoNu"] = PseHplus_NoNu.DeltaR(PseTbar_NoNu);
  //mVariables["PseWp_Mass_Lep"] = PseWp_Lep.M();
  //mVariables["PseWm_Mass_Lep"] = PseWm_Lep.M();
  mVariables["PseTop_Mass_Lep"] = PseTop_Lep.M();
  mVariables["PseTbar_Mass_Lep"] = PseTbar_Lep.M();
  //mVariables["PseHplus_Mass_Lep"] = PseHplus_Lep.M();

  //Added new variables
  mVariables["pT_B1"] = mHpEvent->GetVector(ObjType::B1)->Pt();
  mVariables["pT_B2"] = mHpEvent->GetVector(ObjType::B2)->Pt();
  mVariables["pT_B3"] = mHpEvent->GetVector(ObjType::B3)->Pt();
  mVariables["mv2c10_B1"] = mHpEvent->GetBTagging(ObjType::B1);
  mVariables["mv2c10_B2"] = mHpEvent->GetBTagging(ObjType::B2);
  mVariables["mv2c10_B3"] = mHpEvent->GetBTagging(ObjType::B3);

  return mVariables;
}

std::map<std::string, float> SolveLeptonDirectNeutrinos(DilepEvent *mHpEvent) {
  float Nu_Lp, Nu_Lm, MET;
  float Phi_Lp, Phi_Lm, Phi_MET;
  float cosTheta_Lp, cosTheta_Lm;
  Nu_Lp = 0;
  Nu_Lm = 0;
  MET = mHpEvent->GetVector(ObjType::MET)->Pt();
  Phi_MET = mHpEvent->GetVector(ObjType::MET)->Phi();
  Phi_Lp = mHpEvent->GetVector(ObjType::Lp)->Phi();
  Phi_Lm = mHpEvent->GetVector(ObjType::Lm)->Phi();
  cosTheta_Lp = mHpEvent->GetVector(ObjType::Lp)->CosTheta();
  cosTheta_Lm = mHpEvent->GetVector(ObjType::Lm)->CosTheta();

  Nu_Lp = MET * TMath::Sin(Phi_Lm - Phi_MET) / TMath::Sin(Phi_Lm - Phi_Lp);
  Nu_Lm = MET * TMath::Sin(Phi_Lp - Phi_MET) / TMath::Sin(Phi_Lp - Phi_Lm);

  Nu_Lp = Nu_Lp / cosTheta_Lp;
  Nu_Lm = Nu_Lm / cosTheta_Lm;

  std::map<std::string, float> results;
  results["Lp"] = Nu_Lp;
  results["Lm"] = Nu_Lm;

  return results;
}

int CheckJetsMatchingEff(TTree *mTree, std::string outName) {
  std::cout << "Initialzing...CheckJetsMatchingEff" << std::endl;

  // Variable defination
  int nJets, nBTags;
  int nElectrons, nMuons;

  // information storage
  TH1F *h_4j3bRawEvents = new TH1F("h_4j3bRawEvents", "", 6, 0, 6);
  TH1F *h_4j4bRawEvents = new TH1F("h_4j4bRawEvents", "", 6, 0, 6);
  TH1F *h_4j3bIncRawEvents = new TH1F("h_4j3bIncRawEvents", "", 6, 0, 6);
  TH1F *h_Yields = new TH1F("h_Yields", "", 6, 0, 6);
  TH1F *h_Bit = new TH1F("h_Bit", "", 16, 0, 16);
  double mTotalUsefulEvent4j3b;
  double mTotalUsefulEvent4j4b;
  double mTotalUsefulEvent4j3bInc;
  double mTotal4j3bRawEvents;
  double mTotal4j4bRawEvents;
  double mTotal4j3bIncRawEvents;

  mTotal4j3bRawEvents = 0;
  mTotal4j4bRawEvents = 0;
  mTotal4j3bIncRawEvents = 0;
  mTotalUsefulEvent4j3b = 0;
  mTotalUsefulEvent4j4b = 0;
  mTotalUsefulEvent4j3bInc = 0;

  // loop over TTree
  long nentries = mTree->GetEntriesFast();
  for (long i = 0; i < nentries; ++i) {
    if (i % 500 == 0)
      std::cout << "Processing " << i << std::endl;
    mTree->GetEntry(i);
    nJets = GetTreeValue<int>(mTree, "nJets");
    nBTags = GetTreeValue<int>(mTree, "nBTags");
    nElectrons = GetTreeValue<int>(mTree, "nElectrons");
    nMuons = GetTreeValue<int>(mTree, "nMuons");
    if (nElectrons + nMuons < 2)
      continue;
    if (nJets < 4)
      continue;
    if (nJets > 3 && nBTags < 3)
      continue;

    std::map<std::string, bool> mMatchingResults;
    mMatchingResults = JetMatching(mTree);
    bool b0_match = mMatchingResults["B0"];
    bool b1_match = mMatchingResults["B1"];
    bool b2_match = mMatchingResults["B2"];
    bool b3_match = mMatchingResults["B3"];

    mTotal4j3bIncRawEvents++;
    if (b0_match)
      h_4j3bIncRawEvents->Fill(0);
    if (b1_match)
      h_4j3bIncRawEvents->Fill(1);
    if (b2_match)
      h_4j3bIncRawEvents->Fill(2);
    if (b3_match)
      h_4j3bIncRawEvents->Fill(3);
    if (b1_match && b2_match && b3_match) {
      mTotalUsefulEvent4j3bInc++;
      h_4j3bIncRawEvents->Fill(4);
      if (b0_match)
        h_4j3bIncRawEvents->Fill(5);
    }
    if (nJets > 3 && nBTags == 3) {
      mTotal4j3bRawEvents++;
      if (b0_match)
        h_4j3bRawEvents->Fill(0);
      if (b1_match)
        h_4j3bRawEvents->Fill(1);
      if (b2_match)
        h_4j3bRawEvents->Fill(2);
      if (b3_match)
        h_4j3bRawEvents->Fill(3);
      if (b1_match && b2_match && b3_match) {
        mTotalUsefulEvent4j3b++;
        h_4j3bRawEvents->Fill(4);
        if (b0_match)
          h_4j3bRawEvents->Fill(5);
      }
    } else if (nJets > 3 && nBTags > 3) {
      mTotal4j4bRawEvents++;
      if (b0_match)
        h_4j4bRawEvents->Fill(0);
      if (b1_match)
        h_4j4bRawEvents->Fill(1);
      if (b2_match)
        h_4j4bRawEvents->Fill(2);
      if (b3_match)
        h_4j4bRawEvents->Fill(3);
      if (b1_match && b2_match && b3_match) {
        mTotalUsefulEvent4j4b++;
        h_4j4bRawEvents->Fill(4);
        if (b0_match)
          h_4j4bRawEvents->Fill(5);
      }
    }
  }
  std::cout << "Loop ended, saving information to Histos..." << std::endl;
  h_Yields->Fill(0.0, mTotal4j3bRawEvents);
  h_Yields->Fill(2.0, mTotal4j4bRawEvents);
  h_Yields->Fill(1.0, mTotalUsefulEvent4j3b);
  h_Yields->Fill(3.0, mTotalUsefulEvent4j4b);
  h_Yields->Fill(4.0, mTotal4j3bIncRawEvents);
  h_Yields->Fill(5.0, mTotalUsefulEvent4j3bInc);
  h_4j3bRawEvents->Scale(1.0 / mTotal4j3bRawEvents);
  h_4j4bRawEvents->Scale(1.0 / mTotal4j4bRawEvents);
  h_4j3bIncRawEvents->Scale(1.0 / mTotal4j3bIncRawEvents);

  // Set Label
  h_Yields->GetXaxis()->SetBinLabel(1, "4j3b");
  h_Yields->GetXaxis()->SetBinLabel(3, "4j4b");
  h_Yields->GetXaxis()->SetBinLabel(2, "avail.4j3b");
  h_Yields->GetXaxis()->SetBinLabel(4, "avail.4j4b");
  h_Yields->GetXaxis()->SetBinLabel(5, "4j3bInc");
  h_Yields->GetXaxis()->SetBinLabel(6, "avail.4j3bInc");

  h_4j3bRawEvents->GetXaxis()->SetBinLabel(1, "b0");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(2, "b1");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(3, "b2");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(4, "b3");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(6, "all");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(5, "no_b0");

  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(1, "b0");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(2, "b1");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(3, "b2");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(4, "b3");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(6, "all");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(5, "no_b0");

  h_4j4bRawEvents->GetXaxis()->SetBinLabel(1, "b0");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(2, "b1");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(3, "b2");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(4, "b3");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(6, "all");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(5, "no_b0");

  std::cout << "Saving ROOT file..." << std::endl;
  TFile outFile(outName.c_str(), "RECREATE");
  h_Yields->Write();
  h_4j3bRawEvents->Write();
  h_4j4bRawEvents->Write();
  h_4j3bIncRawEvents->Write();
  h_Bit->Write();
  outFile.Close();

  return 1;
}

int CheckJetsWiLepMatchingEff(TTree *mTree, std::string outName) {
  std::cout << "Initialzing...CheckJetsWiLepMatchingEff" << std::endl;

  // Variable defination
  int nJets, nBTags;
  int nElectrons, nMuons;

  // information storage
  TH1F *h_4j3bRawEvents = new TH1F("h_4j3bRawEvents", "", 8, 0, 8);
  TH1F *h_4j4bRawEvents = new TH1F("h_4j4bRawEvents", "", 8, 0, 8);
  TH1F *h_4j3bIncRawEvents = new TH1F("h_4j3bIncRawEvents", "", 8, 0, 8);
  TH1F *h_Yields = new TH1F("h_Yields", "", 6, 0, 6);
  TH1F *h_Bit = new TH1F("h_Bit", "", 16, 0, 16);
  double mTotalUsefulEvent4j3b;
  double mTotalUsefulEvent4j4b;
  double mTotalUsefulEvent4j3bInc;
  double mTotal4j3bRawEvents;
  double mTotal4j4bRawEvents;
  double mTotal4j3bIncRawEvents;

  mTotal4j3bRawEvents = 0;
  mTotal4j4bRawEvents = 0;
  mTotal4j3bIncRawEvents = 0;
  mTotalUsefulEvent4j3b = 0;
  mTotalUsefulEvent4j4b = 0;
  mTotalUsefulEvent4j3bInc = 0;

  // loop over TTree
  long nentries = mTree->GetEntriesFast();
  for (long i = 0; i < nentries; ++i) {
    if (i % 500 == 0)
      std::cout << "Processing " << i << std::endl;
    mTree->GetEntry(i);

    // remove tau-events and fake events
    int tau = TauVeto(mTree);
    int fake = FakeLeptonRemoval(mTree);
    if (tau || fake)
      continue;

    nJets = GetTreeValue<int>(mTree, "nJets");
    nBTags = GetTreeValue<int>(mTree, "nBTags");
    nElectrons = GetTreeValue<int>(mTree, "nElectrons");
    nMuons = GetTreeValue<int>(mTree, "nMuons");
    if (nElectrons + nMuons < 2)
      continue;
    if (nJets < 4)
      continue;
    if (nJets > 3 && nBTags < 3)
      continue;

    std::map<std::string, bool> mJetMatchingResults;
    std::map<std::string, bool> mLepMatchingResults;
    mJetMatchingResults = JetMatching(mTree);
    mLepMatchingResults = LepMatching(mTree);
    bool b0_match = mJetMatchingResults["B0"];
    bool b1_match = mJetMatchingResults["B1"];
    bool b2_match = mJetMatchingResults["B2"];
    bool b3_match = mJetMatchingResults["B3"];
    bool lp_match = mLepMatchingResults["Lp"];
    bool lm_match = mLepMatchingResults["Lm"];

    mTotal4j3bIncRawEvents++;
    if (b0_match)
      h_4j3bIncRawEvents->Fill(0);
    if (b1_match)
      h_4j3bIncRawEvents->Fill(1);
    if (b2_match)
      h_4j3bIncRawEvents->Fill(2);
    if (b3_match)
      h_4j3bIncRawEvents->Fill(3);
    if (lp_match)
      h_4j3bIncRawEvents->Fill(4);
    if (lm_match)
      h_4j3bIncRawEvents->Fill(5);
    if (b1_match && b2_match && b3_match && lp_match && lm_match) {
      mTotalUsefulEvent4j3bInc++;
      h_4j3bIncRawEvents->Fill(6);
      if (b0_match)
        h_4j3bIncRawEvents->Fill(7);
    }
    if (nJets > 3 && nBTags == 3) {
      mTotal4j3bRawEvents++;
      if (b0_match)
        h_4j3bRawEvents->Fill(0);
      if (b1_match)
        h_4j3bRawEvents->Fill(1);
      if (b2_match)
        h_4j3bRawEvents->Fill(2);
      if (b3_match)
        h_4j3bRawEvents->Fill(3);
      if (lp_match)
        h_4j3bRawEvents->Fill(4);
      if (lm_match)
        h_4j3bRawEvents->Fill(5);
      if (b1_match && b2_match && b3_match && lp_match && lm_match) {
        mTotalUsefulEvent4j3b++;
        h_4j3bRawEvents->Fill(6);
        if (b0_match)
          h_4j3bRawEvents->Fill(7);
      }
    } else if (nJets > 3 && nBTags > 3) {
      mTotal4j4bRawEvents++;
      if (b0_match)
        h_4j4bRawEvents->Fill(0);
      if (b1_match)
        h_4j4bRawEvents->Fill(1);
      if (b2_match)
        h_4j4bRawEvents->Fill(2);
      if (b3_match)
        h_4j4bRawEvents->Fill(3);
      if (lp_match)
        h_4j4bRawEvents->Fill(4);
      if (lm_match)
        h_4j4bRawEvents->Fill(5);
      if (b1_match && b2_match && b3_match && lm_match && lp_match) {
        mTotalUsefulEvent4j4b++;
        h_4j4bRawEvents->Fill(6);
        if (b0_match)
          h_4j4bRawEvents->Fill(7);
      }
    }
  }
  std::cout << "Loop ended, saving information to Histos..." << std::endl;
  h_Yields->Fill(0.0, mTotal4j3bRawEvents);
  h_Yields->Fill(2.0, mTotal4j4bRawEvents);
  h_Yields->Fill(1.0, mTotalUsefulEvent4j3b);
  h_Yields->Fill(3.0, mTotalUsefulEvent4j4b);
  h_Yields->Fill(4.0, mTotal4j3bIncRawEvents);
  h_Yields->Fill(5.0, mTotalUsefulEvent4j3bInc);
  h_4j3bRawEvents->Scale(1.0 / mTotal4j3bRawEvents);
  h_4j4bRawEvents->Scale(1.0 / mTotal4j4bRawEvents);
  h_4j3bIncRawEvents->Scale(1.0 / mTotal4j3bIncRawEvents);

  // Set Label
  h_Yields->GetXaxis()->SetBinLabel(1, "4j3b");
  h_Yields->GetXaxis()->SetBinLabel(3, "4j4b");
  h_Yields->GetXaxis()->SetBinLabel(2, "avail.4j3b");
  h_Yields->GetXaxis()->SetBinLabel(4, "avail.4j4b");
  h_Yields->GetXaxis()->SetBinLabel(5, "4j3bInc");
  h_Yields->GetXaxis()->SetBinLabel(6, "avail.4j3bInc");

  h_4j3bRawEvents->GetXaxis()->SetBinLabel(1, "b0");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(2, "b1");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(3, "b2");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(4, "b3");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(5, "Lp");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(6, "Lm");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(8, "all");
  h_4j3bRawEvents->GetXaxis()->SetBinLabel(7, "no_b0");

  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(1, "b0");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(2, "b1");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(3, "b2");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(4, "b3");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(5, "Lp");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(6, "Lm");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(8, "all");
  h_4j3bIncRawEvents->GetXaxis()->SetBinLabel(7, "no_b0");

  h_4j4bRawEvents->GetXaxis()->SetBinLabel(1, "b0");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(2, "b1");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(3, "b2");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(4, "b3");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(5, "Lp");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(6, "Lm");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(8, "all");
  h_4j4bRawEvents->GetXaxis()->SetBinLabel(7, "no_b0");

  std::cout << "Saving ROOT file..." << std::endl;
  TFile outFile(outName.c_str(), "RECREATE");
  h_Yields->Write();
  h_4j3bRawEvents->Write();
  h_4j4bRawEvents->Write();
  h_4j3bIncRawEvents->Write();
  h_Bit->Write();
  outFile.Close();

  return 1;
}

int PrepareBDTTrees(TTree *fTree, std::string outName) {
  // output objects defination
  TFile *outFile = CreateNewFile(outName.c_str());
  TTree *mSigTree = new TTree("signal", "signal");
  TTree *mBkgTree = new TTree("background", "background");
  TTree *mAppTree = fTree->CloneTree(0);
  TRandom3 *rnd = new TRandom3();

  // neutrio direction same as MET
  float PseTop_Mass, PseTbar_Mass;
  float dR_B1_B2, dR_B1_B3, dR_B2_B3;
  float Pse_dR_ttbar;
  // Add new variables
  // No Neutrinos
  float PseTop_Mass_NoNu, PseTbar_Mass_NoNu;
  float Pse_dR_ttbar_NoNu;
  // Neutrino direction same as corresponding lepton
  float PseTop_Mass_Lep, PseTbar_Mass_Lep;
  float pT_B1, pT_B2,pT_B3;
  float mv2c10_B1, mv2c10_B2,mv2c10_B3;

  const int toMatch = 3;
  int UsedForTrain;

  PseTop_Mass = 0;
  PseTbar_Mass = 0;
  dR_B1_B2 = 0;
  dR_B1_B3 = 0;
  dR_B2_B3 = 0;
  Pse_dR_ttbar = 0;
  PseTop_Mass_NoNu = 0;
  PseTbar_Mass_NoNu = 0;
  Pse_dR_ttbar_NoNu = 0;
  PseTop_Mass_Lep = 0;
  PseTbar_Mass_Lep = 0;
  pT_B1 = 0;
  pT_B2 = 0;
  pT_B3 = 0;
  mv2c10_B1 = 0;
  mv2c10_B2 = 0;
  mv2c10_B3 = 0;
  UsedForTrain = -1;

  mSigTree->Branch("PseTop_Mass", &PseTop_Mass, "PseTop_Mass/F");
  mSigTree->Branch("PseTbar_Mass", &PseTbar_Mass, "PseTbar_Mass/F");
  mSigTree->Branch("dR_B1_B2", &dR_B1_B2, "dR_B1_B2/F");
  mSigTree->Branch("dR_B1_B3", &dR_B1_B3, "dR_B1_B3/F");
  mSigTree->Branch("dR_B2_B3", &dR_B2_B3, "dR_B2_B3/F");
  mSigTree->Branch("Pse_dR_ttbar", &Pse_dR_ttbar, "Pse_dR_ttbar/F");
  mSigTree->Branch("UsedForTrain", &UsedForTrain, "UsedForTrain/I");
  mSigTree->Branch("PseTop_Mass_NoNu", &PseTop_Mass_NoNu, "PseTop_Mass_NoNu/F");
  mSigTree->Branch("PseTbar_Mass_NoNu", &PseTbar_Mass_NoNu,
                   "PseTbar_Mass_NoNu/F");
  mSigTree->Branch("Pse_dR_ttbar_NoNu", &Pse_dR_ttbar_NoNu,
                   "Pse_dR_ttbar_NoNu/F");
  mSigTree->Branch("PseTop_Mass_Lep", &PseTop_Mass_Lep, "PseTop_Mass_Lep/F");
  mSigTree->Branch("PseTbar_Mass_Lep", &PseTbar_Mass_Lep, "PseTbar_Mass_Lep/F");
  mSigTree->Branch("pT_B1",&pT_B1,"pT_B1/F");
  mSigTree->Branch("pT_B2",&pT_B2,"pT_B2/F");
  mSigTree->Branch("pT_B3",&pT_B3,"pT_B3/F");
  mSigTree->Branch("mv2c10_B1",&mv2c10_B1,"mv2c10_B1/F");
  mSigTree->Branch("mv2c10_B2",&mv2c10_B2,"mv2c10_B2/F");
  mSigTree->Branch("mv2c10_B3",&mv2c10_B3,"mv2c10_B3/F");

  mBkgTree->Branch("PseTop_Mass", &PseTop_Mass, "PseTop_Mass/F");
  mBkgTree->Branch("PseTbar_Mass", &PseTbar_Mass, "PseTbar_Mass/F");
  mBkgTree->Branch("dR_B1_B2", &dR_B1_B2, "dR_B1_B2/F");
  mBkgTree->Branch("dR_B1_B3", &dR_B1_B3, "dR_B1_B3/F");
  mBkgTree->Branch("dR_B2_B3", &dR_B2_B3, "dR_B2_B3/F");
  mBkgTree->Branch("Pse_dR_ttbar", &Pse_dR_ttbar, "Pse_dR_ttbar/F");
  mBkgTree->Branch("UsedForTrain", &UsedForTrain, "UsedForTrain/I");
  mBkgTree->Branch("PseTop_Mass_NoNu", &PseTop_Mass_NoNu, "PseTop_Mass_NoNu/F");
  mBkgTree->Branch("PseTbar_Mass_NoNu", &PseTbar_Mass_NoNu,
                   "PseTbar_Mass_NoNu/F");
  mBkgTree->Branch("Pse_dR_ttbar_NoNu", &Pse_dR_ttbar_NoNu,
                   "Pse_dR_ttbar_NoNu/F");
  mBkgTree->Branch("PseTop_Mass_Lep", &PseTop_Mass_Lep, "PseTop_Mass_Lep/F");
  mBkgTree->Branch("PseTbar_Mass_Lep", &PseTbar_Mass_Lep, "PseTbar_Mass_Lep/F");
  mBkgTree->Branch("pT_B1",&pT_B1,"pT_B1/F");
  mBkgTree->Branch("pT_B2",&pT_B2,"pT_B2/F");
  mBkgTree->Branch("pT_B3",&pT_B3,"pT_B3/F");
  mBkgTree->Branch("mv2c10_B1",&mv2c10_B1,"mv2c10_B1/F");
  mBkgTree->Branch("mv2c10_B2",&mv2c10_B2,"mv2c10_B2/F");
  mBkgTree->Branch("mv2c10_B3",&mv2c10_B3,"mv2c10_B3/F");

  // main loop
  long nentries = fTree->GetEntries();
  for (long i = 0; i < nentries; i++) {
    if (i % 500 == 0)
      std::cout << "Processing " << i << "/" << nentries << std::endl;
    fTree->GetEntry(i);

    if (TauVeto(fTree) || FakeLeptonRemoval(fTree))
      continue;

    // define some variables
    int nJets = GetTreeValue<int>(fTree, "nJets");
    int nBTags = GetTreeValue<int>(fTree, "nBTags");
    // if(!(nJets > 3 && nBTags >= 3)) continue; //AnaRegion = SR (Tight Def)
    if (!(nJets >= 3 && nBTags > 0))
      continue; // AnaRegion = Loose Def

    std::map<std::string, bool> mMatchingResults;
    mMatchingResults = JetMatching(fTree);
    if (!(mMatchingResults["B1"] && mMatchingResults["B2"] &&
          mMatchingResults["B3"]))
      continue;

    int UsedForApply = (rnd->Uniform(0, 1) < 0.333) ? 1 : 0;
    if (UsedForApply) {
      mAppTree->Fill();
      continue;
    }
    TLorentzVector *LpVect = new TLorentzVector();
    TLorentzVector *LmVect = new TLorentzVector();
    TLorentzVector *MetVect = new TLorentzVector();
    TLorentzVector *B1Vect = new TLorentzVector();
    TLorentzVector *B2Vect = new TLorentzVector();
    TLorentzVector *B3Vect = new TLorentzVector();

    GetLeptonPlusDetector(fTree, LpVect);
    GetLeptonMinusDetector(fTree, LmVect);
    GetMetVector(fTree, MetVect);

    std::vector<float> jet_pt =
        GetTreeValue<std::vector<float>>(fTree, "jet_pt");
    std::vector<float> jet_eta =
        GetTreeValue<std::vector<float>>(fTree, "jet_eta");
    std::vector<float> jet_phi =
        GetTreeValue<std::vector<float>>(fTree, "jet_phi");
    std::vector<float> jet_e = GetTreeValue<std::vector<float>>(fTree, "jet_e");
    std::vector<float> jet_mv2c10 = GetTreeValue<std::vector<float>>(fTree,"jet_mv2c10");

    // Get Jets permutation and loop them
    int hasCorrectMatch = 0;
    std::vector<std::vector<int>> mPermutations =
        GetPermutations(nJets, toMatch);
    for (auto mPerm : mPermutations) {
      //      if(!hasCorrectMatch) hasCorrectMatch = CheckCorrectMatch(fTree,
      //      mPerm, toMatch);
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

      event->SetBTagging(ObjType::B1, jet_mv2c10.at(mPerm.at(0)));
      event->SetBTagging(ObjType::B2, jet_mv2c10.at(mPerm.at(1)));
      event->SetBTagging(ObjType::B3, jet_mv2c10.at(mPerm.at(2)));

      std::map<std::string, float> mVariables = GetBDTInputVars(event);

      PseTop_Mass = mVariables.at("PseTop_Mass");
      PseTbar_Mass = mVariables.at("PseTbar_Mass");
      dR_B1_B2 = mVariables.at("dR_B1_B2");
      dR_B1_B3 = mVariables.at("dR_B1_B3");
      dR_B2_B3 = mVariables.at("dR_B2_B3");
      Pse_dR_ttbar = mVariables.at("Pse_dR_ttbar");
      PseTop_Mass_NoNu = mVariables.at("PseTop_Mass_NoNu");
      PseTbar_Mass_NoNu = mVariables.at("PseTbar_Mass_NoNu");
      Pse_dR_ttbar_NoNu = mVariables.at("Pse_dR_ttbar_NoNu");
      PseTop_Mass_Lep = mVariables.at("PseTop_Mass_Lep");
      PseTbar_Mass_Lep = mVariables.at("PseTbar_Mass_Lep");
      pT_B1 = mVariables.at("pT_B1");
      pT_B2 = mVariables.at("pT_B2");
      pT_B3 = mVariables.at("pT_B3");
      mv2c10_B1 = mVariables.at("mv2c10_B1");
      mv2c10_B2 = mVariables.at("mv2c10_B2");
      mv2c10_B3 = mVariables.at("mv2c10_B3");

      UsedForTrain = (rnd->Uniform(1) < 0.5) ? 1 : 0;

      if (hasCorrectMatch)
        mBkgTree->Fill();
      else {
        int correct = CheckCorrectMatch(fTree, mPerm, toMatch);
        if (correct) {
          mSigTree->Fill();
          hasCorrectMatch = correct;
        } else {
          mBkgTree->Fill();
        }
      }
    }
  }

  // Save stuff
  std::cout << "Saving TTrees..." << std::endl;
  mSigTree->Write(0, TObject::kOverwrite);
  mBkgTree->Write(0, TObject::kOverwrite);
  mAppTree->Write(0, TObject::kOverwrite);
  std::cout << "Saving TFile " << outName << std::endl;
  outFile->Close();
  return 1;
}

int ApplyRecoBDT(TFile *inFile, TString &WeightFile, TString &SampleName,
                 TFile *outFile) {
  TTree *mTree = GetTTree("nominal_Loose", inFile);
  std::vector<TString> variables;

  std::map<TString, float> mVariables;
  const int toMatch = 3;

  TString MethodName("RecoBDT_Dilepton");

  grabVariableList(WeightFile, variables);

  TMVA::Reader *mReader = new TMVA::Reader("!Color:!Silent");

  for (auto _var : variables) {
    mReader->AddVariable(_var, &mVariables[_var]);
  }
  mReader->BookMVA(MethodName, WeightFile);

  TString histname = MethodName + "_" + SampleName;
  TH1F *hist_out = new TH1F(histname, histname, 20, -1, 1);
  TH1F *hist_eff = new TH1F(histname + "_eff", histname + "_eff", 2, 0, 2);

  TTree *outTree = new TTree("outTree", "RecoBDTapply");

  std::vector<float> mScoresVec;
  std::vector<float> mJetPt;
  std::vector<float> mJetEta;
  std::vector<float> mJetPhi;
  std::vector<float> mJetE;
  int iCorrectMatch;
  int iMaxScore;
  long iEntry;

  outTree->Branch("CorrectMatchIndex", &iCorrectMatch, "iCorrectMatch/I");
  outTree->Branch("MaxScoreIndex", &iMaxScore, "iMaxScore/I");
  outTree->Branch("EntryIndex", &iEntry, "iEntry/L");
  outTree->Branch("RecoBDTScore", &mScoresVec);
  outTree->Branch("jet_pt", &mJetPt);
  outTree->Branch("jet_eta", &mJetEta);
  outTree->Branch("jet_phi", &mJetPhi);
  outTree->Branch("jet_e", &mJetE);

  long nentries = mTree->GetEntries();

  for (long i = 0; i < nentries; ++i) {
    if (i % 500 == 0)
      std::cout << "Processing " << i << "/" << nentries << std::endl;
    mTree->GetEntry(i);

    if (TauVeto(mTree) || FakeLeptonRemoval(mTree))
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
    std::vector<float> jet_mv2c10 = GetTreeValue<std::vector<float>>(mTree, "jet_mv2c10");

    mJetPt = jet_pt;
    mJetEta = jet_eta;
    mJetPhi = jet_phi;
    mJetE = jet_e;

    int nJets = GetTreeValue<int>(mTree, "nJets");
    int nBTags = GetTreeValue<int>(mTree, "nBTags");

    if (!(nJets >= 3 && nBTags > 0))
      continue;

    std::vector<std::vector<int>> mPermutations =
        GetPermutations(nJets, toMatch);
    int nPerms = mPermutations.size();
    mScoresVec.clear();
    iCorrectMatch = -1;
    iMaxScore = -2;
    iEntry = -1;
    bool hasCorrectMatch = false;
    for (int iPerm = 0; iPerm < nPerms; ++iPerm) {
      std::vector<int> mPerm = mPermutations.at(iPerm);

      if (!hasCorrectMatch) {
        int correct = CheckCorrectMatch(mTree, mPerm);
        if (correct == 1) {
          iCorrectMatch = iPerm;
          hasCorrectMatch = true;
        }
      }
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
      event->SetBTagging(ObjType::B1, jet_mv2c10.at(mPerm.at(0)));
      event->SetBTagging(ObjType::B2, jet_mv2c10.at(mPerm.at(1)));
      event->SetBTagging(ObjType::B3, jet_mv2c10.at(mPerm.at(2)));

      std::map<std::string, float> tmpVariables = GetBDTInputVars(event);
      for (auto _var : mVariables) {
        mVariables.at(_var.first) = tmpVariables.at(_var.first.Data());
      }
      float tmpBDTscore = mReader->EvaluateMVA(MethodName);
      mScoresVec.push_back(tmpBDTscore);
      /*if (i == 5850)
      {
        std::cout<<iPerm<<": "<<tmpBDTscore<<std::endl;
        for (auto p : mPerm)
        {
          std::cout<<p<<" ";
        }
        std::cout<<std::endl;
        for (auto _var : mVariables)
        {
          std::cout<<"\t"<<_var.first.Data()<<": "<<_var.second<<std::endl;
        }
        std::cout<<"-----"<<std::endl;
      }*/
    }
    /*    auto ite_score = mScoresVec->begin();
        iMaxScore = distance(ite_score, max_element(ite_score,
       ite_score+nPerms));
        hist_out->Fill(*max_element(ite_score, ite_score+nPerms));*/
    iMaxScore = distance(mScoresVec.begin(),
                         max_element(mScoresVec.begin(), mScoresVec.end()));
    hist_out->Fill(*max_element(mScoresVec.begin(), mScoresVec.end()));

    if (iCorrectMatch == iMaxScore) {
      hist_eff->Fill(1);
      iEntry = i;
    } else
      hist_eff->Fill(0);
    outTree->Fill();
  }
  hist_out->Write(0, TObject::kOverwrite);
  hist_eff->Write(0, TObject::kOverwrite);
  outTree->Write(0, TObject::kOverwrite);
  return 1;
}
