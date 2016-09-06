// for June TB, 

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <math.h>

#include "TROOT.h"
#include "TSystem.h"
#include "TKey.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TString.h"
#include "TCut.h"
#include "TMath.h"
#include "TApplication.h"
#include "TError.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TPad.h"
#include "TStyle.h"
#include <TString.h>
#include <TPaveStats.h>
#include <TLegend.h>
#include "TGraph.h"

using namespace std;

// save pdf path
TString save_path = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study_pType_Pad1Pad3Trigger";

void plot_variables(std::string root_file, TString variable_name, vector<double> &mean_of_fit, vector<double> &meanError_of_fit, vector<double> &sigma_of_fit, vector<double> &sigmaError_of_fit);
void SetStyle_histo (TH1F* h , TString variable_name );

double Calculate_Ratio(double A,double A_error , double B, double B_error);


// main function
void step2_plot(std::string root_file )
{

  // variable name
  TString variable_name[2] = {"pedestalRMS","charge_integ_largew_noise"};

  vector<double> mean_of_fit;  vector<double> meanError_of_fit; 
  vector<double> sigma_of_fit; vector<double> sigmaError_of_fit;  


  // open histogram of "pedestalRMS", fit it, and take out the fit parameter 
  plot_variables( root_file, variable_name[0], mean_of_fit, meanError_of_fit, sigma_of_fit, sigmaError_of_fit );

  vector<double> PedestalRMS_mean  =  mean_of_fit;  vector<double> PedestalRMS_meanError  = meanError_of_fit;
  vector<double> PedestalRMS_sigma =  sigma_of_fit; vector<double> PedestalRMS_sigmaError = sigmaError_of_fit;

  mean_of_fit.clear();  meanError_of_fit.clear() ; sigma_of_fit.clear() ; sigmaError_of_fit.clear();


  // open histogram of "charge_integ_largew_noise", fit it, and take out the fit parameter 
  plot_variables( root_file, variable_name[1], mean_of_fit, meanError_of_fit, sigma_of_fit, sigmaError_of_fit );

  vector<double> ChargeNoise_mean  =  mean_of_fit;  vector<double> ChargeNoise_meanError  = meanError_of_fit;
  vector<double> ChargeNoise_sigma =  sigma_of_fit; vector<double> ChargeNoise_sigmaError = sigmaError_of_fit;

  mean_of_fit.clear();  meanError_of_fit.clear() ; sigma_of_fit.clear() ; sigmaError_of_fit.clear();




  // calculate the ratio and uncertainty

  vector<double> ratio; vector<double> ratio_uncertainty;
  ratio.push_back(-99); ratio_uncertainty.push_back(-99);// for i=0 set dummy


  for(unsigned int i=1;i<ChargeNoise_sigma.size();i++){

    double ratio_ = ChargeNoise_sigma[i] / PedestalRMS_mean[i] ; 

    // calculate the uncertainty of the ratio A/B
    double ratio_uncertainty_ = Calculate_Ratio(ChargeNoise_sigma[i], ChargeNoise_sigmaError[i], PedestalRMS_mean[i], PedestalRMS_meanError[i]);

//    cout<<"i: "<< i << endl;
//    cout<<"ratio_: "<< ratio_ << "+/-" << ratio_uncertainty_ << endl; 

    ratio.push_back( ratio_ );
    ratio_uncertainty.push_back( ratio_uncertainty_ );
  }



  // print the inforamtion in screen 

  TString config_name;
  if     ( root_file.find("Pad1Tri_Ele120um") != std::string::npos ) config_name = "SiPad1Trigger_Ele120um";
  else if( root_file.find("Pad1Tri_Ele200um") != std::string::npos ) config_name = "SiPad1Trigger_Ele200um";
  else if( root_file.find("Pad1Tri_Ele320um") != std::string::npos ) config_name = "SiPad1Trigger_Ele320um";

  else if( root_file.find("Pad3Tri_Ele120um") != std::string::npos ) config_name = "SiPad3Trigger_Ele120um";
  else if( root_file.find("Pad3Tri_Ele200um") != std::string::npos ) config_name = "SiPad3Trigger_Ele200um";
  else if( root_file.find("Pad3Tri_Ele320um") != std::string::npos ) config_name = "SiPad3Trigger_Ele320um";

  TString channel_name[7];
  if( root_file.find("Pad1Tri") != std::string::npos ){
    channel_name[0] = "";
    channel_name[1] = "SiPad1";    channel_name[2] = "SiPad2";    channel_name[3] = "SiPad3";
    channel_name[4] = "SiPad4";    channel_name[5] = "SiPad5";    channel_name[6] = "SiPad6";
  }
  if( root_file.find("Pad3Tri") != std::string::npos ){
    channel_name[0] = "";
    channel_name[1] = "SiPad3";    channel_name[2] = "SiPad1";    channel_name[3] = "SiPad2";
    channel_name[4] = "SiPad4";    channel_name[5] = "SiPad5";    channel_name[6] = "SiPad6";
  }

  cout<<endl<<"configuration: "<< config_name << endl;

  for(int i=1;i<7;i++){
    cout<<"channel_name[i]: "<< channel_name[i] << endl;  
    cout<<"conversion factor: "<< ratio[i] << "+/-" << ratio_uncertainty[i] << endl;

  }

}



