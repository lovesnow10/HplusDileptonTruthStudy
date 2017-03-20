#!/usr/bin/env python

import ROOT as rt
import sys
import os
import collections

def GetEfficiency(hist):
    return hist[2]/(hist[1]+hist[2])

def OpenAllFiles(inFile):
    mFileDict = collections.OrderedDict()
    mFile = open(inFile)
    Lines = mFile.readlines()
    for line in Lines:
        masspoint = line.strip().split(' ')[0]
        filepath  = line.strip().split(' ')[1]
        tmpRFile = rt.TFile.Open(filepath)
        if not tmpRFile.IsZombie():
            mFileDict[masspoint] = tmpRFile
        else:
            print 'Cannot open %s' % (masspoint)
    return mFileDict

def PlotRecoEff(inFiles, outName='effplot.eps'):
    mFileDict = OpenAllFiles(inFiles)
    mHistDict = collections.OrderedDict()
    mEffDict = collections.OrderedDict()
    mMassPoint = mFileDict.keys()

    nMassPoints = len(mMassPoint)

    for mp, _file in mFileDict.items():
        mHistName = 'RecoBDT_Dilepton_'+mp+'_'+mp+'_eff'
        mHistDict[mp] = _file.Get(mHistName)

    for mp, _hist in mHistDict.items():
        mEffDict[mp] = GetEfficiency(_hist)

    hist_eff = rt.TH1F('hist_eff', 'ReconstructionEfficiency', nMassPoints, 0, nMassPoints)
    for iMassPoint, mp in enumerate(mMassPoint):
        hist_eff.SetBinContent(iMassPoint+1, mEffDict[mp])
        hist_eff.GetXaxis().SetBinLabel(mp)

    canvas = rt.TCanvas('c1', 'c1', 800, 600)
    hist_eff.SetStats(0)
    hist_eff.SetTitle('Reconstruction Efficiency')
    hist_eff.SetMinimum(0)
    hist_eff.SetMaximum(1.5)

    canvas.GetPad(0).SetGridy()
    hist_eff.Draw('p')

    hist_eff.GetXaxis().SetTitle('Sample')
    hist_eff.GetYaxis().SetTitle('Efficiency')
    hist_eff.GetYaxis().CenterTitle()

    hist_eff.SetMarkerColor(2)
    hist_eff.SetMarkerSize(1.1)
    hist_eff.SetMarkerStyle(20)

    canvas.Print(outName)

if __name__ == '__main__':
    arguments = sys.argv[1:]
    nArgu = len(arguments)
    if nArgu == 1:
        PlotRecoEff(arguments[0])
    elif nArgu == 2:
        PlotRecoEff(arguments[0], arguments[1])
    else:
        print 'Wrong arguments given'
        sys.exit(-1)
