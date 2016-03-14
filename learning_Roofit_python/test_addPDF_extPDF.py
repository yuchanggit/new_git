#! /usr/bin/env python

from ROOT import gROOT, gSystem, gStyle, gRandom, gPad
from ROOT import TCanvas, TAxis, TH1F, TColor
from ROOT import RooFit, RooGlobalFunc, RooRealVar, RooDataSet, RooGaussian, RooPlot, RooArgSet 
from ROOT import RooExtendPdf, RooAbsReal, RooAddPdf, RooArgList


import optparse

usage = "usage: %prog [options]"
parser = optparse.OptionParser(usage)
parser.add_option("-b", "--bash", action="store_true", default=False, dest="bash")
(options, args) = parser.parse_args()
if options.bash: gROOT.SetBatch(True)


# -------------------------------------------
# 1. gau1 generate toy MC, use gau2 to fit

x = RooRealVar("x","x",-10,10)
xframe1 = x.frame(RooFit.Title("test 1"))

# gauss1
mean1 = RooRealVar("mean1","mean of gaussian",2,-10,10)
sigma1 = RooRealVar("sigma1","width of gaussian",2,0.1,10)

gauss1 = RooGaussian("gauss1","gaussian PDF",x,mean1,sigma1)


# generate toy MC
data1 = gauss1.generate(RooArgSet(x),500) 

data1.plotOn(xframe1)
gauss1.plotOn(xframe1)

#gauss1.plotOn(xframe1, RooFit.Normalization(500, RooAbsReal.NumEvent) , RooFit.LineColor(RooFit.kGreen))

# gauss2
mean2 = RooRealVar("mean2","mean of gaussian",0,-10,10)
sigma2 = RooRealVar("sigma2","width of gaussian",1,0.1,10)

gauss2 = RooGaussian("gauss2","gaussian PDF",x,mean2,sigma2)

# fit
gauss2.fitTo(data1)

gauss2.plotOn(xframe1,RooFit.LineColor(RooFit.kRed))


print "for gauss1"
print "mean1: ", mean1.Print()," sigma1: ",sigma1.Print()

print "for gauss2"
print "mean2: ", mean2.Print()," sigma2: ",sigma2.Print()


# -------------------------------------------
# 2. use gau3's extended PDF to fit data1 
xframe2 = x.frame(RooFit.Title("test 2"))

# gauss 3
mean3 = RooRealVar("mean3","mean of gaussian",0,-10,10)
sigma3 = RooRealVar("sigma3","width of gaussian",1,0.1,10)

gauss3 = RooGaussian("gauss3","gaussian PDF",x,mean3,sigma3)

# convert gauss 3 to extended PDF

nGauss3 =  RooRealVar("nGauss3", "Gauss 3 ext normalization",  600,  0., 1000)
 
gauss3_ext = RooExtendPdf("gauss3_ext",  "extended p.d.f", gauss3,  nGauss3)

#gauss3_ext.plotOn(xframe2, RooFit.Normalization(1.0, RooAbsReal.RelativeExpected), RooFit.LineColor(RooFit.kGreen))

print "for gauss3 before fit"
print "mean3: ", mean3.Print()," sigma3: ",sigma3.Print()
print "nGauss3: ", nGauss3.Print()


# fit
gauss3_ext.fitTo(data1)

# plot

norm3 = nGauss3.getVal()

#gauss3_ext.plotOn(xframe2, RooFit.LineColor(RooFit.kRed))
#gauss3_ext.plotOn(xframe2, RooFit.Normalization(norm3, RooAbsReal.NumEvent), RooFit.LineColor(RooFit.kRed))
gauss3_ext.plotOn(xframe2, RooFit.Normalization(1.0, RooAbsReal.RelativeExpected), RooFit.LineColor(RooFit.kRed))

#gauss3.plotOn(xframe2, RooFit.Normalization(norm3, RooAbsReal.NumEvent), RooFit.LineColor(RooFit.kRed))

data1.plotOn(xframe2)
gauss1.plotOn(xframe2,RooFit.LineColor(RooFit.kBlue))

print "for data1"
print "number of events: ", data1.sumEntries()

print "for gauss3 after fit"
print "mean3: ", mean3.Print()," sigma3: ",sigma3.Print()
print "nGauss3: ", nGauss3.Print()

