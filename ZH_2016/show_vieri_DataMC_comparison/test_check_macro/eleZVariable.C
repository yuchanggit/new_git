#include <vector>
#include <string>
#include <iostream>
#include <TH1D.h>
#include <TMath.h>
#include <TFile.h>
#include <TChain.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include "../interface/untuplizer.h"
#include "../interface/isPassZee.h"
#include "../interface/readSample.h"




//void eleZVariable(std::string inputFile, std::string outputFile){
void eleZVariable(){

  std::string inputFile = "/data7/yuchang/NCUGlobalTuples_80X/SingleElectron";

  // read the ntuples (in pcncu) and combine TTree

  std::vector<string> infiles; 
  readSample(inputFile, infiles);

  cout<<"infiles.size():"<< infiles.size() << endl;

  TChain* tree = new TChain("tree/treeMaker");
  std::string open_root;

  for(unsigned int i=0 ; i<infiles.size() ; i++ ){
    open_root="root://" + infiles[0] ; tree->Add( open_root.c_str()  );
  }

  cout<<"tree->GetEntries(): "<< tree->GetEntries() << endl;

  // read TTree

  TreeReader data( tree );
 
  // Declare the histogram
     
  TFile* f = new TFile(inputFile.data());
  TH1D* h_totalEvents   = new TH1D("h_totalEv"      , "h_totalEv",     10 ,0,     10);


  TH1D* h_Zmass         = new TH1D("h_Zmass",         "Zmass",         30, 60,  120);
  TH1D* h_Zpt           = new TH1D("h_Zpt",           "Zpt",           50,  0, 1000);
  TH1D* h_Zeta          = new TH1D("h_Zeta",          "Zeta",          40, -4,    4);
  TH1D* h_ZRapidity     = new TH1D("h_ZRapidity",     "ZRapidity",     40, -4,    4);
  TH1D* h_leadElePt     = new TH1D("h_leadElePt",     "leadElePt",     16,  0,  800);
  TH1D* h_leadEleEta    = new TH1D("h_leadEleEta",    "leadEleEta",    40, -4,    4);
  TH1D* h_subleadElePt  = new TH1D("h_subleadElePt",  "subleadElePt",  25,  0,  500);
  TH1D* h_subleadEleEta = new TH1D("h_subleadEleEta", "subleadEleEta", 40, -4,    4);

  TH1D* h_1stEle_pt_1           = new TH1D("h_1stEle_pt_1",           "h_1stEle_pt_1",           30,  0, 300);
  TH1D* h_1stEle_pt_2           = new TH1D("h_1stEle_pt_2",           "h_1stEle_pt_2",           30,  0, 300);
  TH1D* h_1stEle_pt_3           = new TH1D("h_1stEle_pt_3",           "h_1stEle_pt_3",           30,  0, 300);

  TH1D* h_Zpt_1           = new TH1D("h_Zpt_1",           "Zpt",           60,  0, 600);
  TH1D* h_Zpt_2           = new TH1D("h_Zpt_2",           "Zpt",           60,  0, 600);
  TH1D* h_Zpt_3           = new TH1D("h_Zpt_3",           "Zpt",           60,  0, 600);

  TH1D* h_Zmass_1         = new TH1D("h_Zmass_1",         "Zmass",         30, 60,  120);
  TH1D* h_Zmass_2         = new TH1D("h_Zmass_2",         "Zmass",         30, 60,  120);
  TH1D* h_Zmass_3         = new TH1D("h_Zmass_3",         "Zmass",         30, 60,  120);

  h_Zmass        ->Sumw2();
  h_Zpt          ->Sumw2();
  h_Zeta         ->Sumw2();
  h_ZRapidity    ->Sumw2();
  h_leadElePt    ->Sumw2();
  h_leadEleEta   ->Sumw2();
  h_subleadElePt ->Sumw2();
  h_subleadEleEta->Sumw2(); 
  
  h_Zmass        ->GetXaxis()->SetTitle("Zmass"); 
  h_Zpt          ->GetXaxis()->SetTitle("Zpt");   
  h_Zeta         ->GetXaxis()->SetTitle("Zeta");    
  h_ZRapidity    ->GetXaxis()->SetTitle("ZRapidity");
  h_leadElePt    ->GetXaxis()->SetTitle("leadElePt");  
  h_leadEleEta   ->GetXaxis()->SetTitle("leadEleEta");
  h_subleadElePt ->GetXaxis()->SetTitle("subleadElePt");   
  h_subleadEleEta->GetXaxis()->SetTitle("subleadEleEta"); 

  // counter 

  int counter_0=0;
  int counter_1=0;
  int counter_2=0;    
  int counter_3=0;


  // begin of event loop

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){

//    if( ev %   100000 == 0 )
    if( ev %   100000 == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

    if( ev > 1000000)break;
//    if( ev > 100)break;


    data.GetEntry(ev);

    h_totalEvents->Fill(1,1);

    const Int_t    nEle       = data.GetInt("nEle");
    Bool_t   isData                  = data.GetBool("isData");
    const Int_t*   eleCharge  = data.GetPtrInt("eleCharge");
    const Float_t* eleScEta   = data.GetPtrFloat("eleScEta");
    const Float_t* eleMiniIsoEA = data.GetPtrFloat("eleMiniIsoEA");
    const vector<bool>& eleIsPassHEEPNoIso = *((vector<bool>*) data.GetPtr("eleIsPassHEEPNoIso"));
    const vector<bool>& eleIsPassLoose = *((vector<bool>*) data.GetPtr("eleIsPassLoose"));
    const TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");

    // ------ counter0  --------

    counter_0++;
//    cout<<"isData: "<< isData << endl;

    // ------ counter1  --------

    if (nEle >1){
      counter_1++;
      TLorentzVector* Ele1 = (TLorentzVector*)eleP4->At(0);
      TLorentzVector* Ele2 = (TLorentzVector*)eleP4->At(1);
      if ( Ele1->Pt() < Ele2->Pt()    ){cout<<" ele[1] pt > ele[0]     "<<endl; }

      TLorentzVector Z_boson = (*Ele1+*Ele2);

      h_1stEle_pt_1->Fill( Ele1->Pt() );
      h_Zpt_1      ->Fill( Z_boson.Pt()  );
      h_Zmass_1    ->Fill( Z_boson.M() );
    }
    // ------ counter2  --------

    // select good electrons 
    std::vector<Int_t> goodElectrons;

    for(Int_t ie = 0; ie < nEle; ie++){

      TLorentzVector* myEle = (TLorentzVector*)eleP4->At(ie);

      if( !(fabs(eleScEta[ie]) < 1.4442 || fabs(eleScEta[ie]) > 1.566) ) continue;
      if( fabs(eleScEta[ie]) > 2.5 ) continue;
      if( myEle->Pt() < 35 ) continue;

      if( !eleIsPassLoose[ie] ) continue; 

      goodElectrons.push_back(ie);
    }

    if ( goodElectrons.size() >1 ){
      counter_2++;
      TLorentzVector* Ele1 = (TLorentzVector*)eleP4->At( goodElectrons[0] );
      TLorentzVector* Ele2 = (TLorentzVector*)eleP4->At( goodElectrons[1] );

      TLorentzVector Z_boson = (*Ele1+*Ele2);

      h_1stEle_pt_2->Fill( Ele1->Pt() );
      h_Zpt_2      ->Fill( Z_boson.Pt()  );
      h_Zmass_2    ->Fill( Z_boson.M() );
    }
    
    // ------ counter3  --------

    // select good Z boson
    vector<Int_t> goodEleID;

    bool findEPair = false;
    TLorentzVector* thisEle = NULL;
    TLorentzVector* thatEle = NULL;

    for(unsigned int i = 0; i < goodElectrons.size(); i++){

      Int_t ie = goodElectrons[i];
      thisEle = (TLorentzVector*)eleP4->At(ie);

      for(unsigned int j = 0; j < i; j++){

        Int_t je = goodElectrons[j];
        thatEle = (TLorentzVector*)eleP4->At(je);

        Float_t pt1 = thisEle->Pt();
        Float_t pt2 = thatEle->Pt();
        Float_t mll = (*thisEle+*thatEle).M();
        Float_t ptll = (*thisEle+*thatEle).Pt();

        if( eleCharge[ie]*eleCharge[je] > 0 ) continue;   
        if( TMath::Max(pt1,pt2) < 115 ) continue;
        if( mll < 70 || mll > 110 ) continue;
        if( ptll < 200 ) continue;

        if( !findEPair ){

	  goodEleID.push_back( (pt1 > pt2) ? ie : je );
	  goodEleID.push_back( (pt1 > pt2) ? je : ie );

        }// end if

        findEPair = true;
        break;

      }// loop j
    }// loop i

    if ( goodEleID.size() >1 ){
      counter_3++;
      TLorentzVector* Ele1 = (TLorentzVector*)eleP4->At( goodEleID[0] );
      TLorentzVector* Ele2 = (TLorentzVector*)eleP4->At( goodEleID[1] );

      TLorentzVector Z_boson = (*Ele1+*Ele2);

      h_1stEle_pt_3->Fill( Ele1->Pt() );
      h_Zpt_3      ->Fill( Z_boson.Pt()  );
      h_Zmass_3    ->Fill( Z_boson.M() );
    }


  } // end of event loop

  cout<<"counter_0: "<< counter_0 << endl;
  cout<<"counter_1: "<< counter_1 << endl;
  cout<<"counter_2: "<< counter_2 << endl;
  cout<<"counter_3: "<< counter_3 << endl;


  fprintf(stderr, "Processed all events\n");


  TFile* outFile = new TFile("test_Ele_data.root", "recreate");

  h_1stEle_pt_1  ->Write("");
  h_1stEle_pt_2  ->Write("");
  h_1stEle_pt_3  ->Write("");

  h_Zpt_1        ->Write("");
  h_Zpt_2        ->Write("");
  h_Zpt_3        ->Write("");

  h_Zmass_1      ->Write("");
  h_Zmass_2      ->Write("");
  h_Zmass_3      ->Write("");  

  outFile->Write();
  
  delete f;
  delete outFile;




}

