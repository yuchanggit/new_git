#! /usr/bin/env python

import os, sys, getopt, multiprocessing
import copy, math
from array import array
from ROOT import gROOT, gSystem, gStyle, gRandom, gPad
from ROOT import TFile, TChain, TTree, TCut, TH1F, TH2F, THStack, TGraph, TGaxis
from ROOT import TStyle, TCanvas, TPad, TLegend, TLatex, TText, TH1D, TFile, TMatrixDSym 
from ROOT import TMatrixD
from ROOT import TColor 


# Import PDF library and PDF diagonalizer
gSystem.Load("PDFs/HWWLVJRooPdfs_cxx.so")
gSystem.Load("PDFs/PdfDiagonalizer_cc.so")
#gSystem.Load("../jacopo_codes/PDFs/HWWLVJRooPdfs_cxx.so")
#gSystem.Load("../jacopo_codes/PDFs/PdfDiagonalizer_cc.so")

from ROOT import RooFit, RooRealVar, RooDataHist, RooDataSet, RooAbsData, RooAbsReal, RooAbsPdf, RooPlot, RooBinning, RooCategory, RooSimultaneous, RooArgList, RooArgSet, RooWorkspace, RooMsgService
from ROOT import RooFormulaVar, RooGenericPdf, RooGaussian, RooExponential, RooPolynomial, RooChebychev, RooBreitWigner, RooCBShape, RooExtendPdf, RooAddPdf, RooProdPdf, RooNumConvPdf, RooFFTConvPdf
from ROOT import PdfDiagonalizer, RooAlphaExp, RooErfExpPdf, Roo2ExpPdf, RooAlpha42ExpPdf, RooExpNPdf, RooAlpha4ExpNPdf, RooExpTailPdf, RooAlpha4ExpTailPdf, RooAlpha

sys.path.append("../jacopo_codes/tools")
from tools.utils import *

import optparse
usage = "usage: %prog [options]"
parser = optparse.OptionParser(usage)
parser.add_option("-a", "--all", action="store_true", default=False, dest="all")
parser.add_option("-b", "--bash", action="store_true", default=False, dest="bash")
parser.add_option("-c", "--channel", action="store", type="string", dest="channel", default="")
parser.add_option("-d", "--different", action="store_true", default=False, dest="different")
parser.add_option("-e", "--extrapolate", action="store_true", default=False, dest="extrapolate")
parser.add_option("-v", "--verbose", action="store_true", default=False, dest="verbose")
(options, args) = parser.parse_args()
if options.bash: gROOT.SetBatch(True)


#####  test TMatrixD #####

print "Hellooooooooooo"

#m = TMatrixD(5,5)
#print m(2,2)
#m(2,2) = 5.4
#print m(2,2)

m = TMatrixD(5,5)
print m[2][2]
m[2][2] = 5.4
print m[2][2]



########## SETTINGS ##########

#gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)
gStyle.SetPadTopMargin(0.06)
gStyle.SetPadRightMargin(0.05)

NTUPLEDIR   = "../jacopo_codes/ntuples/"
PLOTDIR     = "plotsAlpha/"
RATIO       = 4
SHOWERR     = True
ALTERNATIVE = options.different
EXTRAPOLATE = options.extrapolate
BLIND       = True if not EXTRAPOLATE else False
LUMISILVER  = 2460.
LUMIGOLDEN  = 2110.
VERBOSE     = options.verbose

channelList = ['XZhnnb', 'XZhnnbb', 'XWhenb', 'XWhenbb', 'XWhmnb', 'XWhmnbb', 'XZheeb', 'XZhmmb', 'XZheebb', 'XZhmmbb']

LOWMIN = 30.
LOWMAX = 65.

SIGMIN = 105. if not EXTRAPOLATE else 135.
SIGMAX = 135. if not EXTRAPOLATE else 300.

HIGMIN = 135. if not EXTRAPOLATE else 300.
HIGMAX = 300.

HBINMIN= 30.
HBINMAX= 300.
HBINS  = 54

XBINMIN= 750.
XBINMAX= 5000.
XBINS  = 17




########## ######## ##########


def alpha(channel):

    nElec = channel.count('e')
    nMuon = channel.count('m')
    nLept = nElec + nMuon
    nBtag = channel.count('b')
    
    # Channel-dependent settings
    # Background function. Semi-working options are: EXP, EXP2, EXPN, EXPTAIL
    if nLept == 0:
        treeName = 'SR'
        signName = 'XZh'
        colorVjet = sample['DYJetsToNuNu']['linecolor']
        triName = "HLT_PFMET"
        leptCut = "0==0"
        topVeto = selection["TopVetocut"]
        massVar = "X_cmass"
        binFact = 1
        #fitFunc = "EXP"
        #fitFunc = "EXP2"
        #fitFunc = "EXPN"
        #fitFunc = "EXPTAIL"
        fitFunc = "EXPN" if nBtag < 2 else "EXP"
        fitAltFunc = "EXPTAIL" if nBtag < 2 else "EXPTAIL"
        fitFuncVjet = "ERFEXP" if nBtag < 2 else "ERFEXP"
        fitFuncVV   = "EXPGAUS"
        fitFuncTop  = "GAUS2"
    elif nLept == 1:
        treeName = 'WCR'
        signName = 'XWh'
        #colorVjet = sample['WJetsToLNu']['linecolor']
        triName = "HLT_Ele" if nElec > 0 else "HLT_Mu"
        leptCut = "isWtoEN" if nElec > 0 else "isWtoMN"
        topVeto = selection["TopVetocut"]
        massVar = "X_mass"
        binFact = 2
        if nElec > 0:
            fitFunc = "EXP" if nBtag < 2 else "EXP"
            fitAltFunc  = "EXPTAIL" if nBtag < 2 else "EXPTAIL"
        else:
            fitFunc = "EXPTAIL" if nBtag < 2 else "EXP"
            fitAltFunc  = "EXPN" if nBtag < 2 else "EXPTAIL"
        fitFuncVjet = "ERFEXP" if nBtag < 2 else "ERFEXP"
        fitFuncVV   = "EXPGAUS"
        fitFuncTop  = "GAUS3" if nBtag < 2 else "GAUS2"
    else:
        treeName = 'XZh'
        signName = 'XZh'
        colorVjet = sample['DYJetsToLL']['linecolor']
        triName = "HLT_Ele" if nElec > 0 else "HLT_Mu"
        leptCut = "isZtoEE" if nElec > 0 else "isZtoMM"
        topVeto = "0==0"
        massVar = "X_mass"
        binFact = 5
        if nElec > 0:
            fitFunc = "EXP" if nBtag < 2 else "EXP"
            fitAltFunc = "POW" if nBtag < 2 else "POW"
        else:
            fitFunc = "EXP" if nBtag < 2 else "EXP"
            fitAltFunc = "POW" if nBtag < 2 else "POW"
        fitFuncVjet = "ERFEXP" if nBtag < 2 else "EXP"
        fitFuncVV   = "EXPGAUS2"
        fitFuncTop  = "GAUS"
    
    btagCut = selection["2Btag"] if nBtag == 2 else selection["1Btag"]
    
    print "--- Channel", channel, "---"
    print "  number of electrons:", nElec, " muons:", nMuon, " b-tags:", nBtag
    print "  read tree:", treeName, "and trigger:", triName
    if ALTERNATIVE: print "  using ALTERNATIVE fit functions"
    print "-"*11*2
    
    # Silent RooFit
    RooMsgService.instance().setGlobalKillBelow(RooFit.FATAL)
    
    #*******************************************************#
    #                                                       #
    #              Variables and selections                 #
    #                                                       #
    #*******************************************************#
    
    # Define all the variables from the trees that will be used in the cuts and fits
    # this steps actually perform a "projection" of the entire tree on the variables in thei ranges, so be careful once setting the limits
    X_mass = RooRealVar(  massVar, "m_{X}" if nLept > 0 else "m_{T}^{X}", XBINMIN, XBINMAX, "GeV")
    J_mass = RooRealVar( "fatjet1_prunedMassCorr",       "corrected pruned mass", HBINMIN, HBINMAX, "GeV")
    CSV1 = RooRealVar(   "fatjet1_CSVR1",                           "",        -1.e99,   1.e4     )
    CSV2 = RooRealVar(   "fatjet1_CSVR2",                           "",        -1.e99,   1.e4     )
    nBtag = RooRealVar(  "fatjet1_nBtag",                           "",            0.,   4        )
    CSVTop = RooRealVar( "bjet1_CSVR",                              "",        -1.e99,   1.e4     )
    isZtoEE = RooRealVar("isZtoEE",                                 "",            0.,   2        )
    isZtoMM = RooRealVar("isZtoMM",                                 "",            0.,   2        )
    isWtoEN = RooRealVar("isWtoEN",                                 "",            0.,   2        )
    isWtoMN = RooRealVar("isWtoMN",                                 "",            0.,   2        )
    weight = RooRealVar( "eventWeightLumi",                         "",         -1.e9,   1.       )
    
    # Define the RooArgSet which will include all the variables defined before
    # there is a maximum of 9 variables in the declaration, so the others need to be added with 'add'
    variables = RooArgSet(X_mass, J_mass, CSV1, CSV2, nBtag, CSVTop)
    variables.add(RooArgSet(isZtoEE, isZtoMM, isWtoEN, isWtoMN, weight))
    
    # Define the ranges in fatJetMass - these will be used to define SB and SR
    J_mass.setRange("LSBrange", LOWMIN, LOWMAX)
    J_mass.setRange("HSBrange", HIGMIN, HIGMAX)
    J_mass.setRange("VRrange",  LOWMAX, SIGMIN)
    J_mass.setRange("SRrange",  SIGMIN, SIGMAX)
    J_mass.setBins(54)
    
    # Define the selection for the various categories (base + SR / LSBcut / HSBcut )
    baseCut = leptCut + " && " + btagCut + "&&" + topVeto
    massCut = massVar + ">%d" % XBINMIN
    baseCut += " && " + massCut
    
    # Cuts
    SRcut  = baseCut + " && %s>%d && %s<%d" % (J_mass.GetName(), SIGMIN, J_mass.GetName(), SIGMAX)
    LSBcut = baseCut + " && %s>%d && %s<%d" % (J_mass.GetName(), LOWMIN, J_mass.GetName(), LOWMAX)
    HSBcut = baseCut + " && %s>%d && %s<%d" % (J_mass.GetName(), HIGMIN, J_mass.GetName(), HIGMAX)
    SBcut  = baseCut + " && ((%s>%d && %s<%d) || (%s>%d && %s<%d))" % (J_mass.GetName(), LOWMIN, J_mass.GetName(), LOWMAX, J_mass.GetName(), HIGMIN, J_mass.GetName(), HIGMAX)
    VRcut  = baseCut + " && %s>%d && %s<%d" % (J_mass.GetName(), LOWMAX, J_mass.GetName(), SIGMIN)
    
    # Binning
    binsJmass = RooBinning(HBINMIN, HBINMAX)
    binsJmass.addUniform(HBINS, HBINMIN, HBINMAX)
    binsXmass = RooBinning(XBINMIN, XBINMAX)
    binsXmass.addUniform(binFact*XBINS, XBINMIN, XBINMAX)
    
    #*******************************************************#
    #                                                       #
    #                      Input files                      #
    #                                                       #
    #*******************************************************#
    
    # Import the files using TChains (separately for the bkg "classes" that we want to describe: here DY and VV+ST+TT)
    treeData = TChain(treeName)
    treeMC   = TChain(treeName)
    treeVjet = TChain(treeName)
    treeVV   = TChain(treeName)
    treeTop  = TChain(treeName)