void plot_variables(std::string root_file, TString variable_name, vector<double> &mean_of_fit, vector<double> &meanError_of_fit, vector<double> &sigma_of_fit, vector<double> &sigmaError_of_fit ){


  // --------------------
  // open histogram

  TString path = "root_files/" + root_file ;
//  TString path = "root_files_test2/" + root_file ;
  TFile *f = TFile::Open( path );

  TH1F* h_variable[7];

  for(int i=1;i<7;i++){
      TString histo_name = "h_" + variable_name + Form("_ch%d",i);
      h_variable[i] = (TH1F*)f->FindObjectAny(histo_name);
  }

  // --------------------
  // draw each one in pdf

  // Clone
  TH1F* h_variable_clone1[7];

  for(int i=1;i<7;i++){
    h_variable_clone1[i] = (TH1F*)h_variable[i]->Clone("");
  }

  // set style

  TString config_name; 
  if     ( root_file.find("Pad1Tri_Ele120um") != std::string::npos ) config_name = "SiPad1Trigger_Ele120um";
  else if( root_file.find("Pad1Tri_Ele200um") != std::string::npos ) config_name = "SiPad1Trigger_Ele200um";
  else if( root_file.find("Pad1Tri_Ele320um") != std::string::npos ) config_name = "SiPad1Trigger_Ele320um";

  else if( root_file.find("Pad3Tri_Ele120um") != std::string::npos ) config_name = "SiPad3Trigger_Ele120um";
  else if( root_file.find("Pad3Tri_Ele200um") != std::string::npos ) config_name = "SiPad3Trigger_Ele200um";
  else if( root_file.find("Pad3Tri_Ele320um") != std::string::npos ) config_name = "SiPad3Trigger_Ele320um";

  TString channel_name[7];
  if( root_file.find("Pad1Tri") != std::string::npos ){
    channel_name[0] = "";
    channel_name[1] = "SiPad1";    channel_name[2] = "SiPad2";    channel_name[3] = "SiPad3";
    channel_name[4] = "SiPad4";    channel_name[5] = "SiPad5";    channel_name[6] = "SiPad6";
  }
  if( root_file.find("Pad3Tri") != std::string::npos ){
    channel_name[0] = "";
    channel_name[1] = "SiPad3";    channel_name[2] = "SiPad1";    channel_name[3] = "SiPad2";
    channel_name[4] = "SiPad4";    channel_name[5] = "SiPad5";    channel_name[6] = "SiPad6";
  }


  for(int i=1;i<7;i++){
    TString title = config_name +","+ channel_name[i];
    h_variable_clone1[i]->SetTitle(title);
    h_variable_clone1[i]->SetStats(1);
    SetStyle_histo( h_variable_clone1[i]    ,  variable_name );

  }




  // Fit in Gaussian

  mean_of_fit.push_back(-99);// set dummy for i=0 
  meanError_of_fit.push_back(-99);// set dummy for i=0
  sigma_of_fit.push_back(-99);// set dummy for i=0
  sigmaError_of_fit.push_back(-99);// set dummy for i=0


  gStyle->SetOptFit(1111);
  for(int i=1;i<7;i++){

      double Rmin = h_variable_clone1[i]->GetMean() - 3* h_variable_clone1[i]->GetRMS();
      double Rmax = h_variable_clone1[i]->GetMean() + 3* h_variable_clone1[i]->GetRMS();
      h_variable_clone1[i]->Fit("gaus","R","", Rmin , Rmax); 

      TF1 *fit = h_variable_clone1[i]->GetFunction("gaus");

      mean_of_fit.push_back( fit->GetParameter(1) );  meanError_of_fit.push_back( fit->GetParError(1) );  
      sigma_of_fit.push_back( fit->GetParameter(2) );  sigmaError_of_fit.push_back( fit->GetParError(2) ); 

  }



  // draw and save

  TString save_name = save_path +"/"+config_name+"_"+variable_name+".pdf";
  TCanvas *c1 = new TCanvas("c1","c1",200,10,700,500);


  for(int i=1;i<7;i++){

    c1->cd();
    h_variable_clone1[i]->Draw(); 
    c1->Update();

    if (variable_name == "pedestal" && h_variable_clone1[i]->GetMean()>3685){
      
      cout<<"hello"<<endl;
      double newx1 = 0.2; double newx2 = 0.5 ;      double newy1 = 0.4; double newy2 = 0.9 ;
      TPaveStats *st =(TPaveStats*) h_variable_clone1[i]->GetListOfFunctions()->FindObject("stats");
      st->SetX1NDC(newx1); st->SetX2NDC(newx2); st->SetY1NDC(newy1); st->SetY2NDC(newy2);
    
    }
    c1->Update();

    if     (i==1 ){c1->Print(save_name +"(");}
//    else if(i==6 ){c1->Print(save_name +")");}
    else          {c1->Print(save_name     );}    
  }  


  // --------------------
  // compare different SiPad 

  // Clone
  TH1F* h_variable_clone2[7];

  for(int i=1;i<7;i++){
    h_variable_clone2[i] = (TH1F*)h_variable[i]->Clone("");
  }

  // set style

  double y_range_max =0;
  
  for(int i=1;i<7;i++){

    TString title = config_name +", compare different SiPad";
    h_variable_clone2[i]->SetTitle(title);

    h_variable_clone2[i]->SetStats(0);
    h_variable_clone2[i]->Scale(1/h_variable_clone2[i]->Integral() );
    SetStyle_histo( h_variable_clone2[i]    ,  variable_name ); 
    h_variable_clone2[i]->SetLineWidth(2);

    if(i==1) h_variable_clone2[i]->SetLineColor(kPink);
    if(i==2) h_variable_clone2[i]->SetLineColor(kOrange-3);
    if(i==3) h_variable_clone2[i]->SetLineColor(kGreen+2);
    if(i==4) h_variable_clone2[i]->SetLineColor(kAzure+10);
    if(i==5) h_variable_clone2[i]->SetLineColor(kBlue);
    if(i==6) h_variable_clone2[i]->SetLineColor(kMagenta+2);

    double max_temp = h_variable_clone2[i]->GetBinContent( h_variable_clone2[i]->GetMaximumBin() );
    if( max_temp > y_range_max ) y_range_max = max_temp;
  }

//  cout<<"y_range_max: "<< y_range_max << endl;
  h_variable_clone2[1]->GetYaxis()->SetRangeUser(0 , y_range_max*1.2 );

  // draw and save
  TCanvas *c2 = new TCanvas("c2","c2",200,10,700,500);
  TLegend *leg; 

  if (variable_name == "pedestal"){   leg = new TLegend(0.36,0.6,0.51,0.9);}
  else                            {   leg = new TLegend(0.75,0.6,0.9,0.9);}


  for(int i=1;i<7;i++){
    c2->cd();
    if(i==1){ h_variable_clone2[i]->Draw()      ; }
    else    { h_variable_clone2[i]->Draw("same"); }

    leg->AddEntry( h_variable_clone2[i] , channel_name[i]  ,"l");
    leg->Draw();

  }

  c2->Print( save_name + ")" ); 


}



// -----------------------------------------

void SetStyle_histo(TH1F* h, TString variable_name ){


  if (variable_name == "pedestal"){
    h->GetXaxis()->SetTitle("pedestal [ADC]");
    h->GetXaxis()->SetRangeUser(3630 ,3720 );
  }

  if (variable_name == "pedestalRMS"){
    h->GetXaxis()->SetTitle("pedestalRMS [ADC]");
    h->GetXaxis()->SetRangeUser(0 ,50 );
  }

  if (variable_name == "charge_integ_largew_noise"){
    h->GetXaxis()->SetTitle("charge_integ_largew_noise");
    h->GetXaxis()->SetRangeUser(-600 ,600 );
  }

  h->GetYaxis()->SetTitle("number of events");
  h->GetYaxis()->SetTitleOffset(1.4);

}


double Calculate_Ratio(double A,double A_error , double B, double B_error){

  double ratio_uncertainty = A/B * sqrt( pow( A_error/A ,2) + pow( B_error/B ,2)  ); 
  return ratio_uncertainty ;  

}



