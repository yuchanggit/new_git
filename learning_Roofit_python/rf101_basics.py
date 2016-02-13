#! /usr/bin/env python


#from ROOT import gROOT, gSystem, gStyle, gRandom
#from ROOT import TFile, TChain, TTree, TCut, TH1F, TH2F, THStack, TGraph, TGaxis
#from ROOT import TStyle, TCanvas, TPad, TLegend, TLatex, TText, TAxis


#from ROOT import RooFit, RooRealVar, RooDataHist, RooDataSet, RooAbsData, RooAbsReal, RooAbsPdf, RooPlot, RooBinning, RooCategory, RooSimultaneous, RooArgList, RooArgSet, RooWorkspace, RooMsgService
#from ROOT import RooFormulaVar, RooGenericPdf, RooGaussian, RooExponential, RooPolynomial, RooChebychev, RooBreitWigner, RooCBShape, RooExtendPdf, RooAddPdf, RooProdPdf, RooNumConvPdf, RooFFTConvPdf
#from ROOT import RooAlphaExp, RooErfExpPdf, Roo2ExpPdf, RooAlpha42ExpPdf, RooExpNPdf, RooAlpha4ExpNPdf, RooExpTailPdf, RooAlpha4ExpTailPdf, RooAlpha
#from ROOT import RooGlobalFunc

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#using namespace RooFit ;

from ROOT import gROOT, gSystem, gStyle, gRandom, gPad
from ROOT import TCanvas, TAxis, TH1F
from ROOT import RooFit, RooGlobalFunc, RooRealVar, RooDataSet, RooGaussian, RooPlot, RooArgSet 

#void rf101_basics()
#{
#  // S e t u p   m o d e l 
#  // ---------------------

#  // Declare variables x,mean,sigma with associated name, title, initial value and allowed range

x = RooRealVar("x","x",-10,10)
mean = RooRealVar("mean","mean of gaussian",1,-10,10)
sigma = RooRealVar("sigma","width of gaussian",1,0.1,10)

#  RooRealVar x("x","x",-10,10) ;
#  RooRealVar mean("mean","mean of gaussian",1,-10,10) ;
#  RooRealVar sigma("sigma","width of gaussian",1,0.1,10) ;

#//cout<<"test"<< endl;
#//  mean.Print() ;
#//  sigma.Print() ;


#  // Build gaussian p.d.f in terms of x,mean and sigma
#  RooGaussian gauss("gauss","gaussian PDF",x,mean,sigma) ;  
gauss = RooGaussian("gauss","gaussian PDF",x,mean,sigma)

#  // Construct plot frame in 'x'
#  RooPlot* xframe = x.frame(Title("Gaussian p.d.f.")) ;
xframe = x.frame(RooFit.Title("Gaussian p.d.f."))


#  // P l o t   m o d e l   a n d   c h a n g e   p a r a m e t e r   v a l u e s
#  // ---------------------------------------------------------------------------

#  // Plot gauss in frame (i.e. in x) 
gauss.plotOn(xframe) ;

#  // Change the value of sigma to 3
sigma.setVal(3) ;

#  // Plot gauss in frame (i.e. in x) and draw frame on canvas
gauss.plotOn(xframe,RooFit.LineColor(RooFit.kRed)) ;
  

#  // G e n e r a t e   e v e n t s 
#  // -----------------------------

#  // Generate a dataset of 1000 events in x from gauss
#  RooDataSet* data = gauss.generate(x,10000) ;  
data = gauss.generate(RooArgSet(x),10000) 
 
#  // Make a second plot frame in x and draw both the 
#  // data and the p.d.f in the frame
#  RooPlot* xframe2 = x.frame(Title("Gaussian p.d.f. with data")) ;
xframe2 = x.frame(RooFit.Title("Gaussian p.d.f. with data"))
#  data->plotOn(xframe2) ;
data.plotOn(xframe2)

#  gauss.plotOn(xframe2) ;
gauss.plotOn(xframe2)
  

#  // F i t   m o d e l   t o   d a t a
#  // -----------------------------

#  // Fit pdf to data
#  gauss.fitTo(*data) ;
gauss.fitTo(data)

#  // Print values of mean and sigma (that now reflect fitted values and errors)
#//  gauss.plotOn(xframe2,LineColor(kRed)) ;

#  mean.Print() ;
#  sigma.Print() ;

#  gauss.Print();
#  Double_t val = gauss.getVal();
#  cout<<"val: "<< val << endl;

#  // Draw all frames on a canvas
#  TCanvas* c = new TCanvas("rf101_basics","rf101_basics",800,400) ;
c = TCanvas("rf101_basics","rf101_basics",800,400)


#  c->Divide(2) ;
c.Divide(2)
#  c->cd(1) ; gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.6) ; xframe->Draw() ;
c.cd(1)
gPad.SetLeftMargin(0.15)
xframe.GetYaxis().SetTitleOffset(1.6)
xframe.Draw()


#  c->cd(2) ; gPad->SetLeftMargin(0.15) ; xframe2->GetYaxis()->SetTitleOffset(1.6) ; xframe2->Draw() ;
c.cd(2)
gPad.SetLeftMargin(0.15)
xframe2.GetYaxis().SetTitleOffset(1.6)
xframe2.Draw() 

Save_Dir = "/afs/cern.ch/user/y/yuchang/www/jacopo_plotsAlpha/my_test_plot"
c.SaveAs(Save_Dir+"/"+"test_plot.pdf")


"""
}
"""