#    treeSign = {}
#    nevtSign = {}

    
    # Read data
    print "read data start"
    pd = getPrimaryDataset(triName)
    if len(pd)==0: raw_input("Warning: Primary Dataset not recognized, continue?")
    for i, s in enumerate(pd): treeData.Add(NTUPLEDIR + s + ".root")

    
    # Read V+jets backgrounds
    print "read V+jet start"
    for i, s in enumerate(["WJetsToLNu_HT", "DYJetsToNuNu_HT", "DYJetsToLL_HT"]):
        for j, ss in enumerate(sample[s]['files']): treeVjet.Add(NTUPLEDIR + ss + ".root")
    
    # Read VV backgrounds
    print "read VV start"
    for i, s in enumerate(["VV"]):
        for j, ss in enumerate(sample[s]['files']): treeVV.Add(NTUPLEDIR + ss + ".root")
    
    # Read Top backgrounds
    print "read Top start"
    for i, s in enumerate(["ST", "TTbar"]):
        for j, ss in enumerate(sample[s]['files']): treeTop.Add(NTUPLEDIR + ss + ".root")
        
    # Sum all background MC
    treeMC.Add(treeVjet)
    treeMC.Add(treeVV)
    treeMC.Add(treeTop)


#    print "prepare SB dataset"
    
    # create a dataset to host data in sideband (using this dataset we are automatically blind in the SR!)
#    setDataSB = RooDataSet("setDataSB", "setDataSB", variables, RooFit.Cut(SBcut), RooFit.WeightVar(weight), RooFit.Import(treeData))
#    setDataLSB = RooDataSet("setDataLSB", "setDataLSB", variables, RooFit.Import(setDataSB), RooFit.Cut(LSBcut), RooFit.WeightVar(weight))
#    setDataHSB = RooDataSet("setDataHSB", "setDataHSB", variables, RooFit.Import(setDataSB), RooFit.Cut(HSBcut), RooFit.WeightVar(weight))

#    print "prepare SR dataset"
    
    # Observed data (WARNING, BLIND!)
#    setDataSR = RooDataSet("setDataSR", "setDataSR", variables, RooFit.Cut(SRcut), RooFit.WeightVar(weight), RooFit.Import(treeData))
#    setDataVR = RooDataSet("setDataVR", "setDataVR", variables, RooFit.Cut(VRcut), RooFit.WeightVar(weight), RooFit.Import(treeData)) # Observed in the VV mass, just for plotting purposes
    

    print "prepare MC dataset"

    # same for the bkg datasets from MC, where we just apply the base selections (not blind)
    setVjet = RooDataSet("setVjet", "setVjet", variables, RooFit.Cut(baseCut), RooFit.WeightVar(weight), RooFit.Import(treeVjet))
    setVjetSB = RooDataSet("setVjetSB", "setVjetSB", variables, RooFit.Import(setVjet), RooFit.Cut(SBcut), RooFit.WeightVar(weight))
    setVjetSR = RooDataSet("setVjetSR", "setVjetSR", variables, RooFit.Import(setVjet), RooFit.Cut(SRcut), RooFit.WeightVar(weight))

    print "finish Vjet dataset"


#    setVV = RooDataSet("setVV", "setVV", variables, RooFit.Cut(baseCut), RooFit.WeightVar(weight), RooFit.Import(treeVV))
#    setVVSB = RooDataSet("setVVSB", "setVVSB", variables, RooFit.Import(setVV), RooFit.Cut(SBcut), RooFit.WeightVar(weight))
#    setVVSR = RooDataSet("setVVSR", "setVVSR", variables, RooFit.Import(setVV), RooFit.Cut(SRcut), RooFit.WeightVar(weight))

#    print "finish VV dataset"

#    setTop = RooDataSet("setTop", "setTop", variables, RooFit.Cut(baseCut), RooFit.WeightVar(weight), RooFit.Import(treeTop))
#    setTopSB = RooDataSet("setTopSB", "setTopSB", variables, RooFit.Import(setTop), RooFit.Cut(SBcut), RooFit.WeightVar(weight))
#    setTopSR = RooDataSet("setTopSR", "setTopSR", variables, RooFit.Import(setTop), RooFit.Cut(SRcut), RooFit.WeightVar(weight))

#    print "finish Top dataset"

    
#    print "  Data events SB: %.2f" % setDataSB.sumEntries()
    print "  V+jets entries: %.2f" % setVjet.sumEntries()
#    print "  VV, VH entries: %.2f" % setVV.sumEntries()
#    print "  Top,ST entries: %.2f" % setTop.sumEntries()
    
    
    # the relative normalization of the varius bkg is taken from MC by counting all the events in the full fatJetMass range
    #coef = RooRealVar("coef", "coef", setVV.sumEntries()/setVjet.sumEntries(),0.,1.)
#    coef_VV_Vjet = RooRealVar("coef2_1", "coef2_1", setVV.sumEntries()/setVjet.sumEntries(), 0., 1.)
#    coef_Top_VVVjet = RooRealVar("coef3_21", "coef3_21", setTop.sumEntries()/(setVjet.sumEntries()+setVV.sumEntries()),0.,1.);
#    coef_VV_Vjet.setConstant(True)
#    coef_Top_VVVjet.setConstant(True)
    
    # Define entries
    entryVjet = RooRealVar("entryVjets",  "V+jets normalization", setVjet.sumEntries(), 0., 1.e6)
#    entryVV = RooRealVar("entryVV",  "VV normalization", setVV.sumEntries(), 0., 1.e6)
#    entryTop = RooRealVar("entryTop",  "Top normalization", setTop.sumEntries(), 0., 1.e6)
    
#    entrySB = RooRealVar("entrySB",  "Data SB normalization", setDataSB.sumEntries(SBcut), 0., 1.e6)
#    entrySB.setError(math.sqrt(entrySB.getVal()))
    
#    entryLSB = RooRealVar("entryLSB",  "Data LSB normalization", setDataSB.sumEntries(LSBcut), 0., 1.e6)
#    entryLSB.setError(math.sqrt(entryLSB.getVal()))

#    entryHSB = RooRealVar("entryHSB",  "Data HSB normalization", setDataSB.sumEntries(HSBcut), 0., 1.e6)
#    entryHSB.setError(math.sqrt(entryHSB.getVal()))
    
    #*******************************************************#
    #                                                       #
    #                    NORMALIZATION                      #
    #                                                       #
    #*******************************************************#
    
    # set reasonable ranges for J_mass and X_mass
    # these are used in the fit in order to avoid ROOFIT to look in regions very far away from where we are fitting 
    J_mass.setRange("h_reasonable_range", LOWMIN, HIGMAX)
    X_mass.setRange("X_reasonable_range", XBINMIN, XBINMAX)
    
    # Set RooArgSets once for all, see https://root.cern.ch/phpBB3/viewtopic.php?t=11758
    jetMassArg = RooArgSet(J_mass)

    ##############################
    #                            #
    #    Yu-hsiang test region   #
    #                            #
    ##############################

    # test it in the channel "XZhnnb"
    print "the channel is", channel 
    if channel == "XZhnnb":

	# -------------------------------------------------------------------    
    	# draw the setVjet
    	Jmass_frame = J_mass.frame(RooFit.Title("test frame"))
    	setVjet.plotOn(Jmass_frame)    

        # ------------------------------------------------------------------- 
    	# use a PDF to fit the dataset
    	print "fitFuncVjet is", fitFuncVjet 

        constVjet_value_initial = -0.020
	offsetVjet_value_initial = 30.
	widthVjet_value_initial = 100.

    	constVjet_test   = RooRealVar("constVjet_test",   "slope of the exp", constVjet_value_initial , -1.,   0.)
    	offsetVjet_test  = RooRealVar("offsetVjet_test",  "offset of the erf", offsetVjet_value_initial,   -50., 200.)
    	widthVjet_test   = RooRealVar("widthVjet_test",   "width of the erf",  widthVjet_value_initial,     1., 200.)

	offsetVjet_test.setConstant(True)

        modelVjet_test = RooErfExpPdf("modelVjet_test", "error function for V+jets mass", J_mass, constVjet_test, offsetVjet_test, widthVjet_test)

