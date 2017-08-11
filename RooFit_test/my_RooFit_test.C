#include "RooGlobalFunc.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooExtendPdf.h"
#include "RooAbsReal.h"
#include "RooDataHist.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"

using namespace RooFit ;
using namespace std;

void plot_two_frame(TCanvas* c_, RooPlot* frame_left, RooPlot* frame_right );


void my_RooFit_test(){

  cout<<"hello"<<endl;

  /* ---------------------------------------------------------*/
  // (1) building 2 Gaussian PDF 

  RooRealVar x("x","x",-30,30) ;
  x.setRange(-30,50);// WARNING removeFitMin() IS OBSOLETE, PLEASE USE removeMin()
  x.setBins(400);   // WARNING setFitBins() IS OBSOLETE, PLEASE USE setBins()
  // range and bins decide the normalization of PDF, sum all bin-content = 1 


  RooRealVar  mean1 ("mean1" ,"mean of gaussian" ,0 ,-10,10) ;
  RooRealVar  sigma1("sigma1","width of gaussian",2 ,0.1,10) ;
  RooGaussian gauss1("gauss1","gaussian PDF",x,mean1,sigma1) ;

  RooRealVar  mean2 ("mean2" ,"mean of gaussian" ,10 ,-20,20) ;
  RooRealVar  sigma2("sigma2","width of gaussian",7 ,1,30) ;
  RooGaussian gauss2("gauss2","gaussian PDF",x,mean2,sigma2) ;

  RooPlot* xframe1 = x.frame(Title("1. building two Gaussian")) ;

  gauss1.plotOn(xframe1,LineColor(kBlue)) ;
  gauss2.plotOn(xframe1,LineColor(kRed)) ;

  TCanvas* c1 = new TCanvas("c1","c1",800,600) ;
  c1->cd();
  xframe1->Draw() ;

  cout<<"print mean1"<<endl;
  mean1.Print();

  cout<<"print gauss1"<<endl;
  gauss1.Print();

  // get normalization of PDF, see https://root.cern.ch/root/html/tutorials/roofit/rf110_normintegration.C.html
  // --------------------------

  // Return 'raw' unnormalized value of gauss1
//  cout << "gauss1 = " << gauss1.getVal() << endl ;
  
  // Return value of gx normalized over x in range [-30,50]
  RooArgSet nset(x) ;
//  cout << "gauss1_Norm[x] = " << gauss1.getVal(&nset) << endl ;

  // Create object representing integral over gx
  // which is used to calculate  gauss1_Norm[x] == gauss1 / gauss1_Int[x]

//  cout << "gauss1_Int[x] = " << gauss1.createIntegral(x)->getVal() << endl ;
//  cout << "gauss1_Int[x] with NormSet(x)= " << gauss1.createIntegral(x, NormSet(x) )->getVal() << endl ;

  cout << "gauss1 = "                       << gauss1.getVal() << endl ;
  cout << "gauss1_Norm[x] = "               << gauss1.getVal(&nset) << endl ;
  cout << "gauss1_Int[x] = "                << gauss1.createIntegral(x)->getVal() << endl ;
  cout << "gauss1_Int[x] with NormSet(x)= " << gauss1.createIntegral(x, NormSet(x) )->getVal() << endl ;

  cout << "gauss2 = "                       << gauss2.getVal() << endl ;
  cout << "gauss2_Norm[x] = "               << gauss2.getVal(&nset) << endl ;
  cout << "gauss2_Int[x] = "                << gauss2.createIntegral(x)->getVal() << endl ;
  cout << "gauss2_Int[x] with NormSet(x)= " << gauss2.createIntegral(x, NormSet(x) )->getVal() << endl ;




  /* ---------------------------------------------------------*/
  // (2) add 2 Gaussian PDF 

  double frac2_value = 0.3;

  RooRealVar  frac1("frac1"  ,"frac1" , frac2_value , 0 , 1 ) ;
  RooAddPdf   sum("sum","g1+g2",RooArgList(gauss1 ,gauss2) , RooArgList(frac1));  

  RooPlot* xframe2 = x.frame(Title("2. add two Gaussian")) ;

  sum.plotOn(xframe2, LineColor(kGreen)) ;
  sum.plotOn(xframe2, Components(RooArgSet(gauss2)), DrawOption("F"), FillColor(kRed)) ;
  sum.plotOn(xframe2, Components(RooArgSet(gauss1)), LineColor(kBlue), LineStyle(kDashed) ) ;

  TCanvas* c2 = new TCanvas("c2","c2",800,600) ;
  c2->cd();
  xframe2->Draw() ;

  cout<<"print sum"<<endl;
  sum.Print();

  cout<<"print frac1"<<endl;
  frac1.Print();

  cout<<"print gauss2"<<endl;
  gauss2.Print();


  // norm of sum
  cout << "sum = " 			    << sum.getVal() << endl ;
  cout << "sum_Norm[x] = " 		    << sum.getVal(&nset) << endl ;
  cout << "sum_Int[x] = " 		    << sum.createIntegral(x)->getVal() << endl ;
  cout << "sum_Int[x] with NormSet(x)= "    << sum.createIntegral(x, NormSet(x) )->getVal() << endl ;

  cout << "gauss1 = " 	     		    << gauss1.getVal() << endl ;
  cout << "gauss1_Norm[x] = " 		    << gauss1.getVal(&nset) << endl ;
  cout << "gauss1_Int[x] = " 		    << gauss1.createIntegral(x)->getVal() << endl ;
  cout << "gauss1_Int[x] with NormSet(x)= " << gauss1.createIntegral(x, NormSet(x) )->getVal() << endl ;

  cout << "gauss2 = " 			    << gauss2.getVal() << endl ;
  cout << "gauss2_Norm[x] = " 		    << gauss2.getVal(&nset) << endl ;
  cout << "gauss2_Int[x] = "                << gauss2.createIntegral(x)->getVal() << endl ;
  cout << "gauss2_Int[x] with NormSet(x)= " << gauss2.createIntegral(x, NormSet(x) )->getVal() << endl ;


  /* ---------------------------------------------------------*/
  // (3) generate dataset 



  RooDataSet* data1 = sum.generate( x, 10000);  

  RooPlot* xframe3 = x.frame(Title("3. generate dataset")) ;
  data1->plotOn(xframe3);

  TCanvas* c3 = new TCanvas("c3","c3",800,600) ;
  c3->cd();
  xframe3->Draw() ;


  sum.paramOn(xframe2,data1); // to show parameters
  c2->cd();
  xframe2->Draw() ;

  // ---------------------------------------------------------//
  // (4) fit dataset with PDF and extended PDF (with number of expected events)  


  // ------------ //
  // fit with PDF //
  // ------------ //

  RooRealVar  mean3("mean3"  ,"mean of gaussian" ,-1 ,-10,10) ;
  RooRealVar  sigma3("sigma3","width of gaussian",1.5 ,0.1,10) ;
  RooGaussian gauss3("gauss3","gaussian PDF",x,mean3,sigma3) ;

  RooRealVar  mean4("mean4"  ,"mean of gaussian" ,12 ,-20,20) ;
  RooRealVar  sigma4("sigma4","width of gaussian",10 ,1,30) ;
  RooGaussian gauss4("gauss4","gaussian PDF",x,mean4,sigma4) ;

  RooRealVar  frac2("frac2"  ,"frac2" ,0.5 ,0,1) ;
  RooAddPdf   sum2("sum2","g3+g4",RooArgList(gauss3 ,gauss4) , RooArgList(frac2));

  // before fit

  RooPlot* xframe4_1_1 = x.frame(Title("4.1 PDF before fit")) ;
  data1->plotOn(xframe4_1_1);
  sum2.plotOn(xframe4_1_1);

//  data1->statOn(xframe4_1_1);
  sum2.paramOn(xframe4_1_1,data1);

  // after fit

  RooPlot* xframe4_1_2 = x.frame(Title("4.1 PDF after fit")) ;

//  RooFitResult* fitres1 = sum2.fitTo(*data1,"r");
  RooFitResult* fitres1 = sum2.fitTo(*data1 , RooFit::Minimizer("Minuit2","Migrad"),Save());

  data1->plotOn(xframe4_1_2);
  sum2.plotOn(xframe4_1_2);
 
  sum2.paramOn(xframe4_1_2,data1);

  TCanvas* c4_1 = new TCanvas("c4_1","c4_1",800,400) ;
  plot_two_frame( c4_1 , xframe4_1_1, xframe4_1_2 );

  cout<<"print fitres1"<<endl;
  fitres1->Print();

  cout<<"print fitres1 status: "<< fitres1->status()<< endl;


  // --------------------- //
  // fit with extended PDF //
  // --------------------- //

  RooRealVar  mean5 ("mean5"  ,"mean of gaussian" ,-1 ,-10,10) ;
  RooRealVar  sigma5("sigma5" ,"width of gaussian",1.5 ,0.1,10) ;
  RooGaussian gauss5("gauss5" ,"gaussian PDF"     ,x,mean5,sigma5) ;

  RooRealVar  mean6 ("mean6"  ,"mean of gaussian" ,12 ,-20,20) ;
  RooRealVar  sigma6("sigma6" ,"width of gaussian",10 ,1,30) ;
  RooGaussian gauss6("gauss6" ,"gaussian PDF"     ,x,mean6,sigma6) ;

  RooRealVar  frac3("frac3"  ,"frac3" ,0.5 ,0,1) ;
  RooAddPdf   sum3("sum3","g5+g6",RooArgList(gauss5 ,gauss6) , RooArgList(frac3));

  RooRealVar  nSum3("nSum3"  ,"expected events of Sum3" , 5000 ,1000,20000) ;
  RooExtendPdf extend_sum3("extend_sum3","Extended sum3", sum3 ,nSum3 );

  // before fit
 
  RooPlot* xframe4_2_1 = x.frame(Title("4.2 exteneded PDF before fit")) ;
  data1->plotOn(xframe4_2_1);
  double norm = nSum3.getVal();
  extend_sum3.plotOn(xframe4_2_1, RooFit::Normalization(norm, RooAbsReal::NumEvent)); // plot PDF or extended PDF with data, if you don't set norm value then it will scale the PDF to data normalization automatically  

//  data1->statOn(xframe4_2_1);
  extend_sum3.paramOn(xframe4_2_1,data1);

  // after fit

  RooPlot* xframe4_2_2 = x.frame(Title("4.2 extended PDF after fit")) ;

  RooFitResult* fitres2 = extend_sum3.fitTo(*data1 , RooFit::Minimizer("Minuit2","Migrad"),Save());

  norm = nSum3.getVal();

  data1->plotOn(xframe4_2_2);
  extend_sum3.plotOn(xframe4_2_2, RooFit::Normalization(norm, RooAbsReal::NumEvent));

  extend_sum3.paramOn(xframe4_2_2,data1);

  TCanvas* c4_2 = new TCanvas("c4_2","c4_2",800,400) ;
  plot_two_frame( c4_2 , xframe4_2_1, xframe4_2_2 );

  cout<<"print fitres2"<<endl;
  fitres2->Print();

  cout<<"print fitres2 status: "<< fitres2->status()<< endl;



  // --------------------------------------------------------- //
  // (5) convert RooDataSet to RooDataHist  

  x.setBins(100);// the binning will affect the RooDataHist 

  RooDataHist binned_data1("binned_data1", "title" , RooArgSet(x) , *data1) ;

  RooPlot* xframe5 = x.frame(Title("5. convert RooDataSet to RooDataHist")) ;

  binned_data1.plotOn(xframe5);


  TCanvas* c5 = new TCanvas("c5","c5",800,600) ;
  c5->cd();
  xframe5->Draw() ;


  // ---------------------------------------------------------//
  // (6) fit  RooDataHist with PDF and extended PDF 


  // ------------ //
  // fit with PDF //
  // ------------ //

  RooRealVar  mean7 ("mean7"  ,"mean of gaussian" ,-1 ,-10,10) ;
  RooRealVar  sigma7("sigma7" ,"width of gaussian",1.5 ,0.1,10) ;
  RooGaussian gauss7("gauss7" ,"gaussian PDF",x,mean7,sigma7) ;

  RooRealVar  mean8 ("mean8" ,"mean of gaussian" ,12 ,-20,20) ;
  RooRealVar  sigma8("sigma8","width of gaussian",10 ,1,30) ;
  RooGaussian gauss8("gauss8","gaussian PDF",x,mean8,sigma8) ;

  RooRealVar  frac4("frac4"  ,"frac4" ,0.5 ,0,1) ;
  RooAddPdf   sum4("sum4","g7+g8",RooArgList(gauss7 ,gauss8) , RooArgList(frac4));

  // before fit

  RooPlot* xframe6_1_1 = x.frame(Title("6.1 PDF before fit")) ;
  binned_data1  .plotOn(xframe6_1_1);
  sum4          .plotOn(xframe6_1_1);

  binned_data1  .statOn (xframe6_1_1);
  sum4          .paramOn(xframe6_1_1, data1);// paramOn has no argument for RooDataHist, but it's same to use its original RooDataSet 


  // after fit

  RooPlot* xframe6_1_2 = x.frame(Title("6.1 PDF after fit")) ;

  RooFitResult* fitres3 = sum4.fitTo( binned_data1 , RooFit::Minimizer("Minuit2","Migrad"),Save());

  binned_data1 .plotOn(xframe6_1_2);
  sum4         .plotOn(xframe6_1_2);

  sum4.paramOn(xframe6_1_2, data1);

  TCanvas* c6_1 = new TCanvas("c6_1","c6_1",800,400) ;
  plot_two_frame( c6_1 , xframe6_1_1, xframe6_1_2 );

  cout<<"print fitres3"<<endl;
  fitres3->Print();

  cout<<"print fitres3 status: "<< fitres3->status()<< endl;



  // --------------------- //
  // fit with extended PDF //
  // --------------------- //

  RooRealVar  mean9 ("mean9"  ,"mean of gaussian" ,-1 ,-10,10) ;
  RooRealVar  sigma9("sigma9" ,"width of gaussian",1.5 ,0.1,10) ;
  RooGaussian gauss9("gauss9" ,"gaussian PDF"     ,x,mean9,sigma9) ;

  RooRealVar  mean10 ("mean10"  ,"mean of gaussian" ,12 ,-20,20) ;
  RooRealVar  sigma10("sigma10" ,"width of gaussian",10 ,1,30) ;
  RooGaussian gauss10("gauss10" ,"gaussian PDF"     ,x,mean10,sigma10) ;

  RooRealVar  frac5("frac5"  ,"frac5" ,0.5 ,0,1) ;
  RooAddPdf   sum5("sum5","g9+g10",RooArgList(gauss9 ,gauss10) , RooArgList(frac5));

  RooRealVar  nSum5("nSum5"  ,"expected events of Sum5" , 5000 ,1000,20000) ;
  RooExtendPdf extend_sum5("extend_sum5","Extended sum5", sum5 ,nSum5 );

  // before fit

  RooPlot* xframe6_2_1 = x.frame(Title("6.2 exteneded PDF before fit")) ;
  binned_data1.plotOn(xframe6_2_1);

  norm = nSum5.getVal();
  extend_sum5.plotOn(xframe6_2_1, RooFit::Normalization(norm, RooAbsReal::NumEvent)); 

  extend_sum5.paramOn(xframe6_2_1,data1);

  // after fit

  RooPlot* xframe6_2_2 = x.frame(Title("6.2 extended PDF after fit")) ;

  RooFitResult* fitres4 = extend_sum5.fitTo( binned_data1 , RooFit::Minimizer("Minuit2","Migrad"),Save());

  binned_data1 .plotOn(xframe6_2_2);

  norm = nSum5.getVal();
  extend_sum5  .plotOn(xframe6_2_2, RooFit::Normalization(norm, RooAbsReal::NumEvent));

  extend_sum5.paramOn(xframe6_2_2,data1);

  TCanvas* c6_2 = new TCanvas("c6_2","c6_2",800,400) ;
  plot_two_frame( c6_2 , xframe6_2_1, xframe6_2_2 );

  cout<<"print fitres4"<<endl;
  fitres4->Print();

  cout<<"print fitres4 status: "<< fitres4->status()<< endl;




  /* ---------------------------------------------------------*/
  // (7) generate TTree and TH1F 


//  TF1* my_func = new TF1("my_func","[0]*TMath::Gaus(x,[1],[2])+(1-[0])*TMath::Gaus(x,[3],[4])",-30,50);

//  TF1* my_func = new TF1("my_func","[0] * TMath::Gaus(x,[1],[2], true) + (1-[0]) * TMath::Gaus(x,[3],[4],true)",-30,50);

  TF1* my_func = new TF1("my_func","[5]*( [0]*TMath::Gaus(x,[1],[2])+(1-[0])*TMath::Gaus(x,[3],[4]) )",-30,50);
  
  double my_var[5] = { frac2_value , 0, 2, 10, 7 };
  double norm_factor =  13.7856;// 13.7856

//  my_func -> SetParameters( my_var[0] , my_var[1] , my_var[2] , my_var[3] , my_var[4] ); 
  my_func -> SetParameters( my_var[0] , my_var[1] , my_var[2] , my_var[3] , my_var[4] , 1/norm_factor); 

  TCanvas* c7_1 = new TCanvas("c7_1","c7_1",800,600) ;
  c7_1->cd(); my_func->Draw();

  double low  = -30;
  double high =  50;
  cout<<"my_func integral in ["<< low <<","<<high<<"]: "<< my_func->Integral(low,high)<< endl; 


/*
  TF1* test_func = new TF1("test_func","[0]-[1]*x+[2]*x*x", 0 , 4);
  test_func -> SetParameters( 5, 2, 0.2);

  TCanvas* c7_2 = new TCanvas("c7_2","c7_2",800,600) ;
  c7_2->cd(); test_func->Draw();
*/

  TH1F* h_my_func = new TH1F("h_my_func","", 80, -30,50);

  TFile* outputfile = new TFile("test.root","RECREATE");
  TTree* new_tree = new TTree("new_tree", "");

  float  x_;
  new_tree->Branch("x", &x_, "x/F");

  int N_events = 500000;

  for(int i=0;i<N_events;i++){

    double v = my_func->GetRandom();  
    h_my_func->Fill(v);
 
    x_ = v;
    new_tree->Fill();
  }

  TCanvas* c7_2 = new TCanvas("c7_2","c7_2",800,600) ;
  c7_2->cd(); h_my_func->Draw();

  new_tree        ->Write();
  outputfile      ->Write();
//  delete outputfile; // since TTree is save in ROOT file, if you delete this pointer, the converting later will not find it




  /* ---------------------------------------------------------*/
  // (8) convert TTree/TH1F to RooDataSet/RooDataHist (importing data)  


  // convert TTree

  RooDataSet data2("data2","data2",new_tree,RooArgSet(x)); // the observable x is matched to the "name" of branch in TTree  

  RooPlot* xframe8_1 = x.frame(Title("8.1 convert TTree")) ;
  data2.plotOn(xframe8_1);

  TCanvas* c8_1 = new TCanvas("c8_1","c8_1",800,600) ;
  c8_1->cd();
  xframe8_1->Draw() ;


  // convert TH1F

  RooDataHist binned_data2("binned_data2","",RooArgList(x), h_my_func ); // the observable x is matched to the order of TH1F's dimension   

  RooPlot* xframe8_2 = x.frame(Title("8.2 convert TH1F")) ;
  binned_data2.plotOn(xframe8_2);

  TCanvas* c8_2 = new TCanvas("c8_2","c8_2",800,600) ;
  c8_2->cd();
  xframe8_2->Draw() ;


}

void plot_two_frame(TCanvas* c_, RooPlot* frame_left, RooPlot* frame_right ){

  c_ ->Divide(2);
  c_ ->cd(1) ; gPad->SetLeftMargin(0.15) ; frame_left ->GetYaxis()->SetTitleOffset(1.6) ; frame_left ->Draw() ;
  c_ ->cd(2) ; gPad->SetLeftMargin(0.15) ; frame_right->GetYaxis()->SetTitleOffset(1.6) ; frame_right->Draw() ;


}

