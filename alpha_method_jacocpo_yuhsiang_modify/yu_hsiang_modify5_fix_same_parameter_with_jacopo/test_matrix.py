#! /usr/bin/env python

import os, sys, getopt, multiprocessing
import copy, math
from array import array
from ROOT import gROOT, gSystem, gStyle, gRandom, gPad
from ROOT import TFile, TChain, TTree, TCut, TH1F, TH2F, THStack, TGraph, TGaxis
from ROOT import TStyle, TCanvas, TPad, TLegend, TLatex, TText, TH1D, TFile, TMatrixDSym

from ROOT import TMatrixD
from array import array


m = TMatrixD(5,5)
print m[2][2]
m[2][2] = 5.4
print m[2][2]

#elem = 5*5*[0.]
#elem = 5*5*[0.]
#elem[ 2*5 + 2 ] = 5.4
#m = TMatrixD( 5, 5, array( 'd', elem ) )
#print m(2,2)
#m.Print()





