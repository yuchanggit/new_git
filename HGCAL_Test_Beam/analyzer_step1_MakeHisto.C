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


void Read_Tree(std::string runN);

// -----------------------------------------------------

void analyzer_step1_MakeHisto()
{


std::string runN;

// d = 120 um 
runN = "3656"; Read_Tree(runN);
runN = "3683"; Read_Tree(runN);
runN = "3688"; Read_Tree(runN);
runN = "3693"; Read_Tree(runN);
runN = "3697"; Read_Tree(runN);

// d = 200 um
runN = "3666"; Read_Tree(runN);
runN = "3663"; Read_Tree(runN);
runN = "3670"; Read_Tree(runN);

// d = 300 um
runN = "3675"; Read_Tree(runN);
runN = "3679"; Read_Tree(runN);

}

// -----------------------------------------------------

void Read_Tree(std::string runN ){

  std::string inputFolder = "/store/group/upgrade/HGCAL/TimingTB_H2_Apr2016/recoTrees/";

  TChain* tree = new TChain("H4treeReco"); 
  tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN+".root").c_str());

  Long64_t nentries = tree->GetEntries();
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

  TString Pad_name[7] = {"Trigger","SiPad6","SiPad5","SiPad4","SiPad1","SiPad2","SiPad3"};
  TString h_name;

  TH1F* h_wave_max[7];
  TH1F* h_pedestal[7];
  TH1F* h_pedestalRMS[7];

  for(int i=0;i<7;i++){

    h_name = "h_wave_max_"    + Pad_name[i];
    h_wave_max[i]    = new TH1F(h_name, h_name, 2000  , -1000 ,1000   );

    h_name = "h_pedestal_"    + Pad_name[i];
    h_pedestal[i]    = new TH1F(h_name, h_name, 300  , 0 , 300  );

    h_name = "h_pedestalRMS_" + Pad_name[i];
    h_pedestalRMS[i] = new TH1F(h_name, h_name, 60  , 0 , 60   );

  }


  //loop over entries
  for (Long64_t jentry=0; jentry<nentries; ++jentry){

//    if(jentry>1000)break;

    if (jentry % 5000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries );

    //readout the event                                                               
    tree->GetEntry(jentry);

    for(int i=1;i<7;i++){

        h_wave_max[i]   ->Fill( wave_max[i]   );
        h_pedestal[i]   ->Fill( pedestal[i]   );
        h_pedestalRMS[i]->Fill( pedestalRMS[i]);
    }
    

  }// end event loop




  // save histogram
  TString root_name = "root_files/"+ runN + ".root";
  TFile* outFile = new TFile(root_name,"recreate"); 

  for(int i=1;i<7;i++){

    h_wave_max[i]   ->Write();
    h_pedestal[i]   ->Write();
    h_pedestalRMS[i]->Write();

  }



  // delete pointer 
  delete outFile;

  for(int i=0;i<7;i++){

    delete h_wave_max[i];
    delete h_pedestal[i];
    delete h_pedestalRMS[i];

  }

}// end Read_Tree



