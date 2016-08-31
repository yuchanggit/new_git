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

// version of the used recoTrees 
std::string v_recoTree;

// input root path
std::string inputFolder;

// save root path
TString root_name;
TString root_save_path;

// save pdf path
TString save_path = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study_2016June/";

// max event to read in ntuples
int max_event;


void Read_Tree(std::string runN[]);

// -----------------------------------------------------

//void step1_analyzer_MakeHisto()
void step1_analyzer_MakeHisto( std::string v_recoTree_temp, int max_event_temp )
{
v_recoTree = v_recoTree_temp;

root_name = "Pion_300um_combine_" + v_recoTree + ".root";
root_save_path = "root_files/" + root_name;

inputFolder = "/store/group/upgrade/HGCAL/TimingTB_H2_Apr2016/June2016/" + v_recoTree + "/" ;


max_event = max_event_temp;


// for June, Pion, 300um 
const int N_runs = 5;
std::string runN[N_runs];

// d = 300 um
runN[0] = "4298"; 
runN[1] = "4299";
runN[2] = "4300";
runN[3] = "4301";
runN[4] = "4302";

Read_Tree(runN);


}

// -----------------------------------------------------

void Read_Tree(std::string runN[] ){


  TChain* tree = new TChain("H4treeReco"); 

  for(unsigned int i=0;i<= runN->size() ;i++){

    cout<<"i: "<< i <<" runN[i]: "<< runN[i] << endl;
    tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN[i]+".root").c_str());
  }

  Long64_t nentries = tree->GetEntries();
  std::cout << " Tree loaded events = " << nentries << std::endl;


  // flag decide to use 0-50 or 0-150 for wave_aroundPed 

  TString V_RecoTree = v_recoTree;
  cout<<"V_RecoTree: "<< V_RecoTree << endl;
  int flag_RecoTree = 0;
  cout<<"before flag_RecoTree: "<< flag_RecoTree << endl;

  if (   !V_RecoTree.Contains("in5_145") ) flag_RecoTree = 1;// 0-50
  if (    V_RecoTree.Contains("in5_145") ) flag_RecoTree = 2;// 0-150

  cout<<"after flag_RecoTree: "<< flag_RecoTree << endl;


  //Tree variables

  UInt_t nwc;
  Float_t wc_recox[16], wc_recoy[16];
  UInt_t maxch;
  Float_t group[100],ch[100];
  Float_t pedestal[100], pedestalRMS[100], pedestalSlope[100];
  Float_t wave_max[100], wave_max_aft[100], wave_aroundmax[100][50], time_aroundmax[100][50];

  Float_t wave_aroundPed1[100][50] , time_aroundPed1[100][50];
  Float_t wave_aroundPed2[100][150], time_aroundPed2[100][150];

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

  if(flag_RecoTree ==1){
    tree->SetBranchAddress("wave_aroundPed",       wave_aroundPed1);
    tree->SetBranchAddress("time_aroundPed",       time_aroundPed1);
  }

  if(flag_RecoTree ==2){
    tree->SetBranchAddress("wave_aroundPed",       wave_aroundPed2);
    tree->SetBranchAddress("time_aroundPed",       time_aroundPed2);
  }