#	constVjet_test.Print()
#	offsetVjet_test.Print()
#	widthVjet_test.Print()

#    	constVjet_test.setConstant(True)
#    	offsetVjet_test.setConstant(True)
#    	widthVjet_test.setConstant(True)

#	minimizer_choose = "Minuit2"
        minimizer_choose = "Minuit"

        frVjet_test = modelVjet_test.fitTo(setVjet, RooFit.SumW2Error(True), RooFit.Range("h_reasonable_range"), RooFit.Strategy(2), RooFit.Minimizer(minimizer_choose), RooFit.Save(1), RooFit.PrintLevel(1 if VERBOSE else -1))


        par1_fitresult = frVjet_test.floatParsFinal().find("constVjet_test")
        par2_fitresult = frVjet_test.floatParsFinal().find("widthVjet_test")
	print ""
	print "fit from MC" 
        print "par1 value:",par1_fitresult.getVal()
        print "par1 error:",par1_fitresult.getError()
        print "par2 value:",par2_fitresult.getVal()
        print "par2 error:",par2_fitresult.getError()
	print ""



	constVjet_value_fit_MC = constVjet_test.getVal()
	offsetVjet_value_fit_MC = offsetVjet_test.getVal()
	widthVjet_value_fit_MC = widthVjet_test.getVal()

	print "constVjet_value_fit_MC:", constVjet_value_fit_MC, "offsetVjet_value_fit_MC:",offsetVjet_value_fit_MC,"widthVjet_value_fit_MC:",widthVjet_value_fit_MC


        modelVjet_test.plotOn(Jmass_frame,RooFit.LineColor(4))

        # ------------------------------------------------------------------- 
	# use the shape of fit to generate the psudo-data

        nPseudo_data = setVjet.sumEntries()
        nPseudo_data_fluc = gRandom.Poisson( nPseudo_data )

        pseudo_data_fluc = modelVjet_test.generate(RooArgSet(J_mass),nPseudo_data_fluc )

	Jmass_frame2 = J_mass.frame(RooFit.Title("test frame2"))
	pseudo_data_fluc.plotOn(Jmass_frame2)
        modelVjet_test.plotOn(Jmass_frame2,RooFit.LineColor(4))

        # -------------------------------------------------------------------
	# make another dataset that remove the signal region 
        pseudo_data_SB = RooDataSet("pseudo_data_SB", "pseudo_data_SB", RooArgSet(J_mass), RooFit.Import(pseudo_data_fluc), RooFit.Cut("fatjet1_prunedMassCorr<65 || fatjet1_prunedMassCorr>135") )
	pseudo_data_SB.plotOn(Jmass_frame2,RooFit.LineColor(2))

	# SR data set
        pseudo_data_SR_fluc = RooDataSet("pseudo_data_SR_fluc", "pseudo_data_SR_fluc", RooArgSet(J_mass), RooFit.Import(pseudo_data_fluc), RooFit.Cut("fatjet1_prunedMassCorr>105 && fatjet1_prunedMassCorr<135") )
        nGen_SR_fluc = pseudo_data_SR_fluc.sumEntries()

        # -------------------------------------------------------------------
        # use another PDF to fit the pseudo-data in SB only

        constVjet_test2   = RooRealVar("constVjet_test2",   "slope of the exp", constVjet_value_fit_MC , -1.,   0.)
        offsetVjet_test2  = RooRealVar("offsetVjet_test2",  "offset of the erf", offsetVjet_value_fit_MC ,   -50., 200.)
        widthVjet_test2   = RooRealVar("widthVjet_test2",   "width of the erf", widthVjet_value_fit_MC ,     1., 200.)

	offsetVjet_test2.setConstant(True)

        modelVjet_test2 = RooErfExpPdf("modelVjet_test2", "error function for V+jets mass", J_mass, constVjet_test2, offsetVjet_test2, widthVjet_test2)

        frVjet_test2 = modelVjet_test2.fitTo(pseudo_data_SB, RooFit.SumW2Error(True), RooFit.Range("LSBrange,HSBrange"), RooFit.Strategy(2), RooFit.Minimizer(minimizer_choose), RooFit.Save(1), RooFit.PrintLevel(1 if VERBOSE else -1))	
#        frVjet_test2 = modelVjet_test2.fitTo(pseudo_data_SB, RooFit.SumW2Error(True), RooFit.Range("h_reasonable_range"), RooFit.Strategy(2), RooFit.Minimizer(minimizer_choose), RooFit.Save(1), RooFit.PrintLevel(1 if VERBOSE else -1))

	# fit result
	print "frVjet_test2.Print():", frVjet_test2.Print("v")

        par1_fitresult = frVjet_test2.floatParsFinal().find("constVjet_test2")
        par2_fitresult = frVjet_test2.floatParsFinal().find("widthVjet_test2")

        par1_value = par1_fitresult.getVal()
        par1_error = par1_fitresult.getError()

        par2_value = par2_fitresult.getVal()
        par2_error = par2_fitresult.getError()


	# plot
        Jmass_frame3 = J_mass.frame(RooFit.Title("test frame3, fit the pseudo-data in SB only"))
        pseudo_data_SB.plotOn(Jmass_frame3)
        modelVjet_test2.plotOn(Jmass_frame3,RooFit.LineColor(4),RooFit.Range("h_reasonable_range"))


        # ------------------------------------------------------------------- 
        # calculate the Gen_value, the Fit_value and the Bias= ( Fit_value - Gen_value)/Gen_value 


        constVjet_test2.setVal(par1_value)
        widthVjet_test2.setVal(par2_value)


        iFit_SR = modelVjet_test2.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
        iFit_All = modelVjet_test2.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("h_reasonable_range"))
        nFit_SR = nPseudo_data_fluc * (  iFit_SR.getVal() / iFit_All.getVal() )
       
	iFit_SR_central = iFit_SR.getVal()

#	print ""
#	print "check1"
# 	print "nPseudo_data_fluc:", nPseudo_data_fluc ,"iFit_SR:", iFit_SR.getVal(), "iFit_All: ",iFit_All.getVal() 
#	print ""

	Bias_value = ( nFit_SR  - nGen_SR_fluc ) / nGen_SR_fluc

	print "nGen_SR_fluc:", nGen_SR_fluc
	print "nFit_SR:",nFit_SR
        print "Bias_value of SR:", Bias_value


        # ------------------------------------------------------------------- 
        # calculate the pull

	# use def function
        par1_name = "constVjet_test2"
        par2_name = "widthVjet_test2"

        fit_central_value, fit_error_by_function = Get_Fit_Sigma( J_mass , nPseudo_data_fluc, modelVjet_test2 , frVjet_test2, constVjet_test2, par1_name , widthVjet_test2, par2_name  )
	print "iFit_SR_by_function:", fit_central_value," +/-", fit_error_by_function

	
	# use RooFormulaVar
	constVjet_test2.setVal(par1_value)
        widthVjet_test2.setVal(par2_value)

        iFit_SR_formula = RooFormulaVar("iFit_SR_formula", "iFit SR formula", "@0", RooArgList(iFit_SR) )
        iFit_SR_formula_error = iFit_SR_formula.getPropagatedError( frVjet_test2 )

	print ""
	print "test iFit_SR by RooFormulaVar"
        print "iFit_SR_formula:", iFit_SR_formula.getVal() , " +/-", iFit_SR_formula_error 
	print ""


        # ------------------------------------------------------------------- # 
        # ------------------------------------------------------------------- #
        #        repeat thousand times to see bias distribution               #
        # ------------------------------------------------------------------- #
        # ------------------------------------------------------------------- #


        h_Bias_case1 = TH1D("h_Bias_case1","h_Bias case1",40,-1,1);
        h_Pull_case1 = TH1D("h_Pull_case1","h_Pull case1",25,-5,5);

        h_Bias_case2 = TH1D("h_Bias_case2","h_Bias case2",40,-1,1);
        h_Pull_case2 = TH1D("h_Pull_case2","h_Pull case2",25,-5,5);


        Jmass_frame4 = J_mass.frame(RooFit.Title("frame for case 1"))
        Jmass_frame5 = J_mass.frame(RooFit.Title("frame for case 2"))

	# fix modelVjet_test's parameters to generate pseudo-data
        constVjet_test.setConstant(True) 
        offsetVjet_test.setConstant(True)
        widthVjet_test.setConstant(True)

	# parameters in case1 used later
        constVjet_case1   = RooRealVar("constVjet_case1",   "slope of the exp", constVjet_value_fit_MC , -1.,   0.)
        offsetVjet_case1  = RooRealVar("offsetVjet_case1",  "offset of the erf", offsetVjet_value_fit_MC ,   -50., 200.)
        widthVjet_case1   = RooRealVar("widthVjet_case1",   "width of the erf", widthVjet_value_fit_MC ,     1., 200.)

        # parameters in case2 used later
	constVjet_value_case2 =-0.020 	
	a0Vjet_value_case2 = -0.1 
	a1Vjet_value_case2 =  0.6
	a2Vjet_value_case2 = -0.1

        constVjet_case2   = RooRealVar("constVjet_test4",   "slope of the exp", constVjet_value_case2 , -1.,   0.)
    	a0Vjet_case2 = RooRealVar("a0Vjet_test4", "width of the erf", a0Vjet_value_case2, -5, 0)
    	a1Vjet_case2 = RooRealVar("a1Vjet_test4", "width of the erf", a1Vjet_value_case2,  0, 5)
    	a2Vjet_case2 = RooRealVar("a2Vjet_test4", "width of the erf", a2Vjet_value_case2, -1, 1)

        times_max = 1000
	times_to_plot =500

	# starts loop
	print "starting loop"
	for times in range(0,times_max):  

    		# inside loop
