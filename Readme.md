# HplusDileptonTruthStudy

This package is consisted of various main fucntions, aiming at different purpose.
Common functions are placed in *src*, but each main fucntion has separately executable and their source files are placed in *utils*. You can use *CMAKE* or *Make* to compile this package.

## CheckEffLep && CheckEff
This executable is used to check the efficiency of jet-truth-matching and lepton-truth-matching if using CheckEffLEp. The default output-file name pattern is adding a suffix which is your input file name at the end, using '-t' or '--time' to change the suffix to current system time. Plots can be made using python code *PlotEff.py*.

### PlotEff.py
This is a short python script to draw plots in the *CheckEff* or *CheckEffLep* output-file. Using '-c' to draw comparasion plots among  a set of different mass points. Using '-f' to draw plots in single file.
