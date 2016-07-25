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

Float_t pileupWeight(Int_t puntrueint){

  if ( puntrueint <0  ){ return 1; } // for data, the puntrueint is a big negative value

  Float_t puweight[200]= {1.};

  puweight[0]   =  1.;
  puweight[1]   =  162.405;
  puweight[2]   =  123.505;
  puweight[3]   =  30.4728;
  puweight[4]   =  17.0003;
  puweight[5]   =  3.16955;
  puweight[6]   =  1.67983;
  puweight[7]   =  2.00222;
  puweight[8]   =  2.70321;
  puweight[9]   =  2.72198;
  puweight[10]  =  2.66497;
  puweight[11]  =  2.61761;
  puweight[12]  =  2.3039;
  puweight[13]  =  1.73163;
  puweight[14]  =  1.09124;
  puweight[15]  =  0.572786;
  puweight[16]  =  0.25889;
  puweight[17]  =  0.110005;
  puweight[18]  =  0.0524568;
  puweight[19]  =  0.0299666;
  puweight[20]  =  0.0176408;
  puweight[21]  =  0.00921793;
  puweight[22]  =  0.00407931;
  puweight[23]  =  0.00156008;
  puweight[24]  =  0.000561605;
  puweight[25]  =  0.000223715;
  puweight[26]  =  0.000111408;
  puweight[27]  =  6.9408e-05;
  puweight[28]  =  5.01042e-05;
  puweight[29]  =  3.8732e-05;
  puweight[30]  =  2.89728e-05;
  puweight[31]  =  1.87439e-05;
  puweight[32]  =  9.51068e-06;
  puweight[33]  =  4.2903e-06;
  puweight[34]  =  1.69486e-06;
  puweight[35]  =  6.29131e-07;
  puweight[36]  =  2.21324e-07;
  puweight[37]  =  7.49491e-08;
  puweight[38]  =  2.42443e-08;
  puweight[39]  =  7.36554e-09;
  puweight[40]  =  2.22336e-09;
  puweight[41]  =  6.25637e-10;
  puweight[42]  =  1.77453e-10;
  puweight[43]  =  4.67515e-11;
  puweight[44]  =  1.14411e-11;
  puweight[45]  =  2.96267e-12;
  puweight[46]  =  2.13236e-12;
  puweight[47]  =  7.14993e-13;
  puweight[48]  =  4.02716e-13;
  puweight[49]  =  3.10075e-13;

  if( puntrueint >= 50 ) puweight[puntrueint] = 0;
  return puweight[puntrueint];

//  if ( puntrueint >=0 ){      
//	 if( puntrueint >= 50 ) puweight[puntrueint] = 0;
//         return puweight[puntrueint];
//  }

//  if ( puntrueint <0  ){ return 1; } // for data, the puntrueint is a big negative value

}



