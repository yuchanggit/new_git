#! /usr/bin/env python

import os, sys, getopt, multiprocessing
import copy, math
from array import array
from ROOT import gROOT, gSystem, gStyle, gRandom, gPad
from ROOT import TFile, TChain, TTree, TCut, TH1F, TH2F, THStack, TGraph, TGaxis
from ROOT import TStyle, TCanvas, TPad, TLegend, TLatex, TText, TH1D, TFile, TMatrixDSym 
from ROOT import TMatrixD
from ROOT import TColor

from ROOT import RooFit, RooRealVar, RooDataHist, RooDataSet, RooAbsData, RooAbsReal, RooAbsPdf, RooPlot, RooBinning, RooCategory, RooSimultaneous, RooArgList, RooArgSet, RooWorkspace, RooMsgService
from ROOT import RooFormulaVar, RooGenericPdf, RooGaussian, RooExponential, RooPolynomial, RooChebychev, RooBreitWigner, RooCBShape, RooExtendPdf, RooAddPdf, RooProdPdf, RooNumConvPdf, RooFFTConvPdf

# -------------------------------------------------
# test matrix works
print "Hellooooooooooo"

m = TMatrixD(5,5)
print m[2][2]
m[2][2] = 5.4
print m[2][2]

# -------------------------------------------------
# use Gaussian to generate toy MC

x = RooRealVar("x","x",-10,10)
xframe = x.frame(RooFit.Title("Gaussian p.d.f."))

mean1 = RooRealVar("mean1","mean of gaussian",2,-10,10)
sigma1 = RooRealVar("sigma1","width of gaussian",1,0.1,10)

mean1.setConstant(True)
sigma1.setConstant(True)

gauss1 = RooGaussian("gauss1","gaussian PDF",x,mean1,sigma1)

data = gauss1.generate(RooArgSet(x),1000) 

data.plotOn(xframe)
gauss1.plotOn(xframe,RooFit.LineColor(4))

# -------------------------------------------------
# use another Gaussian to fit toy MC

mean2 = RooRealVar("mean2","mean of gaussian",2,-10,10)
sigma2 = RooRealVar("sigma2","width of gaussian",1,0.1,10)

gauss2 = RooGaussian("gauss2","gaussian PDF",x,mean2,sigma2)

fit_result = gauss2.fitTo(data, RooFit.SumW2Error(True), RooFit.Strategy(2), RooFit.Minimizer("Minuit2"), RooFit.Save(1), RooFit.PrintLevel(1))

gauss2.plotOn(xframe,RooFit.LineColor(2))

# -------------------------------------------------
# get parameter and correlation matrix

par1_fitresult = fit_result.floatParsFinal().find("mean2")
par2_fitresult = fit_result.floatParsFinal().find("sigma2")

par1_value = par1_fitresult.getVal()
par1_error = par1_fitresult.getError()

par2_value = par2_fitresult.getVal()
par2_error = par2_fitresult.getError()

print ""
print "mean2(par1):  " , par1_value, " +/- ", par1_error
print "sigma2(par2): ", par2_value, " +/- ", par2_error

corM = fit_result.correlationMatrix() 
#corM.Print()

print ""
# -------------------------------------------------
# calculate [ 2*mean2 + 3*sigma2 ] by hand

print "par1_central: ", par1_value, ", 2 * par1:", 2*par1_value
print "par1_plus =", "par1_value + par1_error= ", par1_value + par1_error, ", 2 * par1_plus:  ", 2*(par1_value + par1_error)
print "par1_minus=", "par1_value - par1_error= ", par1_value - par1_error, ", 2 * par1_minus: ", 2*(par1_value - par1_error)
print ""
print "par2_central: ", par2_value, ", 3 * par2:", 3*par2_value
print "par2_plus =", "par2_value + par2_error= ", par2_value + par2_error, ", 3 * par2_plus:  ", 3*(par2_value + par2_error)
print "par2_minus=", "par2_value - par2_error= ", par2_value - par2_error, ", 3 * par2_minus: ", 3*(par2_value - par2_error)

print ""
# central
mean2.setVal(par1_value)
sigma2.setVal(par2_value)

var_by_hand = 2*mean2.getVal() + 3*sigma2.getVal()    
var_by_hand_central = var_by_hand

