// g++ -Wall -o analyzer `root-config --cflags --glibs` analyzer.cpp
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


void Read_Tree(std::string runN, TH1F* h_variable, Long64_t &nentries, TString variable_name){

  std::string inputFolder = "/store/group/upgrade/HGCAL/TimingTB_H2_Apr2016/recoTrees/";

  TChain* tree = new TChain("H4treeReco"); 
  tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN+".root").c_str());

//  Long64_t nentries = tree->GetEntries();
  nentries = tree->GetEntries();
  std::cout << " Tree loaded events = " << nentries << std::endl;

  //Tree variables

  UInt_t nwc;
  Float_t wc_recox[16], wc_recoy[16];
  UInt_t maxch;
  Float_t group[100],ch[100];
  Float_t pedestal[100], pedestalRMS[100], pedestalSlope[100];
  Float_t wave_max[100], wave_max_aft[100], wave_aroundmax[100][50], time_aroundmax[100][50];
  Float_t charge_integ[100], charge_integ_max[100], charge_integ_fix[100];
  Float_t charge_integ_smallw[100], charge_integ_smallw_noise[100], charge_integ_largew[100], charge_integ_largew_noise[100];
  Float_t t_max[100], t_max_frac30[100], t_max_frac50[100], t_at_threshold[100], t_over_threshold[100];

  //Read tree
  tree->SetBranchAddress("nwc",       &nwc);
  tree->SetBranchAddress("wc_recox",   wc_recox);
  tree->SetBranchAddress("wc_recoy",   wc_recoy);

  tree->SetBranchAddress("maxch",               &maxch);
  tree->SetBranchAddress("group",                group);
  tree->SetBranchAddress("ch",                   ch);
  tree->SetBranchAddress("pedestal",             pedestal);
  tree->SetBranchAddress("pedestalRMS",          pedestalRMS);
  tree->SetBranchAddress("pedestalSlope",        pedestalSlope);
  tree->SetBranchAddress("wave_max",             wave_max);
  tree->SetBranchAddress("wave_max_aft",         wave_max_aft);
  tree->SetBranchAddress("wave_aroundmax",       wave_aroundmax);
  tree->SetBranchAddress("time_aroundmax",       time_aroundmax);

  tree->SetBranchAddress("charge_integ",         charge_integ);
  tree->SetBranchAddress("charge_integ_max",     charge_integ_max);
  tree->SetBranchAddress("charge_integ_fix",     charge_integ_fix);
  tree->SetBranchAddress("charge_integ_smallw",  charge_integ_smallw);
  tree->SetBranchAddress("charge_integ_largew",  charge_integ_largew);
  tree->SetBranchAddress("charge_integ_smallw_noise",  charge_integ_smallw_noise);
  tree->SetBranchAddress("charge_integ_largew_noise",  charge_integ_largew_noise);
  tree->SetBranchAddress("t_max",                t_max);
  tree->SetBranchAddress("t_max_frac30",         t_max_frac30);
  tree->SetBranchAddress("t_max_frac50",         t_max_frac50);
  tree->SetBranchAddress("t_at_threshold",       t_at_threshold);
  tree->SetBranchAddress("t_over_threshold",     t_over_threshold);

  // before loop



  //loop over entries
  for (Long64_t jentry=0; jentry<nentries; ++jentry){


//    if(jentry>1000)break;

    if (jentry % 5000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries );

    //readout the event                                                               
    tree->GetEntry(jentry);


    if( variable_name == "Wave_max")    h_variable->Fill( wave_max[4] );
    if( variable_name == "Pedestal")    h_variable->Fill( pedestal[4] );
    if( variable_name == "PedestalRMS") h_variable->Fill( pedestalRMS[4] );

  }// end event loop


  
}


