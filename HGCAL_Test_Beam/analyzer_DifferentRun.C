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

void SetStyle(TGraphErrors* grer_of_N_run_config, TString variable_name );

void Read_Tree(std::string runN, TH1F* h_variable, Long64_t &nentries, TString variable_name, int channel){

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


    if(jentry>1000)break;

    if (jentry % 5000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries );

    //readout the event                                                               
    tree->GetEntry(jentry);


    if( variable_name == "Pedestal")    h_variable->Fill( pedestal[channel] );
    if( variable_name == "PedestalRMS") h_variable->Fill( pedestalRMS[channel] );

  }// end event loop


  
}

// -----------------------------------------------------

TGraphErrors* Read_configuration(int channel, TString variable_name , const int N_runs_config  , std::string runN_config[],TGraphErrors* grer_of_N_run_config ){

  // cout test

  cout<<"inside Read_configuration"<< endl;
  cout<<"variable_name: "<< variable_name << endl;
  cout<<"N_runs_config: "<< N_runs_config << endl;

  for (int i=0;i<N_runs_config;i++){
    cout<<"runN_config[i]: "<< runN_config[i] << endl;
  }

  cout<< endl;

  // declare histogram  

  double Lbound, Hbound ;

  if( variable_name == "Pedestal"   ){Lbound = 50; Hbound = 500;   }// used for pedestalRMS
  if( variable_name == "PedestalRMS"){Lbound = 0  ; Hbound = 30 ;   }// used for pedestalRMS

  int Nbins = Hbound - Lbound;
  TH1F* h_variable[N_runs_config];

  for (int i=0;i<N_runs_config;i++){

    TString  h_name = "h_"+ variable_name + "_run_" + runN_config[i];

//    cout<<"h_name: "<< h_name << endl;
    h_variable[i] = new TH1F(h_name, h_name, Nbins , Lbound ,Hbound   );

  }

  // Read tree  
 
  Long64_t nentries[N_runs_config];

//  cout<<"channel: "<< channel << endl;
  TString run_number_save = "";

  for (int i=0;i<N_runs_config;i++){

    Read_Tree( runN_config[i] , h_variable[i], nentries[i], variable_name, channel );
//    cout<<"nentries[i]: "<< nentries[i] << endl;

    run_number_save = run_number_save +"_"+ runN_config[i]; 
  }

//  cout<<"run_number_save: "<< run_number_save << endl;

  // save histogram for check

/*
  TCanvas *c1 = new TCanvas("c1","c1",200,10,700,500);

  TString path_name = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study/" ;
  TString save_name;
  save_name = "h_variable";
  save_name = path_name + save_name + "_test_"+run_number_save +".pdf";


  for (int i=0;i<N_runs_config;i++){
     h_variable[i]->Draw();

     if( i==0)                             {c1->Print(save_name +"(");}
     else if( i==N_runs_config-1 )         {c1->Print(save_name +")");}
     else                                  {c1->Print(save_name     ); }
  }
*/


  // construct TGraphError 

  double mean_of_variable[N_runs_config];
  double rms_of_variable[N_runs_config];
  double Nentries[N_runs_config];
  double ex[N_runs_config];


  for (int i=0;i<N_runs_config;i++){
    mean_of_variable[i] = h_variable[i]->GetMean();
    rms_of_variable[i] = h_variable[i] ->GetRMS();
    Nentries[i] = nentries[i];
    ex[i] = 0;

//    cout<<"Nentries[i]: "<< Nentries[i] << endl;
//    cout<<"mean_of_variable[i]: "<< mean_of_variable[i] << endl;

  }

//  cout<<"mean_of_variable[0]: "<< mean_of_variable[0] << endl;

  grer_of_N_run_config = new TGraphErrors(N_runs_config , Nentries , mean_of_variable, ex, rms_of_variable );

  SetStyle( grer_of_N_run_config, variable_name );

  for (int i=0;i<N_runs_config;i++){
    delete h_variable[i];
  }

  return grer_of_N_run_config;
}