#		print "times:", times
		if times % 100 == 0 :
			print "Processing times:", times+1 ,"of", times_max 


		# generate pseudo-data
		nPseudo_data_fluc = gRandom.Poisson( nPseudo_data )

                pseudo_data_fluc = modelVjet_test.generate(RooArgSet(J_mass),nPseudo_data )
#                pseudo_data_fluc = modelVjet_test.generate(RooArgSet(J_mass),nPseudo_data_fluc )


                # take out VR+SR		
	        pseudo_data_SB_fluc = RooDataSet("pseudo_data_SB_fluc", "pseudo_data_SB_fluc", RooArgSet(J_mass), RooFit.Import(pseudo_data_fluc), RooFit.Cut("fatjet1_prunedMassCorr<65 || fatjet1_prunedMassCorr>135") )

		# take only SR(signal Region) dataset for # in SR
		pseudo_data_SR_fluc = RooDataSet("pseudo_data_SR_fluc", "pseudo_data_SR_fluc", RooArgSet(J_mass), RooFit.Import(pseudo_data_fluc), RooFit.Cut("fatjet1_prunedMassCorr>105 && fatjet1_prunedMassCorr<135") )

		# calculation of generation 

                nGen_SR_fluc = pseudo_data_SR_fluc.sumEntries()
		iGen_SR = modelVjet_test.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("SRrange")) 

#		print "nGen_SR_fluc2:",nGen_SR_fluc2
#		print "nGen_SR_fluc:",nGen_SR_fluc

                sigma_Gen_fluc = math.sqrt( nGen_SR_fluc )

		# plot fixed PDF and SB dataset (optional)

                if times == times_to_plot : pseudo_data_fluc.plotOn(Jmass_frame4)
                if times == times_to_plot : pseudo_data_fluc.plotOn(Jmass_frame5)

                if times == times_to_plot : modelVjet_test.plotOn(Jmass_frame4,RooFit.LineColor(4))
                if times == times_to_plot : modelVjet_test.plotOn(Jmass_frame5,RooFit.LineColor(4))


                if times == times_to_plot : pseudo_data_SB_fluc.plotOn(Jmass_frame4,RooFit.LineColor(3))
                if times == times_to_plot : pseudo_data_SB_fluc.plotOn(Jmass_frame5,RooFit.LineColor(3))


                # ---------------------------------
                # case 1, fit with the same function
                # ---------------------------------

		# reset parameters
		constVjet_case1.setVal(constVjet_value_fit_MC)
		offsetVjet_case1.setVal(offsetVjet_value_fit_MC)
		widthVjet_case1.setVal(widthVjet_value_fit_MC)

		offsetVjet_case1.setConstant(True)

		# make PDF with same function
		modelVjet_case1 = RooErfExpPdf("modelVjet_case1", "error function for V+jets mass", J_mass, constVjet_case1, offsetVjet_case1, widthVjet_case1)

		# fit
        	frVjet_case1 = modelVjet_case1.fitTo(pseudo_data_SB_fluc, RooFit.SumW2Error(True), RooFit.Range("LSBrange,HSBrange"), RooFit.Strategy(2), RooFit.Minimizer(minimizer_choose), RooFit.Save(1), RooFit.PrintLevel(1 if VERBOSE else -1))

                if times == times_to_plot : modelVjet_case1.plotOn(Jmass_frame4,RooFit.LineColor(2),RooFit.Range("h_reasonable_range"))


                # get error

                par1_fitresult_case1 = frVjet_case1.floatParsFinal().find("constVjet_case1")
                par2_fitresult_case1 = frVjet_case1.floatParsFinal().find("widthVjet_case1")


                par1_value = par1_fitresult_case1.getVal()
                par1_error = par1_fitresult_case1.getError()

                par2_value = par2_fitresult_case1.getVal()
                par2_error = par2_fitresult_case1.getError()




		# calculate the bias and pull

        	# use def function
        	par1_name = "constVjet_case1"
	        par2_name = "widthVjet_case1"

        	fit_central_value, fit_error_by_function = Get_Fit_Sigma( J_mass , nPseudo_data_fluc, modelVjet_case1 , frVjet_case1, constVjet_case1, par1_name , widthVjet_case1, par2_name  )
#		print ""
#		print " check with function"
#        	print "iFit_SR_by_function:", fit_central_value," +/-", fit_error_by_function





		# ------- bias

                constVjet_case1.setVal(par1_value )
                widthVjet_case1.setVal(par2_value )

        	iFit_SR_case1 = modelVjet_case1.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
                iFit_All_case1 = modelVjet_case1.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("h_reasonable_range"))
                nFit_SR_case1 = nPseudo_data_fluc * (iFit_SR_case1.getVal()/iFit_All_case1.getVal())

#		print ""
#		print " check central value"
#                print "iFit_SR_case1 :", iFit_SR_case1.getVal()
#		print "iGen_SR: ", iGen_SR.getVal()
#		print "nFit_SR_case1:", nFit_SR_case1
#		print ""

#		Bias_value_case1 = ( nFit_SR_case1 - nGen_SR_fluc )/ nGen_SR_fluc
                Bias_value_case1 = ( fit_central_value  - iGen_SR.getVal() )/ iGen_SR.getVal()
		h_Bias_case1.Fill(Bias_value_case1)

		# ------- pull

		# get error

	        par1_fitresult_case1 = frVjet_case1.floatParsFinal().find("constVjet_case1")
        	par2_fitresult_case1 = frVjet_case1.floatParsFinal().find("widthVjet_case1")


        	par1_value = par1_fitresult_case1.getVal()
        	par1_error = par1_fitresult_case1.getError()

        	par2_value = par2_fitresult_case1.getVal()
        	par2_error = par2_fitresult_case1.getError()



        	# get nFit_SR by RooFormulaVar

        	constVjet_case1.setVal(par1_value)
        	widthVjet_case1.setVal(par2_value)

		# nFit_SR
        	nTotal = RooRealVar("nTotal","for nPseudo_data_fluc", nPseudo_data_fluc, 0., 2*nPseudo_data_fluc)
        	nFit_SR_formula = RooFormulaVar("nFit_SR_formula", "nFit SR formula", "@0 * @1 / @2", RooArgList(nTotal,iFit_SR_case1,iFit_All_case1) )

        	nFit_SR_formula_error = nFit_SR_formula.getPropagatedError( frVjet_case1 )

		# iFit_SR
        	iFit_SR_formula = RooFormulaVar("iFit_SR_formula", "iFit SR formula", "@0", RooArgList( iFit_SR_case1 ) )
        	iFit_SR_formula_error = iFit_SR_formula.getPropagatedError( frVjet_case1 )

#        	print ""
#        	print "test iFit_SR by RooFormulaVar"
#        	print "iFit_SR_formula:", iFit_SR_formula.getVal() , " +/-", iFit_SR_formula_error
#	        print ""





                # pull 

#                sigma_Fit_case1 = math.sqrt( nFit_SR_case1 )
#		sigma_Fit_case1 = fit_error_by_function 
		sigma_Fit_case1 = iFit_SR_formula_error 

#                pull_value_case1 = ( nFit_SR_case1 - nGen_SR_fluc )/ sigma_Fit_case1
                pull_value_case1 = ( fit_central_value  - iGen_SR.getVal()  )/ sigma_Fit_case1

		h_Pull_case1.Fill( pull_value_case1 )









		# ---------------------------------
		# case 2, fit with another function
		# ---------------------------------

		# reset parameter
		constVjet_case2.setVal(constVjet_value_case2 )
		a0Vjet_case2.setVal( a0Vjet_value_case2 )
		a1Vjet_case2.setVal( a1Vjet_value_case2 )
		a2Vjet_case2.setVal( a2Vjet_value_case2 )

		# make PDF with different function   	 
