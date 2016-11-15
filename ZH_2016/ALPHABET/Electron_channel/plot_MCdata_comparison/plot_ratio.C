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

const int nHisto =8;

void plot_ratio(){

  // open histogram

  TString histo_name[nHisto];

  histo_name[0] = "h_passDoubleBTagger_Jmass";
  histo_name[1] = "h_passDoubleBTagger_Jmass_wideBinning";
  histo_name[2] = "h_passDoubleBTagger_Jmass_wideBinning_diff";
  histo_name[3] = "h_failDoubleBTagger_Jmass";
  histo_name[4] = "h_failDoubleBTagger_Jmass_wideBinning";
  histo_name[5] = "h_failDoubleBTagger_Jmass_wideBinning_diff";
  histo_name[6] = "h_Ratio";
  histo_name[7] = "h_Ratio_wideBinning";


  TFile* file_data = TFile::Open("../output_root/SingleElectron-combine_histogram.root");
  TFile* file_mc   = TFile::Open("../output_root/MC_combine_histogram.root");

//  TFile* file_data = TFile::Open("../output_root/MC_combine_histogram_withMinorBackground.root");
//  TFile* file_mc   = TFile::Open("../output_root/MC_combine_histogram_DYonly.root");


  TH1F* h_data[nHisto];  TH1F* h_mc[nHisto];

  for(int i=0; i<nHisto; i++){
    h_data[i]  = (TH1F*) file_data ->FindObjectAny( histo_name[i] );
    h_mc[i]    = (TH1F*) file_mc   ->FindObjectAny( histo_name[i] );

    h_data[i] -> Sumw2();
    h_mc[i]   -> Sumw2();
  }


  // Normalize histogram except ratio plot 

  for(int i=0; i<nHisto; i++){
    if(i==6 || i==7) continue;
    h_data[i] ->Scale( 1/h_data[i]->Integral() );
    h_mc[i]   ->Scale( 1/h_mc[i]  ->Integral() );
  }


  // Set Style

  for(int i=0; i<nHisto; i++){

    h_data[i] ->GetXaxis() ->SetRangeUser(30, 200);
    h_mc[i]   ->GetXaxis() ->SetRangeUser(30, 200);

    h_data[i] ->SetLineColor(632);
    h_mc[i]   ->SetLineColor(600);

    h_data[i] ->SetStats(0);
    h_mc[i]   ->SetStats(0);        

    TString y_label; 
    if(i!=6 && i!=7) y_label = "Arbitary Unit"; 
    else y_label = "Pass / Fail Ratio";

    h_data[i] ->GetYaxis() ->SetTitle(y_label);
    h_mc[i]   ->GetYaxis() ->SetTitle(y_label);

    h_data[i] ->GetYaxis() ->SetTitleOffset(.9);
    h_mc[i]   ->GetYaxis() ->SetTitleOffset(.9);

    if(i==6 || i==7){    
          h_data[i] ->GetYaxis() ->SetRangeUser(0, 0.4);  
          h_mc[i]   ->GetYaxis() ->SetRangeUser(0, 0.4);
    }

    h_data[i]->GetYaxis()->SetTitleSize(0.05);
    h_data[i]->GetYaxis()->SetLabelSize(0.045);

  }

  // Data/MC Ratio plot and Style 

  TH1F*    h_DataMC_ratio[nHisto];

  for(int i=0; i<nHisto; i++){

        TString DataMC_ratio_name   = Form("h_DataMC_ratio_%i",i);
        h_DataMC_ratio[i] = (TH1F*) h_data[i]  ->Clone( DataMC_ratio_name );
        h_DataMC_ratio[i] ->Sumw2();
        h_DataMC_ratio[i] ->Divide( h_mc[i] );

        h_DataMC_ratio[i] ->GetXaxis ()->SetTitle("Corrected Pruned Mass");
        h_DataMC_ratio[i] ->GetXaxis()->SetTitleSize(0.11);
        h_DataMC_ratio[i] ->GetXaxis()->SetLabelFont(42);
        h_DataMC_ratio[i] ->GetXaxis()->SetLabelSize(0.10);
        h_DataMC_ratio[i] ->GetXaxis()->SetTitleFont(42);

        h_DataMC_ratio[i] ->GetYaxis()->SetTitle("Data / MC");
//        h_DataMC_ratio[i] ->GetYaxis()->SetTitle("With / Without");
        h_DataMC_ratio[i] ->GetYaxis()->SetNdivisions(505);
        h_DataMC_ratio[i] ->GetYaxis()->SetTitleSize(0.11);
        h_DataMC_ratio[i] ->GetYaxis()->SetLabelSize(0.10);
        h_DataMC_ratio[i] ->GetYaxis()->SetRangeUser(0.0, 2);
        h_DataMC_ratio[i] ->GetYaxis()->SetTitleOffset(0.33);

        h_DataMC_ratio[i] ->SetTitle("");
        h_DataMC_ratio[i] ->SetMarkerStyle(20);
  }

  // Draw

  TCanvas* c_[nHisto];
  TPad*    pad1[nHisto]; TPad* pad2[nHisto]; 
  TLegend* leg[nHisto];
  TLine*   OLine[nHisto];


  for(int i=0; i<nHisto; i++){

    TString c_name   = Form("c_%i",i);
    c_[i]            = new TCanvas(c_name,c_name,10,10,800,600);

    TString pad_name = Form("pad1_%i",i);
    pad1[i]          = new TPad(pad_name,pad_name,0.0,0.3,1.0,1.0);

    pad_name         = Form("pad2_%i",i);
    pad2[i]          = new TPad(pad_name,pad_name,0.,0.,1.0,0.3);

    c_[i]->cd();

      pad1[i]->SetBottomMargin(0.001);
      pad1[i]->Draw();
      pad1[i]->cd();

        h_data[i]->Draw();
        h_mc[i]->Draw("same");

        leg[i] = new TLegend(0.7, 0.8, 0.9, 0.9);
//        leg[i] = new TLegend(0.4, 0.7, 0.9, 0.9);

        leg[i] ->AddEntry(h_data[i],"data","l");
        leg[i] ->AddEntry(h_mc[i]  ,"MC(DY only)","l");
//        leg[i] ->AddEntry(h_data[i],"With Minor Backround","l");
//        leg[i] ->AddEntry(h_mc[i]  ,"Without Minor Backround (DY only)","l");
        leg[i] ->Draw();

    c_[i]->cd();

      pad2[i]  ->SetTopMargin(0.9);
      pad2[i]  ->SetBottomMargin(0.3);
      pad2[i]  ->Draw();
      pad2[i]  ->cd();

        h_DataMC_ratio[i]->Draw("E0PX0");

	OLine[i] = new TLine(30,1. ,200 ,1.);
	OLine[i]->SetLineColor(418);
	OLine[i]->SetLineWidth(2);
	OLine[i]->Draw();

  }


  // Save

  TString save_path = "compare_ratio.pdf";
//  TString save_path = "with_and_without_minorBackground.pdf";

  for(int i=0; i<nHisto; i++){
    if      (i==0)        c_[i]->Print(save_path + "(");
    else if (i==nHisto-1) c_[i]->Print(save_path + ")");
    else                  c_[i]->Print(save_path      );

  }


/*
  TCanvas *c_test = new TCanvas("c_test","c_test",10,10,800,600);
  c_test->cd();
  h_data[0] ->Draw(); 
  h_mc[3]   ->Draw();
*/




}