//  tree->SetBranchAddress("wave_aroundPed",       wave_aroundPed);
//  tree->SetBranchAddress("time_aroundPed",       time_aroundPed);

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

  TString Pad_name[7] = {"Trigger","SiPad1","SiPad2","SiPad3","SiPad4","SiPad5","SiPad6"};
  TString h_name;

  TH1F* h_wave_max[7];
  TH1F* h_pedestal[7];
  TH1F* h_pedestalRMS[7];
  TH2F* h_wave_max_vs_pedestalRMS[7];

  TH1F* h_mean_from_aroundPed[7];
  TH1F* h_RMS_from_aroundPed[7];
  TH1F* h_max_from_aroundPed[7];
  TH1F* h_min_from_aroundPed[7];
  TH1F* h_max_subtract_mean_from_aroundPed[7];
  TH1F* h_mean_subtract_min_from_aroundPed[7];

  TH1F* h_pedestalSlope[7];

  for(int i=0;i<7;i++){

    h_name = "h_wave_max_"    + Pad_name[i];
    h_wave_max[i]    = new TH1F(h_name, h_name, 2000  , -1000 ,1000   );

    h_name = "h_pedestal_"    + Pad_name[i];
    h_pedestal[i]    = new TH1F(h_name, h_name, 1000  , 3000 , 4000  );

    h_name = "h_pedestalRMS_" + Pad_name[i];
    h_pedestalRMS[i] = new TH1F(h_name, h_name, 100  , 0 , 100   );

    h_name = "h_wave_max_vs_pedestalRMS_" + Pad_name[i];
    h_wave_max_vs_pedestalRMS[i] = new TH2F(h_name, h_name, 300  , 0 , 300, 100  , 0 , 100   );



    h_name = "h_mean_from_aroundPed_"    + Pad_name[i];
    h_mean_from_aroundPed[i] = new TH1F(h_name, h_name, 1000  , 3000 ,4000   );

    h_name = "h_RMS_from_aroundPed_"    + Pad_name[i];
    h_RMS_from_aroundPed[i] = new TH1F(h_name, h_name, 100  , 0 ,100   );

    h_name = "h_max_from_aroundPed_"    + Pad_name[i];
    h_max_from_aroundPed[i] = new TH1F(h_name, h_name, 1000  , 3000 ,4000   );

    h_name = "h_min_from_aroundPed_"    + Pad_name[i];
    h_min_from_aroundPed[i] = new TH1F(h_name, h_name, 1000  , 3000 ,4000   );

    h_name = "h_max_subtract_mean_from_aroundPed_"    + Pad_name[i];
    h_max_subtract_mean_from_aroundPed[i] = new TH1F(h_name, h_name, 1000  , 0 ,1000   );

    h_name = "h_mean_subtract_min_from_aroundPed_"    + Pad_name[i];
    h_mean_subtract_min_from_aroundPed[i] = new TH1F(h_name, h_name, 1000  , 0 ,1000   );

    h_name = "h_pedestalSlope_"    + Pad_name[i];
    h_pedestalSlope[i] = new TH1F(h_name, h_name, 80  , -10 ,10   );

  }


  int N_plot_aroundPed =10;
  int counter = 0;
  TGraph* gr_aroundPed[N_plot_aroundPed][7]; 
  TH1F* h_wave_aroundPed[N_plot_aroundPed][7];
  

  //loop over entries
  for (Long64_t jentry=0; jentry<nentries; ++jentry){

    if(max_event!=-1 && jentry>max_event)break;
//    if(jentry>1000)break;

    if (jentry % 5000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries );

    //readout the event                                                               
    tree->GetEntry(jentry);

    for(int i=1;i<7;i++){

      h_wave_max[i]   ->Fill( wave_max[i]   );
      h_pedestal[i]   ->Fill( pedestal[i]   );
      h_pedestalRMS[i]->Fill( pedestalRMS[i]);
      h_wave_max_vs_pedestalRMS[i]->Fill( wave_max[i] , pedestalRMS[i]);    

    }
    
    // save time/wave_max aroundPed

    if( counter< N_plot_aroundPed){

      double Time_aroundPed[7][50]; double Wave_aroundPed[7][50];

      for(int i=1;i<7;i++){    
        
        int temp_index = jentry;
        TString temp = Form("the %d-th event" , temp_index ); 
        TString h_name2 = "h_wave_aroundPed_"    + Pad_name[i] + "," + temp;
        h_wave_aroundPed[counter][i] = new TH1F(h_name2, h_name2, 1000  , 3000 , 4000  );


        if( flag_RecoTree==1){ // 0-50 samples
          for(int j=0;j<50;j++){

            Time_aroundPed[i][j] = time_aroundPed1[i][j] * 1000000000; 
            Wave_aroundPed[i][j] = wave_aroundPed1[i][j];

            h_wave_aroundPed[counter][i]->Fill(  wave_aroundPed1[i][j]  );
          }

          gr_aroundPed[counter][i] = new TGraph(50, Time_aroundPed[i] , Wave_aroundPed[i] );	  
          TString gr_name = "wave around Ped," + Pad_name[i] + "," + temp;
          gr_aroundPed[counter][i]->SetTitle(gr_name);
        }


        if( flag_RecoTree==2){ // 0-150 samples
          for(int j=0;j<150;j++){

            Time_aroundPed[i][j] = time_aroundPed2[i][j] * 1000000000;
            Wave_aroundPed[i][j] = wave_aroundPed2[i][j];

            h_wave_aroundPed[counter][i]->Fill(  wave_aroundPed2[i][j]  );
          }

          gr_aroundPed[counter][i] = new TGraph(150, Time_aroundPed[i] , Wave_aroundPed[i] );
          TString gr_name = "wave around Ped," + Pad_name[i] + "," + temp;
          gr_aroundPed[counter][i]->SetTitle(gr_name);
        }

      }// end loop i

      counter++;
    }

    // use wave aroundPed to mimic pedestal run

    double mean_aroundPed[7];
    double RMS_aroundPed[7];
    double max_aroundPed[7];
    double min_aroundPed[7];

    for(int i=1;i<7;i++){

      TH1F* h_aroundPed = new TH1F("", "", 1000  , 3000 , 4000  ); 

      if( flag_RecoTree==1){ // 0-50 samples
        for(int j=0;j<50;j++){
          if(j<5 || j>45) continue;
          h_aroundPed->Fill(  wave_aroundPed1[i][j]  );
        }
      }     
 
      if( flag_RecoTree==2){ // 0-150 samples
        for(int j=0;j<150;j++){
          if(j<5 || j>145) continue;
          h_aroundPed->Fill(  wave_aroundPed2[i][j]  );
        }
      }

      mean_aroundPed[i] = h_aroundPed->GetMean(); 
      RMS_aroundPed[i]  = h_aroundPed->GetRMS();
      int  binmax = h_aroundPed->FindLastBinAbove();
      int  binmin = h_aroundPed->FindFirstBinAbove();// for p-type the minimum is the maximum after reverse the wave form
      max_aroundPed[i]  = h_aroundPed->GetXaxis()->GetBinCenter(binmax) ;
      min_aroundPed[i]  = h_aroundPed->GetXaxis()->GetBinCenter(binmin) ;

      h_mean_from_aroundPed[i]  -> Fill( mean_aroundPed[i]   );
      h_RMS_from_aroundPed[i]   -> Fill( RMS_aroundPed[i]   );
      h_max_from_aroundPed[i]   -> Fill( max_aroundPed[i]   );
      h_min_from_aroundPed[i]   -> Fill( min_aroundPed[i]   );
      h_max_subtract_mean_from_aroundPed[i]  -> Fill( max_aroundPed[i] - mean_aroundPed[i]   );
      h_mean_subtract_min_from_aroundPed[i]  -> Fill( mean_aroundPed[i]- min_aroundPed[i]   );
    }

//    cout<<"mean_aroundPed[1]: "<< mean_aroundPed[1]<< endl;
//    cout<<"pedestal[1]"<< pedestal[1] << endl; 

    // pedestalSlope
//    cout<<"pedestalSlope[1]"<< pedestalSlope[1] << endl;
    for(int i=1;i<7;i++){
      h_pedestalSlope[i]->Fill(   pedestalSlope[i] );
    }

  }// end event loop


  // wave aroundPed set style


  for(int counter_index =0; counter_index<N_plot_aroundPed; counter_index++){

    for(int i=1;i<7;i++){ 

      gr_aroundPed[counter_index][i]->GetXaxis()->SetTitle("time [ns]");
      gr_aroundPed[counter_index][i]->GetYaxis()->SetTitle("wave amplitude [ADC]");
      gr_aroundPed[counter_index][i]->GetYaxis()->SetTitleOffset(1.3);

      h_wave_aroundPed[counter_index][i]->GetXaxis()->SetRangeUser(3600, 3800);
    }
  }



  // draw & save in pdf
  TCanvas *c1 = new TCanvas("c1","",200,10,700,500);
  TCanvas *c2 = new TCanvas("c2","",200,10,700,500);

  TString save_name = save_path + "wave_aroundPed_"+ v_recoTree +".pdf";

  for(int counter_index =0; counter_index<N_plot_aroundPed; counter_index++){

    for(int i=1;i<7;i++){

      c1->cd();
      gr_aroundPed[counter_index][i]->Draw();

      c2->cd();
      h_wave_aroundPed[counter_index][i]->Draw();

      if(counter_index==0 && i==1  )               {  c1->Print( save_name +"("); c2->Print( save_name );}
      else if(counter_index==N_plot_aroundPed-1 && i==6){  c1->Print( save_name );     c2->Print( save_name +")");}
      else {c1->Print( save_name ); c2->Print( save_name );}

      c1->Clear(); c2->Clear();
    }
  }


  // save histogram in ROOT file 

  TFile* outFile = new TFile(root_save_path,"recreate"); 

  for(int i=1;i<7;i++){

    h_wave_max_vs_pedestalRMS[i]->GetYaxis()->SetTitle("wave_max [ADC]");
    h_wave_max_vs_pedestalRMS[i]->GetXaxis()->SetTitle("pedestalRMS [ADC]");

    h_wave_max[i]   ->Write();
    h_pedestal[i]   ->Write();
    h_pedestalRMS[i]->Write();
    h_wave_max_vs_pedestalRMS[i]->Write();

    h_mean_from_aroundPed[i]  ->Write();
    h_RMS_from_aroundPed[i]   ->Write();
    h_max_from_aroundPed[i]   ->Write();
    h_min_from_aroundPed[i]   ->Write();
    h_max_subtract_mean_from_aroundPed[i] ->Write();
    h_mean_subtract_min_from_aroundPed[i] ->Write();

    h_pedestalSlope[i] ->Write();

  }



  // delete pointer 
  delete outFile;

  for(int i=0;i<7;i++){

    delete h_wave_max[i];
    delete h_pedestal[i];
    delete h_pedestalRMS[i];
    delete h_wave_max_vs_pedestalRMS[i];
  }



}// end Read_Tree