# -------------------------------------------
# 3. Add PDF = gauss4 + gauss5
 
xframe3 = x.frame(RooFit.Title("test 3"))

# gauss 4
mean4 = RooRealVar("mean4","mean of gaussian",0,-10,10)
sigma4 = RooRealVar("sigma4","width of gaussian",2,0.1,10)

gauss4 = RooGaussian("gauss4","gaussian PDF",x,mean4,sigma4)


# gauss 5
mean5 = RooRealVar("mean5","mean of gaussian",5,-10,10)
sigma5 = RooRealVar("sigma5","width of gaussian",0.5,0.1,10)

gauss5 = RooGaussian("gauss5","gaussian PDF",x,mean5,sigma5)


# add PDF gauss_combine1 = gauss4 + gauss5

frac_combine1   = RooRealVar("frac_combine1",   "fraction of gauss4 wrt gauss5", 0.7, 0.,   1.)

pdf_combine1 = RooAddPdf("pdf_combine1"," gauss4 + gauss5 ", RooArgList(gauss4 , gauss5 ), RooArgList( frac_combine1 ))


#pdf_combine1.plotOn(xframe3,RooFit.LineColor(RooFit.kBlue))

gauss4.plotOn(xframe3, RooFit.Normalization( frac_combine1.getVal()   ,RooAbsReal.Relative),RooFit.LineColor(RooFit.kOrange))
gauss5.plotOn(xframe3, RooFit.Normalization( 1-frac_combine1.getVal() ,RooAbsReal.Relative),RooFit.LineColor(RooFit.kCyan))
pdf_combine1.plotOn(xframe3, RooFit.Normalization(1.0,RooAbsReal.Relative) ,RooFit.LineColor(RooFit.kBlue))

# -------------------------------------------
# 4. use combine PDF to generate MC

xframe4 = x.frame(RooFit.Title("test 4"))

data2 = pdf_combine1.generate(RooArgSet(x),500)

#pdf_combine1.plotOn(xframe4, RooFit.Normalization(500, RooAbsReal.NumEvent) , RooFit.LineColor(RooFit.kOrange))
data2.plotOn(xframe4)
pdf_combine1.plotOn(xframe4,RooFit.LineColor(RooFit.kBlue))

# -------------------------------------------
# 5. use combine PDF to fit the toy MC

xframe5 = x.frame(RooFit.Title("test 5"))

# gauss 6
mean6 = RooRealVar("mean6","mean of gaussian",-1,-10,10)
sigma6 = RooRealVar("sigma6","width of gaussian",4,0.1,10)

gauss6 = RooGaussian("gauss6","gaussian PDF",x,mean6,sigma6)


# gauss 7
mean7 = RooRealVar("mean7","mean of gaussian",8,-10,10)
sigma7 = RooRealVar("sigma7","width of gaussian",0.25,0.1,10)

gauss7 = RooGaussian("gauss7","gaussian PDF",x,mean7,sigma7)

# comine PDF
frac_combine2   = RooRealVar("frac_combine2",   "fraction of gauss6 wrt gauss7", 0.5, 0.,   1.)

pdf_combine2 = RooAddPdf("pdf_combine2"," gauss6 + gauss7 ", RooArgList(gauss6 , gauss7 ), RooArgList( frac_combine2 ))


nData2 = data2.sumEntries() 

pdf_combine2.plotOn(xframe5, RooFit.Normalization(nData2, RooAbsReal.NumEvent) ,RooFit.LineColor(RooFit.kBlue))

# fit

pdf_combine2.fitTo(data2)

data2.plotOn(xframe5)
pdf_combine2.plotOn(xframe5, RooFit.Normalization(nData2, RooAbsReal.NumEvent) ,RooFit.LineColor(RooFit.kRed))

# print
print ""
print "for pdf_combine1, the one used to generate toy MC"
print "mean4: ", mean4.Print(), " sigma4: ", sigma4.Print()
print "mean5: ", mean5.Print(), " sigma5: ", sigma5.Print()
print "frac_combine1: ", frac_combine1.Print()

