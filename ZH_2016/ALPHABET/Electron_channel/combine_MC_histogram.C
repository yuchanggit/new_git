#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <deque>
#include <list>

#include <TPaveStats.h>
#include <TH1D.h>
#include <TFile.h>
#include <TF1.h>
#include <TPad.h>
#include <TFile.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TTree.h>
#include "TObject.h"
#include "TColor.h"
#include "TFile.h"
#include "TMarker.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TString.h"
#include "TMath.h"

const int nMC =9;   // number of MC background to combine 
const int nHisto =6;// number of histogram to add 

void combine_MC_histogram(){

  // open MC ROOT file and its histogram

  TString root_name[nMC];
  
  root_name[0] = "DYJetsToLL_M-50_HT-100to200_13TeV_histogram.root";
  root_name[1] = "DYJetsToLL_M-50_HT-200to400_13TeV_histogram.root";
  root_name[2] = "DYJetsToLL_M-50_HT-400to600_13TeV_histogram.root";
  root_name[3] = "DYJetsToLL_M-50_HT-600toInf_13TeV_histogram.root";
  root_name[4] = "TT_TuneCUETP8M1_13TeV_histogram.root";
  root_name[5] = "WW_TuneCUETP8M1_13TeV_histogram.root";
  root_name[6] = "WZ_TuneCUETP8M1_13TeV_histogram.root";
  root_name[7] = "ZZ_TuneCUETP8M1_13TeV_histogram.root";
  root_name[8] = "ZH_HToBB_ZToLL_M125_13TeV_amcatnlo_histogram.root";

  TFile* file[nMC];
  TH1F*  histo[nMC][nHisto];

  TString histo_name[nHisto];

  histo_name[0] = "h_passDoubleBTagger_Jmass";
  histo_name[1] = "h_passDoubleBTagger_Jmass_wideBinning";
  histo_name[2] = "h_passDoubleBTagger_Jmass_wideBinning_diff";
  histo_name[3] = "h_failDoubleBTagger_Jmass";
  histo_name[4] = "h_failDoubleBTagger_Jmass_wideBinning";
  histo_name[5] = "h_failDoubleBTagger_Jmass_wideBinning_diff";

  TH1F*  h_totalEv[nMC];

  for(int i=0; i<nMC; i++){
    root_name[i] = "output_root/" + root_name[i];
    file[i] = TFile::Open( root_name[i] );

    for(int j=0; j<nHisto; j++ ){
      histo[i][j]  = (TH1F*)file[i] ->FindObjectAny( histo_name[j] );    
      h_totalEv[i] = (TH1F*)file[i] ->FindObjectAny("h_totalEv");
    }
  }

  // Provide the weight

//  double Lumi = 1.0;// 1/pb 
  double Lumi = 12700;// 12.7/fb


  double Xsec[nMC], nTotal[nMC], Weight[nMC];

  Xsec[0] = 147.40 *1.23;// DYHt100to200  
  Xsec[1] =  41    *1.23;// DYHt200to400
  Xsec[2] =   5.678*1.23;// DYHt400to600
  Xsec[3] =   2.198*1.23;// DYHt600toInf

  Xsec[4] = 831.76;      // TTbar

  Xsec[5] =  12.178;     // WW
  Xsec[6] =  63.21;      // WZ
  Xsec[7] =  16.523;     // ZZ

  Xsec[8] =   0.05;      // ZH amcatnlo


  for(int i=0; i<nMC; i++){
    nTotal[i] = h_totalEv[i]->Integral(); 
    Weight[i] = Lumi * Xsec[i] / nTotal[i] ;
  }


  // Scale each MC to same luminosity and Add together 

  for(int i=0; i<nMC; i++){
    for(int j=0; j<nHisto; j++ ){
      histo[i][j] -> Sumw2();
      histo[i][j] -> Scale( Weight[i] );
    }
  }


  TH1F* h_MC_combine[nMC];

  for(int j=0; j<nHisto; j++ ){
    h_MC_combine[j] = (TH1F*) histo[0][j] ->Clone( histo_name[j]); 
    h_MC_combine[j] -> Reset();
    h_MC_combine[j] -> Sumw2();

    for(int i=0; i<nMC; i++){

      if(i>3) continue; // remove other minor background
      h_MC_combine[j] -> Add( histo[i][j] );
    }
  }



  // Add Ratio plot 


  TH1F* h_Ratio = (TH1F*) h_MC_combine[0] ->Clone("h_Ratio");
  h_Ratio ->Sumw2();
  h_Ratio ->Divide( h_MC_combine[3] );
  h_Ratio ->SetTitle("h_Ratio");


  TH1F* h_Ratio_wideBinning = (TH1F*) h_MC_combine[1] ->Clone("h_Ratio_wideBinning");
  h_Ratio_wideBinning ->Sumw2();
  h_Ratio_wideBinning ->Divide( h_MC_combine[4] );
  h_Ratio_wideBinning ->SetTitle("h_Ratio_wideBinning");


  // Save combined histogram in ROOT file 

  TString save_path = "output_root/MC_combine_histogram.root";
  TFile* outFile = new TFile( save_path , "recreate");

  for(int j=0; j<nHisto; j++ ){
      h_MC_combine[j] ->Write();
  }

  h_Ratio  	      ->Write();
  h_Ratio_wideBinning ->Write();


  outFile->Write();
  delete outFile;



/*
  TCanvas *c_test = new TCanvas("c_test","c_test",10,10,800,600);
  c_test->cd();
  histo[4][3]->Draw();
  h_totalEv[0]->Draw();
  h_MC_combine[1] ->Draw();
*/

}