void eleZVariable(std::string inputFile, std::string outputFile){

  // read the ntuples (in pcncu) and combine TTree

  std::vector<string> infiles; 
  readSample(inputFile, infiles);

  cout<<"infiles.size():"<< infiles.size() << endl;

  TChain* tree = new TChain("tree/treeMaker");
  std::string open_root;

  for(unsigned int i=0 ; i<infiles.size() ; i++ ){
//    cout<<"infiles[i]: "<< infiles[i]<< endl;
    open_root="root://" + infiles[0] ; tree->Add( open_root.c_str()  );
  }

  cout<<"tree->GetEntries(): "<< tree->GetEntries() << endl;

  // read TTree

  TreeReader data( tree );
 
  // Declare the histogram
     
  TFile* f = new TFile(inputFile.data());
//  TH1D* h_totalEvents = (TH1D*)f->Get("h_totalEv");
  TH1D* h_totalEvents   = new TH1D("h_totalEv"      , "h_totalEv",     10 ,0,     10);

//  TH1D* h_ele1_pt_Nocut = new TH1D("h_ele1_pt_Nocut", ""     ,         50, 0,  1000);

  TH1D* h_Zmass         = new TH1D("h_Zmass",         "Zmass",         30, 60,  120);
  TH1D* h_Zpt           = new TH1D("h_Zpt",           "Zpt",           50,  0, 1000);
  TH1D* h_Zeta          = new TH1D("h_Zeta",          "Zeta",          40, -4,    4);
  TH1D* h_ZRapidity     = new TH1D("h_ZRapidity",     "ZRapidity",     40, -4,    4);
  TH1D* h_leadElePt     = new TH1D("h_leadElePt",     "leadElePt",     16,  0,  800);
  TH1D* h_leadEleEta    = new TH1D("h_leadEleEta",    "leadEleEta",    40, -4,    4);
  TH1D* h_subleadElePt  = new TH1D("h_subleadElePt",  "subleadElePt",  25,  0,  500);
  TH1D* h_subleadEleEta = new TH1D("h_subleadEleEta", "subleadEleEta", 40, -4,    4);

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
    
  // begin of event loop

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){

//    if( ev % 1000000 == 0 )
    if( ev %   100000 == 0 )
//    if( ev %   5000 == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

    if( ev > 1000000)break;
//    if( ev > 20000)break;
//    if( ev > 50)break;


    data.GetEntry(ev);

    Float_t pu_nTrueInt = data.GetFloat("pu_nTrueInt");
    Int_t puntrueint = pu_nTrueInt;
    float pu_weight =  pileupWeight( puntrueint);

    Bool_t   isData                  = data.GetBool("isData");

//    Float_t eventWeight = data.GetFloat("ev_weight");

    float new_eventWeight = 1;


//    if( isData) {new_eventWeight = eventWeight; }//  for data, eventWeight = 1 already
//    if(!isData) {new_eventWeight = eventWeight * pu_weight; }

    h_totalEvents->Fill(1,1); 


    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");

    // test
    const Int_t    nEle       = data.GetInt("nEle");
    for(Int_t ie = 0; ie < nEle; ie++){

      TLorentzVector* myEle = (TLorentzVector*)eleP4->At(ie);
//      h_ele1_pt_Nocut ->Fill( myEle->Pt()   );

    }

    // select good electrons

    vector<Int_t> goodEleID;
    if( !isPassZee(data, goodEleID) ) continue;

    TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(goodEleID[0]);
    TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(goodEleID[1]);

    TLorentzVector l4_Z = (*thisEle+*thatEle);

    cout<<"l4_Z.M(): "<< l4_Z.M() << endl;

    h_Zmass    ->Fill(l4_Z.M(),new_eventWeight);
    h_Zpt      ->Fill(l4_Z.Pt(),new_eventWeight);
    h_Zeta     ->Fill(l4_Z.Eta(),new_eventWeight);
    h_ZRapidity->Fill(l4_Z.Rapidity(),new_eventWeight);

    if( thisEle->Pt() > thatEle->Pt() ){

      h_leadElePt    ->Fill(thisEle->Pt(),new_eventWeight);
      h_leadEleEta   ->Fill(thisEle->Eta(),new_eventWeight);
      h_subleadElePt ->Fill(thatEle->Pt(),new_eventWeight);
      h_subleadEleEta->Fill(thatEle->Eta(),new_eventWeight);

    }else{

      h_leadElePt    ->Fill(thatEle->Pt(),new_eventWeight);
      h_leadEleEta   ->Fill(thatEle->Eta(),new_eventWeight);
      h_subleadElePt ->Fill(thisEle->Pt(),new_eventWeight);
      h_subleadEleEta->Fill(thisEle->Eta(),new_eventWeight);

    }

  } // end of event loop



  fprintf(stderr, "Processed all events\n");

  TFile* outFile = new TFile(Form("%s_ZeeVariable.root",outputFile.c_str()), "recreate");

//  h_ele1_pt_Nocut->Write("test_ele0_pt");
      
  h_Zmass        ->Write("Zmass");
  h_Zpt          ->Write("Zpt");
  h_Zeta         ->Write("Zeta");
  h_ZRapidity    ->Write("ZRapidity");
  h_leadElePt    ->Write("leadElePt");
  h_leadEleEta   ->Write("leadEleEta");
  h_subleadElePt ->Write("subleadElePt");
  h_subleadEleEta->Write("subleadEleEta");
  h_totalEvents  ->Write("totalEvents");
  
  outFile->Write();
  
  delete f;
  delete outFile;




}

