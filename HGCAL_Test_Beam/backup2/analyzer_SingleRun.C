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


TH1F*  Read_Tree(std::string runN, TH1F* h_variable, TString variable_name, int start_Event, int end_Event){

  std::string inputFolder = "/store/group/upgrade/HGCAL/TimingTB_H2_Apr2016/recoTrees/";

  TChain* tree = new TChain("H4treeReco"); 
  tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN+".root").c_str());

  Long64_t nentries = tree->GetEntries();
  std::cout << " Tree loaded events = " << nentries << std::endl;

  double Lbound = start_Event; 
  double Hbound = end_Event; if(end_Event == -1){Hbound = nentries;}
 
  int Nbins = Hbound - Lbound;

  TString  h_name = "h_"+ variable_name + "_run_" + runN;
  h_variable = new TH1F(h_name, h_name, Nbins , Lbound ,Hbound   );


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


    if(jentry < Lbound   )continue; 
    if(jentry > Hbound   )break;

    if (jentry % 5000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries );

    //readout the event                                                               
    tree->GetEntry(jentry);


    if( variable_name == "Pedestal") {   

        int bin_index = jentry - start_Event+1;
	h_variable->SetBinContent( bin_index  ,pedestal[4]    );
        h_variable->SetBinError  ( bin_index  ,pedestalRMS[4] );

    }

//    if(jentry==0)cout<<"jentry=0, pedestal[4] :"<< pedestal[4] << endl;
//    if(jentry==1)cout<<"jentry=1, pedestal[4] :"<< pedestal[4] << endl;
//    if(jentry==2)cout<<"jentry=2, pedestal[4] :"<< pedestal[4] << endl;

  }// end event loop

  return h_variable;
  
}


TH1F*  Read_Tree_average(std::string runN, TH1F* h_variable, TString variable_name, 
int start_Event, int end_Event, int Nbins){

  std::string inputFolder = "/store/group/upgrade/HGCAL/TimingTB_H2_Apr2016/recoTrees/";

  TChain* tree = new TChain("H4treeReco");
  tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN+".root").c_str());

  Long64_t nentries = tree->GetEntries();
  std::cout << " Tree loaded events = " << nentries << std::endl;

  double Lbound = start_Event;
  double Hbound = end_Event; if(end_Event == -1){Hbound = nentries;}

//  int Nbins = Hbound - Lbound;

  TString  h_name = "h_"+ variable_name + "_run_" + runN;
  h_variable = new TH1F(h_name, h_name, Nbins , Lbound ,Hbound   );

  int Bin_width = (Hbound - Lbound) / Nbins; 
  cout<<"Bin_width: "<< Bin_width << endl;


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
 
  double sum =0;
  double sum_uncert =0;
  int histo_index =0;

  //loop over entries

  for (Long64_t jentry=0; jentry<nentries; ++jentry){

    if(jentry < Lbound   )continue;
    if(jentry > Hbound   )break;

    if (jentry % 5000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries );

    //readout the event  
    tree->GetEntry(jentry);

    sum        = sum        + pedestal[4]    ;
    sum_uncert = sum_uncert + pedestalRMS[4] ;

    if( (jentry+1) % Bin_width == 0){

        double average        = sum/Bin_width;
        double average_uncert = sum_uncert/Bin_width;

        int bin_index = histo_index +1;
        h_variable->SetBinContent( bin_index  , average       );
        h_variable->SetBinError  ( bin_index  , average_uncert);

        sum = 0;
        sum_uncert = 0;
        histo_index++; 
    }


  }// end event loop

  return h_variable;

}

void histo_style(TH1F* h_variable){

  h_variable->GetYaxis()->SetRangeUser(150 ,250 );
  h_variable->SetMarkerStyle(20);
  h_variable->SetMarkerColor(2);
  h_variable->SetMarkerSize(1);

  h_variable->GetXaxis()->SetTitle("Event Number");
  h_variable->GetYaxis()->SetTitle("Pedestal and PedestalRMS [ADC]");
  h_variable->GetYaxis()->SetTitleOffset(1.3);

  gStyle->SetOptStat(11);


}
        

void analyzer_SingleRun()
{


TString variable_name; 

variable_name = "Pedestal";


std::string runN;
runN = "3656";

int start_Event, end_Event; 
start_Event =        0;
//end_Event   =      100;
//end_Event   =     1000;
end_Event   =     -1;// full statistic

TH1F* h_variable;
h_variable = new TH1F("h_test","", 10, 0 , 10);
h_variable = Read_Tree( runN , h_variable , variable_name, start_Event, end_Event );
histo_style( h_variable );

// for average 

int Nbins ;

Nbins = 10;
TH1F* h_variable_average1;
h_variable_average1 = new TH1F("h_test_average1","", 10, 0 , 10);
h_variable_average1 = Read_Tree_average( runN , h_variable_average1 , variable_name, start_Event, end_Event, Nbins );

histo_style( h_variable_average1 );

Nbins = 50;
TH1F* h_variable_average2;
h_variable_average2 = new TH1F("h_test_average2","", 10, 0 , 10);
h_variable_average2 = Read_Tree_average( runN , h_variable_average2 , variable_name, start_Event, end_Event, Nbins );

histo_style( h_variable_average2 );

Nbins = 100;
TH1F* h_variable_average3;
h_variable_average3 = new TH1F("h_test_average3","", 10, 0 , 10);
h_variable_average3 = Read_Tree_average( runN , h_variable_average3 , variable_name, start_Event, end_Event, Nbins );

histo_style( h_variable_average3 );


// fit linearly 
TF1 *myfit = new TF1("myfit","[0]*x + [1]", 170, 220);
myfit->SetParName(0,"slope");
myfit->SetParName(1,"constant");
myfit->SetParameter(0,   0 );
myfit->SetParameter(1, 193 );
myfit->SetLineColor(8);
myfit->SetLineWidth(3);
gStyle->SetOptFit(1111);

TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
leg->SetHeader("fit with y=ax+b");

// draw and save
TString path_name = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study/" ;
TString save_name = "single_run_pedestal";
save_name = path_name + save_name + ".pdf";


TCanvas *c1 = new TCanvas("c1","c1",200,10,700,500);
c1->cd();

h_variable->Draw("E0");
c1->Print(save_name + "(");

h_variable_average1->Draw("E0");
h_variable_average1->Fit("myfit");
leg->Draw();
c1->Print(save_name );

h_variable_average2->Draw("E0");
h_variable_average2->Fit("myfit");
leg->Draw();
c1->Print(save_name );

h_variable_average3->Draw("E0");
h_variable_average3->Fit("myfit");
leg->Draw();
c1->Print(save_name + ")");


//TCanvas *c2 = new TCanvas("c2","c2",200,10,700,500);
//c2->cd();
//h_variable_average2->Draw("E0");
//h_variable_average2->Fit("myfit");

//cout<<"myfit->GetParameter(0): "<< myfit->GetParameter(0) << endl;
//cout<<"myfit->GetParameter(1): "<< myfit->GetParameter(1) << endl;

}




