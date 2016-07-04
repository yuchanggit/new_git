// for June TB, 

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

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

TString root_dir = "root_files/";
TString save_path = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study_2016June/";

void plot_variables();

void SetStyle_histo (TH1F* h          , TString variable_name );

void step2_plot()// main function
{

  cout<<"Hello"<< endl;

  plot_variables();


}



void plot_variables(){

  const int N_variables = 5;  
  TString variable_name[N_variables] = {"mean_from_aroundPed","RMS_from_aroundPed","max_from_aroundPed","max_subtract_mean_from_aroundPed","pedestalSlope"} ;

  TString Pad_name[7] = {"Trigger","SiPad1","SiPad2","SiPad3","SiPad4","SiPad5","SiPad6"};

  TH1F* h_variable[7][N_variables];// index of SiPad, index of variables

  // open histogram
  for(int i=1;i<7;i++){

    TString path = root_dir + "Pion_300um_combine.root" ;	
    TFile *f = TFile::Open( path );

    for(int k=0;k<N_variables;k++){
      TString h_name = "h_" + variable_name[k] + "_" + Pad_name[i] ;
      h_variable[i][k] = (TH1F*)f->FindObjectAny(h_name);
    }

  }


  // set style

  for(int i=1;i<7;i++){  
    for(int k=0;k<N_variables;k++){
      h_variable[i][k]->SetStats(1);
      SetStyle_histo( h_variable[i][k]    ,  variable_name[k] );
    }
  }

  // draw and save pdf
  TCanvas *c1 = new TCanvas("c1","c1",200,10,700,500);

  TString save_name = save_path + "Pion_300um_each_SiPad.pdf";

  for(int i=1;i<7;i++){
    for(int k=0;k<N_variables;k++){

      c1->cd();
      h_variable[i][k]->Draw(); 

        if     (i==1 && k==0 )              {c1->Print(save_name +"(");}
        else if(i==6 && k== N_variables-1)  {c1->Print(save_name +")");}
        else {c1->Print(save_name     );}    
    }
  }

  //----- plot the comparison of different SiPad ----------- 


  TCanvas *c2 = new TCanvas("c2","c2",200,10,700,500);

  save_name = save_path + "Pion_300um_compare_different_SiPad.pdf";

  for(int k=0;k<N_variables;k++){

    TLegend *leg = new TLegend(0.75,0.6,0.9,0.9);
    leg->SetHeader("d= 300 #mu m");

    c2->cd();
    for(int i=1;i<7;i++){

      if(i==4)h_variable[i][k]->SetLineColor(1);
      else h_variable[i][k]->SetLineColor(i+1);

      h_variable[i][k]->SetLineWidth(2);      
      h_variable[i][k]->SetStats(0);
      h_variable[i][k]->SetTitle("compare different SiPad");
      h_variable[i][k]->Scale(  1/h_variable[i][k]->Integral() );
      h_variable[i][k]->GetYaxis()->SetTitle("Arbitrary Unit");
      h_variable[i][k]->GetYaxis()->SetTitleOffset(1.3);

      if(i==1)h_variable[i][k]->Draw(); 
      else h_variable[i][k]->Draw("same");

      leg->AddEntry( h_variable[i][k] , Pad_name[i]  ,"l");
      leg->Draw();

    }

    if(k==0)c2->Print(save_name +"(");
    else if (k==N_variables-1)c2->Print(save_name +")");
    else c2->Print(save_name );
    c2->Clear();  
  }

}


// -----------------------------------------

void SetStyle_histo(TH1F* h, TString variable_name ){

  if (variable_name == "mean_from_aroundPed"){
    h->GetXaxis()->SetTitle("mean_from_aroundPed [ADC]");
    h->GetXaxis()->SetRangeUser(3620 ,3800 );
  }

  if (variable_name == "RMS_from_aroundPed"){
    h->GetXaxis()->SetTitle("RMS_from_aroundPed [ADC]");
    h->GetXaxis()->SetRangeUser(0 ,70 );
  }

  if (variable_name == "max_from_aroundPed"){
    h->GetXaxis()->SetTitle("max_from_aroundPed [ADC]");
    h->GetXaxis()->SetRangeUser(3620 ,3800 );
  }

  if (variable_name == "max_subtract_mean_from_aroundPed"){
    h->GetXaxis()->SetTitle("max_subtract_mean_from_aroundPed [ADC]");
    h->GetXaxis()->SetRangeUser(0 ,70 );
  }

  if (variable_name == "pedestalSlope"){
    h->GetXaxis()->SetTitle("pedestalSlope [ADC/ns]");
    h->GetXaxis()->SetRangeUser(-10 ,10 );
  }

  h->GetYaxis()->SetTitle("number of events");
  h->GetYaxis()->SetTitleOffset(1.4);


}