#		modelVjet_case2 = RooExponential("modelVjet_case2", "exp for V+jets mass", J_mass, constVjet_case2)
#		modelVjet_case2 = RooChebychev("modelVjet_case2", "polynomial for V+jets mass", J_mass, RooArgList(a0Vjet_case2, a1Vjet_case2, a2Vjet_case2))
		modelVjet_case2 = RooGenericPdf("modelVjet_case2", "powerlaw for X mass", "@0^@1", RooArgList(J_mass, a0Vjet_case2))

		# fit
                frVjet_case2 = modelVjet_case2.fitTo(pseudo_data_SB_fluc, RooFit.SumW2Error(True), RooFit.Range("LSBrange,HSBrange"), RooFit.Strategy(2), RooFit.Minimizer(minimizer_choose), RooFit.Save(1), RooFit.PrintLevel(1 if VERBOSE else -1))

                # calculate the bias and pull

                iFit_SR_case2 = modelVjet_case2.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
                iFit_All_case2 = modelVjet_case2.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("h_reasonable_range"))
                nFit_SR_case2 = nPseudo_data_fluc * (iFit_SR_case2.getVal()/iFit_All_case2.getVal())

                Bias_value_case2 = ( nFit_SR_case2 - nGen_SR_fluc )/ nGen_SR_fluc
                h_Bias_case2.Fill(Bias_value_case2)

                pull_value_case2 = ( nFit_SR_case2 - nGen_SR_fluc )/ sigma_Gen_fluc
                h_Pull_case2.Fill( pull_value_case2 )


                # plot PDF used to fit (optional)
                if times == times_to_plot : modelVjet_case2.plotOn(Jmass_frame5,RooFit.LineColor(2),RooFit.Range("h_reasonable_range"))


        # ------------------------------------------------------------------- 
	# plot and save

        Save_Dir = "/afs/cern.ch/user/y/yuchang/www/jacopo_plotsAlpha/yu_hsiang_bias_study"

        c_test = TCanvas("test","test draw",800,600)
        c_test.cd()
        Jmass_frame.Draw()
        c_test.SaveAs(Save_Dir+"/"+"VJet_MC_fit_get_shape.pdf")

        c_test2 = TCanvas("test2","test draw 2",800,600)
        c_test2.cd()
        Jmass_frame2.Draw()
        c_test2.SaveAs(Save_Dir+"/"+"use_shape_to_generate_pseudo_data.pdf")
#        c_test2.SaveAs(Save_Dir+"/"+"use_shape_to_generate_pseudo_data_test.pdf")

        c_test3 = TCanvas("test3","test draw 3",800,600)
        c_test3.cd()
        Jmass_frame3.Draw()
        c_test3.SaveAs(Save_Dir+"/"+"fit_pseudo_data_in_SB_only.pdf")

        # -----------------------------
        # case 1 figure

        c_test4 = TCanvas("test4","test draw 4",800,400)
        c_test4.Divide(2)

        c_test4.cd(1)
        gPad.SetLeftMargin(0.15)
        h_Bias_case1.GetYaxis().SetTitleOffset(1.6)
        h_Bias_case1.Draw()

        c_test4.cd(2)
        gPad.SetLeftMargin(0.15)
        h_Pull_case1.GetYaxis().SetTitleOffset(1.6)
        h_Pull_case1.Draw()

        c_test4.SaveAs(Save_Dir+"/"+"h_Bias_and_pull_case1.pdf")

        # -----------------------------
        # case 2 figure

        c_test5 = TCanvas("test5","test draw 5",800,400)
        c_test5.Divide(2)

        c_test5.cd(1)
        gPad.SetLeftMargin(0.15)
        h_Bias_case2.GetYaxis().SetTitleOffset(1.6)
        h_Bias_case2.Draw()

        c_test5.cd(2)
        gPad.SetLeftMargin(0.15)
        h_Pull_case2.GetYaxis().SetTitleOffset(1.6)
        h_Pull_case2.Draw()

        c_test5.SaveAs(Save_Dir+"/"+"h_Bias_and_pull_case2.pdf")

        # -----------------------------
        # plot one time fit of case1 and case2 

        c_test6 = TCanvas("test6","test draw 6",800,400)
        c_test6.Divide(2)

        c_test6.cd(1)
        gPad.SetLeftMargin(0.15)
        Jmass_frame4.GetYaxis().SetTitleOffset(1.6)
        Jmass_frame4.Draw()

        c_test6.cd(2)
        gPad.SetLeftMargin(0.15)
        Jmass_frame5.GetYaxis().SetTitleOffset(1.6)
        Jmass_frame5.Draw()

        latex = TLatex()
        latex.SetNDC()
        latex.SetTextSize(0.04)
        latex.SetTextAlign(31)
        latex.SetTextAlign(11)

        c_test6.cd(1)
        latex.DrawLatex(0.25, 0.87, "case 1")
        c_test6.cd(2)
        latex.DrawLatex(0.25, 0.87, "case 2")

        c_test6.SaveAs(Save_Dir+"/"+"plot_one_time_fit_of_case1_case2.pdf")

        # -----------------------------
        # save histogram in ROOT file

        myFile = TFile("bias_and_pull.root","recreate");
        h_Bias_case1.Write()
        h_Pull_case1.Write()

        h_Bias_case2.Write()
        h_Pull_case2.Write()





#    else
#	print "not XZhnnb channel"

    ###################

