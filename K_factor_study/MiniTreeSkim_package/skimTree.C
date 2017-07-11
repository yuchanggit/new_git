#include <vector>
#include <string>
#include <iostream>
#include <TH1D.h>
#include <TMath.h>
#include <TFile.h>
#include "TTree.h"
#include <TChain.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TF1.h>

#include "untuplizer.h"

using namespace std;

//void xAna_ele(){
void skimTree(int w , string st){

//  std::string inputFile = "ntuple/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/NCUGlobalTuples_973" ;
//  std::string outputFolder = "output";
//  std::string outputFile = "test.root"; 

  cout<<"finish compiling and start to run macro"<< endl;

  // --------  open  ntuples -------------------------------------

  cout<<"w: "<< w << endl;
  cout<<"st: "<< st <<endl;

//  return;
/*
  //  The Way to read Multi-ROOT file


  // get paths of every root files
  std::vector<string> infiles; 
  readSample(inputFile, infiles);

  cout<<"infiles.size():"<< infiles.size() << endl<<endl;

  // combine TTree
//  TChain* tree = new TChain("tree/treeMaker");
  TChain* tree = new TChain("treeMaker");


  for(unsigned int i=0 ; i<infiles.size() ; i++ ){
    std::string open_root="root://" + infiles[i] ;
    tree->Add( open_root.c_str()  );
  }

*/

  //  The Way to read Single ROOT file (combined file from hadd)

//  TString file_path = inputFile + ".root"; 
  TString file_path = st;
  TFile* file_sample = TFile::Open( file_path );
//  TFile* file_sample = TFile::Open(st);
  TTree* tree = (TTree*) file_sample->Get("tree/treeMaker");

//  TChain* tree = new TChain("tree/treeMaker");
//  tree->Add(st.data());
//  TFile* outputfile = new TFile(Form("skimmed_NCUGlobalTuples_%d.root",w),"RECREATE");

  cout<<"tree->GetEntries(): "<< tree->GetEntries() << endl<<endl;

/*
  TH1F* h_totalEv_beforeSkim = NULL;     bool ThisIsMC = false;

  if( inputFile.find("SingleMuon_Run2016")     == std::string::npos && 
      inputFile.find("SingleElectron_Run2016") == std::string::npos ){

    ThisIsMC=true;    
    h_totalEv_beforeSkim = (TH1F*)file_sample->FindObjectAny("h_totalEv"); // Save total events of MC before skimming
//    cout<<"totalEv: "<< h_totalEv_beforeSkim ->Integral() << endl;
  }
*/

  // read the TTree

  TreeReader data( tree );
  cout<<"finish TreeReader data( tree );"<< endl<<endl; 

  // -------- Create new TTree ----------

//  std::string root_name = Form("%s.root",outputFile.c_str() ) ;
//  TString save_path = outputFolder +"/"+  root_name;
//  TFile* outFile = new TFile( save_path , "recreate");

  TFile* outputfile = new TFile(Form("skimmed_NCUGlobalTuples_%d.root",w),"RECREATE");

  // Mini TTree
  TTree* new_tree = new TTree("new_tree", "Skiming MiniTTree");

  float  genZpt;
  float  eventHT;

  new_tree->Branch("genZpt",                 &genZpt,                  "genZpt/F");
  new_tree->Branch("eventHT",                &eventHT,                 "eventHT/F");

  // ------- Declare the histogram ----------------


  TH1D* h_genZpt      = new TH1D("h_genZpt",          "gen Z pt",       600,     0,   3000);
  TH1D* h_eventHT     = new TH1D("h_eventHT",         "event HT",      600,     0,   3000);

  TH1D* h_totalEvents      = new TH1D("h_totalEv",          "totalEvents",       10,     0,   10);

/*
  if(ThisIsMC) h_totalEvents ->Fill ( 1, h_totalEv_beforeSkim ->Integral() );
  else 	       h_totalEvents ->Fill ( 1 );
*/

  // -----------------------------------------

  int counter_0=0;
  int counter_1=0;
  int counter_2=0;    
  int counter_3=0;

  cout<<"finish define new TTree"<< endl<<endl;

  // ------ begin of event loop ---------------

  int Number_to_print =  10000;
//  int Max_number_to_read =  10;

  cout<<"starting loop events"<< endl<<endl;


  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){

//    cout<<endl<<"event: "<< ev <<endl;

    if( ev %   Number_to_print == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

//    if( ev > Max_number_to_read ) break;

    data.GetEntry(ev);


    // get Branch

    // gen-level variable

    Int_t    nGenPar                    = data.GetInt("nGenPar");
    const TClonesArray* genParP4 = (TClonesArray*) data.GetPtrTObject("genParP4");

//    Int_t*   genParQ     = data.GetPtrInt("genParQ");
    Int_t*   genParId    = data.GetPtrInt("genParId");
//    Int_t*   genParSt    = data.GetPtrInt("genParSt");
//    Int_t*   genMomParId = data.GetPtrInt("genMomParId");
//    Int_t*   genParIndex = data.GetPtrInt("genParIndex");
//    Int_t*   genMo1      = data.GetPtrInt("genMo1");
//    Int_t*   genMo2      = data.GetPtrInt("genMo2");
//    Int_t*   genDa1      = data.GetPtrInt("genDa1");
//    Int_t*   genDa2      = data.GetPtrInt("genDa2");

    // variable of event
    Float_t    HT        = data.GetFloat("HT");
    Float_t    mcWeight  = data.GetFloat("mcWeight");

//    Int_t    nVtx                    = data.GetInt("nVtx");

    // selection region

    double eventWeight = 1 ;
    if ( mcWeight < 0 ) eventWeight = -1;

    h_totalEvents->Fill(1.0, eventWeight );


//    cout<<endl<<"nGenPar: "<< nGenPar << endl;

    for ( int iGen=0; iGen<nGenPar; iGen++ ){

      TLorentzVector* thisGenPar = (TLorentzVector*) genParP4 ->At(iGen);

      if( genParId[iGen] != 23 ) continue;

      genZpt  = thisGenPar ->Pt();
      eventHT = HT;

      if( thisGenPar ->Pt() <10 ) continue;
      if( HT <100 ) continue;

      h_genZpt -> Fill( genZpt , eventWeight );
      h_eventHT-> Fill( eventHT, eventWeight );

/*
      cout<<"gen particle loop index: "<< iGen 
          <<" genParId: "<< genParId[iGen] 
          <<" genParQ: "<< genParQ[iGen]
          <<" genParSt: "<< genParSt[iGen]
          <<" genMomParId: "<< genMomParId[iGen]
          <<" genParIndex: "<< genParIndex[iGen]
          <<" genMo1: "<< genMo1[iGen]
          <<" genMo2: "<< genMo2[iGen]
          <<" genDa1: "<< genDa1[iGen]
          <<" genDa2: "<< genDa2[iGen]
          << endl;
*/

/*
      cout<<"pt: "    << thisGenPar ->Pt()
          <<" px: "<< thisGenPar ->Px()
          <<" py: "<< thisGenPar ->Py()
          <<" energy: "<< thisGenPar ->Energy()
          <<" mass: "  << thisGenPar ->M()
          <<" eta: "   << thisGenPar ->Eta()
          <<" phi: "   << thisGenPar ->Phi()
          <<endl;
*/

    }



    // -----------------------------------------------
    new_tree->Fill();


  } // ------------------ end of event loop ------------------

  cout<<"counter_0: "<< counter_0 << endl;
  cout<<"counter_1: "<< counter_1 << endl;
  cout<<"counter_2: "<< counter_2 << endl;
  cout<<"counter_3: "<< counter_3 << endl;


  fprintf(stderr, "Processed all events\n");

  h_totalEvents   ->Write();
  h_genZpt        ->Write();

  new_tree        ->Write();  

//  outFile         ->Write();  
//  delete outFile;
  outputfile      ->Write();
  delete outputfile;

  cout<<endl<<"save ROOT file in: "<< Form("skimmed_NCUGlobalTuples_%d.root",w)  << endl;
//  cout<<endl<<"save ROOT file in: "<< save_path << endl;

}

