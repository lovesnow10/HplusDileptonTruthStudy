#!/usr/bin/env python

import ROOT as rt
import sys
import os
import collections


def GetSeparation(hsig, hbkg):
    separation = 0.0
    # check hsig and hbkg have same binning
    if not hsig.GetNbinsX() == hbkg.GetNbinsX():
        print 'They do not have the same binniing'
        sys.exit(-1)
    nBins = hsig.GetNbinsX()
    dx = (hsig.GetXaxis().GetXmax() - hsig.GetXaxis().GetXmin()) / nBins
    nS = hsig.GetSumOfWeights() * dx
    nB = hbkg.GetSumOfWeights() * dx
    if nB > 0 and nS > 0:
        for iBin in xrange(1, nBins + 1):
            s = hsig.GetBinContent(iBin) / nS
            b = hbkg.GetBinContent(iBin) / nB
            if s + b > 0:
                separation += 0.5 * (s - b) * (s - b) / (s + b)
        separation *= dx
    return separation


def NormlizeHist(hist):
    if hist.GetSumw2N() == 0:
        hist.Sumw2()
    if hist.GetSumOfWeights() != 0:
        dx = (hist.GetXaxis().GetXmax() -
              hist.GetXaxis().GetXmin()) / hist.GetNbinsX()
        hist.Scale(1.0 / hist.GetSumOfWeights() / dx)
    return hist


def DrawPlots(path, region):
    Samples = ("hp200", "hp225", "hp250", "hp275", "hp300",
               "hp350", "hp400", "hp500", "ttbarPP8")
    Methods = ("hp200", "hp225", "hp250", "hp275",
               "hp300", "hp350", "hp400", "hp500")
    Colors = {"hp200": 2, "hp225": 3, "hp250": 4, "hp275": 6,
              "hp300": 7, "hp350": 8, "hp400": 9, "hp500": 42, "ttbarPP8": 1}

    mHistDict = collections.OrderedDict()
    mFileDict = collections.OrderedDict()

    for sp in Samples:
        mFilePath = path + '/' + region + '/' + sp + '.root'
        mFile = rt.TFile.Open(mFilePath)
        if mFile.IsZombie():
            print "Cannot Open %s" % (mFilePath)
            sys.exit(-1)
        mFileDict[sp] = mFile
        mTree = mFile.Get("nominal_Loose")

        for method in Methods:
            histname = sp + '_Reco' + method
            hist = rt.TH1F(histname, histname, 40, -1, 1)
            varName = "HplusDilRecoBDT_{METHOD}_Output".format(METHOD=method)

            mTree.Project(histname, varName)
            hist.SetLineWidth(1)
            hist.SetLineColor(Colors[sp])
            hist.SetTitle('')
            hist = NormlizeHist(hist)

            mHistDict[(method, sp)] = hist
            print "Got hist {METHOD} in {SAMPLE}, EVENTS {NUMBER}".format(METHOD=method, SAMPLE=sp, NUMBER=hist.GetSumOfWeights())

    for method in Methods:
        canvas = rt.TCanvas("c1", "c1", 800, 600)

        legend = rt.TLegend(0.75, 0.75, 0.95, 0.95)

        mBkgHist = mHistDict[(method, "ttbarPP8")]
        mGhostHist = mBkgHist.Clone("Ghost")
        for iBin in xrange(1, mGhostHist.GetNbinsX() + 1):
            mGhostHist.SetBinContent(iBin, 0)

        mGhostHist.SetStats(0)
        mGhostHist.SetMinimum(0)
        mGhostHist.SetMaximum(mBkgHist.GetMaximum() * 1.5)

        mGhostHist.Draw()

        mGhostHist.GetXaxis().SetTitle('Max RecoBDT Score')
        mGhostHist.GetYaxis().SetTitle('(1/N) dN^{ }/^{ }dx')

        mBkgHist.Draw('same hist')
        legend.AddEntry(mBkgHist, "t#bar{t}", "L")

        iStep = 0

        for sp in Samples:
            if sp == "ttbarPP8":
                continue
            hist = mHistDict[(method, sp)]
            hist.Draw('same hist')
            legend.AddEntry(hist, sp, "L")

            separation = GetSeparation(hist, mBkgHist)

            text = 'Separation %s, %1.4f' % (sp, separation)
            Ttext = rt.TText(0.12, 0.8 - 0.04 * iStep, text)
            Ttext.SetNDC()
            Ttext.SetTextSize(0.032)
            Ttext.AppendPad()

            iStep += 1

        mGhostHist.SetTitle(method)

        canvas.Print("{REGION}_{METHOD}.eps".format(
            REGION=region, METHOD=method))
        del canvas


def main(path, region):
    rt.gROOT.SetBatch(True)
    DrawPlots(path, region)

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