void analyzer() 
{


TString variable_name; 

//variable_name = "Wave_max";
variable_name = "Pedestal";
//variable_name = "PedestalRMS";

const int N_runs = 3;

TH1F* h_variable[N_runs];

//std::string runN[N_runs] = {"3737","3751","3752"};
std::string runN[N_runs] = {"3656","3683","3688"};// pedestal run for pion beam 120um, 600V/600V

double Lbound, Hbound ;

if( variable_name == "Pedestal"   ){Lbound = 170; Hbound = 215;   }// used for pedestalRMS
if( variable_name == "PedestalRMS"){Lbound = 0; Hbound = 25;   }// used for pedestalRMS

int Nbins = Hbound - Lbound;

for (int i=0;i<N_runs;i++){

  TString  h_name = "h_"+ variable_name + "_run_" + runN[i];

  cout<<"h_name: "<< h_name << endl;
  h_variable[i] = new TH1F(h_name, h_name, Nbins , Lbound ,Hbound   );

}


Long64_t nentries[N_runs] = {0};

for (int i=0;i<N_runs;i++){

  Read_Tree( runN[i] , h_variable[i], nentries[i], variable_name );
  cout<<"nentries[i]: "<< nentries[i] << endl;

}


// TGraph and TGraphErrors


double mean_of_variable[N_runs] ={0};
double rms_of_variable[N_runs] ={0};
double Nentries[N_runs] = {0};
double ex[N_runs] ={0};

for (int i=0;i<N_runs;i++){
  mean_of_variable[i] = h_variable[i]->GetMean();
  rms_of_variable[i] = h_variable[i] ->GetRMS();
  Nentries[i] = nentries[i];
}

TGraph*       gr_of_N_run   = new TGraph(N_runs , Nentries , mean_of_variable );
TGraphErrors* grer_of_N_run = new TGraphErrors(N_runs , Nentries , mean_of_variable, ex, rms_of_variable );


//

TString path_name = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study/" ;
TString save_name;

// h_variable

save_name = "h_variable";
save_name = path_name + save_name + ".pdf";

TCanvas *c1 = new TCanvas("c1","c1",200,10,700,500);

TString h_x_label, h_y_label;

if( variable_name == "Pedestal"){
  h_x_label = "pedestal [ADC]";
  h_y_label = "number of events";
}

if( variable_name == "PedestalRMS"){
  h_x_label = "pedestalRMS [ADC]";
  h_y_label = "number of events";
}

for (int i=0;i<N_runs;i++){


  h_variable[i]->GetXaxis()->SetTitle(h_x_label);
  h_variable[i]->GetYaxis()->SetTitle(h_y_label);
  h_variable[i]->GetYaxis()->SetTitleOffset(1.3);

  c1->cd();
//  h_variable[i]->Draw();
  if( variable_name == "PedestalRMS"){ h_variable[i]->Draw(); }
  if( variable_name == "Pedestal")   { gStyle->SetOptFit(1111); h_variable[i]->Fit("gaus"); }

  if( i==0)         {c1->Print(save_name +"(");}
  if( i!=0 && i!=2 ){c1->Print(save_name     );}
  if( i==2)         {c1->Print(save_name +")");}

}


// different_run

save_name = "different_run";
save_name = path_name + save_name + ".pdf";

TString gr_title, gr_x_label, gr_y_label;
if( variable_name == "Pedestal"){
  gr_title   = "Pedestal in different runs";
  gr_x_label = "total number of events in that run";
  gr_y_label = "pedestal [ADC]";
}

if( variable_name == "PedestalRMS"){
  gr_title   = "PedestalRMS in different runs";
  gr_x_label = "total number of events in that run";
  gr_y_label = "pedestalRMS [ADC]";
}

//Lbound = 185; Hbound = 200;

gr_of_N_run->SetTitle(gr_title);
gr_of_N_run->GetXaxis()->SetTitle(gr_x_label);
gr_of_N_run->GetYaxis()->SetTitle(gr_y_label);
gr_of_N_run->GetYaxis()->SetTitleOffset(1.3);
gr_of_N_run->SetMarkerStyle(29);
gr_of_N_run->SetMarkerColor(2);
gr_of_N_run->SetMarkerSize(5);
gr_of_N_run->GetYaxis()->SetRangeUser(Lbound ,Hbound );

grer_of_N_run->SetTitle(gr_title);
grer_of_N_run->GetXaxis()->SetTitle(gr_x_label);
grer_of_N_run->GetYaxis()->SetTitle(gr_y_label);
grer_of_N_run->GetYaxis()->SetTitleOffset(1.3);
grer_of_N_run->SetMarkerStyle(20);
grer_of_N_run->SetMarkerColor(1);
grer_of_N_run->SetMarkerSize(2);
grer_of_N_run->GetYaxis()->SetRangeUser(Lbound ,Hbound );

TCanvas *c2 = new TCanvas("c2","c2",200,10,700,500);
c2->cd();
gr_of_N_run->Draw("AP");
c2->Print(save_name +"(");

c2->cd();
grer_of_N_run->Draw("AP");
c2->Print(save_name +")");

//TCanvas *c3 = new TCanvas("c3","c3",200,10,700,500);
//c3->cd();
//grer_of_N_run->Draw("AP");


}




