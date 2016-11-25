#!/usr/bin/env python
import sys
import os
import ROOT as rt


def GetMassPoint(mFileName):
    '''Get mass point, must follow right naming scheme. eg: CheckEff_hplus200'''
    ss = mFileName.split('_')
    ms = ''
    for s in ss:
        if s.find('hplus') or s.find('Hplus'):
            ms = s[:-5]
    if ms == '':
        print 'Cannot find mass point name'
    return ms


def GetAllHists(mFilesDict, mHistName):
    mHistDict = {}
    for _name, _file in mFilesDict.items():
        mHist = _file.Get(mHistName)
        mName = mHist.GetName()
        mHistDict[_name] = mHist.Clone(mName + '_' + _name)
    return mHistDict


def OpenAllFiles(mDirTxt):
    mFilesDict = {}
    mFile = open(mDirTxt)
    Lines = mFile.readlines()
    for line in Lines:
        tmpRFile = rt.TFile.Open(line.strip())
        if not tmpRFile.IsZombie():
            masspoint = GetMassPoint(line)
            mFilesDict[masspoint] = tmpRFile
        else:
            print 'Cannot open file %s' % (line)
    return mFilesDict


def DrawDictPlot(Canvas, mHistDict, outName):
    Canvas.Clear()
    mHistNameList = mHistDict.keys()
    # Setup a ghost hist for style
    GhostHist = mHistDict[mHistNameList[0]].Clone("Ghost")
    for nBin in xrange(1, GhostHist.GetNbinsX() + 1):
        GhostHist.SetBinContent(nBin, 0.0)
    GhostHist.SetStats(0)
    GhostHist.SetTitle('')
    GhostHist.SetMinimum(0)
    GhostHist.SetMaximum(1.5)

    # Draw hists
    Canvas.GetPad(0).SetGridy()
    GhostHist.Draw()

    # Set axis title
    GhostHist.GetYaxis().SetTitle('Events')
    GhostHist.GetXaxis().SetTitle('Objects')

    # Setup real hists style and Draw
    legend = rt.TLegend(0.75, 0.75, 0.95, 0.95)
    legend.AddEntry(None, outName.split('_')[1], '')
    for i, hname in enumerate(mHistNameList):
        mHist = mHistDict[hname]
        mName = mHist.GetName()
        mHist.SetMarkerColor(i + 1)
        mHist.SetMarkerSize(1.1)
        mHist.SetMarkerStyle(20)
        mHist.Draw('same P0')
        legend.AddEntry(mName, hname, 'p')

    legend.Draw('same')
    Canvas.Print(outName + '.png')


def DrawOneFile(mFileName):
    '''Function to draw eff plots in one mass point,
    give one file name.'''
    mFile = rt.TFile.Open(mFileName)
    c1 = rt.TCanvas('c1', '', 800, 600)

    # read all histograms
    h_4j3b = mFile.Get('h_4j3bRawEvents')
    h_4j4b = mFile.Get('h_4j4bRawEvents')
    h_4j3binc = mFile.Get('h_4j3bIncRawEvents')
    h_Yields = mFile.Get('h_Yields')

    # Set histos' properties
    h_4j3b.SetMarkerColor(rt.kRed)
    h_4j4b.SetMarkerColor(rt.kBlue)
    h_4j3binc.SetMarkerColor(rt.kBlack)

    h_4j3b.SetMarkerStyle(20)
    h_4j4b.SetMarkerStyle(20)
    h_4j3binc.SetMarkerStyle(20)

    h_4j3b.SetMarkerSize(1.2)
    h_4j4b.SetMarkerSize(1.2)
    h_4j3binc.SetMarkerSize(1.2)

    # Draw plots
    h_4j3b.SetStats(0)
    h_4j3b.SetTitle('')
    h_4j3b.SetMinimum(0.0)
    h_4j3b.SetMaximum(1.7)
    c1.GetPad(0).SetGridy()

    h_4j3b.Draw('P0')
    h_4j4b.Draw('same P0')
    h_4j3binc.Draw('same P0')

    h_4j3b.GetXaxis().SetTitle('Objects')
    h_4j3b.GetYaxis().SetTitle('Events')

    masspoint = GetMassPoint(mFileName)
    # Draw legend
    legend = rt.TLegend(0.80, 0.80, 0.95, 0.95)
    legend.AddEntry(None, masspoint, '')
    legend.AddEntry('h_4j3bRawEvents', '4j3b', 'p')
    legend.AddEntry('h_4j4bRawEvents', '4j4b', 'p')
    legend.AddEntry('h_4j3bIncRawEvents', '4j3bInc', 'p')
    legend.Draw('same')

    # Draw text
    yields_4j3b = h_Yields.GetBinContent(1)
    yields_4j4b = h_Yields.GetBinContent(3)
    yields_4j3binc = h_Yields.GetBinContent(5)

    avail_4j3b = h_Yields.GetBinContent(2)
    avail_4j4b = h_Yields.GetBinContent(4)
    avail_4j3binc = h_Yields.GetBinContent(6)

    pave1 = rt.TPaveText(0.5, 1.1, 1.9, 1.6)
    pave1.AddText('Yields for 4j3b:')
    pave1.AddText('Total: %d' % (yields_4j3b))
    pave1.AddText('Available: %d' % (avail_4j3b))
    pave1.Draw()

    pave2 = rt.TPaveText(2.1, 1.1, 3.5, 1.6)
    pave2.AddText('Yields for 4j4b:')
    pave2.AddText('Total: %d' % (yields_4j4b))
    pave2.AddText('Available: %d' % (avail_4j4b))
    pave2.Draw()

    pave3 = rt.TPaveText(3.7, 1.1, 5.1, 1.6)
    pave3.AddText('Yields for 4j3bInc:')
    pave3.AddText('Total: %d' % (yields_4j3binc))
    pave3.AddText('Available: %d' % (avail_4j3binc))
    pave3.Draw()

    c1.Print('Eff_' + masspoint + '.png')


def DrawAllFile(mFileTxt):
    '''Function to draw compare eff plots between different mass points,
    give a txt file which contains all the files.'''
    mFilesDict = OpenAllFiles(mFileTxt)
    h_4j3b_Dict = GetAllHists(mFilesDict, 'h_4j3bRawEvents')
    h_4j4b_Dict = GetAllHists(mFilesDict, 'h_4j4bRawEvents')
    h_4j3binc_Dict = GetAllHists(mFilesDict, 'h_4j3bIncRawEvents')
    c1 = rt.TCanvas('c1', '', 800, 600)
    DrawDictPlot(c1, h_4j3b_Dict, 'Eff_4j3b_compare')
    DrawDictPlot(c1, h_4j4b_Dict, 'Eff_4j4b_compare')
    DrawDictPlot(c1, h_4j3binc_Dict, 'Eff_4j3bInc_compare')


def main(argv):
    rt.gROOT.SetBatch(True)
    if argv[1] == '-f':
        DrawOneFile(argv[2])
    elif argv[1] == '-c':
        DrawAllFile(argv[2])

if __name__ == '__main__':
    main(sys.argv)
