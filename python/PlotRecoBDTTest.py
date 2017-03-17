#!/usr/bin/env python

import ROOT as rt
import sys
import os


def GetBDTScoreHist(mFile, mHistName):
    return mFile.Get(mHistName)


def DrawPlots(mSigHist, mBkgHist):
    canvas = rt.TCanvas('c1', '', 800, 600)
    GhostHist = mSigHist.Clone('Ghost')
    for iBin in xrange(1, GhostHist.GetNbinsX() + 1):
        GhostHist.SetBinContent(iBin, 0.0)

    GhostHist.SetStats(0)
    GhostHist.SetTitle('')
    yMaximun = max(mSigHist.GetMaximum(), mBkgHist.GetMaximum())

    GhostHist.SetMaximum(yMaximun * 1.7)
    GhostHist.SetMinimum(0.0)

    GhostHist.Draw()

    GhostHist.GetXaxis().SetTitle('Max RecoBDT Score')
    GhostHist.GetYaxis().SetTitle('1 / Events')

    # Set hist styles
    mSigHist.SetLineWidth(2)
    mBkgHist.SetLineWidth(2)

    mSigHist.SetLineColor(2)
    mBkgHist.SetLineColor(3)

    legend = rt.TLegend(0.75, 0.75, 0.95, 0.95)

    legend.AddEntry(mSigHist, mSigHist.GetName())
    legend.AddEntry(mBkgHist, 't#bar{t}')

    mSigHist.Draw('same hist')
    mBkgHist.Draw('same hist')
    legend.Draw()

    GhostHist.SetTitle(mSigHist.GetName())

    canvas.Print(mSigHist.GetName() + '.eps')


def main(mSigFilePath, mBkgFilePath):
    rt.gROOT.SetBatch(True)
    if not os.path.isfile(mSigFilePath):
        print 'Wrong Signal File Path!'
        sys.exit(-1)
    if not os.path.isfile(mBkgFilePath):
        print 'Wrong Background File Path'
        sys.exit(-1)
    mSigFile = rt.TFile.Open(mSigFilePath)
    mBkgFile = rt.TFile.Open(mBkgFilePath)

    mMassPoint = mSigFilePath.split('.')[-2]
    mMassPoint = mMassPoint.split('/')[-1]

    mSigHist = GetBDTScoreHist(mSigFile, 'RecoBDT_Dilepton_' + mMassPoint + '_' + mMassPoint)
    mBkgHist = GetBDTScoreHist(
        mBkgFile, 'RecoBDT_Dilepton_' + mMassPoint + '_ttbarPP8')

    mSigHist.SetName(mMassPoint)
    mBkgHist.SetName('ttbar')

    mSigHist.Scale(1.0 / mSigHist.GetSumOfWeights())
    mBkgHist.Scale(1.0 / mBkgHist.GetSumOfWeights())

    DrawPlots(mSigHist, mBkgHist)

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
