# HplusDileptonTruthStudy

This package is consisted of various main fucntions, aiming at different purpose.
Common functions are placed in *src*, but each main fucntion has separately executable and their source files are placed in *utils*. You can use *CMAKE* or *Make* to compile this package. *!!EXTREMELY RECOMMEND CMAKE!!*

## Main functions

### CheckEffLep && CheckEff
This executable is used to check the efficiency of jet-truth-matching and lepton-truth-matching if using CheckEffLEp. The default output-file name pattern is adding a suffix which is your input file name at the end, using '-t' or '--time' to change the suffix to current system time. Plots can be made using python code *PlotEff.py*.

Usage: It accepts 1 or 2 arguments.
* `$ CheckEff(Lep) input.root` Use $DSID as output file name. In this case, your input file name must be in this pattern: "mc.$(DSID).root"
* `$ CheckEff(Lep) --time(-t) input.root` Use current time as output file name. Your input file name doesn't matter.

### PrepareBDT
This is used to make RecoBDT input ntuples. Orginal TTHbbLeptonic Ntuple is splitted to three pieces with approximately the same number of events controlled by a uniform random number. Except two trees that used as ~signal~ and ~background~ in BDT training, it also contains a tree which is a directly copy of the ogrinal ~nominal_Loose~ tree for applying trained BDT. It is used to do the validation and tests.

Usage: It accepts 2 arguments
* `$ PrepareBDT input.root output.root` Input is the original TTHbbLeptonic Ntuple.

### TrainRecoBDT
This is the main horse used to train the RecoBDT. Variables and parameters for the BDT training is hard-coded in the file *TrainRecoBDT.C*, if you want to tune them, please modify the file and compile again.

Usage: It accepts 2 arguments
* `$ TrainRecoBDT input.root output.root` Input is the output from `PrepareBDT`. Due to TMVA's behaviour, pls run the executable in a stand-alone folder. No matter which output path you give to your "output.root", the more important "weights" folder will be always in the folder you run the executable. Please take care to avoid unexpected over-written.

### ApplyRecoBDT
This executable takes the results from training and use it on other events. It gives a Max RecoBDT score for a givin event, which is expeted to be used as an input for classification BDT. For validation purpose, it also save some infomation to an outputTree.

Usage: It accepts 4 arguments
* `$ ApplyRecoBDT input.root weigts.xml sampleName output.root` Input can be PrepareBDT-output or TTHbbLeptonic Ntuples. Weight file is in the folder `weights` which you should get in `TrainRecoBDT`. sampleName follows the name policy: (RecoBDTMasspoint)\_(AppliedSampleName) . *RecoBDTMasspoint* should indicate which mass point of weight file you used here, *AppliedSampleName* should indicate on which sample you apply the RecoBDT. It's not forced to follow this policy, but if you want to use the python script provided in `python` folder, you MUST follow it.

## Auxiliary funcions (python)

### PlotEff.py
This is a short python script to draw plots from the `CheckEff` or `CheckEffLep` output-file. Using '-c' to draw comparasion plots among  a set of different mass points. Using '-f' to draw plots in single file.

Usage: It accepts 2 arguments
* `PlotEff.py -f input.root` Draw plots from one single root file.
* `PlotEff.py -c input.txt` Draw comparasion plots from root files listed in input.txt

### PlotRecoEff.py
This is used to check the reconstruction efficiency of the RecoBDT. We consider the map of jets and b parton which gives max RecoBDT score is the right match. The efficiency is then checked by counting how many events in which the correct match givin by truth-matching has the max RecoBDT score. This is done in `ApplyRecoBDT` and this script is just reading the results and plot it.

Usage: It accepts 1 or 2 arguments
* `PlotRecoEff.py input.txt (outputname)` the input root files, which are `ApplyRecoBDT` outputs should be listed in a txt file, with following policy: *masspointlabel path_to_file*. *outputname* is an optional argument, if not givin the output name is "effplot.eps".

### PlotCSRank.py
This is used to check the ranking of the "Correct" match's RecoBDT score in one single event. By default the plot are just shown and not saved.

Usage: It accepts 1 argument
* `PlotCSRank.py input.root` Input is the output of `ApplyRecoBDT`

### CheckPerEvent.py
This is used to plot the RecoBDT score in one single event. The correct match's score is plot separately. By default the plot is not saved. And you can input "y" to continue check next event.

Usage: It accepts 1 argument
* 'CheckPerEvent.py input.root' Input is the output of 'ApplyRecoBDT'

### PlotRecoBDTTest.py
This is used to test the separation power of the variable given by RecoBDT, so called "Max RecoBDT Score" between signal sample and background sample (ttbar).

Usage: It accepts 2 arguments
* `PlotRecoBDTTest.py signal.root background.root` Both are `ApplyRecoBDT` output.

## Installation and Usage

### Installation

Requirement:
1. ROOT v6.06/08. *!!NOT COMPATIBLE WITH LATEST ROOT, SINCE TMVA STRUCTURE HAS BEEN TOTALLY CHANGED!!*
2. cmake (>= v3.3)
3. g++ 4.9

```
$ cd $YOUR_WORK_DIR
$ mkdir RecoBDT && cd RecoBDT
$ git clone git@github.com:lovesnow10/HplusDileptonTruthStudy.git
Alternative: $ git clone https://github.com/lovesnow10/HplusDileptonTruthStudy.git
$ cd HplusDileptonTruthStudy/
$ git fetch && git checkout BDT
$ mkdir build && cd build
$ cmake ..
$ make
```

Additionally I extremely suggest to add *bin* and *python* to your `$PATH` for simplicity.

Usage(take 200GeV for example):

```
$ cd RecoBDT
$ mkdir run && cd run
$ mkdir BDTInput && mkdir BDTInput/hp200
$ PrepareBDT PATH_TO_YOUR_NTUPLE BDTInput/hp200/hp200.root
$ mkdir BDTOutput && mkdir BDTOutput/hp200 && cd BDTOutput/hp200
$ TrainRecoBDT ../../BDTInput/hp200/hp200.root hp200.root
$ cd ../.. && mkdir BDTApply && mkdir BDTApply/hp200
$ ApplyRecoBDT BDTInput/hp200/hp200.root BDTOutput/hp200/weights/weights.xml hp200_hp200 hp200.root
```

This is a brief example showing the baseline of running the program. And I supply an bash script to make the folders.
