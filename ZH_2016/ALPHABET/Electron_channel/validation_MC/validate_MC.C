#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <deque>
#include <list>

#include <TPaveStats.h>
#include <TH1D.h>
#include <TFile.h>
#include <TF1.h>
#include <TPad.h>
#include <TFile.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TTree.h>
#include "TObject.h"
#include "TColor.h"
#include "TFile.h"
#include "TMarker.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TString.h"
#include "TMath.h"

#include "supportHeader.h"

void validate_MC(){

  // --------------------------------
  // Open MC histogram from ROOT file  

  TFile* file_mc   = TFile::Open("../output_root/corrPRmass/MC_combine_histogram_DYonly.root");

  TH1F* h_passDoubleBTagger_Jmass 		    = (TH1F*) file_mc   ->FindObjectAny("h_passDoubleBTagger_Jmass");
  TH1F* h_passDoubleBTagger_Jmass_wideBinning_diff  = (TH1F*) file_mc   ->FindObjectAny("h_passDoubleBTagger_Jmass_wideBinning_diff");

  TH1F* h_failDoubleBTagger_Jmass 		    = (TH1F*) file_mc   ->FindObjectAny("h_failDoubleBTagger_Jmass");
  TH1F* h_failDoubleBTagger_Jmass_wideBinning_diff  = (TH1F*) file_mc   ->FindObjectAny("h_failDoubleBTagger_Jmass_wideBinning_diff");

  TH1F* h_Ratio 				    = (TH1F*) file_mc   ->FindObjectAny("h_Ratio");
  TH1F* h_Ratio_wideBinning 			    = (TH1F*) file_mc   ->FindObjectAny("h_Ratio_wideBinning");


  // --------------------------------
  // Style

  double Xmin,Xmax,Ymin,Ymax;
  TString XTitle,YTitle;

  Xmin= 30; Xmax=200; Ymin= -1; Ymax= 1;
  XTitle= "Corrected Pruned Jet Mass [GeV]";
  YTitle= "Number of Events";

  Set_h1_Style( h_passDoubleBTagger_Jmass , Xmin,Xmax,Ymin,Ymax, XTitle,YTitle );
  Set_h1_Style( h_failDoubleBTagger_Jmass , Xmin,Xmax,Ymin,Ymax, XTitle,YTitle );

  YTitle= "Number of Events / GeV";
  Set_h1_Style( h_passDoubleBTagger_Jmass_wideBinning_diff , Xmin,Xmax,Ymin,Ymax, XTitle,YTitle );
  Set_h1_Style( h_failDoubleBTagger_Jmass_wideBinning_diff , Xmin,Xmax,Ymin,Ymax, XTitle,YTitle );

  YTitle= "Pass / Fail Ratio";
  Set_h1_Style( h_Ratio , Xmin,Xmax,Ymin,Ymax, XTitle,YTitle );
  Set_h1_Style( h_Ratio_wideBinning , Xmin,Xmax,Ymin,Ymax, XTitle,YTitle );



  // --------------------------------
  // Draw and Fit 

  

  // Canvas 
  const int nCanvas = 6; 
  TCanvas* c_[nCanvas];

  for(int i=0; i<nCanvas; i++){
    TString c_name = Form("c_%i",i);
    c_[i] = new TCanvas(c_name,c_name,10,10,800,600);

  }

  // define Fit

  const int nTF1 = 6;
  TF1* fn_[nTF1];

  double parameters[10];

  fn_[0] = new TF1("f0", fline_Exp2 ,30,200,2);
  fn_[1] = new TF1("f1", fline_Exp2 ,30,200,2);

  fn_[2] = new TF1("f2", fline_Exp2 ,30,200,2);
//  fn_[2] = new TF1("f2", fline_Exp3 ,30,200,3);
//  fn_[2]->SetParLimits(2,0,0.001);  

//  fn_[2] = new TF1("f2", fline_Quadric ,30,200,3);
  fn_[2] = new TF1("f2", fline_ExpTail ,30,200,3);
//  fn_[2] = new TF1("f2", fline_Quadric ,30,200,3);


  fn_[3] = new TF1("f3", fline_Exp2 ,30,200,2);

//  fn_[4] = new TF1("f4", fline_Exp2 ,30,200,2);
//  fn_[4] = new TF1("f4", fline_Quadric ,30,200,3);
//  fn_[4] = new TF1("f4", fline_Gaussian ,30,200,3);
  fn_[4] = new TF1("f4", fline_ExpTail ,30,200,3);

  fn_[5] = new TF1("f5", fline_Exp2 ,30,200,2);
//  fn_[5] = new TF1("f5", fline_Exp3 ,30,200,3);
//  fn_[5]->SetParLimits(2,0,0.001); 

//  fn_[5] = new TF1("f5", fline_Quadric ,30,200,3);
  fn_[5] = new TF1("f5", fline_ExpTail ,30,200,3);
//  fn_[5] = new TF1("f5", fline_Quadric ,30,200,3);

  gStyle->SetOptFit(11111111);

  // Draw and fit


  // h_passDoubleBTagger_Jmass
  c_[0]->cd();  h_passDoubleBTagger_Jmass		   ->Draw(); 
  parameters[0] = 181; parameters[1] = -0.02; 
  Fit_TwoRange( h_passDoubleBTagger_Jmass , fn_[0] , "Exp2", parameters );


  // h_failDoubleBTagger_Jmass 
  c_[1]->cd();  h_failDoubleBTagger_Jmass		   ->Draw();
  parameters[0] = 500; parameters[1] = -0.02;  
  Fit_TwoRange( h_failDoubleBTagger_Jmass , fn_[1] , "Exp2", parameters );

  // h_Ratio
  c_[2]->cd();  h_Ratio					   ->Draw();

  cout<<" Area in Signal region of h_Ratio["<<Xmax1<<","<<Xmin2<<"]: "<< GetMyHisto_Area(h_Ratio, Xmax1 , Xmin2)<< endl ;

//  parameters[0] = 0.2; parameters[1] = -0.004; parameters[2] = 0.0001;  
//  Fit_TwoRange( h_Ratio , fn_[2] , "Exp2", parameters );

  parameters[0] = -0.15; parameters[1] = 69; parameters[2] = 0.1;
  Fit_TwoRange( h_Ratio , fn_[2] , "ExpTail", parameters );

//  parameters[0] = 0.003; parameters[1] = -1.17; parameters[2] = 0.1; 
//  Fit_TwoRange( h_Ratio , fn_[2] , "Quadric", parameters );

//  double Vmin = 45; double Vmax = 65;
//  double Vmin = 135; double Vmax = 165;
  double Vmin = 105; double Vmax = 135;


  double Area_histo = GetMyHisto_Area(h_Ratio , Vmin , Vmax);
  double Area_fit   = fn_[2]->Integral(Vmin,Vmax);

  cout<<" Area in Validate of h_Ratio["<<Vmin<<","<<Vmax<<"]: "<< Area_histo<< endl ;

  cout<<" Area in Validate of fit ["<<Vmin<<","<<Vmax<<"]: "<< Area_fit<< endl ; 

  cout<<"diff: "<< (Area_fit - Area_histo)/Area_histo << endl;

//  double mychi2 = GetMyChisquare( h_Ratio, fn_[2] );
//  cout<<" h_Ratio to fn_[2], chi2/ndf= " << mychi2 <<"/"<< GetMyNbins(h_Ratio) - fn_[2]->GetNpar()<<endl; 
//  cout<<" Area in Signal region ["<<Xmax1<<","<<Xmin2<<"]: "<< fn_[2]->Integral(Xmax1,Xmin2)<< endl ; 

/*
  int ColorNumber = 418;  
  TF1 *f_divide1  = new TF1("f_divide1", flineDivide_Exp2_Exp2 ,30,200,4);
  Draw_DivideTwoFunctions( c_[2], f_divide1 , "flineDivide_Exp2_Exp2" , fn_[0], fn_[1], ColorNumber );

  mychi2 = GetMyChisquare( h_Ratio, f_divide1 );  
  cout<<" h_Ratio to f_divide1, chi2/ndf= " << mychi2 <<"/"<< GetMyNbins(h_Ratio) <<endl;	  
  cout<<" Area in Signal region ["<<Xmax1<<","<<Xmin2<<"]: "<< f_divide1->Integral(Xmax1,Xmin2)<< endl ;

  cout<<endl;
*/


  // h_passDoubleBTagger_Jmass_wideBinning_diff
  c_[3]->cd();  h_passDoubleBTagger_Jmass_wideBinning_diff ->Draw();
  parameters[0] = 30; parameters[1] = -0.02;  
  Fit_TwoRange( h_passDoubleBTagger_Jmass_wideBinning_diff , fn_[3] , "Exp2", parameters );


  // h_failDoubleBTagger_Jmass_wideBinning_diff
  c_[4]->cd();  h_failDoubleBTagger_Jmass_wideBinning_diff ->Draw();

//  parameters[0] = 80; parameters[1] = -0.02; parameters[2] = 0.0001; 
//  Fit_TwoRange( h_failDoubleBTagger_Jmass_wideBinning_diff , fn_[4] , "Exp2", parameters );

//  parameters[0] = 0.003; parameters[1] = -1.17; parameters[2] = 102; 
//  Fit_TwoRange( h_failDoubleBTagger_Jmass_wideBinning_diff , fn_[4] , "Quadric", parameters );
//  parameters[0] = -25; parameters[1] = 70; parameters[2] = 93; 
//  Fit_TwoRange( h_failDoubleBTagger_Jmass_wideBinning_diff , fn_[4] , "Gaussian", parameters );
  parameters[0] = -0.15; parameters[1] = 69; parameters[2] = 115;
  Fit_TwoRange( h_failDoubleBTagger_Jmass_wideBinning_diff , fn_[4] , "ExpTail", parameters );

  // h_Ratio_wideBinning
  c_[5]->cd();  h_Ratio_wideBinning			   ->Draw();

//  parameters[0] = 0.2; parameters[1] = -0.02; parameters[2] = 0.0001; 
//  Fit_TwoRange( h_Ratio_wideBinning , fn_[5] , "Exp2", parameters );

  parameters[0] = -0.15; parameters[1] = 69; parameters[2] = 0.1;
  Fit_TwoRange( h_Ratio_wideBinning , fn_[5] , "ExpTail", parameters );

//  parameters[0] = 0.003; parameters[1] = -1.17; parameters[2] = 0.1;  
//  Fit_TwoRange( h_Ratio_wideBinning , fn_[5] , "Quadric", parameters );


//  cout<<"last bin content of h_Ratio_wideBinning: " << h_Ratio_wideBinning->GetBinContent(13)<<endl;
//  cout<<"area of h_Ratio_wideBinning in [152,200]: "<< GetMyHisto_Area(h_Ratio_wideBinning, 152,200)<< endl;



  // --------------------------------
  // Save PDF file

  TString save_path1 ="fit_MC_finer_binning.pdf";
  c_[0]->Print( save_path1 +"(" );
  c_[1]->Print( save_path1      );
  c_[2]->Print( save_path1 +")" );

  TString save_path2 ="fit_MC_wider_binning.pdf";
  c_[3]->Print( save_path2 +"(" );
  c_[4]->Print( save_path2      );
  c_[5]->Print( save_path2 +")" );


}


