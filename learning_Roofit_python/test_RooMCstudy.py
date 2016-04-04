#! /usr/bin/env python

from ROOT import gROOT, gSystem, gStyle, gRandom, gPad
from ROOT import TCanvas, TAxis, TH1F, TColor
from ROOT import RooFit, RooGlobalFunc, RooRealVar, RooDataSet, RooGaussian, RooPlot, RooArgSet 
from ROOT import RooExtendPdf, RooAbsReal, RooAddPdf, RooArgList
from ROOT import RooMCStudy

#from ROOT import *

import optparse

usage = "usage: %prog [options]"
parser = optparse.OptionParser(usage)
parser.add_option("-b", "--bash", action="store_true", default=False, dest="bash")
(options, args) = parser.parse_args()
if options.bash: gROOT.SetBatch(True)


# -------------------------------------------
# 1. gau1 generate toy MC, use gau2 to fit

x = RooRealVar("x","x",-10,10)
xframe1 = x.frame(RooFit.Title("1. use gauss1 generate toy MC, use gauss2 to fit"))



# -------------------------------------------
# 10. use Gaussian to test RooMCStudy 



# --------------------
def RooMCStudy_box( mgr1 , list_par ):

  print ""
  print "RooMCStudy_box"
  print ""


  frame1_1  =  mgr1.plotParam( mean16 )
  frame1_2  =  mgr1.plotError( mean16 )
  frame1_3  =  mgr1.plotPull ( mean16 ,RooFit.FitGauss(True)  )

  frame2_1  =  mgr1.plotParam( sigma16 )
  frame2_2  =  mgr1.plotError( sigma16 )
  frame2_3  =  mgr1.plotPull ( sigma16 ,RooFit.FitGauss(True)  )

  frame3_1  =  mgr1.plotParam( nGauss16 )
  frame3_2  =  mgr1.plotError( nGauss16 )
  frame3_3  =  mgr1.plotPull ( nGauss16 ,RooFit.FitGauss(False)  )

  frame4_0  =  mgr1.plotNLL()

  list_frame = [frame1_1, frame1_2, frame1_3, frame2_1, frame2_2, frame2_3, frame3_1, frame3_2, frame3_3, frame4_0] 

  return list_frame

# end RooMCStudy_box









xframe10 = x.frame(RooFit.Title("10. A Gaussian later used to test RooMCStudy"))

xArg = RooArgSet(x)

N_times_experiments = 1000
N_number_of_events = 500

# gauss 16
mean16 = RooRealVar("mean16","mean of gaussian",-1,-10,10)
sigma16 = RooRealVar("sigma16","width of gaussian",2,0.1,10)

gauss16 = RooGaussian("gauss16","gaussian PDF",x,mean16,sigma16)

nGauss16  = RooRealVar("nGauss16", "nGauss16", N_number_of_events ,  0. ,1000 )

gauss16_ext =  RooExtendPdf("gauss16_ext",  "extended p.d.f", gauss16,  nGauss16)

gauss16_ext.plotOn( xframe10 )

# RooMCStudy
mgr1 = RooMCStudy(gauss16_ext , gauss16_ext , xArg )
mgr1.generateAndFit( N_times_experiments , N_number_of_events )

# plot

list_par = [mean16, sigma16, nGauss16]

list_frame1 = RooMCStudy_box( mgr1 , list_par )



# -------------------------------------------
# plot and save
Save_Dir = "/afs/cern.ch/user/y/yuchang/www/jacopo_plotsAlpha/my_test_plot"
Save_name = Save_Dir + "/" + "test_RooMCstudy_gauss16_ext.pdf"

c1 = TCanvas("c1","",800,600)


for i in range(0, len(list_frame1)+1  ):

  if i == 0:
	c1.cd()
	xframe10.Draw()
	c1.Print( Save_name + "(")

  if i == len(list_frame1):
	c1.cd()
	list_frame1[ len(list_frame1)-1 ].Draw()
	c1.Print( Save_name + ")" )

  else:
        c1.cd()
        list_frame1[ i-1  ].Draw()
        c1.Print( Save_name  )

# end for loop


# -------------------------------------------
# use two ext PDF of Gaussian to combine PDF then do RooMCStudy 







