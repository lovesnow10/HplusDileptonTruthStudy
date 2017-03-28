#include <iostream>
#include <vector>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TMVA/Factory.h"
#include "TString.h"

#include "Utilities.h"
#include "Tools.h"

int main(int argc, char const *argv[]) {
  //open files and get trees
  TFile *inFile = OpenFile(argv[1]);
  TFile *outFile = CreateNewFile(argv[2]);

  TTree *mSigTree = GetTTree("signal", inFile);
  TTree *mBkgTree = GetTTree("background", inFile);

  //definde options
  TString classifierName = "RecoBDT_Dilepton";
  TString trainingOptions;
  TString classifierOptions;

  trainingOptions = ":NormMode=NumEvents";
  classifierOptions += ":!H";
  classifierOptions += ":NTrees=500";
  classifierOptions += ":BoostType=Grad";
  classifierOptions += ":Shrinkage=0.1";
  classifierOptions += ":UseBaggedBoost";
  classifierOptions += ":GradBaggingFraction=0.5";
  classifierOptions += ":nCuts=20";
  classifierOptions += ":MaxDepth=3";

  std::vector<TString> mVariables;

  mVariables.push_back("PseTop_Mass");
  mVariables.push_back("PseTbar_Mass");
  mVariables.push_back("dR_B1_B2");
  mVariables.push_back("dR_B1_B3");
  mVariables.push_back("dR_B2_B3");
  mVariables.push_back("Pse_dR_ttbar");
  mVariables.push_back("PseTop_Mass_NoNu");
  mVariables.push_back("PseTbar_Mass_NoNu");
  mVariables.push_back("Pse_dR_ttbar_NoNu");
  mVariables.push_back("PseTop_Mass_Lep");
  mVariables.push_back("PseTbar_Mass_Lep");
  mVariables.push_back("pT_B1");
  mVariables.push_back("pT_B2");
  mVariables.push_back("pT_B3");
  mVariables.push_back("mv2c10_B1");
  mVariables.push_back("mv2c10_B2");
  mVariables.push_back("mv2c10_B3");


  TCut cutSigTrain = "UsedForTrain == 1";
  TCut cutSigTest = "UsedForTrain == 0";
  TCut cutBkgTrain = "UsedForTrain == 1";
  TCut cutBkgTest = "UsedForTrain == 0";

  //Setup TMVA Factory and training BDT
  TMVA::Factory factory("RecoBDT_Dilepton", outFile);
  factory.SetInputVariables(&mVariables);
  factory.AddTree(mSigTree, "Signal", 1.0, cutSigTrain, "train");
  factory.AddTree(mSigTree, "Signal", 1.0, cutSigTest, "test");
  factory.AddTree(mBkgTree, "Background", 1.0, cutBkgTrain, "train");
  factory.AddTree(mBkgTree, "Background", 1.0, cutBkgTest, "test");

  factory.PrepareTrainingAndTestTree("", trainingOptions);
  factory.BookMethod(TMVA::Types::kBDT, classifierName, classifierOptions);
  factory.TrainAllMethods();
  factory.TestAllMethods();
  factory.EvaluateAllMethods();

  outFile->Close();
  return 0;
}
