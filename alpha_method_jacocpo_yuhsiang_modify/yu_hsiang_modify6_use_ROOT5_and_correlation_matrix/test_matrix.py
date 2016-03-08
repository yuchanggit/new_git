#! /usr/bin/env python

import os, sys, getopt, multiprocessing
import copy, math
from array import array
from ROOT import gROOT, gSystem, gStyle, gRandom, gPad
from ROOT import TFile, TChain, TTree, TCut, TH1F, TH2F, THStack, TGraph, TGaxis
from ROOT import TStyle, TCanvas, TPad, TLegend, TLatex, TText, TH1D, TFile, TMatrixDSym

from ROOT import TMatrixD, Math
from array import array


m = TMatrixD(5,5)
print m[2][2]
m[2][2] = 5.4
print m[2][2]


m2 = TMatrixD(2,2)
m2[0][0] = 1
m2[0][1] = 2
m2[1][0] = 3
m2[1][1] = 4
m2.Print()


rowM = TMatrixD(1,2)
rowM[0][0] = 5
rowM[0][1] = -2
rowM.Print()

colM = TMatrixD(2,1)
colM[0][0] = 1
colM[1][0] = -1
colM.Print()

result = rowM*(m2*colM)
print result[0][0] 


#elem = 5*5*[0.]
#elem = 5*5*[0.]
#elem[ 2*5 + 2 ] = 5.4
#m = TMatrixD( 5, 5, array( 'd', elem ) )
#print m(2,2)
#m.Print()

a1=3
a2=10
#c= math.fmax(a1,a2)
c= max(a1,a2)
print c

w= -55.6
w1= abs(w)
print w1

x = 2
y = 3
z = pow(x,y)
print z

bb = 25
bbb = math.sqrt(bb)
print bbb



