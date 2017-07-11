#include <vector>
#include <string>
#include <iostream>

#include <TH1D.h>
#include <TFile.h>
#include "TTree.h"
#include <TF1.h>
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPad.h"
#include "TLine.h"
#include "TString.h"

#include "XSecs.h"

using namespace std;

void My_plotting( TCanvas* & c_ ,TPad* pad_a, TPad* pad_b ,
		  TH1F* h_NLO, TH1F* h_LO_combine, TH1F* h_Ht100to200, TH1F* h_Ht200to400, TH1F* h_Ht400to600, TH1F* h_Ht600toInf, 
		  int option =0 );

void My_Kfactor( TH1F* h_NLO , TH1F* h1, TH1F* h2, TH1F* h3, TH1F* h4);


TString variable_name;

// K-factor
double K1 = 1.;
double K2 = 1.;
double K3 = 1.;
double K4 = 1.;



void compute(){

  cout<<"hello"<<endl;

  // get DY sample's cross sections (defined in XSecs.h) 
  /* -----------------------------------------------------*/

  cout<<"xs_DY_NLO_inclusive: "<< xs_DY_NLO_inclusive << endl;
  cout<<"xs_DY_LO_HT100to200: "<< xs_DY_LO_HT100to200 << endl;
  cout<<"xs_DY_LO_HT200to400: "<< xs_DY_LO_HT200to400 << endl;
  cout<<"xs_DY_LO_HT400to600: "<< xs_DY_LO_HT400to600 << endl;

  cout<<"xs_DY_LO_HT600to800: "  << xs_DY_LO_HT600to800   << endl;
  cout<<"xs_DY_LO_HT800to1200: " << xs_DY_LO_HT800to1200  << endl;
  cout<<"xs_DY_LO_HT1200to2500: "<< xs_DY_LO_HT1200to2500 << endl;
  cout<<"xs_DY_LO_HT2500toInf: " << xs_DY_LO_HT2500toInf  << endl;

  // open DY sample's root file 
  /* -----------------------------------------------------*/


  TFile* f0 = TFile::Open("../MiniTreeSkim_package/skimmedFile_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root");

  TFile* f1 = TFile::Open("../MiniTreeSkim_package/skimmedFile_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  TFile* f2 = TFile::Open("../MiniTreeSkim_package/skimmedFile_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  TFile* f3 = TFile::Open("../MiniTreeSkim_package/skimmedFile_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");

  TFile* f4 = TFile::Open("../MiniTreeSkim_package/skimmedFile_DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  TFile* f5 = TFile::Open("../MiniTreeSkim_package/skimmedFile_DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  TFile* f6 = TFile::Open("../MiniTreeSkim_package/skimmedFile_DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  TFile* f7 = TFile::Open("../MiniTreeSkim_package/skimmedFile_DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");


  // get DY sample's genZpt histogram
  /* -----------------------------------------------------*/ 

//  variable_name = "h_genZpt";
  variable_name = "h_eventHT";

 
  TH1F* h_genZpt_NLO           = (TH1F*) f0->FindObjectAny( variable_name );
  TH1F* h_genZpt_LO_HT100to200 = (TH1F*) f1->FindObjectAny( variable_name );
  TH1F* h_genZpt_LO_HT200to400 = (TH1F*) f2->FindObjectAny( variable_name );
  TH1F* h_genZpt_LO_HT400to600 = (TH1F*) f3->FindObjectAny( variable_name );

  TH1F* h_genZpt_LO_HT600to800   = (TH1F*) f4->FindObjectAny( variable_name );
  TH1F* h_genZpt_LO_HT800to1200  = (TH1F*) f5->FindObjectAny( variable_name );
  TH1F* h_genZpt_LO_HT1200to2500 = (TH1F*) f6->FindObjectAny( variable_name );
  TH1F* h_genZpt_LO_HT2500toInf  = (TH1F*) f7->FindObjectAny( variable_name );

  h_genZpt_NLO          ->Sumw2();
  h_genZpt_LO_HT100to200->Sumw2();
  h_genZpt_LO_HT200to400->Sumw2();
  h_genZpt_LO_HT400to600->Sumw2();

  h_genZpt_LO_HT600to800  ->Sumw2();
  h_genZpt_LO_HT800to1200 ->Sumw2();
  h_genZpt_LO_HT1200to2500->Sumw2();
  h_genZpt_LO_HT2500toInf ->Sumw2();


  // get DY sample's total number of events
  /* -----------------------------------------------------*/

  TH1F* h_totalEv_NLO           = (TH1F*) f0->FindObjectAny("h_totalEv");
  TH1F* h_totalEv_LO_HT100to200 = (TH1F*) f1->FindObjectAny("h_totalEv");
  TH1F* h_totalEv_LO_HT200to400 = (TH1F*) f2->FindObjectAny("h_totalEv");
  TH1F* h_totalEv_LO_HT400to600 = (TH1F*) f3->FindObjectAny("h_totalEv");

  TH1F* h_totalEv_LO_HT600to800   = (TH1F*) f4->FindObjectAny("h_totalEv");
  TH1F* h_totalEv_LO_HT800to1200  = (TH1F*) f5->FindObjectAny("h_totalEv");
  TH1F* h_totalEv_LO_HT1200to2500 = (TH1F*) f6->FindObjectAny("h_totalEv");
  TH1F* h_totalEv_LO_HT2500toInf  = (TH1F*) f7->FindObjectAny("h_totalEv");

  double totalEv_NLO 	       = h_totalEv_NLO		->Integral();
  double totalEv_LO_HT100to200 = h_totalEv_LO_HT100to200->Integral();
  double totalEv_LO_HT200to400 = h_totalEv_LO_HT200to400->Integral();
  double totalEv_LO_HT400to600 = h_totalEv_LO_HT400to600->Integral();

  double totalEv_LO_HT600to800   = h_totalEv_LO_HT600to800  ->Integral();
  double totalEv_LO_HT800to1200  = h_totalEv_LO_HT800to1200 ->Integral();
  double totalEv_LO_HT1200to2500 = h_totalEv_LO_HT1200to2500->Integral();
  double totalEv_LO_HT2500toInf  = h_totalEv_LO_HT2500toInf ->Integral();


  // scale DY sample to same luminosity 
  /* -----------------------------------------------------*/

  h_genZpt_NLO          -> Scale( xs_DY_NLO_inclusive / totalEv_NLO          );
  h_genZpt_LO_HT100to200-> Scale( xs_DY_LO_HT100to200 / totalEv_LO_HT100to200);
  h_genZpt_LO_HT200to400-> Scale( xs_DY_LO_HT200to400 / totalEv_LO_HT200to400);
  h_genZpt_LO_HT400to600-> Scale( xs_DY_LO_HT400to600 / totalEv_LO_HT400to600);

  h_genZpt_LO_HT600to800  -> Scale( xs_DY_LO_HT600to800   / totalEv_LO_HT600to800);
  h_genZpt_LO_HT800to1200 -> Scale( xs_DY_LO_HT800to1200  / totalEv_LO_HT800to1200);
  h_genZpt_LO_HT1200to2500-> Scale( xs_DY_LO_HT1200to2500 / totalEv_LO_HT1200to2500);
  h_genZpt_LO_HT2500toInf -> Scale( xs_DY_LO_HT2500toInf  / totalEv_LO_HT2500toInf);


  TH1F *h_genZpt_LO_HT600toInf = (TH1F*) h_genZpt_NLO ->Clone("h_genZpt_LO_HT600toInf");
  h_genZpt_LO_HT600toInf -> Reset();
  h_genZpt_LO_HT600toInf -> Sumw2();
  h_genZpt_LO_HT600toInf -> Add( h_genZpt_LO_HT600to800 );
  h_genZpt_LO_HT600toInf -> Add( h_genZpt_LO_HT800to1200 );
  h_genZpt_LO_HT600toInf -> Add( h_genZpt_LO_HT1200to2500 );
  h_genZpt_LO_HT600toInf -> Add( h_genZpt_LO_HT2500toInf );


  cout<<"h_genZpt_LO_HT100to200 in [100,200]: "<< h_genZpt_LO_HT100to200->Integral(21,40)  <<endl;
  cout<<"h_genZpt_LO_HT100to200 in [200,400]: "<< h_genZpt_LO_HT100to200->Integral(41,80)  <<endl;
  cout<<"h_genZpt_LO_HT100to200 in [400,600]: "<< h_genZpt_LO_HT100to200->Integral(81,120)  <<endl;
  cout<<"h_genZpt_LO_HT100to200 in [600,1000]: "<< h_genZpt_LO_HT100to200->Integral(121,200)  <<endl;

  cout<<"h_genZpt_LO_HT200to400 in [100,200]: "<< h_genZpt_LO_HT200to400->Integral(21,40)  <<endl;
  cout<<"h_genZpt_LO_HT200to400 in [200,400]: "<< h_genZpt_LO_HT200to400->Integral(41,80)  <<endl;
  cout<<"h_genZpt_LO_HT200to400 in [400,600]: "<< h_genZpt_LO_HT200to400->Integral(81,120)  <<endl;
  cout<<"h_genZpt_LO_HT200to400 in [600,1000]: "<< h_genZpt_LO_HT200to400->Integral(121,200)  <<endl;

  cout<<"h_genZpt_LO_HT400to600 in [100,200]: "<< h_genZpt_LO_HT400to600->Integral(21,40)  <<endl;
  cout<<"h_genZpt_LO_HT400to600 in [200,400]: "<< h_genZpt_LO_HT400to600->Integral(41,80)  <<endl;
  cout<<"h_genZpt_LO_HT400to600 in [400,600]: "<< h_genZpt_LO_HT400to600->Integral(81,120)  <<endl;
  cout<<"h_genZpt_LO_HT400to600 in [600,1000]: "<< h_genZpt_LO_HT400to600->Integral(121,200)  <<endl;

  cout<<"h_genZpt_LO_HT600toInf in [100,200]: "<< h_genZpt_LO_HT600toInf->Integral(21,40)  <<endl;
  cout<<"h_genZpt_LO_HT600toInf in [200,400]: "<< h_genZpt_LO_HT600toInf->Integral(41,80)  <<endl;
  cout<<"h_genZpt_LO_HT600toInf in [400,600]: "<< h_genZpt_LO_HT600toInf->Integral(81,120)  <<endl;
  cout<<"h_genZpt_LO_HT600toInf in [600,1000]: "<< h_genZpt_LO_HT600toInf->Integral(121,200)  <<endl;

  // get the stack of three DY HT samples and the ratio of LO/NLO
  /* -----------------------------------------------------*/

  TH1F *h_LO = (TH1F*) h_genZpt_NLO ->Clone("h_LO");
  h_LO -> Reset();
  h_LO->Sumw2();

  h_LO -> Add(h_genZpt_LO_HT100to200);
  h_LO -> Add(h_genZpt_LO_HT200to400);
  h_LO -> Add(h_genZpt_LO_HT400to600);
  h_LO -> Add(h_genZpt_LO_HT600toInf);


  cout<<"h_LO in [100,200]: "<< h_LO ->Integral(21,40)  <<endl;
  cout<<"h_LO in [200,400]: "<< h_LO ->Integral(41,80)  <<endl;
  cout<<"h_LO in [400,600]: "<< h_LO ->Integral(81,120)  <<endl;
  cout<<"h_LO in [600,1000]: "<< h_LO ->Integral(121,200)  <<endl;

  // set DY sample's figure style 
  /* -----------------------------------------------------*/


  // Draw DY sample's genZpt in same Canvas 
  /* -----------------------------------------------------*/


  TCanvas* c1 = new TCanvas("c1","c1",10,10,800,600);

  TPad* pad1   = new TPad("pad1","pad1",0.0, 0.3, 1.0, 1.0);
  TPad* pad2   = new TPad("pad2","pad2",0.0, 0.0, 1.0, 0.3);

  My_plotting( c1 , pad1 , pad2 , h_genZpt_NLO , h_LO , h_genZpt_LO_HT100to200 , h_genZpt_LO_HT200to400 , h_genZpt_LO_HT400to600 ,h_genZpt_LO_HT600toInf, 0);


//--------------------------------------------------------------------------------

  // compute DY sample's k-factor
  /* -----------------------------------------------------*/


  K1 = h_genZpt_NLO->Integral(21,40)  / h_genZpt_LO_HT100to200->Integral(21,40)  ;// Zpt 100-200
  K2 = h_genZpt_NLO->Integral(41,80)  / h_genZpt_LO_HT200to400->Integral(41,80)  ;// Zpt 200-400
  K3 = h_genZpt_NLO->Integral(81,120) / h_genZpt_LO_HT400to600->Integral(81,120 );// Zpt 400-600
  K4 = h_genZpt_NLO->Integral(121,200) / h_genZpt_LO_HT600toInf->Integral(121,200 );// Zpt 400-600

/*
  cout<<"Kfactor_100to200: "<< K1 << endl; 
  cout<<"Kfactor_200to400: "<< K2 << endl;
  cout<<"Kfactor_400to600: "<< K3 << endl;
  cout<<"Kfactor_600toInf: "<< K4 << endl;
*/

  double global_K = h_genZpt_NLO->Integral(21,200)/ h_LO ->Integral(21,200); 
  K1= global_K; K2= global_K; K3= global_K; K4= global_K; 

  cout<<"NLO in [100,1000]: "<<  h_genZpt_NLO->Integral(21,200) << endl;
  cout<<"LO in [100,1000]: "<<  h_LO->Integral(21,200) << endl;
  cout<<"NLO/LO in [100,1000]: "<< global_K << endl; 

//  My_Kfactor( h_genZpt_NLO , h_genZpt_LO_HT100to200 , h_genZpt_LO_HT200to400 , h_genZpt_LO_HT400to600 , h_genZpt_LO_HT600toInf);


  cout<<"Kfactor_100to200: "<< K1 << endl;
  cout<<"Kfactor_200to400: "<< K2 << endl;
  cout<<"Kfactor_400to600: "<< K3 << endl;
  cout<<"Kfactor_600toInf: "<< K4 << endl;


//  K1 = 1.42;
//  K2 = 1.38;
//  K3 = 2.05;

//  K1 = 1.416;
//  K2 = 1.422;
//  K3 = 1.415;
//  K4 = 1.044;


  // Clone DY sample's histogram and apply k-factor
  /* -----------------------------------------------------*/

  TH1F *h_genZpt_LO_HT100to200_new = (TH1F*) h_genZpt_LO_HT100to200 ->Clone("h_genZpt_LO_HT100to200_new");
  TH1F *h_genZpt_LO_HT200to400_new = (TH1F*) h_genZpt_LO_HT200to400 ->Clone("h_genZpt_LO_HT200to400_new");
  TH1F *h_genZpt_LO_HT400to600_new = (TH1F*) h_genZpt_LO_HT400to600 ->Clone("h_genZpt_LO_HT400to600_new");
  TH1F *h_genZpt_LO_HT600toInf_new = (TH1F*) h_genZpt_LO_HT600toInf ->Clone("h_genZpt_LO_HT600toInf_new");

  h_genZpt_LO_HT100to200_new->Sumw2();
  h_genZpt_LO_HT200to400_new->Sumw2();
  h_genZpt_LO_HT400to600_new->Sumw2();
  h_genZpt_LO_HT600toInf_new->Sumw2();

  h_genZpt_LO_HT100to200_new-> Scale( K1 );
  h_genZpt_LO_HT200to400_new-> Scale( K2 );
  h_genZpt_LO_HT400to600_new-> Scale( K3 );
  h_genZpt_LO_HT600toInf_new-> Scale( K4 );


  cout<<"h_genZpt_LO_HT100to200_new in [100,200]: "<< h_genZpt_LO_HT100to200_new->Integral(21,40)  <<endl;
  cout<<"h_genZpt_LO_HT100to200_new in [200,400]: "<< h_genZpt_LO_HT100to200_new->Integral(41,80)  <<endl;
  cout<<"h_genZpt_LO_HT100to200_new in [400,600]: "<< h_genZpt_LO_HT100to200_new->Integral(81,120)  <<endl;
  cout<<"h_genZpt_LO_HT100to200_new in [600,1000]: "<< h_genZpt_LO_HT100to200_new->Integral(121,200)  <<endl;

  cout<<"h_genZpt_LO_HT200to400_new in [100,200]: "<< h_genZpt_LO_HT200to400_new->Integral(21,40)  <<endl;
  cout<<"h_genZpt_LO_HT200to400_new in [200,400]: "<< h_genZpt_LO_HT200to400_new->Integral(41,80)  <<endl;
  cout<<"h_genZpt_LO_HT200to400_new in [400,600]: "<< h_genZpt_LO_HT200to400_new->Integral(81,120)  <<endl;
  cout<<"h_genZpt_LO_HT200to400_new in [600,1000]: "<< h_genZpt_LO_HT200to400_new->Integral(121,200)  <<endl;

  cout<<"h_genZpt_LO_HT400to600_new in [100,200]: "<< h_genZpt_LO_HT400to600_new->Integral(21,40)  <<endl;
  cout<<"h_genZpt_LO_HT400to600_new in [200,400]: "<< h_genZpt_LO_HT400to600_new->Integral(41,80)  <<endl;
  cout<<"h_genZpt_LO_HT400to600_new in [400,600]: "<< h_genZpt_LO_HT400to600_new->Integral(81,120)  <<endl;  
  cout<<"h_genZpt_LO_HT400to600_new in [600,1000]: "<< h_genZpt_LO_HT400to600_new->Integral(121,200)  <<endl;

  cout<<"h_genZpt_LO_HT600toInf_new in [100,200]: "<< h_genZpt_LO_HT600toInf_new->Integral(21,40)  <<endl;
  cout<<"h_genZpt_LO_HT600toInf_new in [200,400]: "<< h_genZpt_LO_HT600toInf_new->Integral(41,80)  <<endl;
  cout<<"h_genZpt_LO_HT600toInf_new in [400,600]: "<< h_genZpt_LO_HT600toInf_new->Integral(81,120)  <<endl;
  cout<<"h_genZpt_LO_HT600toInf_new in [600,1000]: "<< h_genZpt_LO_HT600toInf_new->Integral(121,200)  <<endl;


  // get the stack of three DY HT samples and the ratio of LO/NLO iafter correction
  /* -----------------------------------------------------*/

  TH1F *h_LO_new = (TH1F*) h_genZpt_NLO ->Clone("h_LO_new");
  h_LO_new -> Reset();
  h_LO_new ->Sumw2();

  h_LO_new -> Add(h_genZpt_LO_HT100to200_new);
  h_LO_new -> Add(h_genZpt_LO_HT200to400_new);
  h_LO_new -> Add(h_genZpt_LO_HT400to600_new);
  h_LO_new -> Add(h_genZpt_LO_HT600toInf_new);

  TH1F *h_genZpt_NLO_same = (TH1F*) h_genZpt_NLO ->Clone("h_genZpt_NLO_same");
  h_genZpt_NLO_same          ->Sumw2();


  cout<<"h_LO_new in [100,200]: "<< h_LO_new->Integral(21,40)  <<endl;
  cout<<"h_LO_new in [200,400]: "<< h_LO_new->Integral(41,80)  <<endl;
  cout<<"h_LO_new in [400,600]: "<< h_LO_new->Integral(81,120)  <<endl;
  cout<<"h_LO_new in [600,1000]: "<< h_LO_new->Integral(121,200)  <<endl;


  cout<<"h_genZpt_NLO_same in [100,200]: "<< h_genZpt_NLO_same->Integral(21,40)  <<endl;
  cout<<"h_genZpt_NLO_same in [200,400]: "<< h_genZpt_NLO_same->Integral(41,80)  <<endl;
  cout<<"h_genZpt_NLO_same in [400,600]: "<< h_genZpt_NLO_same->Integral(81,120) <<endl;
  cout<<"h_genZpt_NLO_same in [600,1000]: "<< h_genZpt_NLO_same->Integral(121,200) <<endl;

  // set figure style 
  /* -----------------------------------------------------*/


  // Draw DY sample's genZpt after correction in another Canvas 
  /* -----------------------------------------------------*/



  TCanvas* c2 = new TCanvas("c2","c2",10,10,800,600);

  TPad* pad3   = new TPad("pad3","pad3",0.0, 0.3, 1.0, 1.0);
  TPad* pad4   = new TPad("pad4","pad4",0.0, 0.0, 1.0, 0.3);

  My_plotting( c2 , pad3 , pad4 , h_genZpt_NLO_same , h_LO_new  , h_genZpt_LO_HT100to200_new  , h_genZpt_LO_HT200to400_new  , h_genZpt_LO_HT400to600_new, h_genZpt_LO_HT600toInf_new  , 1);


  // Save PDF file 
  /* -----------------------------------------------------*/



  if (variable_name == "h_genZpt"  ) {c1->SaveAs("before_apply_Kfactor_Zpt.pdf");
    c2->SaveAs("after_apply_Kfactor_Zpt_onlyDiagonal.pdf");
//    c2->SaveAs("after_apply_Kfactor_Zpt_allTerms.pdf");
//    c2->SaveAs("after_apply_Kfactor_Zpt_global.pdf");
  }

  if (variable_name == "h_eventHT" ) {c1->SaveAs("before_apply_Kfactor_HT.pdf") ;
//    c2->SaveAs("after_apply_Kfactor_HT_onlyDiagonal.pdf");
    c2->SaveAs("after_apply_Kfactor_HT_global.pdf");
  }

}


void My_plotting( TCanvas* & c_ , TPad* pad_a, TPad* pad_b, 
		  TH1F* h_NLO, TH1F* h_LO_combine, TH1F* h_Ht100to200, TH1F* h_Ht200to400, TH1F* h_Ht400to600, TH1F* h_Ht600toInf,  
		  int option ){


  TH1F *h_ratio_ = (TH1F*) h_LO_combine ->Clone("h_ratio_");
  h_ratio_ ->Sumw2();
  h_ratio_ ->Divide( h_NLO );


  // ----------------

  gStyle->SetOptStat(0);

  if( option == 0) h_NLO->SetTitle("before apply k-factor, scale each sample to lumi=1/pb");
  if( option == 1) h_NLO->SetTitle("after apply k-factor, scale each sample to lumi=1/pb");

  if (variable_name == "h_genZpt"  ) h_ratio_ ->GetXaxis()->SetTitle("gen Z pt [GeV]");
  if (variable_name == "h_eventHT" ) h_ratio_ ->GetXaxis()->SetTitle("HT [GeV]");

//  h_NLO->GetXaxis()->SetTitle("gen Z pt [GeV]");
  h_NLO->GetYaxis()->SetTitle("Events");
  h_NLO->GetYaxis()->SetTitleSize(0.05);
  h_NLO->GetYaxis()->SetTitleOffset(0.7);


  h_NLO->GetXaxis()->SetRangeUser(0, 1000);
//  h_NLO->GetXaxis()->SetRangeUser(0, 3000);
  h_NLO->GetYaxis()->SetRangeUser(0.0001, 1000);
//  h_NLO->GetYaxis()->SetRangeUser(0.000001, 1000);

  h_ratio_ ->GetXaxis()->SetRangeUser(0, 1000);
//  h_ratio_ ->GetXaxis()->SetRangeUser(0, 3000);
  h_ratio_ ->GetYaxis()->SetRangeUser(0, 2);

//  h_ratio_ ->GetXaxis()->SetTitle("gen Z pt [GeV]");
  h_ratio_ ->GetYaxis()->SetTitle("LO/NLO");
  h_ratio_ ->SetTitle("");

  h_ratio_ ->GetXaxis()->SetLabelSize(0.08);
  h_ratio_ ->GetYaxis()->SetLabelSize(0.08);
  h_ratio_ ->GetXaxis()->SetTitleSize(0.1);
  h_ratio_ ->GetYaxis()->SetTitleSize(0.1);
  h_ratio_ ->GetYaxis()->SetTitleOffset(0.3);
  h_ratio_ ->GetYaxis()->SetNdivisions(505);

  h_Ht100to200 ->SetLineColor(2);
  h_Ht200to400 ->SetLineColor(6);
  h_Ht400to600 ->SetLineColor(7);
  h_Ht600toInf ->SetLineColor(801); 

//  h_NLO        ->SetLineColor(801);
  h_LO_combine ->SetLineColor(3);
  h_ratio_     ->SetLineColor(602);

  h_NLO        ->SetLineWidth(3);
  h_Ht100to200 ->SetLineWidth(3);
  h_Ht200to400 ->SetLineWidth(3);
  h_Ht400to600 ->SetLineWidth(3);
  h_Ht600toInf ->SetLineWidth(3);
  h_LO_combine ->SetLineWidth(3);
  h_ratio_     ->SetLineWidth(3);

  // ----------------

  c_->cd();

  pad_a->SetBottomMargin(0.01);
  pad_a->Draw();
  pad_a->cd();
  pad_a->SetLogy();

    h_NLO                 ->Draw("same histe");
    h_Ht100to200 ->Draw("same histe");
    h_Ht200to400 ->Draw("same histe");
    h_Ht400to600 ->Draw("same histe");
    h_Ht600toInf ->Draw("same histe");
    h_LO_combine  ->Draw("same histe");

    TLegend *leg1 = new TLegend(0.6, 0.547, 0.9, 0.88); ;
    leg1->AddEntry(h_NLO,"DY NLO inclusive","l");
    leg1->AddEntry(h_LO_combine,"DY LO combined","l");
    if( option == 0 ){
      leg1->AddEntry(h_Ht100to200,"DY LO Ht100to200","l");
      leg1->AddEntry(h_Ht200to400,"DY LO Ht200to400","l");
      leg1->AddEntry(h_Ht400to600,"DY LO Ht400to600","l");
      leg1->AddEntry(h_Ht600toInf,"DY LO Ht600toInf","l");
    }
    else if( option == 1 ){
      leg1->AddEntry(h_Ht100to200,Form("DY LO Ht100to200, k1=%.3f",K1),"l");
      leg1->AddEntry(h_Ht200to400,Form("DY LO Ht200to400, k2=%.3f",K2),"l");
      leg1->AddEntry(h_Ht400to600,Form("DY LO Ht400to600, k3=%.3f",K3),"l");
      leg1->AddEntry(h_Ht600toInf,Form("DY LO Ht600toInf, k4=%.3f",K4),"l");
    }



    leg1->Draw();

  c_->cd();
    pad_b  ->SetTopMargin(0.9);
    pad_b  ->SetBottomMargin(0.3);
    pad_b  ->Draw();
    pad_b  ->cd();
    h_ratio_->Draw("histe");

    TLine *OLine = new TLine(0 ,1. ,3000 ,1.);
    OLine->SetLineColor(kRed);
    OLine->SetLineWidth(1);
    OLine->Draw();


}


void My_Kfactor( TH1F* h_NLO , TH1F* h1, TH1F* h2, TH1F* h3, TH1F* h4){

  // Zpt 100-200 region 
  double a1 = h1->Integral(21,40);
  double b1 = h2->Integral(21,40);
  double c1 = h3->Integral(21,40);
  double d1 = h4->Integral(21,40);
  double e1 = h_NLO->Integral(21,40);

  // Zpt 200-400 region 
  double b2 = h2->Integral(41,80);
  double c2 = h3->Integral(41,80);
  double d2 = h4->Integral(41,80);
  double e2 = h_NLO->Integral(41,80);

  // Zpt 400-600 region 
  double c3 = h3->Integral(81,120);
  double d3 = h4->Integral(81,120);
  double e3 = h_NLO->Integral(81,120);

  // Zpt 600-1000 region 
  double d4 = h4->Integral(121,200);
  double e4 = h_NLO->Integral(121,200);


  double k1,k2,k3,k4;

  k4 = e4/d4 ;
  k3 = ( e3 - d3*k4 )/c3 ;
  k2 = ( e2 - c2*k3 - d2*k4 )/b2 ;
  k1 = ( e1 - b1*k2 - c1*k3 - d1*k4 )/a1 ;

  cout<<"k1: "<<k1<<" k2: "<<k2<<" k3: "<<k3<<" k4: "<<k4<< endl;

  // save the output k into global variable K 
  K1 = k1;
  K2 = k2;
  K3 = k3;
  K4 = k4;

}

