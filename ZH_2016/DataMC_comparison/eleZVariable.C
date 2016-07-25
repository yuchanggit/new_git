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




void eleZVariable(std::string inputFile, std::string outputFile){
//void eleZVariable(){

//  std::string inputFile = "/data7/yuchang/NCUGlobalTuples_80X/SingleElectron";

  // read the ntuples (in pcncu) and combine TTree

  std::vector<string> infiles; 
  readSample(inputFile, infiles);

  cout<<"infiles.size():"<< infiles.size() << endl;

  TChain* tree = new TChain("tree/treeMaker");
  std::string open_root;

  for(unsigned int i=0 ; i<infiles.size() ; i++ ){
//  for(unsigned int i=0 ; i<5 ; i++ ){
//    open_root="root://" + infiles[0] ;
    open_root="root://" + infiles[i] ;
//    cout<<"open_root: "<< open_root<< endl;
    tree->Add( open_root.c_str()  );
  }

  cout<<"tree->GetEntries(): "<< tree->GetEntries() << endl;

  // read TTree

  TreeReader data( tree );
 
  // Declare the histogram
     
  TFile* f = new TFile(inputFile.data());
  TH1D* h_totalEvents   = new TH1D("h_totalEv"      , "totalEvents",     10 ,0,     10);


  TH1D* h_1stEle_pt_1           = new TH1D("h_1stEle_pt_1",           "Leading_pt_stage1",           30,  0, 300);
  TH1D* h_1stEle_pt_2           = new TH1D("h_1stEle_pt_2",           "Leading_pt_stage2",           30,  0, 300);
  TH1D* h_1stEle_pt_3           = new TH1D("h_1stEle_pt_3",           "Leading_pt_stage3",           30,  0, 300);

  TH1D* h_2ndEle_pt_2           = new TH1D("h_2ndEle_pt_2",           "SubLeading_pt_stage2",        30,  0, 300);

  TH1D* h_1stEle_eta_2           = new TH1D("h_1stEle_eta_2",         "Leading_eta_stage2",          60 , -3 , 3);
  TH1D* h_2ndEle_eta_2           = new TH1D("h_2ndEle_eta_2",         "SubLeading_eta_stage2",       60 , -3 , 3);


  TH1D* h_Zpt_1           = new TH1D("h_Zpt_1",           "Zpt",           60,  0, 600);
  TH1D* h_Zpt_2           = new TH1D("h_Zpt_2",           "Zpt_stage2",           60,  0, 600);
  TH1D* h_Zpt_3           = new TH1D("h_Zpt_3",           "Zpt_stage3",           60,  0, 600);

  TH1D* h_Zmass_1         = new TH1D("h_Zmass_1",         "Zmass",         30, 60,  120);
  TH1D* h_Zmass_2         = new TH1D("h_Zmass_2",         "Zmass_stage2",         30, 60,  120);
  TH1D* h_Zmass_3         = new TH1D("h_Zmass_3",         "Zmass_stage3",         30, 60,  120);


  h_1stEle_pt_2->Sumw2();
  h_1stEle_pt_3->Sumw2();

  h_2ndEle_pt_2->Sumw2();

  h_1stEle_eta_2->Sumw2();
  h_2ndEle_eta_2->Sumw2();

  h_Zpt_2->Sumw2();
  h_Zpt_3->Sumw2();
  h_Zmass_2->Sumw2();
  h_Zmass_3->Sumw2();

  h_1stEle_pt_2->GetXaxis()->SetTitle("leadElePt");
  h_1stEle_pt_3->GetXaxis()->SetTitle("leadElePt");

  h_2ndEle_pt_2->GetXaxis()->SetTitle("subleadElePt");  

  h_1stEle_eta_2->GetXaxis()->SetTitle("leadEleEta");  
  h_2ndEle_eta_2->GetXaxis()->SetTitle("subleadEleEta");  

  h_Zpt_2->GetXaxis()->SetTitle("Zpt");  
  h_Zpt_3->GetXaxis()->SetTitle("Zpt");

  h_Zmass_2->GetXaxis()->SetTitle("Zmass");  
  h_Zmass_3->GetXaxis()->SetTitle("Zmass");

  // counter 

  int counter_0=0;
  int counter_1=0;
  int counter_2=0;    
  int counter_3=0;


  // begin of event loop

//  int Number_to_print    =  100000;
  int Number_to_print    =  100000;

  int Max_number_to_read = 1000000;
//  int Max_number_to_read = 1000;
//  int Max_number_to_read = 100;

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){

    if( ev %   Number_to_print == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

    if( ev > Max_number_to_read) break;

    data.GetEntry(ev);

    h_totalEvents->Fill(1,1);

    // ------ counter0  --------

    unsigned long eventId            = data.GetLong64("eventId");
    unsigned long runId              = data.GetLong64("runId"); 
    unsigned long lumiSection        = data.GetLong64("lumiSection");

    Bool_t   isData                  = data.GetBool("isData");
    Int_t    nVtx                    = data.GetInt("nVtx");

    std::string* trigName    = data.GetPtrString("hlt_trigName");
    vector<bool>& trigResult = *((vector<bool>*) data.GetPtr("hlt_trigResult"));

    bool triggerStat = false;
    std::string TRIGGERNAME = "HLT_Ele105";// HLT_Ele105_CaloIdVT_GsfTrkIdT_v3

    if (isData){ // apply HLT on data   

    for(int it = 0; it < data.GetPtrStringSize(); it++){

      std::string thisTrig = trigName[it];
      bool results = trigResult[it];

      if( thisTrig.find(TRIGGERNAME) != std::string::npos && results ){
        triggerStat = true;

        break;

      }
    }

    }// if isData
    else triggerStat = true; // don't apply HLT on MC temporarily  


    if( nVtx < 1 ) continue;
//    if( !triggerStat ) continue;

    counter_0++;
//    cout<<"isData: "<< isData << endl;

    // ------ counter1  --------
    
    
    const Int_t    nEle       = data.GetInt("nEle");
    const Int_t*   eleCharge  = data.GetPtrInt("eleCharge");
    const Float_t* eleScEta   = data.GetPtrFloat("eleScEta");
    const Float_t* eleMiniIsoEA = data.GetPtrFloat("eleMiniIsoEA");
    const vector<bool>& eleIsPassHEEPNoIso = *((vector<bool>*) data.GetPtr("eleIsPassHEEPNoIso"));
    const vector<bool>& eleIsPassLoose = *((vector<bool>*) data.GetPtr("eleIsPassLoose"));
    const TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");


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
    goodElectrons.clear();
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
      h_2ndEle_pt_2->Fill( Ele2->Pt() );

      h_1stEle_eta_2->Fill( eleScEta[ goodElectrons[0]   ] );
      h_2ndEle_eta_2->Fill( eleScEta[ goodElectrons[1]   ] );

      h_Zpt_2      ->Fill( Z_boson.Pt()  );
      h_Zmass_2    ->Fill( Z_boson.M() );

    }
    
    // ------ counter3  --------


    // select good Z boson
    vector<Int_t> goodEleID;
    goodEleID.clear();

    bool findEPair = false;
    TLorentzVector* thisEle = NULL;
    TLorentzVector* thatEle = NULL;
    
//    std::cout<<" goodElectrons.size = "<<goodElectrons.size()<<std::endl;
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
//      std::cout<<" goodEleID.size = "<<goodEleID.size()<<std::endl;
      counter_3++;
      TLorentzVector* Ele1 = (TLorentzVector*)eleP4->At( goodEleID[0] );
      TLorentzVector* Ele2 = (TLorentzVector*)eleP4->At( goodEleID[1] );

      TLorentzVector Z_boson = (*Ele1+*Ele2);

/*      
      cout<<"eventId:     "<< eventId << endl;
      cout<<"runId:       "<< runId << endl;
      cout<<"lumiSection: "<< lumiSection << endl;

      std::cout<<" px = "<<Ele1->Px()
	       <<" py = "<<Ele1->Py()
	       <<" pz = "<<Ele1->Pz()
	       <<" E = "<<Ele1->E()
	       <<std::endl;
      std::cout<<" Z pt = "<< Z_boson.Pt()
	       <<" Z mass = "<<Z_boson.M()
	       <<std::endl;
*/      

      h_1stEle_pt_3->Fill( Ele1->Pt() );
      h_Zpt_3      ->Fill( Z_boson.Pt()  );
      h_Zmass_3    ->Fill( Z_boson.M() );

//      cout<<endl;
//      cout<<"ev: "<< ev <<endl;

//      cout<<"Ele1->Pt(): "  << Ele1->Pt()   << endl;
//      cout<<"Z_boson.Pt(): "<< Z_boson.Pt() << endl;
//      cout<<"Z_boson.M(): " << Z_boson.M()  << endl;

    }




  } // end of event loop

  cout<<"counter_0: "<< counter_0 << endl;
  cout<<"counter_1: "<< counter_1 << endl;
  cout<<"counter_2: "<< counter_2 << endl;
  cout<<"counter_3: "<< counter_3 << endl;


  fprintf(stderr, "Processed all events\n");


//  TFile* outFile = new TFile("test_Ele_data.root", "recreate");
  TFile* outFile = new TFile(Form("%s_NoCut.root",outputFile.c_str()), "recreate");



//  h_1stEle_pt_1  ->Write();
//  h_1stEle_pt_2  ->Write();
  h_1stEle_pt_3  ->Write("Leading_pt_stage3");

//  h_Zpt_1        ->Write();
//  h_Zpt_2        ->Write();
  h_Zpt_3        ->Write("Zpt_stage3");

//  h_Zmass_1      ->Write();
//  h_Zmass_2      ->Write();
  h_Zmass_3      ->Write("Zmass_stage3");

/*
  h_1stEle_pt_2  ->Write("Leading_pt_stage2");

  h_2ndEle_pt_2  ->Write("SubLeading_pt_stage2");

  h_1stEle_eta_2  ->Write("Leading_eta_stage2");
  h_2ndEle_eta_2  ->Write("SubLeading_eta_stage2");

  h_Zpt_2        ->Write("Zpt_stage2");

  h_Zmass_2      ->Write("Zmass_stage2");
*/

  h_totalEvents ->Write("totalEvents");

  outFile->Write();
  
  delete f;
  delete outFile;


}




