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

using namespace std;

// version of the used recoTrees  
TString v_recoTree;

// define name
TString root_dir = "root_files/";
TString path;

// save pdf path
TString save_path = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study_2016June/";


void plot_variables();
void compare_two_variable();

void SetStyle_histo (TH1F* h          , TString variable_name );

// main function
//void step2_plot()
void step2_plot( TString v_recoTree_temp )
{

  cout<<"Hello"<< endl;

  v_recoTree = v_recoTree_temp;
  path = root_dir + "Pion_300um_combine_" + v_recoTree + ".root" ;


  plot_variables();

  compare_two_variable();



}



void plot_variables(){

  const int N_variables = 7;  
  TString variable_name[N_variables] = {"mean_from_aroundPed","RMS_from_aroundPed","max_from_aroundPed","min_from_aroundPed","max_subtract_mean_from_aroundPed","mean_subtract_min_from_aroundPed","pedestalSlope"} ;

  TString Pad_name[7] = {"Trigger","SiPad1","SiPad2","SiPad3","SiPad4","SiPad5","SiPad6"};

  TH1F* h_variable[7][N_variables];// index of SiPad, index of variables

  TFile *f = TFile::Open( path );

  // open histogram
  for(int i=1;i<7;i++){

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

  TString save_name = save_path + "Pion_300um_each_SiPad_"+ v_recoTree + ".pdf";

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

  save_name = save_path + "Pion_300um_compare_different_SiPad_ "+ v_recoTree+ ".pdf";

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


void compare_two_variable(){

  const int N_variables = 4;  
  TString variable_name[N_variables] = {"mean_from_aroundPed","RMS_from_aroundPed","pedestal","pedestalRMS"} ;

  TString Pad_name[7] = {"Trigger","SiPad1","SiPad2","SiPad3","SiPad4","SiPad5","SiPad6"};

  TH1F* h_variable[7][N_variables];// index of SiPad, index of variables

  TFile *f = TFile::Open( path );

  // open histogram
  for(int i=1;i<7;i++){

    for(int k=0;k<N_variables;k++){
      TString h_name = "h_" + variable_name[k] + "_" + Pad_name[i] ;
      h_variable[i][k] = (TH1F*)f->FindObjectAny(h_name);
    }
  }

  // draw and save pdf
  TString save_name = save_path + "Pion_300um_compare_two_variables_" + v_recoTree + ".pdf";

  TCanvas *c1 = new TCanvas("c1","c1",200,10,700,500);
  TCanvas *c2 = new TCanvas("c2","c2",200,10,700,500);

  for(int i=1;i<7;i++){

    TLegend *leg1;
    if(h_variable[i][0]->GetMean()>3700){ leg1 = new TLegend(0.2,0.7,0.5,0.9);}
    else leg1 = new TLegend(0.6,0.7,0.9,0.9); 
    leg1->SetHeader("d= 300 #mu m");

    TLegend *leg2 = new TLegend(0.6,0.7,0.9,0.9);
    leg2->SetHeader("d= 300 #mu m");


    for(int k=0;k<N_variables;k++){
      h_variable[i][k]->Scale(  1/h_variable[i][k]->Integral() );
      h_variable[i][k]->SetTitle(Pad_name[i]);
      h_variable[i][k]->GetXaxis()->SetTitle("[ADC]");
      h_variable[i][k]->GetYaxis()->SetTitle("Arbitrary Unit");
      h_variable[i][k]->SetStats(0);
      h_variable[i][k]->SetLineWidth(2);
    }

    h_variable[i][0]->SetLineColor(2);
    h_variable[i][1]->SetLineColor(2);
    h_variable[i][2]->SetLineColor(4);
    h_variable[i][3]->SetLineColor(4);

    h_variable[i][0]->SetLineWidth(5);
    h_variable[i][1]->SetLineWidth(5);

    c1->cd();
    h_variable[i][0]->GetXaxis()->SetRangeUser(3600 ,3760 );
    h_variable[i][0]->Draw();
    h_variable[i][2]->Draw("same");
    leg1->AddEntry( h_variable[i][0] , variable_name[0]  ,"l");
    leg1->AddEntry( h_variable[i][2] , variable_name[2]  ,"l");
    leg1->Draw();

    c2->cd();
    h_variable[i][1]->GetXaxis()->SetRangeUser(0 ,40 );
    h_variable[i][1]->Draw();
    h_variable[i][3]->Draw("same");
    leg2->AddEntry( h_variable[i][1] , variable_name[1]  ,"l");
    leg2->AddEntry( h_variable[i][3] , variable_name[3]  ,"l");
    leg2->Draw();


    if(i==1){c1->Print( save_name +"(");c2->Print( save_name );}
    else if(i==6){c1->Print( save_name );c2->Print( save_name +")");}
    else {c1->Print( save_name );c2->Print( save_name );}
  }

}



// -----------------------------------------

void SetStyle_histo(TH1F* h, TString variable_name ){

  int Low_range = 3590;   int High_range = 3800;

  if (variable_name == "mean_from_aroundPed"){
    h->GetXaxis()->SetTitle("mean_from_aroundPed [ADC]");
    h->GetXaxis()->SetRangeUser(Low_range , High_range );
  }

  if (variable_name == "RMS_from_aroundPed"){
    h->GetXaxis()->SetTitle("RMS_from_aroundPed [ADC]");
    h->GetXaxis()->SetRangeUser(0 ,70 );
  }

  if (variable_name == "max_from_aroundPed"){
    h->GetXaxis()->SetTitle("max_from_aroundPed [ADC]");
    h->GetXaxis()->SetRangeUser(Low_range , High_range );
  }

  if (variable_name == "min_from_aroundPed"){
    h->GetXaxis()->SetTitle("min_from_aroundPed [ADC]");
    h->GetXaxis()->SetRangeUser(Low_range , High_range );
  }

  if (variable_name == "max_subtract_mean_from_aroundPed"){
    h->GetXaxis()->SetTitle("max_subtract_mean_from_aroundPed [ADC]");
    h->GetXaxis()->SetRangeUser(0 ,70 );
  }

  if (variable_name == "mean_subtract_min_from_aroundPed"){
    h->GetXaxis()->SetTitle("mean_subtract_min_from_aroundPed [ADC]");
    h->GetXaxis()->SetRangeUser(0 ,70 );
  }


  if (variable_name == "pedestalSlope"){
    h->GetXaxis()->SetTitle("pedestalSlope [ADC/ns]");
    h->GetXaxis()->SetRangeUser(-10 ,10 );
  }

  h->GetYaxis()->SetTitle("number of events");
  h->GetYaxis()->SetTitleOffset(1.4);


}






