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

    hist.Draw('hist')

    raw_input('Press ENTER to quit')

if __name__ == '__main__':
    main(sys.argv[1])
