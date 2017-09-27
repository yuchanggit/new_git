#define my_MakeClass_cxx
#include "my_MakeClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <TLorentzVector.h> // Yu-Hsiang add (maybe need)

void my_MakeClass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L my_MakeClass.C
//      root> my_MakeClass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   if (fChain == 0) return;

  // Below: Yu-Hsiang add -----------------------------------------
  std::string remword=".root";                                    //
  size_t pos = inputFile_.find(remword);                          //
  std::string forOutput = inputFile_;                             // 
  if(pos!= std::string::npos)                                     //
    forOutput.swap(forOutput.erase(pos,remword.length()));        //
  std::string endfix = "_filtered.root";                          //
  std::string outputFile = forOutput + endfix;                    //
   // now open new root file                                      //
  TFile* newfile_data = new TFile(outputFile.data(),"recreate");  //

  // clone tree                                                   //
  TTree* newtree = fChain->CloneTree(0);                          //
  newtree->SetMaxTreeSize(5000000000);                            //
  cout << "Saving "  << outputFile       << " tree" << endl;      //

  ofstream fout;                                                  //
  fout.open("wrong.dat");                                         //
  // Above: Yu-Hsiang add ----------------------------------------- 


  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nPassEvt=0; // Yu-Hsiang add

  Long64_t nbytes = 0, nb = 0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) { // event loop
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    // Below: Yu-Hsiang add ---------------------------------------------------
									     //
    if (jentry%100==0)                                                       //
      printf("%4.1f%% done.\r",(float)jentry/(float)nentries*100.);          //
									     //
    // an example: if nEle>=2 and ele[0]Pt>55, ele[1]Pt>20 then pass the skim//
									     //
    bool passElePt = false;                                                  //
    double elePt0,elePt1;                                                    //
									     //
    if (nEle>=2){                                                            //
									     //
      elePt0 = ( (TLorentzVector*) eleP4->At(0) )->Pt();                     //
      elePt1 = ( (TLorentzVector*) eleP4->At(1) )->Pt();                     //
									     //
      if (elePt0>55 && elePt1>20) passElePt = true;                          //
    }                                                                        //
									     //
    if (!passElePt) continue;                                                //
        								     //
    // if pass skim cut, then fill in the new TTree                          //
    newtree->Fill();                                                         //
    nPassEvt++;                                                              //
                                                                             //
    // Above: Yu-Hsiang add --------------------------------------------------- 

  }// end event loop

  newtree->AutoSave(); // Yu-Hsiang add
  delete newfile_data; // Yu-Hsiang add
  fout.close(); // Yu-Hsiang add

  cout << "nentries = " << nentries << endl; // Yu-Hsiang add
  cout << "Number of passed events = " << nPassEvt << endl; // Yu-Hsiang add
  cout << "Reduction rate = " << (double)nPassEvt/(double)nentries << endl; // Yu-Hsiang add


}// end my_MakeClass::Loop()
