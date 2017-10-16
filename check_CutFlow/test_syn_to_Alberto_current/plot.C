#include <string>
#include <iostream>
#include <fstream>

#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TString.h>
#include "TLegend.h"

using namespace std;

void plot( std::string outputFolder, std::string outputFile){

  // open ROOT file and TH1D

  std::string root_name = Form("%s.root",outputFile.c_str() ) ;
  TString save_path = outputFolder +"/"+  root_name;

  TFile* file_sample = TFile::Open( save_path );

  TH1D* h_CutFlow_eff = (TH1D*) file_sample->FindObjectAny("h_CutFlow_eff");
  TH1D* h_CutFlow_eff_Alberto = (TH1D*) file_sample->FindObjectAny("h_CutFlow_eff_Alberto");


  // figure style


  TString h_title; int Nbins_temp = 1;
 
  if ( outputFile.find("DiMuonChannel"    )!= std::string::npos ) {h_title = "Cut Flow in DiMuon Channel at M_{Z'}=1000 GeV";     Nbins_temp = 14;}
  if ( outputFile.find("DiElectronChannel")!= std::string::npos ) {h_title = "Cut Flow in DiElectron Channel at M_{Z'}=1000 GeV"; Nbins_temp = 13;}

  const int Nbins = Nbins_temp; 
 
  char* cut_name[Nbins];

  char* cut_name_Ele[13] = {"All             ","Trigger         ","Ele in acc.     ","Z(ee) candidate ","Ele P_{T}       ","Ele Id          ","Z boost         ","AK8 jet         ","Cleaning        ","X mass          ","H mass          ","1 b-tag         ","2 b-tag         "};

  char* cut_name_Mu[14] = {"All                  ","Trigger              ","Muon in acc.         ","Z(#mu#mu) candidate  ","Muon P_{T}           ","Muon Id              ","Muon Iso             ","Z boost              ","AK8 jet              ","Cleaning             ","X mass               ","H mass               ","1 b-tag              ","2 b-tag              "};

  if (Nbins == 13) { for (int i=0; i< Nbins ; i++) { cut_name[i] = cut_name_Ele[i];}  }
  if (Nbins == 14) { for (int i=0; i< Nbins ; i++) { cut_name[i] = cut_name_Mu [i];}  } 


  h_CutFlow_eff->SetTitle( h_title );

  h_CutFlow_eff->GetYaxis ()->SetRangeUser(0 ,1.2 );

  h_CutFlow_eff->GetYaxis()->SetNdivisions(512);

  h_CutFlow_eff->GetYaxis()->SetTitle("Efficiency");
  h_CutFlow_eff->SetStats(0);

  h_CutFlow_eff         ->SetLineColor(2);
  h_CutFlow_eff_Alberto ->SetLineColor(4);

  // Draw

  TCanvas* c1 = new TCanvas("c1","c1",10,10,800,600);
  c1-> SetGrid();

  h_CutFlow_eff         ->Draw();
  h_CutFlow_eff_Alberto ->Draw("same");

  TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.85);
  leg->AddEntry( h_CutFlow_eff ,"YuHsiang's result","l");
  leg->AddEntry( h_CutFlow_eff_Alberto ,"Alberto's result","l");
  leg ->Draw();

  // Save

  TString pdf_name;
  if ( outputFile.find("DiMuonChannel"    )!= std::string::npos ) pdf_name = "output_ROOT/compareEff_Mu.pdf";
  if ( outputFile.find("DiElectronChannel")!= std::string::npos ) pdf_name = "output_ROOT/compareEff_Ele.pdf";
  c1->SaveAs( pdf_name );

  //  calculate the difference between Alberto'eff and Yu-Hsiang's eff

  TString txt_name;
  if ( outputFile.find("DiMuonChannel"    )!= std::string::npos ) txt_name = "output_ROOT/record_eff_Mu.txt";
  if ( outputFile.find("DiElectronChannel")!= std::string::npos ) txt_name = "output_ROOT/record_eff_Ele.txt";

  ofstream outfile;
  outfile.open(txt_name);
 
  cout   << "cut name            Alberto's eff       YuHsiang's eff      relative difference"<< endl;
  outfile<< "cut name            Alberto's eff       YuHsiang's eff      relative difference"<< endl;

  for(int i=1;i<=Nbins;i++){

 
    double A_eff = h_CutFlow_eff_Alberto->GetBinContent(i);
    double Y_eff = h_CutFlow_eff ->GetBinContent(i);
    double rel_diff = ( A_eff - Y_eff )/ A_eff;
    
    cout    << cut_name[i-1] <<" "<< A_eff <<"       "<< Y_eff <<"    " << rel_diff << endl;
    outfile << cut_name[i-1] <<" "<< A_eff <<"       "<< Y_eff <<"    " << rel_diff << endl;

  }

  outfile.close();
  cout<<"save efficiency in text file:"<< txt_name << endl;

}