"""
    
    #*******************************************************#
    #                                                       #
    #                 V+jets normalization                  #
    #                                                       #
    #*******************************************************#
    
    # Variables for V+jets
    constVjet   = RooRealVar("constVjet",   "slope of the exp",      -0.020, -1.,   0.)
    offsetVjet  = RooRealVar("offsetVjet",  "offset of the erf",     30.,   -50., 200.)
    widthVjet   = RooRealVar("widthVjet",   "width of the erf",     100.,     1., 200.)
    offsetVjet.setConstant(True)
    a0Vjet = RooRealVar("a0Vjet", "width of the erf", -0.1, -5, 0)
    a1Vjet = RooRealVar("a1Vjet", "width of the erf", 0.6,  0, 5)
    a2Vjet = RooRealVar("a2Vjet", "width of the erf", -0.1, -1, 1)
    
    # Define V+jets model
    if fitFuncVjet == "ERFEXP": modelVjet = RooErfExpPdf("modelVjet", "error function for V+jets mass", J_mass, constVjet, offsetVjet, widthVjet)
    elif fitFuncVjet == "EXP": modelVjet = RooExponential("modelVjet", "exp for V+jets mass", J_mass, constVjet)
    elif fitFuncVjet == "POL": modelVjet = RooChebychev("modelVjet", "polynomial for V+jets mass", J_mass, RooArgList(a0Vjet, a1Vjet, a2Vjet))
    elif fitFuncVjet == "POW": modelVjet = RooGenericPdf("modelVjet", "powerlaw for X mass", "@0^@1", RooArgList(J_mass, a0Vjet))
    else:
        print "  ERROR! Pdf", fitFuncVjet, "is not implemented for Vjets"
        exit()
    
    # fit to main bkg in MC (whole range)
    frVjet = modelVjet.fitTo(setVjet, RooFit.SumW2Error(True), RooFit.Range("h_reasonable_range"), RooFit.Strategy(2), RooFit.Minimizer("Minuit2"), RooFit.Save(1), RooFit.PrintLevel(1 if VERBOSE else -1))
    
    # integrals and number of events
    iSBVjet = modelVjet.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("LSBrange,HSBrange"))
    iLSBVjet = modelVjet.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("LSBrange"))
    iHSBVjet = modelVjet.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("HSBrange"))
    iSRVjet = modelVjet.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
    iVRVjet = modelVjet.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("VRrange"))
    # Do not remove the following lines, integrals are computed here
    iALVjet = modelVjet.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg))
    nSBVjet = iSBVjet.getVal()/iALVjet.getVal()*setVjet.sumEntries(SBcut)
    nLSBVjet = iLSBVjet.getVal()/iALVjet.getVal()*setVjet.sumEntries(LSBcut)
    nHSBVjet = iHSBVjet.getVal()/iALVjet.getVal()*setVjet.sumEntries(HSBcut)
    nSRVjet = iSRVjet.getVal()/iALVjet.getVal()*setVjet.sumEntries(SRcut)
    
    drawPlot("JetMass_Vjet", channel, J_mass, modelVjet, setVjet, binsJmass, frVjet)

    if VERBOSE: print "********** Fit result [JET MASS Vjets] *"+"*"*40, "\n", frVjet.Print(), "\n", "*"*80
    
    #*******************************************************#
    #                                                       #
    #                 VV, VH normalization                  #
    #                                                       #
    #*******************************************************#
    
    # Variables for VV
    # Error function and exponential to model the bulk
    constVV  = RooRealVar("constVV",  "slope of the exp",  -0.030, -0.1,   0.)
    offsetVV = RooRealVar("offsetVV", "offset of the erf", 90.,     1., 300.)
    widthVV  = RooRealVar("widthVV",  "width of the erf",  50.,     1., 100.)
    erfrVV   = RooErfExpPdf("baseVV", "error function for VV jet mass", J_mass, constVV, offsetVV, widthVV)
    expoVV   = RooExponential("baseVV", "error function for VV jet mass", J_mass, constVV)
    # gaussian for the V mass peak
    meanVV   = RooRealVar("meanVV",   "mean of the gaussian",           90.,    60., 100.)
    sigmaVV  = RooRealVar("sigmaVV",  "sigma of the gaussian",          10.,     6.,  30.)
    fracVV   = RooRealVar("fracVV",   "fraction of gaussian wrt erfexp", 3.2e-1, 0.,   1.)
    gausVV   = RooGaussian("gausVV",  "gaus for VV jet mass", J_mass, meanVV, sigmaVV)
    # gaussian for the H mass peak
    meanVH   = RooRealVar("meanVH",   "mean of the gaussian",           125.,   100., 150.)
    sigmaVH  = RooRealVar("sigmaVH",  "sigma of the gaussian",           30.,     5.,  40.)
    fracVH   = RooRealVar("fracVH",   "fraction of gaussian wrt erfexp",  1.5e-2, 0.,   1.)
    gausVH   = RooGaussian("gausVH",  "gaus for VH jet mass", J_mass, meanVH, sigmaVH)
    
    # Define VV model
    if fitFuncVV == "ERFEXPGAUS": modelVV  = RooAddPdf("modelVV",   "error function + gaus for VV jet mass", RooArgList(gausVV, erfrVV), RooArgList(fracVV))
    elif fitFuncVV == "ERFEXPGAUS2": modelVV  = RooAddPdf("modelVV",   "error function + gaus + gaus for VV jet mass", RooArgList(gausVH, gausVV, erfrVV), RooArgList(fracVH, fracVV))
    elif fitFuncVV == "EXPGAUS": modelVV  = RooAddPdf("modelVV",   "error function + gaus for VV jet mass", RooArgList(gausVV, expoVV), RooArgList(fracVV))
    elif fitFuncVV == "EXPGAUS2": modelVV  = RooAddPdf("modelVV",   "error function + gaus + gaus for VV jet mass", RooArgList(gausVH, gausVV, expoVV), RooArgList(fracVH, fracVV))
    else:
        print "  ERROR! Pdf", fitFuncVV, "is not implemented for VV"
        exit()
    
    # fit to secondary bkg in MC (whole range)
    frVV = modelVV.fitTo(setVV, RooFit.SumW2Error(True), RooFit.Range("h_reasonable_range"), RooFit.Strategy(2), RooFit.Minimizer("Minuit2"), RooFit.Save(1), RooFit.PrintLevel(1 if VERBOSE else -1))
    
    # integrals and number of events
    iSBVV = modelVV.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("LSBrange,HSBrange"))
    iLSBVV = modelVV.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("LSBrange"))
    iHSBVV = modelVV.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("HSBrange"))
    iSRVV = modelVV.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
    iVRVV = modelVV.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("VRrange"))
    # Do not remove the following lines, integrals are computed here
    iALVV = modelVV.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg))
    nSBVV = iSBVV.getVal()/iALVV.getVal()*setVV.sumEntries(SBcut)
    nLSBVV = iLSBVV.getVal()/iALVV.getVal()*setVV.sumEntries(LSBcut)
    nHSBVV = iHSBVV.getVal()/iALVV.getVal()*setVV.sumEntries(HSBcut)
    nSRVV = iSRVV.getVal()/iALVV.getVal()*setVV.sumEntries(SRcut)
    rSBSRVV = nSRVV/nSBVV
    
    drawPlot("JetMass_VV", channel, J_mass, modelVV, setVV, binsJmass, frVV)
    
    if VERBOSE: print "********** Fit result [JET MASS VV] ****"+"*"*40, "\n", frVV.Print(), "\n", "*"*80
    
    #*******************************************************#
    #                                                       #
    #                 Top, ST normalization                 #
    #                                                       #
    #*******************************************************#
    
    # Variables for Top
    # Error Function * Exponential to model the bulk
    constTop  = RooRealVar("constTop",  "slope of the exp", -0.030,   -1.,   0.)
    offsetTop = RooRealVar("offsetTop", "offset of the erf", 175.0,   50., 250.)
    widthTop  = RooRealVar("widthTop",  "width of the erf",  100.0,    1., 300.)
    gausTop   = RooGaussian("baseTop",  "gaus for Top jet mass", J_mass, offsetTop, widthTop)
    erfrTop   = RooErfExpPdf("baseTop", "error function for Top jet mass", J_mass, constTop, offsetTop, widthTop)
    # gaussian for the W mass peak
    meanW     = RooRealVar("meanW",     "mean of the gaussian",           80., 70., 90.)
    sigmaW    = RooRealVar("sigmaW",    "sigma of the gaussian",          10.,  2., 20.)
    fracW     = RooRealVar("fracW",     "fraction of gaussian wrt erfexp", 0.1, 0.,  1.)
    gausW     = RooGaussian("gausW",    "gaus for W jet mass", J_mass, meanW, sigmaW)
    # gaussian for the Top mass peak
    meanT     = RooRealVar("meanT",     "mean of the gaussian",           175., 150., 200.)
    sigmaT    = RooRealVar("sigmaT",    "sigma of the gaussian",           12.,   5.,  50.)
    fracT     = RooRealVar("fracT",     "fraction of gaussian wrt erfexp",  0.1,  0.,   1.)
    gausT     = RooGaussian("gausT",    "gaus for T jet mass", J_mass, meanT, sigmaT)
    
    # Define Top model
    if fitFuncTop == "ERFEXPGAUS2": modelTop = RooAddPdf("modelTop",   "error function + gaus + gaus for Top jet mass", RooArgList(gausW, gausT, erfrTop), RooArgList(fracW, fracT))
    elif fitFuncTop == "ERFEXPGAUS": modelTop = RooAddPdf("modelTop",   "error function + gaus for Top jet mass", RooArgList(gausT, erfrTop), RooArgList(fracT))
    elif fitFuncTop == "GAUS3": modelTop  = RooAddPdf("modelTop",   "gaus + gaus + gaus for Top jet mass", RooArgList(gausW, gausT, gausTop), RooArgList(fracW, fracT))
    elif fitFuncTop == "GAUS2": modelTop  = RooAddPdf("modelTop",   "gaus + gaus for Top jet mass", RooArgList(gausT, gausTop), RooArgList(fracT))
    elif fitFuncTop == "GAUS": modelTop  = RooGaussian("modelTop", "gaus for Top jet mass", J_mass, offsetTop, widthTop)
    else:
        print "  ERROR! Pdf", fitFuncTop, "is not implemented for Top"
        exit()
    
    # fit to secondary bkg in MC (whole range)
    frTop = modelTop.fitTo(setTop, RooFit.SumW2Error(True), RooFit.Range("h_reasonable_range"), RooFit.Strategy(2), RooFit.Minimizer("Minuit2"), RooFit.Save(1), RooFit.PrintLevel(1 if VERBOSE else -1))
    
    # integrals and number of events
    iSBTop = modelTop.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("LSBrange,HSBrange"))
    iLSBTop = modelTop.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("LSBrange"))
    iHSBTop = modelTop.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("HSBrange"))
    iSRTop = modelTop.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
    iVRTop = modelTop.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("VRrange"))
    # Do not remove the following lines, integrals are computed here
    iALTop = modelTop.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg))
    nSBTop = iSBTop.getVal()/iALTop.getVal()*setTop.sumEntries(SBcut)
    nLSBTop = iLSBTop.getVal()/iALTop.getVal()*setTop.sumEntries(LSBcut)
    nHSBTop = iHSBTop.getVal()/iALTop.getVal()*setTop.sumEntries(HSBcut)
    nSRTop = iSRTop.getVal()/iALTop.getVal()*setTop.sumEntries(SRcut)
    
    drawPlot("JetMass_Top", channel, J_mass, modelTop, setTop, binsJmass, frTop)
    
    if VERBOSE: print "********** Fit result [JET MASS TOP] ***"+"*"*40, "\n", frTop.Print(), "\n", "*"*80
    
    #*******************************************************#
    #                                                       #
    #                 All bkg normalization                 #
    #                                                       #
    #*******************************************************#
    
    constVjet.setConstant(True)
    offsetVjet.setConstant(True)
    widthVjet.setConstant(True)
    a0Vjet.setConstant(True)
    a1Vjet.setConstant(True)
    a2Vjet.setConstant(True)
    
    constVV.setConstant(True)
    offsetVV.setConstant(True)
    widthVV.setConstant(True)
    meanVV.setConstant(True)
    sigmaVV.setConstant(True)
    fracVV.setConstant(True)
    meanVH.setConstant(True)
    sigmaVH.setConstant(True)
    fracVH.setConstant(True)
    
    constTop.setConstant(True)
    offsetTop.setConstant(True)
    widthTop.setConstant(True)
    meanW.setConstant(True)
    sigmaW.setConstant(True)
    fracW.setConstant(True)
    meanT.setConstant(True)
    sigmaT.setConstant(True)
    fracT.setConstant(True)
    
    
    # Final background model by adding the main+secondary pdfs (using 'coef': ratio of the secondary/main, from MC)
    model = RooAddPdf("model", "model", RooArgList(modelTop, modelVV, modelVjet), RooArgList(coef_Top_VVVjet, coef_VV_Vjet))#FIXME
    model.fixAddCoefRange("h_reasonable_range")
    
    # Extended fit model to data in SB
    # all the 3 sidebands (Low / High / the 2 combined) could be used
    # currently using the LOW+HIGH (the others are commented out)
    yieldLSB = RooRealVar("yieldLSB", "Lower SB normalization",  10, 0., 1.e6)
    yieldHSB = RooRealVar("yieldHSB", "Higher SB normalization", 10, 0., 1.e6)
    yieldSB  = RooRealVar("yieldSB",  "All SB normalization",    10, 0., 1.e6)
    #model_ext = RooExtendPdf("model_ext", "extended p.d.f",   model,  yieldLSB)
    #model_ext = RooExtendPdf("model_ext", "extended p.d.f",   model,  yieldHSB)
    model_ext = RooExtendPdf("model_ext", "extended p.d.f",   model,  yieldSB)
    #frMass = model_ext.fitTo(setDataSB, RooFit.ConditionalObservables(RooArgSet(J_mass)),RooFit.SumW2Error(True),RooFit.Extended(True),RooFit.Range("LSBrange"),RooFit.PrintLevel(-1))
    #frMass = model_ext.fitTo(setDataSB, RooFit.ConditionalObservables(RooArgSet(J_mass)),RooFit.SumW2Error(True),RooFit.Extended(True),RooFit.Range("HSBrange"),RooFit.PrintLevel(-1))
    #frMass = model_ext.fitTo(setDataSB, RooFit.ConditionalObservables(RooArgSet(J_mass)), RooFit.SumW2Error(True), RooFit.Extended(True), RooFit.Range("LSBrange,HSBrange"), RooFit.Strategy(2), RooFit.Minimizer("Minuit2"), RooFit.PrintLevel(1 if VERBOSE else -1))
    
    #print "********** Fit result [JET MASS DATA] **"+"*"*40
    #print frMass.Print()
    #print "*"*80
    
    # Calculate integral of the model obtained from the fit to data (fraction of PDF that is within a given region)
    #nSB = model_ext.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("LSBrange,HSBrange"))
    #nSB = model_ext.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("LSBrange"))
    #nSB = model_ext.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("HSBrange"))
    #nSR = model_ext.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
    #nVR = model_ext.createIntegral(jetMassArg, RooFit.NormSet(jetMassArg), RooFit.Range("VRrange"))
    
    # scale the yieldSB from SB to SR using the ratio of the PDFs defined by the two integrals
    SRyield = RooFormulaVar("SRyield", "extrapolation to SR","(@0-@1*@3-@2*@4) * @5/@6 +@1*@7+@2*@8", RooArgList(entrySB, entryVV, entryTop, iSBVV, iSBTop, iSRVjet, iSBVjet, iSRVV, iSRTop))
    VRyield = RooFormulaVar("VRyield", "extrapolation to VR","(@0-@1*@3-@2*@4) * @5/@6 +@1*@7+@2*@8", RooArgList(entrySB, entryVV, entryTop, iSBVV, iSBTop, iVRVjet, iSBVjet, iVRVV, iVRTop))
    HSByield = RooFormulaVar("SRyield", "extrapolation to SR","(@0-@1*@3-@2*@4) * @5/@6 +@1*@7+@2*@8", RooArgList(entryLSB, entryVV, entryTop, iLSBVV, iLSBTop, iHSBVjet, iLSBVjet, iHSBVV, iHSBTop))
    #   RooFormulaVar SRyield("SRyield","extrapolation to SR","(@0/@1)*@2",RooArgList(*nSR,*nSB,yieldLowerSB))
    #   RooFormulaVar SRyield("SRyield","extrapolation to SR","(@0/@1)*@2",RooArgList(*nSR,*nSB,yieldHigherSB))
    #SRyield = RooFormulaVar("SRyield", "extrapolation to SR","(@0/@1)*@2", RooArgList(nSR, nSB, entrySB))
    
    bkgYield            = SRyield.getVal()
    bkgYield_error      = math.sqrt(SRyield.getPropagatedError(frVjet)**2 + SRyield.getPropagatedError(frVV)**2 + SRyield.getPropagatedError(frTop)**2 + (entrySB.getError()*rSBSRVV)**2)
    bkgNorm             = entrySB.getVal() + SRyield.getVal() + VRyield.getVal()
    bkgYield_eig_norm   = RooRealVar("predSR_eig_norm", "expected yield in SR", bkgYield, 0., 1.e6)
    bkgYieldExt         = HSByield.getVal()
    
    drawPlot("JetMass", channel, J_mass, model, setDataSB, binsJmass, None, None, "", bkgNorm, True)

    
    print channel, "normalization = %.3f +/- %.3f, observed = %.0f" % (bkgYield, bkgYield_error, setDataSR.sumEntries() if not BLIND else -1)
    if VERBOSE: raw_input("Press Enter to continue...")

"""
    
    #exit()
    # ====== CONTROL VALUE ======

