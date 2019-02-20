#!/usr/bin/python
import ROOT
import sys, os
from ROOT import TTree, TFile, TH1F, AddressOf
import numpy as np
import csv
from array import array
path = os.getcwd()
file_list = os.listdir(path)
tree = TTree('T','dump CAEN data')

histosize = 252
evtID = array('I',[0])
timeStamp = array('L',[0]) #unsigned long
energy = array('I',[0])
energyShort = array('I',[0])
flag = array('I',[0])
histo = array('i',histosize*[0])

tree.Branch('eventID',evtID,'eventID/s')
tree.Branch("timeStamp", timeStamp, "timeStamp/l");#ULong64_6
tree.Branch("energy", energy, "energy/s")
tree.Branch("energyShort", energyShort, "energyShort/s")
tree.Branch("flag", flag, "flag/s")
#tree.Branch("hwf","TH1F", hwaveform)

f0 = open('ex.csv')
reader = csv.reader(f0)
csvdata = list(reader)
print "total events: "+str(len(csvdata))
lineNum = 0 # eventID == line number in data 
f = TFile("dumpEvt.root","recreate")
for item in csvdata:
  if (item != csvdata[0] and lineNum<10000): # pass the title
    evtID[0] = lineNum
    lineNum = lineNum+1
    timeStamp[0] = int(item[0])
    energy[0] = int(item[1])
    energyShort[0] = int(item[2])
    flag[0] = int(item[3],16)
    waveformdata = item[4:4+histosize]
    waveformdata = map(int,waveformdata)
    #print evtID, timeStamp, energy,energyShort,flag, waveformdata
    hwaveform = TH1F("hwf","",histosize-1,0,histosize)
    ibin=0
    for idata in waveformdata:
      hwaveform.SetBinContent(ibin+1,idata)
      ibin = ibin+1
    f.cd()
    hwaveform.SetName("hwf"+str(lineNum))
    hwaveform.Write()
    #hwaveform.BufferEmpty()
    tree.Fill()

f.cd()
tree.Write()
f.Write()
f.Close()