# par1 plus
mean2.setVal(par1_value + par1_error )
sigma2.setVal(par2_value)

var_by_hand = 2*mean2.getVal() + 3*sigma2.getVal()
var_by_hand_par1_plus = var_by_hand

# par1 minus
mean2.setVal(par1_value - par1_error )
sigma2.setVal(par2_value)

var_by_hand = 2*mean2.getVal() + 3*sigma2.getVal()
var_by_hand_par1_minus = var_by_hand

# par2 plus
mean2.setVal(par1_value  )
sigma2.setVal(par2_value + par2_error)

var_by_hand = 2*mean2.getVal() + 3*sigma2.getVal()
var_by_hand_par2_plus = var_by_hand

# par2 minus
mean2.setVal(par1_value  )
sigma2.setVal(par2_value - par2_error )

var_by_hand = 2*mean2.getVal() + 3*sigma2.getVal()
var_by_hand_par2_minus = var_by_hand

print "var_by_hand_central:    ",  var_by_hand_central    ," = ", 2*par1_value," + ", 3*par2_value 
print "var_by_hand_par1_plus:  ",  var_by_hand_par1_plus  ," = ", 2*(par1_value + par1_error)," + ", 3*par2_value
print "var_by_hand_par1_minus: ",  var_by_hand_par1_minus ," = ", 2*(par1_value - par1_error)," + ", 3*par2_value
print "var_by_hand_par2_plus:  ",  var_by_hand_par2_plus  ," = ", 2*par1_value," + ", 3*(par2_value + par2_error)
print "var_by_hand_par2_minus: ",  var_by_hand_par2_minus ," = ", 2*par1_value," + ", 3*(par2_value - par2_error)

print ""
# shift
var_shift_par1 = max( abs( var_by_hand_par1_plus - var_by_hand_central ) , abs( var_by_hand_central - var_by_hand_par1_minus ) )
var_shift_par2 = max( abs( var_by_hand_par2_plus - var_by_hand_central ) , abs( var_by_hand_central - var_by_hand_par2_minus ) )

print "var_by_hand_par1_plus - var_by_hand_central   = ", var_by_hand_par1_plus, " - ", var_by_hand_central,    " = ", var_by_hand_par1_plus - var_by_hand_central 
print "var_by_hand_central   - var_by_hand_par1_minus= ", var_by_hand_central,   " - ", var_by_hand_par1_minus, " = ", var_by_hand_central - var_by_hand_par1_minus
print "var_by_hand_par2_plus - var_by_hand_central   = ", var_by_hand_par2_plus, " - ", var_by_hand_central,    " = ", var_by_hand_par2_plus - var_by_hand_central
print "var_by_hand_central   - var_by_hand_par2_minus= ", var_by_hand_central,   " - ", var_by_hand_par2_minus, " = ", var_by_hand_central - var_by_hand_par2_minus

print ""
print "var_shift_par1: ", var_shift_par1
print "var_shift_par2: ", var_shift_par2

rowM = TMatrixD(1,2)
rowM[0][0] = var_shift_par1 
rowM[0][1] = var_shift_par2

colM = TMatrixD(2,1)
colM[0][0] = var_shift_par1
colM[1][0] = var_shift_par2

rowM.Print()
corM.Print()
colM.Print()

resultM = rowM * ( corM * colM )
print "resultM(0,0):", resultM(0,0)

var_by_hand_error = math.sqrt( pow( resultM(0,0) , 2 ) )


print "var_by_hand_central: ", var_by_hand_central ," +/- ",var_by_hand_error

# -------------------------------------------------
# Rooformula var = [ 2*mean2 + 3*sigma2 ]

mean2.setVal(par1_value)
sigma2.setVal(par2_value)

var_formula = RooFormulaVar("var", "2*mean2 + 3*sigma2", "2 * @0  + 3 * @1", RooArgList(mean2,sigma2) )
var_formula_error = var_formula.getPropagatedError( fit_result )

print "var_formula:         ", var_formula.getVal()," +/- ", var_formula_error

print ""
# save
Save_Dir = "/afs/cern.ch/user/y/yuchang/www/jacopo_plotsAlpha/my_test_plot"

c1 = TCanvas("c1","c 1",800,600)
c1.cd()
xframe.Draw()
c1.SaveAs(Save_Dir+"/"+"test_correlation_matrix_and_error.pdf")


