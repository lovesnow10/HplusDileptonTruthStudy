#include "Tools.h"
#include <TMath.h>

int CheckJetsMatchingEff(TTree* fTree, const char* outName)
{
    std::cout<<"Initialzing..."<<std::endl;
     //Constants
    const int BIT_B0 = 10;
    const int BIT_B1 = 12;
    const int BIT_B2 = 11;
    const int BIT_B3 = 13;

    //Variable defination
    std::vector<int> *jet_truthmatch = new std::vector<int>;
    int nJets, nBTags;
    int nElectrons, nMuons;

    //Set branches
    fTree->SetBranchAddress("jet_truthmatch", &jet_truthmatch);
    fTree->SetBranchAddress("nJets", &nJets);
    fTree->SetBranchAddress("nBTags", &nBTags);
    fTree->SetBranchAddress("nElectrons", &nElectrons);
    fTree->SetBranchAddress("nMuons", &nMuons);

    //information storage
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

    //loop over TTree
    long nentries = fTree->GetEntriesFast();
    for (long i = 0; i < nentries; ++i) {
        if (i % 500 == 0) std::cout<<"Processing "<<i<<std::endl;
        fTree->GetEntry(i);
        if (nElectrons + nMuons < 2) continue;
        if (nJets < 4) continue;
        if (nJets > 3 && nBTags < 3) continue;

        bool b0_match = false;
        bool b1_match = false;
        bool b2_match = false;
        bool b3_match = false;
        
        for (int iJet = 0; iJet < nJets; ++iJet) {
            int bit_jet = jet_truthmatch->at(iJet);
            int bit = int(TMath::Log2(bit_jet));
            if (bit != 0) h_Bit->Fill(bit);
            switch (bit) {
                case BIT_B0:
                    b0_match = true;
                    break;
                case BIT_B1:
                    b1_match = true;
                    break;
                case BIT_B2:
                    b2_match = true;
                    break;
                case BIT_B3:
                    b3_match = true;
                    break;
                default:
                    break;
            }
        }
        mTotal4j3bIncRawEvents++;
        if (b0_match) h_4j3bIncRawEvents->Fill(0);
        if (b1_match) h_4j3bIncRawEvents->Fill(1);
        if (b2_match) h_4j3bIncRawEvents->Fill(2);
        if (b3_match) h_4j3bIncRawEvents->Fill(3);
        if (b1_match && b2_match && b3_match) {
            mTotalUsefulEvent4j3bInc++;
            h_4j3bIncRawEvents->Fill(4);
            if (b0_match) h_4j3bIncRawEvents->Fill(5);
        }
        if (nJets > 3 && nBTags == 3)
        {
            mTotal4j3bRawEvents++;
            if (b0_match) h_4j3bRawEvents->Fill(0);
            if (b1_match) h_4j3bRawEvents->Fill(1);
            if (b2_match) h_4j3bRawEvents->Fill(2);
            if (b3_match) h_4j3bRawEvents->Fill(3);
            if (b1_match && b2_match && b3_match) {
                mTotalUsefulEvent4j3b++;
                h_4j3bRawEvents->Fill(4);
                if (b0_match) h_4j3bRawEvents->Fill(5);
            }
        } else if (nJets > 3 && nBTags >3) {
            mTotal4j4bRawEvents++;
            if (b0_match) h_4j4bRawEvents->Fill(0);
            if (b1_match) h_4j4bRawEvents->Fill(1);
            if (b2_match) h_4j4bRawEvents->Fill(2);
            if (b3_match) h_4j4bRawEvents->Fill(3);
            if (b1_match && b2_match && b3_match) {
                mTotalUsefulEvent4j4b++;
                h_4j4bRawEvents->Fill(4);
                if (b0_match) h_4j4bRawEvents->Fill(5);
            }          
        }
    }
    std::cout<<"Loop ended, saving information to Histos..."<<std::endl;
    h_Yields->Fill(0.0, mTotal4j3bRawEvents);
    h_Yields->Fill(2.0, mTotal4j4bRawEvents);
    h_Yields->Fill(1.0, mTotalUsefulEvent4j3b);
    h_Yields->Fill(3.0, mTotalUsefulEvent4j4b);
    h_Yields->Fill(4.0, mTotal4j3bIncRawEvents);
    h_Yields->Fill(5.0, mTotalUsefulEvent4j3bInc);
    h_4j3bRawEvents->Scale(1.0 / mTotal4j3bRawEvents);
    h_4j4bRawEvents->Scale(1.0 / mTotal4j4bRawEvents);
    h_4j3bIncRawEvents->Scale(1.0 / mTotal4j3bIncRawEvents);

    //Set Label
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

    std::cout<<"Saving ROOT file..."<<std::endl;
    TFile outFile(outName, "RECREATE");
    h_Yields->Write();
    h_4j3bRawEvents->Write();
    h_4j4bRawEvents->Write();
    h_4j3bIncRawEvents->Write();
    h_Bit->Write();
    outFile.Close();

    return 1;
}    
