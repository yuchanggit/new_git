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
xframe1 = x.frame(RooFit.Title("1. use gauss1 generate toy MC, use gauss2 to fit"))

"""

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
xframe2 = x.frame(RooFit.Title("2. use gauss3's extended PDF to fit data1 "))

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
 
xframe3 = x.frame(RooFit.Title("3. Add PDF = gauss4 + gauss5"))

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

xframe4 = x.frame(RooFit.Title("4. use combine PDF to generate MC"))

data2 = pdf_combine1.generate(RooArgSet(x),500)

#pdf_combine1.plotOn(xframe4, RooFit.Normalization(500, RooAbsReal.NumEvent) , RooFit.LineColor(RooFit.kOrange))
data2.plotOn(xframe4)
pdf_combine1.plotOn(xframe4,RooFit.LineColor(RooFit.kBlue))

# -------------------------------------------
# 5. use combine PDF to fit the toy MC

xframe5 = x.frame(RooFit.Title("5. use combine PDF to fit the toy MC"))

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
# 6. use the extended PDF of combine PDF to fit the toy MC

xframe6 = x.frame(RooFit.Title("6. use the extended PDF of combine PDF to fit the toy MC"))

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

"""


# -------------------------------------------
# 7. use ext PDF to fit SB only and plot

xframe7 = x.frame(RooFit.Title("7. use ext PDF to fit SB only and plot"))

# gauss 10
mean10 = RooRealVar("mean10","mean of gaussian",3,-10,10)
sigma10 = RooRealVar("sigma10","width of gaussian",2,0.1,10)

gauss10 = RooGaussian("gauss10","gaussian PDF",x,mean10,sigma10)

# generate to MC 
data3 = gauss10.generate(RooArgSet(x),1000)

# split to half dataset
data3_half  = RooDataSet("data3_half", "data3 half", RooArgSet(x), RooFit.Import( data3 ), RooFit.Cut("x<3") )

# set range

x.setRange("whole_range",-10 ,10 )
x.setRange("right_gaussian_range",3 ,10 )
x.setRange("left_gaussian_range",-10 ,3 )

# another PDF gauss 11
mean11 = RooRealVar("mean11","mean of gaussian",2,-10,10)
sigma11 = RooRealVar("sigma11","width of gaussian",3,0.1,10)

gauss11 = RooGaussian("gauss11","gaussian PDF",x ,mean11 ,sigma11)

# fit partial range
#gauss11.fitTo(data3_half,RooFit.Range("left_gaussian_range"))

# convert to ext PDF then fit
nGauss11 = RooRealVar("nGauss11", "Gauss 11 ext pdf",750 , 0., 2000)
gauss11_ext = RooExtendPdf("gauss11_ext", "extended p.d.f", gauss11, nGauss11)

#gauss11_ext.plotOn(xframe7,RooFit.Normalization( nGauss11.getVal() , RooAbsReal.NumEvent), RooFit.Range("left_gaussian_range"), RooFit.LineColor(RooFit.kRed))
#gauss11_ext.plotOn(xframe7,RooFit.Normalization( nGauss11.getVal() , RooAbsReal.NumEvent), RooFit.Range("whole_range"), RooFit.LineColor(RooFit.kRed))

gauss11_ext.fixAddCoefRange("whole_range")

gauss11_ext.fitTo(data3_half,RooFit.Range("left_gaussian_range"))

print ""
print "mean11: ", mean11.Print(), 
print ""
print "sigma11: ", sigma11.Print()
print ""
print "nGauss11: ", nGauss11.Print()
print ""

# plot
#gauss10.plotOn(xframe7, RooFit.Normalization( data3.sumEntries() , RooAbsReal.NumEvent) )
#gauss10.plotOn(xframe7, RooFit.Normalization( data3.sumEntries() , RooAbsReal.NumEvent) , RooFit.Range("left_gaussian_range"))
gauss10.plotOn(xframe7, RooFit.Normalization( 500 , RooAbsReal.NumEvent) , RooFit.Range("left_gaussian_range"))


#gauss11.plotOn(xframe7,RooFit.Normalization( data3_half.sumEntries() , RooAbsReal.NumEvent), RooFit.LineColor(RooFit.kRed))
#gauss11.plotOn(xframe7,RooFit.Normalization( data3_half.sumEntries() , RooAbsReal.NumEvent), RooFit.Range("left_gaussian_range"), RooFit.LineColor(RooFit.kRed))

#gauss11_ext.plotOn(xframe7,RooFit.Normalization( nGauss11.getVal() , RooAbsReal.NumEvent), RooFit.LineColor(RooFit.kRed))
#gauss11_ext.plotOn(xframe7,RooFit.Normalization( 1.0 , RooAbsReal.RelativeExpected ), RooFit.LineColor(RooFit.kRed))
#gauss11_ext.plotOn(xframe7,RooFit.Normalization( 1.0 , RooAbsReal.RelativeExpected ), RooFit.LineColor(RooFit.kRed),RooFit.DrawOption("F"), RooFit.FillColor(RooFit.kRed), RooFit.FillStyle(1001) )