def drawPlot(name, channel, variable, model, dataset, binning, fitRes=None, reg=None, cat="", norm=-1, isData=False):
    # Plotting details
    if 'Top' in name: color = 798
    elif 'VV' in name: color = 602
    elif 'XWh' in channel: color = sample['WJetsToLNu']['linecolor']
    elif 'XZhnn' in channel: color = sample['DYJetsToNuNu']['linecolor']
    else: color = sample['DYJetsToLL']['linecolor']
    cut = "reg==reg::"+cat if reg is not None else ""
    lumi = LUMISILVER if 'XZhee' in channel or 'XZhmm' in channel else LUMIGOLDEN
    cmslabel = "Preliminary" if isData else "Simulation"
    logscale = not "JetMass" in name
    
    #FIXME
    if logscale:
        if reg is not None: pre, post = "", "SB"
        else:  pre, post = "", "SR"
    else: pre, post = "model", ""
    
    # ====== CONTROL PLOT ======
    c = TCanvas("c_"+name, "Fitting "+name, 800, 800)
    c.Divide(1, 2)
    setTopPad(c.GetPad(1), RATIO)
    setBotPad(c.GetPad(2), RATIO)
    c.cd(1)
    frame = variable.frame()
    setHistStyle(frame)
    # Plot Data
    if dataset is not None: dataset.plotOn(frame, RooFit.Binning(binning), RooFit.Cut(cut), RooFit.DataError(RooAbsData.Poisson if isData else RooAbsData.SumW2))
    # dataset.plotOn(frame, RooFit.Binning(binning), RooFit.DataError(RooAbsData.Poisson), RooFit.Range("LSBrange,HSBrange"))
    # Plot models
    # Case 1: multifits
    if reg is not None:
        model.plotOn(frame, RooFit.Slice(reg, cat), RooFit.ProjWData(RooArgSet(reg), dataset), RooFit.LineColor(color)) #, RooFit.DrawOption("F"), RooFit.FillColor(color), RooFit.FillStyle(1001), RooFit.VLines()
        res = frame.pullHist()
        model.plotOn(frame, RooFit.Slice(reg, cat), RooFit.ProjWData(RooArgSet(reg), dataset), RooFit.Components(pre+"VV"+post+","+pre+"Top"+post), RooFit.LineColor(798)) # , RooFit.DrawOption("F"), RooFit.FillColor(798), RooFit.FillStyle(1001), RooFit.VLines()
        model.plotOn(frame, RooFit.Slice(reg, cat), RooFit.ProjWData(RooArgSet(reg), dataset), RooFit.Components(pre+"VV"+post), RooFit.LineColor(602)) # , RooFit.DrawOption("F"), RooFit.FillColor(602), RooFit.FillStyle(1001), RooFit.VLines()
        if SHOWERR and fitRes is not None: model.plotOn(frame, RooFit.Slice(reg, cat), RooFit.ProjWData(RooArgSet(reg), dataset), RooFit.VisualizeError(fitRes, 1, False), RooFit.FillColor(1), RooFit.FillStyle(3003))
    # Case 2: normalization is already set
    elif norm>0:
        model.plotOn(frame, RooFit.Normalization(norm, RooAbsReal.NumEvent), RooFit.LineColor(color), RooFit.DrawOption("F"), RooFit.FillColor(color), RooFit.FillStyle(1001))
        res = frame.pullHist()
        #model.plotOn(frame, RooFit.Range("h_reasonable_range"), RooFit.Range("LSBrange,HSBrange"), RooFit.LineColor(colorVjet), RooFit.FillStyle(3003), RooFit.FillColor(colorVjet))
        model.plotOn(frame, RooFit.Normalization(norm, RooAbsReal.NumEvent), RooFit.Components(pre+"VV"+post+","+pre+"Top"+post), RooFit.LineColor(798), RooFit.DrawOption("F"), RooFit.FillColor(798), RooFit.FillStyle(1001))
        model.plotOn(frame, RooFit.Normalization(norm, RooAbsReal.NumEvent), RooFit.Components(pre+"VV"+post), RooFit.LineColor(602), RooFit.DrawOption("F"), RooFit.FillColor(602), RooFit.FillStyle(1001))
        if SHOWERR and fitRes is not None: model.plotOn(frame, RooFit.Normalization(norm, RooAbsReal.NumEvent), RooFit.VisualizeError(fitRes, 1, False), RooFit.FillColor(1), RooFit.FillStyle(3003))
    # Case 2: basic scenario
    else:
        model.plotOn(frame, RooFit.LineColor(color))
        res = frame.pullHist()
        if SHOWERR and fitRes is not None: model.plotOn(frame, RooFit.VisualizeError(fitRes, 1, False), RooFit.FillColor(1), RooFit.FillStyle(3003))
    # Replot data
    if dataset is not None: dataset.plotOn(frame, RooFit.Binning(binning), RooFit.Cut(cut), RooFit.DataError(RooAbsData.Poisson if isData else RooAbsData.SumW2))

    if SHOWERR and fitRes is not None: model.paramOn(frame, RooFit.Layout(0.5, 0.95, 0.8))
    frame.GetXaxis().SetRangeUser(XBINMIN, XBINMAX)
    if logscale: 
        frame.SetMaximum(frame.GetMaximum()*2)
        frame.SetMinimum(max(frame.SetMinimum(), 2.e-3))
        c.GetPad(1).SetLogy()
    else:
        frame.SetMinimum(0)
    frame.Draw()
    drawCMS(lumi, cmslabel)
    drawAnalysis("VH")
    drawRegion(channel)
    c.cd(2)
    frame_res = variable.frame()
    #res = frame.residHist()
    if dataset is not None: frame_res.addPlotable(res, "P")
    setBotStyle(frame_res, RATIO, False)
    frame_res.GetXaxis().SetRangeUser(HBINMIN, HBINMAX)
    frame_res.GetYaxis().SetRangeUser(-5, 5)
    frame_res.GetYaxis().SetTitle("Pulls")
    frame_res.Draw()
    #drawChi2(frame)
    c.SaveAs(PLOTDIR+"/"+channel+"/"+name+".pdf")
    c.SaveAs(PLOTDIR+"/"+channel+"/"+name+".png")
    #c.SaveAs(PLOTDIR+"/"+channel+"/"+name+".root")
    if VERBOSE: raw_input("Press Enter to continue...")
    # ======   END PLOT   ======

