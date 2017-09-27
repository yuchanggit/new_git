#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include <TH1F.h>

#include <iostream>
#include <fstream>

#include "untuplizer.h"

using namespace std;

void skimTree_Ele( string st ){

  // open ROOT file
  TChain* tree = new TChain("tree/treeMaker");
  tree->Add(st.data());

  // skim tree
  TFile* outputfile = new TFile("skimmed_output.root","RECREATE");
  TTree* newtree = tree->CopyTree("( eleP4[0].Pt()>55 && eleP4[1].Pt()>20 && FATjetP4[0].Pt()>200)");

  // print number of events and event Id 

  cout<<"events passing skim: "<< newtree->GetEntries() <<endl;


  ofstream fout;
  fout.open("Event_check_skimTree.txt");
  cout<<"save event Id in Event_check_skimTree.txt"<< endl;

  TreeReader data( newtree );

  int Number_to_print =  5000;

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){// event loop

    if( ev %   Number_to_print == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

    data.GetEntry(ev);

    Long64_t run          = data.GetLong64("runId");
    Long64_t lumi         = data.GetLong64("lumiSection");
    Long64_t event        = data.GetLong64("eventId");

    fout<< run << " " << lumi << " " << event << endl;
//   cout<< run << " " << lumi << " " << event << endl;
  }

  fprintf(stderr, "Processed all events\n");

  fout.close();

  // save 
  newtree->AutoSave();
//  delete outputfile;

}
