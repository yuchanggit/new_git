#include <vector>
#include <string>
#include <iostream>
#include <TH1D.h>
#include <TMath.h>
#include <TFile.h>
#include <TChain.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "interface/untuplizer.h"
#include "interface/isPassZee.h"
#include "interface/readSample.h"
#include "interface/standalone_LumiReWeighting.cc"



void eleZVariable(std::string inputFile, std::string outputFile){
//void eleZVariable(){

  // read the ntuples (in pcncu) and combine TTree

  std::vector<string> infiles; 
  readSample(inputFile, infiles);

  cout<<"infiles.size():"<< infiles.size() << endl;

  TChain* tree = new TChain("tree/treeMaker");
  std::string open_root;

  for(unsigned int i=0 ; i<infiles.size() ; i++ ){
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


  TH1D* h_1stEle_pt_3           = new TH1D("h_1stEle_pt_3",           "Leading_pt_stage3",           30,  0, 300);
  TH1D* h_Zpt_3           = new TH1D("h_Zpt_3",           "Zpt_stage3",           60,  0, 600);
  TH1D* h_Zmass_3         = new TH1D("h_Zmass_3",         "Zmass_stage3",         30, 60,  120);


  h_1stEle_pt_3->Sumw2();
  h_Zpt_3->Sumw2();
  h_Zmass_3->Sumw2();

  h_1stEle_pt_3->GetXaxis()->SetTitle("leadElePt");
  h_Zpt_3->GetXaxis()->SetTitle("Zpt");
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
//  int Max_number_to_read =  10;

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){

    if( ev %   Number_to_print == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

    if( ev > Max_number_to_read) break;

    data.GetEntry(ev);

    h_totalEvents->Fill(1,1);

    // -------  nVtx>=1 -------

    Int_t    nVtx                    = data.GetInt("nVtx");

    if( nVtx < 1 ) continue;

    // -------  get Pile-Up weight -------

    Bool_t   isData                  = data.GetBool("isData");

    double PU_weight_central =1;// get PU_weight for MC, but weight=1 for data

    if(!isData){
      standalone_LumiReWeighting LumiWeights_central(0);

      Float_t ntrue= data.GetFloat("pu_nTrueInt");
      PU_weight_central = LumiWeights_central.weight(ntrue);

    }

//    PU_weight_central =1;// if you turn off the PU weight on MC

    // -------- apply HLT ---------------------
    
    std::string* trigName    = data.GetPtrString("hlt_trigName");
    vector<bool>& trigResult = *((vector<bool>*) data.GetPtr("hlt_trigResult"));

    bool triggerStat = false;
//    std::string TRIGGERNAME = "HLT_Ele105";// HLT_Ele105_CaloIdVT_GsfTrkIdT_v3
    std::string TRIGGERNAME = "HLT_Ele";
//    std::string TRIGGERNAME = "HLT_Mu";

//    if (isData){ // apply HLT on data   
    if (true){

//    cout<<"ev: "<< ev << endl;
   
    for(int it = 0; it < data.GetPtrStringSize(); it++){

      std::string thisTrig = trigName[it];
      bool results = trigResult[it];

      if( thisTrig.find(TRIGGERNAME) != std::string::npos  && results )
      cout<<"thisTrig: "<< thisTrig <<" results: "<< results << endl; 

      if( thisTrig.find(TRIGGERNAME) != std::string::npos && results ){
        triggerStat = true;

//      cout<<"thisTrig: "<< thisTrig <<" results: "<< results << endl; 

        break;

      }

    }

    }// if isData
    else triggerStat = true; // don't apply HLT on MC temporarily  

//    if( !triggerStat ) continue;

    counter_0++;

    // ------ select good electrons and Z boson --------
    
    const Int_t*   eleCharge  = data.GetPtrInt("eleCharge");
    const TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");

    vector<Int_t> goodEleID;
    if( !isPassZee(data, goodEleID) ) continue;

    // ------ fill histogram ---------------------------

    TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(goodEleID[0]);
    TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(goodEleID[1]);

    TLorentzVector l4_Z = (*thisEle+*thatEle);

    h_1stEle_pt_3->Fill( thisEle->Pt() , PU_weight_central );
    h_Zpt_3      ->Fill( l4_Z.Pt()     , PU_weight_central );
    h_Zmass_3    ->Fill( l4_Z.M()      , PU_weight_central );

    counter_3++;


  } // end of event loop

  cout<<"counter_0: "<< counter_0 << endl;
  cout<<"counter_1: "<< counter_1 << endl;
  cout<<"counter_2: "<< counter_2 << endl;
  cout<<"counter_3: "<< counter_3 << endl;


  fprintf(stderr, "Processed all events\n");


  TFile* outFile = new TFile( Form("%s.root",outputFile.c_str() ), "recreate");

  h_1stEle_pt_3  ->Write("Leading_pt_stage3");
  h_Zpt_3        ->Write("Zpt_stage3");
  h_Zmass_3      ->Write("Zmass_stage3");

  h_totalEvents ->Write("totalEvents");

  outFile->Write();
  
  delete f;
  delete outFile;


}




