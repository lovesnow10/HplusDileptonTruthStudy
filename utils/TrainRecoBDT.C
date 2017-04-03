#include <iostream>
#include <string>
#include <vector>

#include "TFile.h"
#include "TMVA/Factory.h"
#include "TString.h"
#include "TTree.h"

#include "Tools.h"
#include "Utilities.h"

int main(int argc, char const *argv[]) {
  // open files and get trees
  TFile *inFile = OpenFile(argv[1]);
  TFile *outFile = CreateNewFile(argv[2]);

  std::string _additional;
  std::string _suffix = std::string(argv[3]);
  if (argc > 4) _additional = std::string(argv[4]);
  else _additional = "NO";
  bool noBtag, useWeight;
  noBtag = (_additional == "NOBTAG&WEIGHT")?true:(_additional == "NOBTAG")?true:false;
  useWeight = (_additional == "NOBTAG&WEIGHT")?true:(_additional == "WEIGHT")?true:false;

  TTree *mSigTree = GetTTree("signal", inFile);
  TTree *mBkgTree = GetTTree("background", inFile);

  // definde options
  TString classifierName = "RecoBDThpDil";
  classifierName = classifierName + "_" + _suffix;
  TString trainingOptions;
  TString classifierOptions;

  trainingOptions = ":NormMode=NumEvents";
  classifierOptions += ":!H";
  classifierOptions += ":NTrees=1000";
  classifierOptions += ":BoostType=Grad";
  classifierOptions += ":Shrinkage=0.3";
  classifierOptions += ":UseBaggedBoost";
  classifierOptions += ":GradBaggingFraction=0.7";
  classifierOptions += ":nCuts=25";
  classifierOptions += ":MaxDepth=5";

  std::vector<TString> mVariables;

  //  mVariables.push_back("PseTop_Mass");
  //  mVariables.push_back("PseTbar_Mass");
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
  if (!noBtag) {
    mVariables.push_back("mv2c10_B1");
    mVariables.push_back("mv2c10_B2");
    mVariables.push_back("mv2c10_B3");
  }

  TCut cutSigTrain = "UsedForTrain == 1";
  TCut cutSigTest = "UsedForTrain == 0";
  TCut cutBkgTrain = "UsedForTrain == 1";
  TCut cutBkgTest = "UsedForTrain == 0";

  // Setup TMVA Factory and training BDT
  TMVA::Factory factory("RecoBDThpDil", outFile);
  factory.SetInputVariables(&mVariables);
  factory.AddTree(mSigTree, "Signal", 1.0, cutSigTrain, "train");
  factory.AddTree(mSigTree, "Signal", 1.0, cutSigTest, "test");
  factory.AddTree(mBkgTree, "Background", 1.0, cutBkgTrain, "train");
  factory.AddTree(mBkgTree, "Background", 1.0, cutBkgTest, "test");

  if (useWeight)
  {
    factory.SetSignalWeightExpression("eventWeight");
    factory.SetBackgroundWeightExpression("eventWeight");
  }

  factory.PrepareTrainingAndTestTree("", trainingOptions);
  factory.BookMethod(TMVA::Types::kBDT, classifierName, classifierOptions);
  factory.TrainAllMethods();
  factory.TestAllMethods();
  factory.EvaluateAllMethods();

  outFile->Close();
  return 0;
}
