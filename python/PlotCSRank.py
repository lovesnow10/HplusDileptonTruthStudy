#!/usr/bin/env python

import ROOT as rt
import sys
import os

def GetRank(mTree, iEntry):
    mTree.GetEntry(iEntry)
    mScoreMap = getattr(mTree, 'RecoBDTScore')
    iCorrect = getattr(mTree, 'CorrectMatchIndex')

    correctScore = mScoreMap[iCorrect]

    return sorted(mScoreMap,reverse=True).index(correctScore)+1

def main(inFilePath):
    inFile = rt.TFile.Open(inFilePath)
    if inFile.IsZombie():
        print 'Cannot open %s' % (inFilePath)
        sys.exit(-1)

    mTree = inFile.Get('outTree')

    hist = rt.TH1F('rank', 'rank', 10, 0, 10)

    entries = mTree.GetEntries()

    for ientry in xrange(0, entries):
        hist.Fill(GetRank(mTree, ientry))

    canvas = rt.TCanvas('c1', 'c1', 800, 600)

    hist.SetStats(0)
    hist.SetTitle('Correct Matched Score Ranking')
    hist.GetYaxis().SetTitle('Events')
    hist.GetXaxis().SetTitle('Rank')
    hist.SetLineWidth(2)
    hist.SetMinimum(0)
    hist.SetMaximum(hist.GetMaximum()*1.4)

    correctReco = hist[1]
    wrongReco = 0.0
    for i in xrange(2, 11):
        wrongReco += hist[i]

    eff = correctReco / wrongReco

    tt = rt.TText(0.12, 0.8, 'Reconstruction Efficiency: {}'.format(eff))
    tt.SetNDC()
    tt.SetTextSize(0.032)
    tt.AppendPad()

    hist.Draw('hist')

    raw_input('Press ENTER to quit')

if __name__ == '__main__':
    main(sys.argv[1])
