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

double Xmin1= 30;

//double Xmax1= 65; 
double Xmax1=105;

double Xmin2=135; double Xmax2=200;

void Differential(TH1F* &histo1D  );


void make_histogram(std::string sample_path, std::string save_name){

  cout<<"sample_path: "<< sample_path << endl;


  bool isData = false; // false for MC
  if( sample_path.find("SingleElectron") != std::string::npos ) {cout<<"find data" << endl; isData = true;}// true for Data


  // ------ define histogram --------

  const int NXbins4 = 13;// used for ratio

  double xbins4[NXbins4+1]={30, 40, 49, 57, 65, 75, 85, 95, 105,115,125,
                            135 ,152,200 };

  TH1F* h_passDoubleBTagger_Jmass = new TH1F("h_passDoubleBTagger_Jmass" ,"passDoubleBTagger Jmass ",200,0,1000);
  TH1F* h_failDoubleBTagger_Jmass = new TH1F("h_failDoubleBTagger_Jmass" ,"failDoubleBTagger Jmass ",200,0,1000);


  TH1F* h_passDoubleBTagger_Jmass_wideBinning = new TH1F("h_passDoubleBTagger_Jmass_wideBinning" ,"passDoubleBTagger Jmass wideBinning ",NXbins4, xbins4);


  TH1F* h_failDoubleBTagger_Jmass_wideBinning = new TH1F("h_failDoubleBTagger_Jmass_wideBinning" ,"failDoubleBTagger Jmass wideBinning ",NXbins4, xbins4);

  // Sumw2


  h_passDoubleBTagger_Jmass             ->Sumw2();
  h_failDoubleBTagger_Jmass             ->Sumw2();

  h_passDoubleBTagger_Jmass_wideBinning ->Sumw2();
  h_failDoubleBTagger_Jmass_wideBinning ->Sumw2();


  // ------ open root file ---------- 

  TFile* file   = TFile::Open( sample_path.c_str() );

  TH1F* h_totalEv = (TH1F*)file->FindObjectAny("totalEvents");

  TTree* tree = (TTree*) file->Get("new_tree");

  double Event_Weight;
  double PRmass, PRmass_L2L3Corrected, SDmass, SDmass_TheaCorrected;
  double Double_bTagger;
  double Tau21;
  double ZHmass;

  tree->SetBranchAddress("Event_Weight",         &Event_Weight);
  tree->SetBranchAddress("PRmass",               &PRmass);
  tree->SetBranchAddress("PRmass_L2L3Corrected", &PRmass_L2L3Corrected);
  tree->SetBranchAddress("SDmass",               &SDmass);
  tree->SetBranchAddress("SDmass_TheaCorrected", &SDmass_TheaCorrected);
  tree->SetBranchAddress("Double_bTagger",       &Double_bTagger);
  tree->SetBranchAddress("Tau21",                &Tau21);
  tree->SetBranchAddress("ZHmass",               &ZHmass);

  // ----- event loop on Mini TTree -----------


  int Number_to_print    =  10000;

  for( Long64_t ev = 0; ev < tree->GetEntriesFast(); ev++ ){

    if( ev %   Number_to_print == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, tree->GetEntriesFast());

    tree->GetEntry(ev);

    PRmass_L2L3Corrected = SDmass_TheaCorrected; // use SD mass to replace PR mass

    // blind data in the signal region (no blind in MC)
    if ( isData && PRmass_L2L3Corrected> Xmax1 && PRmass_L2L3Corrected< Xmin2 && Double_bTagger >0.6 )continue;

    if ( PRmass_L2L3Corrected< Xmin1 )  continue;// remove low mass peak in Jet Mass
    if ( PRmass_L2L3Corrected> Xmax2 )  continue;// remove high mass spikes


    double DoubleBTaggerCut = 0.3;

    if( Double_bTagger > DoubleBTaggerCut){

      if( isData && PRmass_L2L3Corrected> Xmax1 && PRmass_L2L3Corrected< Xmin2 ) continue;
 
      h_passDoubleBTagger_Jmass             ->Fill( PRmass_L2L3Corrected , Event_Weight);
      h_passDoubleBTagger_Jmass_wideBinning ->Fill( PRmass_L2L3Corrected , Event_Weight);
    }
    else                                  {

      if( isData && PRmass_L2L3Corrected>Xmax1  && PRmass_L2L3Corrected< Xmin2 ) continue;

      h_failDoubleBTagger_Jmass             ->Fill( PRmass_L2L3Corrected , Event_Weight);
      h_failDoubleBTagger_Jmass_wideBinning ->Fill( PRmass_L2L3Corrected , Event_Weight);

    }

  }// ------ end event loop -------------


  // Differential histogram
  TH1F* h_passDoubleBTagger_Jmass_wideBinning_diff = (TH1F*) h_passDoubleBTagger_Jmass_wideBinning->Clone("h_passDoubleBTagger_Jmass_wideBinning_diff");
  Differential (  h_passDoubleBTagger_Jmass_wideBinning_diff );

  TH1F* h_failDoubleBTagger_Jmass_wideBinning_diff = (TH1F*) h_failDoubleBTagger_Jmass_wideBinning->Clone("h_failDoubleBTagger_Jmass_wideBinning_diff");
  Differential (  h_failDoubleBTagger_Jmass_wideBinning_diff );


  // Add Ratio plot for data only

  TH1F* h_Ratio; TH1F* h_Ratio_wideBinning;
 
  if(isData){ 

    h_Ratio = (TH1F*) h_passDoubleBTagger_Jmass ->Clone("h_Ratio");
    h_Ratio ->Sumw2();
    h_Ratio ->Divide( h_failDoubleBTagger_Jmass );
    h_Ratio ->SetTitle("h_Ratio");

    h_Ratio_wideBinning = (TH1F*) h_passDoubleBTagger_Jmass_wideBinning ->Clone("h_Ratio_wideBinning");
    h_Ratio_wideBinning ->Sumw2();
    h_Ratio_wideBinning ->Divide( h_failDoubleBTagger_Jmass_wideBinning );
    h_Ratio_wideBinning ->SetTitle("h_Ratio_wideBinning");

  }


  // save histogram in root file
  TString save_path = "output_root/"+ save_name +"_histogram.root";
  TFile* outFile = new TFile( save_path , "recreate");

  h_passDoubleBTagger_Jmass                  ->Write();
  h_passDoubleBTagger_Jmass_wideBinning      ->Write();
  h_passDoubleBTagger_Jmass_wideBinning_diff ->Write();

  h_failDoubleBTagger_Jmass                  ->Write();
  h_failDoubleBTagger_Jmass_wideBinning      ->Write();
  h_failDoubleBTagger_Jmass_wideBinning_diff ->Write();

  h_totalEv				     ->Write();

  if(isData) { // for data only
    h_Ratio                                  ->Write();
    h_Ratio_wideBinning                      ->Write();
  }

  outFile->Write();
  delete outFile;

}




void Differential (TH1F* &histo1D ){


  histo1D ->Sumw2();

  int Nbins = histo1D ->GetNbinsX();

  for(int i=1;i<=Nbins; i++){
    double BinContent = histo1D -> GetBinContent(i);
    double BinWidth   = histo1D -> GetBinWidth(i);
    histo1D -> SetBinContent(i, BinContent/ BinWidth );
    histo1D -> SetBinError(i, (1/BinWidth) * sqrt(BinContent) );
  }

  TString title_name = histo1D ->GetTitle();
  title_name = title_name + "differential";
  histo1D ->SetTitle(title_name);

}



