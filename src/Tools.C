#include "Tools.h"
#include <TMath.h>

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

int CheckJetsMatchingEff(TTree *mTree, const char *outName) {
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
  TFile outFile(outName, "RECREATE");
  h_Yields->Write();
  h_4j3bRawEvents->Write();
  h_4j4bRawEvents->Write();
  h_4j3bIncRawEvents->Write();
  h_Bit->Write();
  outFile.Close();

  return 1;
}

int CheckJetsWiLepMatchingEff(TTree *mTree, const char *outName) {
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
  TFile outFile(outName, "RECREATE");
  h_Yields->Write();
  h_4j3bRawEvents->Write();
  h_4j4bRawEvents->Write();
  h_4j3bIncRawEvents->Write();
  h_Bit->Write();
  outFile.Close();

  return 1;
}