// -----------------------------------------------------

void SetStyle(TGraphErrors* grer_of_N_run_config, TString variable_name ){


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

  grer_of_N_run_config ->SetTitle(gr_title);
  grer_of_N_run_config ->GetXaxis()->SetTitle(gr_x_label);
  grer_of_N_run_config ->GetYaxis()->SetTitle(gr_y_label);
  grer_of_N_run_config ->GetYaxis()->SetTitleOffset(1.3);
  grer_of_N_run_config ->SetMarkerStyle(20);
  grer_of_N_run_config ->SetMarkerSize(2);



}

// -----------------------------------------------------






void analyzer_DifferentRun() 
{


TString variable_name; 
variable_name = "Pedestal";
//variable_name = "PedestalRMS";

// ---- pre define ----------- 

double x_array[2]={0}; double y_array[2]={0}; double x_err_array[2]={0}; double y_err_array[2]={0};

// decide the range in Y axis in gr_fake
if( variable_name == "Pedestal"   ){y_array[0] = 150; y_array[1] = 300 ;}
if( variable_name == "PedestalRMS"){y_array[0] = 0; y_array[1] = 25 ;}

// decide the range in X axis in gr_fake
x_array[0] = 9000 ; x_array[1] = 24000;
TGraphErrors* gr_fake = new TGraphErrors(2, x_array, y_array, x_err_array, y_err_array );
SetStyle( gr_fake, variable_name );

TString path_name = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study/" ;
TString save_name;

if( variable_name == "Pedestal"   ){save_name = "different_run_pedestal" ;}
if( variable_name == "PedestalRMS"){save_name = "different_run_pedestalRMS" ;}

save_name = path_name + save_name +".pdf";


int channel;// SiPad-x

// ----- SiPad1 -----

///*

const int   N_SiPad1 = 3;// number of configrations for SiPad-1
int         N_runs_SiPad1[N_SiPad1]={0};
std::string runN_SiPad1[N_SiPad1][5];

TGraphErrors* grer_of_N_run_SiPad1[N_SiPad1];

N_runs_SiPad1[0] = 5;
runN_SiPad1[0][0] = "3656";
runN_SiPad1[0][1] = "3683";
runN_SiPad1[0][2] = "3688";
runN_SiPad1[0][3] = "3693";
runN_SiPad1[0][4] = "3697";

N_runs_SiPad1[1] = 3;
runN_SiPad1[1][0] = "3666";
runN_SiPad1[1][1] = "3663";
runN_SiPad1[1][2] = "3670";
runN_SiPad1[1][3] = "";
runN_SiPad1[1][4] = "";

N_runs_SiPad1[2] = 2;
runN_SiPad1[2][0] = "3675";
runN_SiPad1[2][1] = "3679";
runN_SiPad1[2][2] = "";
runN_SiPad1[2][3] = "";
runN_SiPad1[2][4] = "";

channel = 4;// SiPad-1 

for(int i=0;i<N_SiPad1;i++){
  grer_of_N_run_SiPad1[i] = new TGraphErrors(2 , x_array, y_array, x_err_array, y_err_array );
  grer_of_N_run_SiPad1[i] = Read_configuration( channel ,variable_name , N_runs_SiPad1[i], runN_SiPad1[i], grer_of_N_run_SiPad1[i] );
}


TCanvas *c5 = new TCanvas("c5","c5",200,10,700,500);
c5->cd();
if( variable_name == "Pedestal"   ){ gr_fake->GetYaxis()->SetRangeUser(186 ,202 ); }
gr_fake->GetXaxis()->SetRangeUser(10000 ,23000 );
gr_fake->Draw("AP");

for(int i=0;i<N_SiPad1;i++){
  c5->cd();
  grer_of_N_run_SiPad1[i]->SetMarkerColor(i+1);
  grer_of_N_run_SiPad1[i]->Draw("P");
}


TLegend *leg = new TLegend(0.5,0.7,0.8,0.9);
leg->SetHeader("SiPad-1, un-irradiated");
leg->AddEntry( grer_of_N_run_SiPad1[0] , "120 #mu m,600V" ,"pl");
leg->AddEntry( grer_of_N_run_SiPad1[1] , "200 #mu m,600V" ,"pl");
leg->AddEntry( grer_of_N_run_SiPad1[2] , "300 #mu m,600V" ,"pl");
leg->Draw();

c5->Print(save_name+"(");

//*/

// --- SiPad3 ----------

///*

const int   N_SiPad3 = 7;// number of configrations for SiPad-3

int         N_runs_SiPad3[N_SiPad3]={0};
std::string runN_SiPad3[N_SiPad3][3];

TGraphErrors* grer_of_N_run_SiPad3[N_SiPad3];

N_runs_SiPad3[0] = 3;
runN_SiPad3[0][0] = "3656";
runN_SiPad3[0][1] = "3683";
runN_SiPad3[0][2] = "3688";

N_runs_SiPad3[1] = 1;
runN_SiPad3[1][0] = "3693";
runN_SiPad3[1][1] = "";
runN_SiPad3[1][2] = "";

N_runs_SiPad3[2] = 1;
runN_SiPad3[2][0] = "3697";
runN_SiPad3[2][1] = "";
runN_SiPad3[2][2] = "";

N_runs_SiPad3[3] = 1;
runN_SiPad3[3][0] = "3666";
runN_SiPad3[3][1] = "";
runN_SiPad3[3][2] = "";

N_runs_SiPad3[4] = 2;
runN_SiPad3[4][0] = "3663";
runN_SiPad3[4][1] = "3670";
runN_SiPad3[4][2] = "";

N_runs_SiPad3[5] = 1;
runN_SiPad3[5][0] = "3675";
runN_SiPad3[5][1] = "";
runN_SiPad3[5][2] = "";

N_runs_SiPad3[6] = 1;
runN_SiPad3[6][0] = "3679";
runN_SiPad3[6][1] = "";
runN_SiPad3[6][2] = "";


channel = 6;// SiPad-3 


for(int i=0;i<N_SiPad3;i++){
  grer_of_N_run_SiPad3[i] = new TGraphErrors(2 , x_array, y_array, x_err_array, y_err_array );
  grer_of_N_run_SiPad3[i] = Read_configuration( channel ,variable_name , N_runs_SiPad3[i], runN_SiPad3[i], grer_of_N_run_SiPad3[i] );
}


TCanvas *c6 = new TCanvas("c6","c6",200,10,700,500);
c6->cd();
if( variable_name == "Pedestal"   ){ gr_fake->GetYaxis()->SetRangeUser(200 ,216 ); }
gr_fake->GetXaxis()->SetRangeUser(10000 ,23000 );
gr_fake->Draw("AP");


for(int i=0;i<N_SiPad3;i++){
  c6->cd();
  grer_of_N_run_SiPad3[i]->SetMarkerColor(i+1);
  grer_of_N_run_SiPad3[i]->Draw("P");
}

TLegend *leg2 = new TLegend(0.5,0.6,0.8,0.9);
leg2->SetHeader("SiPad-3, irradiated");
leg2->AddEntry( grer_of_N_run_SiPad3[0] , "120 #mu m,600V" ,"pl");
leg2->AddEntry( grer_of_N_run_SiPad3[1] , "120 #mu m,700V" ,"pl");
leg2->AddEntry( grer_of_N_run_SiPad3[2] , "120 #mu m,800V" ,"pl");
leg2->AddEntry( grer_of_N_run_SiPad3[3] , "200 #mu m,600V" ,"pl");
leg2->AddEntry( grer_of_N_run_SiPad3[4] , "200 #mu m,800V" ,"pl");
leg2->AddEntry( grer_of_N_run_SiPad3[5] , "300 #mu m,600V" ,"pl");
leg2->AddEntry( grer_of_N_run_SiPad3[6] , "300 #mu m,800V" ,"pl");
leg2->Draw();

c6->Print(save_name+")");
//*/




// ------


}




