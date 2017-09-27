#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <TH1D.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TF1.h>
#include <TCanvas.h>
#include "TMath.h"

#include "untuplizer.h"

void xAna_skim_Ele(std::string inputFile){

  // ----------- open ntuple, read TTree ----------------

  TString file_path = inputFile ;
  TFile* file_sample = TFile::Open( file_path );

  TTree* tree = (TTree*) file_sample->Get("tree/treeMaker");
  cout<<"tree->GetEntries(): "<< tree->GetEntries() << endl<<endl;
  TreeReader data( tree );

  // ----------- begin of event loop ---------------------------------

  ofstream fout;
  fout.open("Event_check.txt");
  cout<<"save event Id in Event_check.txt"<< endl;

  Long64_t Ev_pass = 0;

  int Number_to_print =  5000; int Max_number_to_read =  100;
  cout<<"starting loop events"<< endl<<endl;

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){// event loop

    if( ev %   Number_to_print == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

//    if( ev > Max_number_to_read ) break;

//    cout<<endl<<"this is event: "<< ev <<endl;

    data.GetEntry(ev);


    // get variable Branch 
    Long64_t run          = data.GetLong64("runId");
    Long64_t lumi         = data.GetLong64("lumiSection");
    Long64_t event        = data.GetLong64("eventId");

    Bool_t   isData                  = data.GetBool("isData");

    const Int_t    nEle        = data.GetInt("nEle");
    const TClonesArray* eleP4  = (TClonesArray*) data.GetPtrTObject("eleP4");

    Int_t          FATnJet           = data.GetInt("FATnJet");
    TClonesArray*  FATjetP4          = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    Float_t*       FATjetPuppiSDmass = data.GetPtrFloat("FATjetPuppiSDmass");


    // Ele Pt > 55,20     

    bool passElePt = false;
    double elePt0,elePt1,elePt2;

    if (nEle >= 2){
    
      elePt0 = ( (TLorentzVector*) eleP4->At(0) )->Pt(); 
      elePt1 = ( (TLorentzVector*) eleP4->At(1) )->Pt();

      if (elePt0>55 && elePt1>20) passElePt = true;
    }

    if (!passElePt) continue;


    // FatJet Pt > 200     

    bool passJetPt = false;
    double jetPt0;

    if (FATnJet >= 1){ 

      jetPt0 = ( (TLorentzVector*) FATjetP4->At(0) ) ->Pt() ;
      if ( jetPt0>200 ) passJetPt=true;

    }    

    if (!passJetPt) continue;

    // if pass the skimming (elePt[0]>55 + elePt[1]>20 + jetPt[0]>200)

    fout<< run << " " << lumi << " " << event << endl;
//    cout<< run << " " << lumi << " " << event << endl;

    Ev_pass ++;

  } // ------------------ end of event loop ------------------

  fprintf(stderr, "Processed all events\n");

  fout.close();

  cout<<"Event passing skim: "<< Ev_pass << endl;


}