# try to fix the fill color problem

xArg = RooArgSet(x)

iLeft = gauss11_ext.createIntegral(xArg, RooFit.NormSet(xArg), RooFit.Range("left_gaussian_range"))
iTotal = gauss11_ext.createIntegral(xArg, RooFit.NormSet(xArg), RooFit.Range("whole_range"))

print "with NormSet"
print "iLeft: ", iLeft.getVal()
print "iTotal: ", iTotal.getVal()

#iLeft = gauss11_ext.createIntegral(xArg, RooFit.Range("left_gaussian_range"))
#iTotal = gauss11_ext.createIntegral(xArg, RooFit.Range("whole_range"))

#print "without NormSet"
#print "iLeft: ", iLeft.getVal()
#print "iTotal: ", iTotal.getVal()

n_total_evaluate = nGauss11.getVal() / iLeft.getVal()
print "n_total_evaluate: ", n_total_evaluate

#gauss11_ext.plotOn(xframe7,RooFit.Normalization( n_total_evaluate , RooAbsReal.NumEvent), RooFit.Range("whole_range"), RooFit.LineColor(RooFit.kRed))
#gauss11_ext.plotOn(xframe7,RooFit.Normalization( nGauss11.getVal() , RooAbsReal.NumEvent), RooFit.Range("whole_range"), RooFit.LineColor(RooFit.kRed))
gauss11_ext.plotOn(xframe7,RooFit.Normalization( nGauss11.getVal() , RooAbsReal.NumEvent), RooFit.Range("left_gaussian_range"), RooFit.LineColor(RooFit.kRed))

#gauss11_ext.plotOn(xframe7,RooFit.Normalization( nGauss11.getVal() , RooAbsReal.NumEvent), RooFit.Range("whole_range"), RooFit.LineColor(RooFit.kRed),RooFit.DrawOption("F"), RooFit.FillColor(RooFit.kRed), RooFit.FillStyle(1001) )


#data3.plotOn(xframe7)
data3_half.plotOn(xframe7)

#gauss11.plotOn(xframe7,RooFit.LineColor(RooFit.kRed))

# -------------------------------------------
# 8. use combined PDF to fit SB only and test fixAddCoefRange

xframe8 = x.frame(RooFit.Title("8. use combined PDF to fit SB only and test fixAddCoefRange"))

# gauss 12
mean12 = RooRealVar("mean12","mean of gaussian",-1,-10,10)
sigma12 = RooRealVar("sigma12","width of gaussian",2,0.1,10)

gauss12 = RooGaussian("gauss12","gaussian PDF",x,mean12,sigma12)

# gauss 13
mean13 = RooRealVar("mean13","mean of gaussian",5,-10,10)
sigma13 = RooRealVar("sigma13","width of gaussian",1,0.1,10)

gauss13 = RooGaussian("gauss13","gaussian PDF",x,mean13,sigma13)

# add PDF gauss_combine2 = gauss12 + gauss13

frac_combine4   = RooRealVar("frac_combine4",   "fraction of gauss4 wrt gauss5", 0.7, 0.,   1.)

pdf_combine4 = RooAddPdf("pdf_combine4"," gauss12 + gauss13 ", RooArgList(gauss12 , gauss13 ), RooArgList( frac_combine4 ))


#pdf_combine1.plotOn(xframe3,RooFit.LineColor(RooFit.kBlue))

#gauss12.plotOn(xframe8, RooFit.Normalization( frac_combine4.getVal()   ,RooAbsReal.Relative),RooFit.LineColor(RooFit.kOrange))
#gauss13.plotOn(xframe8, RooFit.Normalization( 1-frac_combine4.getVal() ,RooAbsReal.Relative),RooFit.LineColor(RooFit.kCyan))
#pdf_combine2.plotOn(xframe8, RooFit.Normalization(1.0,RooAbsReal.Relative) ,RooFit.LineColor(RooFit.kBlue))

# generate toy MC

n_generate = 5000

data4 = pdf_combine4.generate(RooArgSet(x), n_generate )


data4_SB  = RooDataSet("data4_SB", "data4 SB", RooArgSet(x), RooFit.Import( data4 ), RooFit.Cut("x<-2||x>4") )

# set range

x.setRange("signal_region",-2 ,4 )
x.setRange("left_side_band_region",-10 ,-2 )
x.setRange("right_side_band_region",4 ,10 )

# use gauss 13 to generate toy MC and cut right SB 

