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

#include "supportHeader.h"

//double Xmin1= 30;

//double Xmax1= 65; 
//double Xmax1=105;

//double Xmin2=135; double Xmax2=200;

const int nDY =4;

void predict_ZH_mass(){

  cout<<"hello "<< endl;



  // ------ define histogram --------

  TH1F* h_ZH_mass_pass = new TH1F("h_ZH_mass_pass" ,"h_ZH_mass_pass",100,0,2000);
  TH1F* h_ZH_mass_fail = new TH1F("h_ZH_mass_fail" ,"h_ZH_mass_fail",100,0,2000);

  TH1F* h_ZH_mass_pass_predict = new TH1F("h_ZH_mass_pass_predict" ,"h_ZH_mass_pass_predict",100,0,2000);

  h_ZH_mass_pass ->Sumw2();
  h_ZH_mass_fail ->Sumw2();
  h_ZH_mass_pass_predict->Sumw2();

  // ------ open DY sample, loop events, fill histogram, predict ZH mass ---------

  // ROOT file
  std::string sample_path[nDY];

  sample_path[0] = "../test_ele_with_PUweight_NoMassCut/DY/output_ele/DYJetsToLL_M-50_HT-100to200_13TeV.root";
  sample_path[1] = "../test_ele_with_PUweight_NoMassCut/DY/output_ele/DYJetsToLL_M-50_HT-200to400_13TeV.root";
  sample_path[2] = "../test_ele_with_PUweight_NoMassCut/DY/output_ele/DYJetsToLL_M-50_HT-400to600_13TeV.root";
  sample_path[3] = "../test_ele_with_PUweight_NoMassCut/DY/output_ele/DYJetsToLL_M-50_HT-600toInf_13TeV.root";



  // Xsec and TotalEv
  TFile* file_DY[nDY]; TTree* tree_DY[nDY]; 
  TH1F* h_totalEv[nDY];

  double Xsec[nDY], nTotal[nDY], Weight[nDY];

  Xsec[0] = 147.40 *1.23;// DYHt100to200  
  Xsec[1] =  41    *1.23;// DYHt200to400
  Xsec[2] =   5.678*1.23;// DYHt400to600
  Xsec[3] =   2.198*1.23;// DYHt600toInf



  // function for Fit Ratio
  TF1* fn_ratio = new TF1("fn_ratio", fline_ExpTail ,30,200,3);

  double par0,par1,par2;
  par0 = 0.63; par1= 21.53, par2= 0.42;
  fn_ratio ->SetParameters(par0, par1, par2);




  for(int iDY=0; iDY< nDY; iDY++){

    // open TTree
    file_DY[iDY] = TFile::Open( sample_path[iDY].c_str() );
    tree_DY[iDY] = (TTree*) file_DY[iDY]->Get("new_tree");

    double Event_Weight;                 
    double PRmass_L2L3Corrected;
    double Double_bTagger;
    double ZHmass;   

    tree_DY[iDY] ->SetBranchAddress("Event_Weight",         &Event_Weight);
    tree_DY[iDY] ->SetBranchAddress("PRmass_L2L3Corrected", &PRmass_L2L3Corrected);
    tree_DY[iDY] ->SetBranchAddress("ZHmass",               &ZHmass);
    tree_DY[iDY] ->SetBranchAddress("Double_bTagger",       &Double_bTagger);

    // set event weight 
    double Lumi = 12700;// 12.7/fb
    h_totalEv[iDY] = (TH1F*)file_DY[iDY]->FindObjectAny("totalEvents");
    nTotal[iDY] = h_totalEv[iDY]->Integral();
    Weight[iDY] = Lumi * Xsec[iDY] / nTotal[iDY] ;   

 
    // Event loop
    int Number_to_print    =  10000;
//    cout<<"iDY: "<< iDY << endl;
    for( Long64_t ev = 0; ev < tree_DY[iDY]->GetEntriesFast(); ev++ ){

      if( ev %   Number_to_print == 0 )
        fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, tree_DY[iDY]->GetEntriesFast());

      tree_DY[iDY]->GetEntry(ev);

//      cout<<"PRmass_L2L3Corrected: "<< PRmass_L2L3Corrected << endl; 
      
      // Jet mass signal region 
      if(PRmass_L2L3Corrected <105 || PRmass_L2L3Corrected>135)continue;

      // pass
      if(Double_bTagger >0.3){
        h_ZH_mass_pass         ->Fill(ZHmass, Weight[iDY] ) ;

      }

      // fail
      else{
        h_ZH_mass_fail         ->Fill(ZHmass, Weight[iDY] ) ;
 
        h_ZH_mass_pass_predict ->Fill(ZHmass, Weight[iDY] * fn_ratio->Eval( PRmass_L2L3Corrected )  ) ;


      }


    }// end event loop

  }// end DY loop



  // ------ figure style -------
 
  h_ZH_mass_fail->SetTitle("");
  h_ZH_mass_fail->SetStats(0);
  h_ZH_mass_fail->GetXaxis ()->SetTitle("ZH invariant mass");
  h_ZH_mass_fail->GetYaxis ()->SetTitle("Events");

  h_ZH_mass_fail->SetLineColor(4);
  h_ZH_mass_pass->SetLineColor(3);
  h_ZH_mass_pass_predict->SetLineColor(2);

  // ------- Draw and Save ----------

  TLegend* leg = new TLegend(0.5, 0.6, 0.9, 0.9);

  TCanvas *c1 = new TCanvas("c1","c1",10,10,800,600);
  c1->cd();
  h_ZH_mass_fail->Draw();
  h_ZH_mass_pass->Draw("same");
  h_ZH_mass_pass_predict->Draw("same");

  leg->AddEntry(h_ZH_mass_fail,"h_ZH_mass_fail","l");
  leg->AddEntry(h_ZH_mass_pass,"h_ZH_mass_pass","l");
  leg->AddEntry(h_ZH_mass_pass_predict,"h_ZH_mass_pass_predict","l");

  leg->Draw();

  TString pdf_name = "predict_ZH_mass.pdf";
  c1->Print( pdf_name );  



//  TCanvas *c2 = new TCanvas("c2","c2",10,10,800,600);
//  c2->cd();
//  fn_ratio ->Draw();



}




