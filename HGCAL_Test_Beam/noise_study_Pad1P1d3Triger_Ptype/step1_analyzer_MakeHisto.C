// g++ -Wall -o analyzer `root-config --cflags --glibs` analyzer.cpp
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>

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

std::string ntuple_path = "/store/group/upgrade/HGCAL/TimingTB_H2_Apr2016/June2016";

void Read_Tree(std::string folder_name , const int N_runs ,std::string runN[], int max_event_to_read);

// -----------------------------------------------------

void step1_analyzer_MakeHisto(std::string folder_name, int max_event_to_read)
{

  cout<<"folder_name: "<< folder_name << endl;
  cout<<"max_event_to_read(-1 mean full statistics): "<< max_event_to_read << endl;

  // for p-type (2016 June), Electron run, 120um 
  if ( folder_name.find("fit100Ele") != std::string::npos ){

    const int N_runs1 = 10;
    std::string runN1[N_runs1]={"4174","4175","4176","4178","4179","4180","4181","4182","4183","4184"};
    Read_Tree( folder_name ,N_runs1, runN1, max_event_to_read );

  } 

  // for p-type (2016 June), Electron run, 200um 
  if ( folder_name.find("fit200Ele") != std::string::npos ){

    const int N_runs2 = 7;
    std::string runN2[N_runs2]={"4187","4195","4196","4197","4199","4200","4202"};
    Read_Tree( folder_name ,N_runs2, runN2, max_event_to_read );

  }


  // for p-type (2016 June), Electron run, 320um 
  if ( folder_name.find("fit300Ele") != std::string::npos ){

    const int N_runs3 = 9;
    std::string runN3[N_runs3]={"4203","4204","4205","4206","4207","4208","4209","4210","4211"};
    Read_Tree( folder_name ,N_runs3, runN3, max_event_to_read );

  }

  return;
}

// -----------------------------------------------------

void Read_Tree(std::string folder_name ,const int N_runs , std::string runN[], int max_event_to_read ){

  std::string inputFolder = ntuple_path + folder_name ;
  std::cout <<"inputFolder: "<< inputFolder << endl;

  TChain* tree = new TChain("H4treeReco"); 

  for( int i=0;i<N_runs  ;i++){
    cout<<"i: "<< i <<" runN[i]: "<< runN[i] << endl;
    tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN[i]+".root").c_str());
  }

  Long64_t nentries = tree->GetEntries();
  std::cout << " Tree loaded events = " << nentries << std::endl;



  //Tree variables

  UInt_t nwc;
  Float_t wc_recox[16], wc_recoy[16];
  UInt_t maxch;
  Float_t group[100],ch[100];
  Float_t pedestal[100], pedestalRMS[100], pedestalSlope[100];
  Float_t wave_max[100], wave_max_aft[100], wave_aroundmax[100][50], time_aroundmax[100][50];
  Float_t wave_aroundPed[100][50] , time_aroundPed[100][50];
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
  tree->SetBranchAddress("wave_aroundPed",       wave_aroundPed);
  tree->SetBranchAddress("time_aroundPed",       time_aroundPed);
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

  TH1F* h_pedestal[7];
  TH1F* h_pedestalRMS[7];
  TH1F* h_charge_integ_largew_noise[7];

  TString h_name;

  for(int i=0;i<7;i++){

    h_name = Form("h_pedestal_ch%d" , i );
    h_pedestal[i]    = new TH1F(h_name, h_name, 1000  , 3000 , 4000  );

    h_name = Form("h_pedestalRMS_ch%d" , i );
    h_pedestalRMS[i]    = new TH1F(h_name, h_name, 100  , 0 , 100  );

    h_name = Form("h_charge_integ_largew_noise_ch%d" , i );
    h_charge_integ_largew_noise[i]    = new TH1F(h_name, h_name, 2000  , -1000 , 1000  );

  }

  //loop over entries
  for (Long64_t jentry=0; jentry<nentries; ++jentry){

    if(max_event_to_read !=-1 && jentry>max_event_to_read)break;

//    if (jentry % 5000 == 0)
    if (jentry % 50000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries );

    //readout the event                                                               
    tree->GetEntry(jentry);

    for(int i=1;i<7;i++){
      h_pedestal[i]->Fill( pedestal[i] );
      h_pedestalRMS[i]->Fill( pedestalRMS[i] );
      h_charge_integ_largew_noise[i]->Fill( charge_integ_largew_noise[i]  );
    }

  }// end event loop



  // save histogram in ROOT file 
  
  TString root_name; 

  if( folder_name.find("SiPad1Trigger") != std::string::npos ){
    if( folder_name.find("fit100Ele") != std::string::npos )root_name = "Pad1Tri_Ele120um.root";
    if( folder_name.find("fit200Ele") != std::string::npos )root_name = "Pad1Tri_Ele200um.root";
    if( folder_name.find("fit300Ele") != std::string::npos )root_name = "Pad1Tri_Ele320um.root";
  }
  else if( folder_name.find("SiPad3Trigger") != std::string::npos ){
    if( folder_name.find("fit100Ele") != std::string::npos )root_name = "Pad3Tri_Ele120um.root";
    if( folder_name.find("fit200Ele") != std::string::npos )root_name = "Pad3Tri_Ele200um.root";
    if( folder_name.find("fit300Ele") != std::string::npos )root_name = "Pad3Tri_Ele320um.root";
  }

  TString root_save_path = "root_files/" + root_name;


  TFile* outFile = new TFile(root_save_path,"recreate");

  for(int i=1;i<7;i++){
    h_pedestal[i]  ->Write(); 
    h_pedestalRMS[i]  ->Write();
    h_charge_integ_largew_noise[i] ->Write();
  }

  for(int i=0;i<7;i++){
    delete h_pedestal[i];
    delete h_pedestalRMS[i];
    delete h_charge_integ_largew_noise[i];
  }

  delete outFile;

}// end Read_Tree



