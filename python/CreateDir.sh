#!/bin/bash

CurrentDir=$(pwd)
DirName=$1
InputName="BDTInput"
OutputName="BDTOutput"
ApplyName="BDTApply"
MassPoint="hp200 hp225 hp250 hp275 hp300 hp350 hp400 hp500 ttbarPP6 ttbarPP8"

echo "Creating Folders in ${CurrentDir}"
echo "Your Dir Name is ${DirName}"

mkdir ${DirName}
cd ${DirName}
mkdir ${InputName} ${OutputName} ${ApplyName}
cd ${OutputName}
mkdir ${MassPoint}
cd ..
cd ${ApplyName}
mkdir ${MassPoint}