def Get_Fit_Sigma( J_mass ,N_total_events , model_PDF , fit_result , par1 , par1_name, par2, par2_name):

    jetMassArg = RooArgSet(J_mass)

    # get parameter
    par1_fitresult = fit_result.floatParsFinal().find(par1_name)
    par2_fitresult = fit_result.floatParsFinal().find(par2_name)

    par1_value = par1_fitresult.getVal()
    par1_error = par1_fitresult.getError()

    par2_value = par2_fitresult.getVal()
    par2_error = par2_fitresult.getError()

    par1_plus = par1_value + par1_error
    par1_minus = par1_value - par1_error

    par2_plus = par2_value + par2_error
    par2_minus = par2_value - par2_error

    # get correlation matrix
    cor = fit_result.correlationMatrix() ;

    # get N_fit_central value

    par1.setVal(par1_value )
    par2.setVal(par2_value )

    iFit_SR_error = model_PDF.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
    iFit_All_error = model_PDF.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("h_reasonable_range"))

    N_fit_central = N_total_events * (  iFit_SR_error.getVal() / iFit_All_error.getVal() )
    iFit_SR_error_central_value = iFit_SR_error.getVal()
#    print "iFit_SR_error_central_value:", iFit_SR_error_central_value

    # get N_fit_par1_plus value

    par1.setVal(par1_plus )
    par2.setVal(par2_value )

    iFit_SR_error = model_PDF.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
    iFit_All_error = model_PDF.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("h_reasonable_range"))

    N_fit_par1_plus = N_total_events * (  iFit_SR_error.getVal() / iFit_All_error.getVal() )
    iFit_SR_error_par1_plus_value = iFit_SR_error.getVal()

    # get N_fit_par1_minus value

    par1.setVal(par1_minus )
    par2.setVal(par2_value )

    iFit_SR_error = model_PDF.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
    iFit_All_error = model_PDF.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("h_reasonable_range"))

    N_fit_par1_minus = N_total_events * (  iFit_SR_error.getVal() / iFit_All_error.getVal() )
    iFit_SR_error_par1_minus_value = iFit_SR_error.getVal()

    # get N_fit_par2_plus value

    par1.setVal(par1_value )
    par2.setVal(par2_plus )

    iFit_SR_error = model_PDF.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
    iFit_All_error = model_PDF.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("h_reasonable_range"))

    N_fit_par2_plus = N_total_events * (  iFit_SR_error.getVal() / iFit_All_error.getVal() )
    iFit_SR_error_par2_plus_value = iFit_SR_error.getVal()

    # get N_fit_par2_minus value

    par1.setVal(par1_value )
    par2.setVal(par2_minus )

    iFit_SR_error = model_PDF.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("SRrange"))
    iFit_All_error = model_PDF.createIntegral(jetMassArg,RooFit.NormSet(jetMassArg), RooFit.Range("h_reasonable_range"))

    N_fit_par2_minus = N_total_events * (  iFit_SR_error.getVal() / iFit_All_error.getVal() )
    iFit_SR_error_par2_minus_value = iFit_SR_error.getVal()

    # get shift

#    nFit_SR_shift_par1 = max( abs( N_fit_par1_plus - N_fit_central ) , abs( N_fit_central - N_fit_par1_minus) )
#    nFit_SR_shift_par2 = max( abs( N_fit_par2_plus - N_fit_central ) , abs( N_fit_central - N_fit_par2_minus) )

    iFit_SR_value_shift_par1 = max( abs( iFit_SR_error_par1_plus_value - iFit_SR_error_central_value ) , abs( iFit_SR_error_central_value - iFit_SR_error_par1_minus_value) )
    iFit_SR_value_shift_par2 = max( abs( iFit_SR_error_par2_plus_value - iFit_SR_error_central_value ) , abs( iFit_SR_error_central_value - iFit_SR_error_par2_minus_value) )



    # row matirx * correlation matrix * column matrix

    rowM = TMatrixD(1,2)
#    rowM[0][0] = nFit_SR_shift_par1
#    rowM[0][1] = nFit_SR_shift_par2
    rowM[0][0] = iFit_SR_value_shift_par1
    rowM[0][1] = iFit_SR_value_shift_par2

    colM = TMatrixD(2,1)
#    colM[0][0] = nFit_SR_shift_par1
#    colM[1][0] = nFit_SR_shift_par2
    colM[0][0] = iFit_SR_value_shift_par1
    colM[1][0] = iFit_SR_value_shift_par2

#    cor.Print()
#    rowM.Print()
#    colM.Print()

    resultM = rowM * ( cor * colM )
    sigma_Fit = math.sqrt( pow( resultM(0,0) , 2 ) )
    return (iFit_SR_error_central_value ,sigma_Fit)

    # ======   END Get_Fit_Sigma  ======



"""
def drawAlpha(name, channel, variable, alpha, bkgSB, bkgSR, fitRes, alpha2=None, bkgSB2=None, bkgSR2=None, fitRes2=None):

    # ====== CONTROL PLOT ======
    c = TCanvas("c_"+name, "Alpha function", 800, 800)
    c.cd()
    frame = variable.frame()
    #bkgSB.plotOn(frame, RooFit.LineColor(602)) #FIXME
    #bkgSR.plotOn(frame, RooFit.LineColor(2)) #FIXME
    alpha.plotOn(frame, RooFit.VisualizeError(fitRes, 2, False), RooFit.FillColor(400))
    alpha.plotOn(frame, RooFit.VisualizeError(fitRes, 1, False), RooFit.FillColor(416))
    alpha.plotOn(frame, RooFit.LineColor(1))
    if ALTERNATIVE:
        #alpha2.plotOn(frame, RooFit.VisualizeError(fitRes2, 2, False), RooFit.DrawOption("L"), RooFit.LineColor(920), RooFit.LineStyle(8))
        #alpha2.plotOn(frame, RooFit.VisualizeError(fitRes2, 1, False), RooFit.DrawOption("L"), RooFit.LineColor(920), RooFit.LineStyle(7))
        alpha2.plotOn(frame, RooFit.LineColor(920), RooFit.LineStyle(1))
    frame.GetXaxis().SetRangeUser(XBINMIN, XBINMAX)
    frame.SetYTitle("#alpha function")
    frame.Draw()
    drawCMS(-1, "Simulation")
    drawAnalysis("VH")
    drawRegion(channel)
    c.SaveAs(PLOTDIR+"/"+channel+"/AlphaRatio.pdf")
    c.SaveAs(PLOTDIR+"/"+channel+"/AlphaRatio.png")
    #c.SaveAs(PLOTDIR+"/"+channel+"/AlphaRatio.root")
#    frame.SetYTitle("")
#    #bkgSB.plotOn(frame, RooFit.LineColor(602))
#    #bkgSR.plotOn(frame, RooFit.LineColor(2))
#    c.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod.pdf")
#    c.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod.png")
#    #c.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod.root")
#    frame.SetMinimum(max(frame.SetMinimum(), 2.e-3))
#    c.GetPad(0).SetLogy()  
#    c.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod_log.pdf")
#    c.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod_log.png")
#    #c.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod_log.root")
    if VERBOSE: raw_input("Press Enter to continue...")
    # ======   END PLOT   ======
    
    
    # ====== CONTROL PLOT ======
    c_alpha2 = TCanvas("c_alpha2", "Alpha method", 800, 800)
    c_alpha2.cd()
    frame_alpha2 = variable.frame()
    #alpha.plotOn(frame_alpha2, RooFit.VisualizeError(fitRes, 2, False), RooFit.FillColor(400))
    #alpha.plotOn(frame_alpha2, RooFit.VisualizeError(fitRes, 1, False), RooFit.FillColor(416))
    alpha.plotOn(frame_alpha2, RooFit.LineColor(1))
    bkgSB.plotOn(frame_alpha2, RooFit.LineColor(602)) 
    bkgSR.plotOn(frame_alpha2, RooFit.LineColor(2)) 
    if ALTERNATIVE:
        alpha2.plotOn(frame_alpha2, RooFit.LineColor(920), RooFit.LineStyle(1))
        bkgSB2.plotOn(frame_alpha2, RooFit.LineColor(602), RooFit.LineStyle(7)) 
        bkgSR2.plotOn(frame_alpha2, RooFit.LineColor(2), RooFit.LineStyle(7)) 
    frame_alpha2.GetXaxis().SetRangeUser(XBINMIN, XBINMAX)
    #   frame_alpha2.GetYaxis().SetRangeUser(0, frame_alpha2.GetMaximum())
    frame_alpha2.Draw()
    frame_alpha2.SetYTitle("")
    drawCMS(-1, "Preliminary")
    drawAnalysis("VH")
    drawRegion(channel)
    c_alpha2.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod.pdf")
    c_alpha2.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod.png")
    #c_alpha2.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod.root")
    frame_alpha2.SetMinimum(max(frame_alpha2.SetMinimum(), 2.e-3))
    c_alpha2.GetPad(0).SetLogy()  
    c_alpha2.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod_log.pdf")
    c_alpha2.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod_log.png")
    #c_alpha2.SaveAs(PLOTDIR+"/"+channel+"/AlphaMethod_log.root")
"""

jobs = []

if options.all:
    for c in channelList:
        p = multiprocessing.Process(target=alpha, args=(c,))
        jobs.append(p)
        p.start()

else:
    if options.channel in channelList: alpha(options.channel)

    else:
        print "Channel not set or not recognized. Quitting..."
        exit()


# os.system('cp -r plotsAlpha/* /afs/cern.ch/user/y/yuchang/www/jacopo_plotsAlpha/yu_hsiang_bias_study')

