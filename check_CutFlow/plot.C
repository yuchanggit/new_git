#include <string>

#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TString.h>
#include "TLegend.h"


void plot( std::string outputFolder, std::string outputFile){

  // open ROOT file and TH1D

  std::string root_name = Form("%s.root",outputFile.c_str() ) ;
  TString save_path = outputFolder +"/"+  root_name;

  TFile* file_sample = TFile::Open( save_path );

  TH1D* h_CutFlow_eff = (TH1D*) file_sample->FindObjectAny("h_CutFlow_eff");
  TH1D* h_CutFlow_eff_Alberto = (TH1D*) file_sample->FindObjectAny("h_CutFlow_eff_Alberto");


  // figure style

  h_CutFlow_eff->GetYaxis ()->SetRangeUser(0 ,1.2 );

//  h_CutFlow_eff ->GetYaxis()->SetNdivisions(505);
  h_CutFlow_eff ->GetYaxis()->SetNdivisions(512);

  h_CutFlow_eff->GetYaxis()->SetTitle("Efficiency");
  h_CutFlow_eff->SetStats(0);

  TString h_title; 
  if ( outputFile.find("DiMuonChannel"    )!= std::string::npos ) h_title = "Cut Flow in DiMuon Channel at M_{Z'}=1000 GeV";
  if ( outputFile.find("DiElectronChannel")!= std::string::npos ) h_title = "Cut Flow in DiElectron Channel at M_{Z'}=1000 GeV";

  h_CutFlow_eff->SetTitle( h_title );

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


}
