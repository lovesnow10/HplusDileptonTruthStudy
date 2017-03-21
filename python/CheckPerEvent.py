#!/usr/bin/env python

import ROOT as rt
import sys
import os

def CheckTree(mTree):
    index = long(raw_input('Please give entry index:'))
    mTree.GetEntry(index)

    mScoreMap = getattr(mTree, 'RecoBDTScore')
    iCorrect = getattr(mTree, 'CorrectMatchIndex')

    correctScore = mScoreMap[iCorrect]

    hsig = rt.TH1F('hsig', 'hsig', 100, -1, 1)
    hbkg = rt.TH1F('hbkg', 'hbkg', 100, -1, 1)

    hsig.Fill(correctScore)
    for score in mScoreMap:
        if not score == correctScore:
            hbkg.Fill(score)
    tmpMap = sorted(mScoreMap, reverse=True)
    pos = tmpMap.index(correctScore) + 1
    print 'Correct Score is {}'.format(pos)
    canvas = rt.TCanvas('c1','c1',800,600)
    hsig.SetLineColor(2)
    hbkg.Draw('hist')
    hsig.Draw('hist same')
    return raw_input('Y to continue, other to exit \n')

def main(inFilePath):
    inFile = rt.TFile.Open(inFilePath)
    if inFile.IsZombie():
        print 'Cannot open %s' % (inFilePath)
        sys.exit(-1)

    mTree = inFile.Get('outTree')

    print 'Initialze complete'

    while CheckTree(mTree) == 'y':
        pass

if __name__ == '__main__':
    main(sys.argv[1])
