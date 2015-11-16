#include <stdio.h>
#include <iostream>
#include <fstream>
#include <TString.h>
#include <TH1D.h>
#include <TFile.h>
#include <string>
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"

#include <cstring>

using namespace std;



void plot_var_distribution(){

// basic definition
TString path = "plot/";
//double corresponding_luminosity = 3000;// 3000/pb

int variable_flag = 0;
//variable_flag = 1;
//variable_flag = 2;

for (int  variable_index =1; variable_index<=2;variable_index++){ 
//if(variable_index!=1)continue;

variable_flag = variable_index;

// define variable 
TString variable_name;
if(variable_flag==1){ variable_name = "h_ele_1st_pT" ;}
if(variable_flag==2){ variable_name = "h_Zprime_mass" ;}
//TString variable_name = "h_ele_1st_pT" ;
//TString variable_name = "h_Zprime_mass" ;

  const int N_signal_mass_points = 11;
  int Zprime_mass[N_signal_mass_points]={800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000};
  const int N_DYJetsHTbin_background_points = 4;



// signal Zprime

  TString ROOT_name_signal[N_signal_mass_points];

  TH1D *h_signal[N_signal_mass_points];


//  TCanvas *c1 = new TCanvas("c1", "c 1", 630, 600);

  for(int i=0;i<N_signal_mass_points;i++){


        ROOT_name_signal[i] = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[i]); 
        ROOT_name_signal[i] = path + ROOT_name_signal[i];


        TFile *f_1 = new TFile ( ROOT_name_signal[i] );

        TString histo_name2 = variable_name ;

        h_signal[i] = (TH1D*) f_1 -> Get(histo_name2);
	h_signal[i]->Sumw2();
        
//        c1->cd();
//        h_2_signal[i]->Draw("same");

//        f_1->Close();
//        delete f_1;

  }// loop signal



//        h_signal[2]->Draw();







// background

  TH1D *h_background[N_DYJetsHTbin_background_points];

  TH1D *h_background_combine = (TH1D*) h_signal[0] ->Clone("h_background_combine");
  h_background_combine->Reset();
  h_background_combine->Sumw2();

  TString ROOT_name_background_DYJets[N_DYJetsHTbin_background_points];

  double cross_section_background_DYJets[N_DYJetsHTbin_background_points]={ // unit in pb
  139.4 , 42.75 , 5.497 , 2.21};

  for(int i=0;i<N_DYJetsHTbin_background_points;i++){

     if(i==0 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT100to200_in_Zprime_M-600.root";}
     if(i==1 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT200to400_in_Zprime_M-600.root";}
     if(i==2 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT400to600_in_Zprime_M-600.root";}
     if(i==3 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT600toInf_in_Zprime_M-600.root";}

     ROOT_name_background_DYJets[i] = path + ROOT_name_background_DYJets[i];
     TFile *f_1 = new TFile ( ROOT_name_background_DYJets[i] );

     TString histo_name2= variable_name ;
     h_background[i] = (TH1D*) f_1 -> Get(histo_name2);
     h_background[i]->Sumw2();

     // cross section
     cross_section_background_DYJets[i] = cross_section_background_DYJets[i] * 1.23 ;// apply the k-factor

     // total # events
     TString histo_name1= "h_eventWeight" ;
     TH1D *h_1 = (TH1D*) f_1 -> Get(histo_name1);
     double n_Total_bkg = h_1 ->Integral();// total number of event

     // scale
     double weight = cross_section_background_DYJets[i] / n_Total_bkg;
     h_background[i] -> Scale(weight);

     // add 
     h_background_combine -> Add( h_background[i] );


  }// loop background


//     h_background[3]->Draw("same");
//     h_background_combine->Draw("same");








  // draw signal and background in same Canvas
  TCanvas *c1 = new TCanvas("c1", "c 1", 630, 600);
  TLegend *leg=new TLegend(0.6,0.3,0.9,0.9);
//  TLegend *leg=new TLegend(0.4,0.4,0.9,0.9);
  TString X_title;

  int colorN = 1;
  int rebin_times =1 ;
  double X_upper_bound = 4500;
  double Y_upper_bound = 1;

if(variable_flag==1){  rebin_times = 32;  X_upper_bound = 2000; Y_upper_bound = 0.26; X_title="Leading electron p_{T} [GeV]"; }
if(variable_flag==2){  rebin_times = 8;   X_upper_bound = 4500; Y_upper_bound = 0.8; X_title="M_{Z'} [GeV]"; }

  TString leg_signal_name[N_signal_mass_points];
  double TitleOffset = 1.3;

  // signal 
  for(int i=0;i<N_signal_mass_points;i++){
//     if(i>4)continue;

     // normalize to 1
     h_signal[i] ->Scale(1/h_signal[i]->Integral() );

        if (i==0){colorN = kRed;}
        if (i==3){colorN = kOrange;}
        if (i==6){colorN = kYellow;}
        if (i==9){colorN = kCyan;}

     h_signal[i]->SetTitle("");
     h_signal[i]->SetStats(0);
     h_signal[i]->SetLineColor(colorN);
     h_signal[i]->SetLineWidth(2);
     h_signal[i]->Rebin(rebin_times);
     h_signal[i]->GetYaxis()->SetRangeUser(0, Y_upper_bound);
     h_signal[i]->GetXaxis()->SetRangeUser(0, X_upper_bound);
//     h_signal[i]->GetYaxis()->SetRangeUser(0, 0.45);
//     h_signal[i]->GetXaxis()->SetRangeUser(0, 800);
     h_signal[i]->GetXaxis()->SetTitle(X_title);
     h_signal[i]->GetYaxis()->SetTitle("Arbitrary Unit");
     h_signal[i]->GetXaxis()->SetTitleOffset(TitleOffset);
     h_signal[i]->GetYaxis()->SetTitleOffset(TitleOffset);

     leg_signal_name[i] = Form("signal M_{Z'}=%d_GeV", Zprime_mass[i] );

     c1->cd();
     if(i==0) h_signal[i] ->Draw("hist e");
     else if(i!=0) h_signal[i] ->Draw("same hist e");

     leg->AddEntry( h_signal[i] , leg_signal_name[i] ,"pl");
     leg->SetFillStyle(0);
     leg->Draw();

     colorN = colorN +1 ;
  }


  // background
  h_background_combine -> Scale(1/h_background_combine->Integral() ); 

  h_background_combine ->SetLineColor(1);
  h_background_combine ->SetLineWidth(3);
  h_background_combine ->Rebin(rebin_times);

  c1->cd();
  h_background_combine ->Draw("same hist e");

  leg->AddEntry( h_background_combine , "DYJets background" ,"pl");
  leg->Draw();


  // save

 TString save_png_name;
if(variable_flag==1)  {save_png_name = "leading_pt.png";}
if(variable_flag==2)  {save_png_name = "ZH_mass.png";}
  c1  -> SaveAs(save_png_name);


}// loop variable_flag




}// end code