data_gauss13 = gauss13.generate(RooArgSet(x), n_generate*(1-frac_combine4.getVal() ) )
#data_gauss13.plotOn(xframe8,RooFit.LineColor(RooFit.kGreen))
data_gauss13_right_SB = RooDataSet("data_gauss13_right_SB", "data_gauss13_right_SB", RooArgSet(x), RooFit.Import( data_gauss13 ), RooFit.Cut("x>4") )
#data_gauss13_right_SB.plotOn(xframe8,RooFit.LineColor(RooFit.kGreen))
nDataGauss_right_SB = data_gauss13_right_SB.sumEntries()
print ""
print "nDataGauss_right_SB: ", nDataGauss_right_SB
print ""

# combined ext PDF  

# gauss 14
mean14 = RooRealVar("mean14","mean of gaussian",-1.5,-10,10)
sigma14 = RooRealVar("sigma14","width of gaussian",1.5,0.1,10)

gauss14 = RooGaussian("gauss14","gaussian PDF",x,mean14,sigma14)

# gauss 15
mean15 = RooRealVar("mean15","mean of gaussian",4,-10,10)
sigma15 = RooRealVar("sigma15","width of gaussian",1.3,0.1,10)

gauss15 = RooGaussian("gauss15","gaussian PDF",x,mean15,sigma15)

# convert PDF to extended PDF 

nGauss14 =  RooRealVar("nGauss14", "Gauss 14 ext normalization",  2000,  0., 6000)
gauss14_ext = RooExtendPdf("gauss14_ext",  "extended p.d.f", gauss14,  nGauss14)

nGauss15 =  RooRealVar("nGauss15", "Gauss 15 ext normalization",  1000,  0., 6000)
gauss15_ext = RooExtendPdf("gauss15_ext",  "extended p.d.f", gauss15,  nGauss15)

#nGauss15.setVal(nDataGauss_right_SB)
nGauss15.setVal( n_generate*(1-frac_combine4.getVal() ) )
nGauss15.setConstant(True)

# comine ext PDF

pdf_ext_combine5 = RooAddPdf("pdf_ext_combine5"," gauss14_ext + gauss15_ext ", RooArgList(gauss14_ext , gauss15_ext ), RooArgList( nGauss14 , nGauss15 ))

pdf_ext_combine5.fixAddCoefRange("whole_range")

# fit

#pdf_ext_combine5.fitTo(data4, RooFit.Range("whole_range") )
pdf_ext_combine5.fitTo(data4_SB, RooFit.Range("left_side_band_region,right_side_band_region") )

print ""
print "after fit"
print "nGauss14: ", nGauss14.getVal()
print "nGauss15: ", nGauss15.getVal()
print "nGauss14 + nGauss15: ", nGauss14.getVal() + nGauss15.getVal()
print ""

# plot
#gauss12.plotOn(xframe8, RooFit.Normalization( n_generate * frac_combine4.getVal()   ,RooAbsReal.NumEvent),RooFit.LineColor(RooFit.kOrange))
#gauss13.plotOn(xframe8, RooFit.Normalization( n_generate*(1-frac_combine4.getVal() ) ,RooAbsReal.NumEvent),RooFit.LineColor(RooFit.kCyan))
pdf_combine4.plotOn(xframe8, RooFit.Normalization(n_generate ,RooAbsReal.NumEvent) ,RooFit.LineColor(RooFit.kBlue))

#data4.plotOn(xframe8)
data4_SB.plotOn(xframe8)

#pdf_ext_combine5.plotOn(xframe8, RooFit.Normalization(nGauss14.getVal() + nGauss15.getVal() ,RooAbsReal.NumEvent) ,RooFit.LineColor(RooFit.kRed))
pdf_ext_combine5.plotOn(xframe8, RooFit.Normalization(data4_SB.sumEntries() ,RooAbsReal.NumEvent) ,RooFit.LineColor(RooFit.kRed))
#pdf_ext_combine5.plotOn(xframe8, RooFit.Normalization(1.0,RooAbsReal.RelativeExpected) ,RooFit.LineColor(RooFit.kRed))

print ""
print "n_generate * frac_combine4.getVal(): ", n_generate * frac_combine4.getVal()
print "n_generate*(1-frac_combine4.getVal() ): ", n_generate*(1-frac_combine4.getVal() )
print "data4_SB: ", data4_SB.sumEntries()
print ""

# -------------------------------------------
# plot and save
Save_Dir = "/afs/cern.ch/user/y/yuchang/www/jacopo_plotsAlpha/my_test_plot"
Save_name = Save_Dir + "/" + "test_fit_SB_plot.pdf"

c1 = TCanvas("c1","",800,600)

"""
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
c1.Print(Save_name)

# xframe7
c1.cd()
xframe7.Draw()
c1.Print(Save_name + ")" )
"""

# xframe7
c1.cd()
xframe7.Draw()
c1.Print(Save_name + "(")

# xframe8
c1.cd()
xframe8.Draw()
c1.Print(Save_name + ")" )