print ""
print "for pdf_combine2, the one used to fit toy MC, after fit"
print "mean6: ", mean6.Print(), " sigma6: ", sigma6.Print()
print "mean7: ", mean7.Print(), " sigma7: ", sigma7.Print()
print "frac_combine2: ", frac_combine2.Print()


print ""

# -------------------------------------------
# 5. use the extended PDF of combine PDF to fit the toy MC

xframe6 = x.frame(RooFit.Title("test 6"))

# gauss 8
mean8 = RooRealVar("mean8","mean of gaussian",-1,-10,10)
sigma8 = RooRealVar("sigma8","width of gaussian",4,0.1,10)

gauss8 = RooGaussian("gauss8","gaussian PDF",x,mean8,sigma8)

# gauss 9
mean9 = RooRealVar("mean9","mean of gaussian",8,-10,10)
sigma9 = RooRealVar("sigma9","width of gaussian",0.25,0.1,10)

gauss9 = RooGaussian("gauss9","gaussian PDF",x,mean9,sigma9)

# convert PDF to extended PDF 

nGauss8 =  RooRealVar("nGauss8", "Gauss 8 ext normalization",  200,  0., 1000)
gauss8_ext = RooExtendPdf("gauss8_ext",  "extended p.d.f", gauss8,  nGauss8)

nGauss9 =  RooRealVar("nGauss9", "Gauss 9 ext normalization",  100,  0., 1000)
gauss9_ext = RooExtendPdf("gauss9_ext",  "extended p.d.f", gauss9,  nGauss9)

# comine PDF

pdf_ext_combine3 = RooAddPdf("pdf_ext_combine3"," gauss8_ext + gauss9_ext ", RooArgList(gauss8_ext , gauss9_ext ), RooArgList( nGauss8 , nGauss9 ))

#pdf_ext_combine3.plotOn(xframe6, RooFit.Normalization(1.0, RooAbsReal.RelativeExpected) ,RooFit.LineColor(RooFit.kBlue))

# fit

pdf_ext_combine3.fitTo(data2)


# plot

color1 = RooFit.kGreen +2
pdf_ext_combine3.plotOn(xframe6, RooFit.Normalization(1.0, RooAbsReal.RelativeExpected) ,RooFit.LineColor(color1),RooFit.DrawOption("F"), RooFit.FillColor(color1), RooFit.FillStyle(1001))

color2 = RooFit.kOrange
pdf_ext_combine3.plotOn(xframe6, RooFit.Normalization(1.0, RooAbsReal.RelativeExpected) ,RooFit.Components("gauss9_ext") ,RooFit.LineColor(color2),RooFit.DrawOption("F"), RooFit.FillColor(color2), RooFit.FillStyle(1001))

data2.plotOn(xframe6)
#pdf_ext_combine3.plotOn(xframe6, RooFit.Normalization(1.0, RooAbsReal.RelativeExpected) ,RooFit.LineColor(RooFit.kRed))

pdf_combine1.plotOn(xframe6,  RooFit.Normalization(nData2, RooAbsReal.NumEvent) ,RooFit.LineColor(RooFit.kBlue))

# print 

print ""
print "for pdf_ext_combine3, the one used to fit toy MC, after fit"
print "mean8: ", mean8.Print(), " sigma8: ", sigma8.Print(), " nGauss8: ", nGauss8.Print() 
print "mean9: ", mean9.Print(), " sigma9: ", sigma9.Print(), " nGauss9: ", nGauss9.Print()


print ""




# -------------------------------------------
# plot and save
Save_Dir = "/afs/cern.ch/user/y/yuchang/www/jacopo_plotsAlpha/my_test_plot"
Save_name = Save_Dir + "/" + "test_AddPDF_extPDF.pdf"

c1 = TCanvas("c1","",800,600)

# xframe1
c1.cd()
xframe1.Draw()
c1.Print(Save_name + "(" )

# xframe2
c1.cd()
xframe2.Draw()
c1.Print(Save_name)

# xframe3
c1.cd()
xframe3.Draw()
c1.Print(Save_name)

# xframe4
c1.cd()
xframe4.Draw()
c1.Print(Save_name)

# xframe5
c1.cd()
xframe5.Draw()
c1.Print(Save_name)

# xframe6
c1.cd()
xframe6.Draw()
c1.Print(Save_name + ")" )










