#include <vector>
#include <string>
#include <iostream>
#include <TH1D.h>
#include <TFile.h>
#include <TProfile.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
//#include "../../untuplizer.h"
//#include "../../readSample.h"
//#include "../../dataFilter.h"
//#include "../../correctMCweight.h"
#include "untuplizer.h"
#include "readSample.h"
#include "dataFilter.h"
#include "correctMCweight.h"
#include "TCanvas.h"
#include "TString.h"

void eleVariable(std::string inputFile, std::string outputFile){

  // read the ntuples (in pcncu)

  std::vector<string> infiles;

  readSample(inputFile, infiles);
  
  TreeReader data(infiles);

  // try save TTree for skim sample
  TTree* tree_pass = new TTree("treeMaker","save event after pre-selection");

  int nEle_pass; tree_pass->Branch("nEle_pass",&nEle_pass,"nEle_pass/I");
  double eventWeight_pass; tree_pass->Branch("eventWeight_pass",&eventWeight_pass,"eventWeight_pass/D");

  vector<float> eleScEn_pass;// tree_pass->Branch("eleScEn_pass",&eleScEn_pass,"eleScEn_pass/F");
  tree_pass->Branch("eleScEn_pass",&eleScEn_pass); 

  vector<float> eleScEta_pass; tree_pass->Branch("eleScEta_pass",&eleScEta_pass);
  vector<float> eleEtaseedAtVtx_pass; tree_pass->Branch("eleEtaseedAtVtx_pass",&eleEtaseedAtVtx_pass);
  vector<float> eledPhiAtVtx_pass; tree_pass->Branch("eledPhiAtVtx_pass",&eledPhiAtVtx_pass);
  vector<float> eleHoverE_pass; tree_pass->Branch("eleHoverE_pass",&eleHoverE_pass);
  vector<int> eleMissHits_pass; tree_pass->Branch("eleMissHits_pass",&eleMissHits_pass);
  vector<float> eleD0_pass; tree_pass->Branch("eleD0_pass",&eleD0_pass);
  vector<float> eleMiniIsoEA_pass; tree_pass->Branch("eleMiniIsoEA_pass",&eleMiniIsoEA_pass);
  vector<float> eleE2x5Full5x5_pass; tree_pass->Branch("eleE2x5Full5x5_pass",&eleE2x5Full5x5_pass);
  vector<float> eleE5x5Full5x5_pass; tree_pass->Branch("eleE5x5Full5x5_pass",&eleE5x5Full5x5_pass);
  vector<float> eleE1x5Full5x5_pass; tree_pass->Branch("eleE1x5Full5x5_pass",&eleE1x5Full5x5_pass);
  vector<float> eleSigmaIEtaIEtaFull5x5_pass; tree_pass->Branch("eleSigmaIEtaIEtaFull5x5_pass",&eleSigmaIEtaIEtaFull5x5_pass);



  // Declare the histogram (barrel,endcap)

  TH1D* h_eventWeight[2];

  for(Int_t i = 0; i < 2; i++){
    h_eventWeight[i]             = new TH1D(Form("h_eventWeight%d",i),             "eventWeight",              2,     -1,     1);
  }
/*
*/
  // define for cut flow

  Long64_t nTotal=0;
  Long64_t nPass[20]={0};

  // begin of event loop

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){

    if( ev % 1000000 == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

    data.GetEntry(ev);
    nTotal ++;

    Int_t    nVtx                    = data.GetInt("nVtx");
    Int_t    nEle                    = data.GetInt("nEle");
    Int_t*   eleMissHits             = data.GetPtrInt("eleMissHits");
    Bool_t   isData                  = data.GetBool("isData");
    Float_t  pu_nTrueInt             = data.GetFloat("pu_nTrueInt");
    Float_t* eleScEn                 = data.GetPtrFloat("eleScEn");
    Float_t* eleScEt                 = data.GetPtrFloat("eleScEt");
    Float_t* eleScEta                = data.GetPtrFloat("eleScEta");
    Float_t* eleEtaseedAtVtx         = data.GetPtrFloat("eleEtaseedAtVtx");	
    Float_t* eledPhiAtVtx            = data.GetPtrFloat("eledPhiAtVtx");
    Float_t* eleHoverE               = data.GetPtrFloat("eleHoverE");
    Float_t* eleSigmaIEtaIEtaFull5x5 = data.GetPtrFloat("eleSigmaIEtaIEtaFull5x5");
    Float_t* eleE1x5Full5x5          = data.GetPtrFloat("eleE1x5Full5x5");
    Float_t* eleE2x5Full5x5          = data.GetPtrFloat("eleE2x5Full5x5");
    Float_t* eleE5x5Full5x5          = data.GetPtrFloat("eleE5x5Full5x5");   
    Float_t* eleD0                   = data.GetPtrFloat("eleD0");
    Float_t* eleMiniIsoEA            = data.GetPtrFloat("eleMiniIsoEA");
    TClonesArray* eleP4              = (TClonesArray*) data.GetPtrTObject("eleP4");
    vector<bool>& eleEcalDrivenSeed  = *((vector<bool>*) data.GetPtr("eleEcalDrivenSeed"));

    // remove event which is no hard interaction (noise)

    if( nVtx < 1 ) continue;
    nPass[0]++;

    // Correct the pile-up shape of MC

    Double_t eventWeight = correctMCWeight(isData, (Int_t)pu_nTrueInt);
    
    h_eventWeight[0]->Fill(0.,eventWeight);
    h_eventWeight[1]->Fill(0.,eventWeight);

    // data filter (to filter non-collision bkg (ECAL/HCAL noise)) and trigger cut
      
    bool eleTrigger = TriggerStatus(data, "HLT_Ele105");
    bool CSCT       = FilterStatus(data, "Flag_CSCTightHaloFilter");
    bool eeBadSc    = FilterStatus(data, "Flag_eeBadScFilter");
    bool Noise      = FilterStatus(data, "Flag_HBHENoiseFilter");
    bool NoiseIso   = FilterStatus(data, "Flag_HBHENoiseIsoFilter");

    if( !eleTrigger ) continue;
    nPass[1]++;

    if( isData && !CSCT ) continue;
    if( isData && !eeBadSc ) continue;
    if( isData && !Noise ) continue;
    if( isData && !NoiseIso ) continue;
    nPass[2]++;

    // choosing electron

    vector<Int_t> eleId;

    bool findEPair = false;
    
    for(Int_t ie = 0; ie < nEle; ie++){

      if( !(fabs(eleScEta[ie]) < 1.442 || fabs(eleScEta[ie]) > 1.566) ) continue;
      if( fabs(eleScEta[ie]) > 2.5 ) continue;

      TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);
      
      for(Int_t je = 0; je < ie; je++){

	if( eleScEt[ie] <= 35 || eleScEt[je] <= 35 ) continue;
	if( !eleEcalDrivenSeed[ie] || !eleEcalDrivenSeed[je] ) continue;
	if( !(fabs(eleScEta[je]) < 1.442 || fabs(eleScEta[je]) > 1.566) ) continue;
	if( fabs(eleScEta[je]) > 2.5 ) continue;

	TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(je);
	
	Float_t mll  = (*thisEle+*thatEle).M();
	Float_t ptll = (*thisEle+*thatEle).Pt();

	if( mll < 60 || mll > 120 ) continue;		
	if( ptll < 150 ) continue;

	if( !findEPair ){

	  eleId.push_back(ie);
	  eleId.push_back(je);

	} 

	findEPair = true;
	break;
	
      }
    }

    if(	!findEPair ) continue;
    nPass[3]++;   

    // save event in TTree for skim

    nEle_pass = nEle;
    eventWeight_pass = eventWeight ;

    eleScEn_pass .clear();
    eleScEta_pass .clear();
    eleEtaseedAtVtx_pass .clear();
    eledPhiAtVtx_pass .clear();
    eleHoverE_pass .clear();
    eleMissHits_pass .clear();
    eleD0_pass .clear();
    eleMiniIsoEA_pass .clear();
    eleE2x5Full5x5_pass .clear();
    eleE5x5Full5x5_pass .clear();
    eleE1x5Full5x5_pass .clear();
    eleSigmaIEtaIEtaFull5x5_pass .clear();

    for(Int_t ie = 0; ie < nEle; ie++){

	if( !( ie == eleId[0] || ie == eleId[1]) ) continue;// only save the electron pair 

//       cout<<"eleScEn[ie] in : "<< eleScEn[ie] << endl;
       eleScEn_pass.push_back( eleScEn[ie]   ); 
//       h_eleScEn_pass->Fill(eleScEn[ie]);

       eleScEta_pass.push_back( eleScEta[ie]   );
       eleEtaseedAtVtx_pass.push_back( eleEtaseedAtVtx[ie]   );
       eledPhiAtVtx_pass.push_back( eledPhiAtVtx[ie]   );
       eleHoverE_pass.push_back( eleHoverE[ie]   );
       eleMissHits_pass.push_back( eleMissHits[ie]   );
       eleD0_pass.push_back( eleD0[ie]   );
       eleMiniIsoEA_pass.push_back( eleMiniIsoEA[ie]   );
       eleE2x5Full5x5_pass.push_back( eleE2x5Full5x5[ie]   );
       eleE5x5Full5x5_pass.push_back( eleE5x5Full5x5[ie]   );
       eleE1x5Full5x5_pass.push_back( eleE1x5Full5x5[ie]   );
       eleSigmaIEtaIEtaFull5x5_pass.push_back( eleSigmaIEtaIEtaFull5x5[ie]   );

    }

    for(Int_t ie = 0; ie < eleScEn_pass.size(); ie++){     
//       cout<<"eleScEn_pass out: "<< eleScEn_pass[ie] << endl;
    }

    tree_pass -> Fill();



    // electron selections and cuts
/*
*/ 
     
  } // end of event loop

  fprintf(stderr, "Processed all events\n");
/*    
*/


  // save root file for skim 

  TFile* skim_root = new TFile(Form("%s_skim.root", outputFile.c_str() ), "recreate");
  tree_pass->Write();
//  h_eleScEn_pass->Write();
    h_eventWeight[0]->Write("eventWeight");// choose [0] or [1] are no difference



  // for cut flow
  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++){
    if(nPass[i]>0)  std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;
  }

  TH1D* h_CutFlow = new TH1D("h_CutFlow", "" ,5 , 0,5 );

  char* cut_name[5] = {"Began","nVtx < 1","HLT","data filter","find electron pair"};

  for(int i=1;i<=5;i++){ // i is the index of column of cut flow plot 
                if(i==1) {h_CutFlow->SetBinContent(i,nTotal); }
                else {h_CutFlow->SetBinContent(i,nPass[i-2]); }
                h_CutFlow->GetXaxis()->SetBinLabel( i , cut_name[i-1] );
  }

  TCanvas *c1 = new TCanvas("c1","try to show cut flow ",200,10,700,500);
  c1->cd();

  gPad->SetGridx();
  h_CutFlow->SetMarkerStyle(8);
  h_CutFlow->SetMarkerSize(1);
  h_CutFlow->GetXaxis()->SetLabelSize(0.041);
  h_CutFlow->SetStats(0);
  h_CutFlow->SetMarkerSize(2.0);

  h_CutFlow->Draw();
  h_CutFlow->Draw("HIST TEXT0 SAME");

  TString path_to_save = "/afs/cern.ch/user/y/yuchang/www/MC_Data_comparison/" ;
//  TString pdf_name = path_to_save + "test_cut_flow.pdf";

  std::string sample_name = Form("%s",outputFile.c_str());
//  cout<< "sample is: "<< sample_name << endl;

  TString Sample_Name = (TString) sample_name;
//  cout<< "Sample is: "<< Sample_Name << endl; 

  TString pdf_name = path_to_save + Sample_Name + "_cut_flow"+".pdf";

// outputFile

  c1->SaveAs( pdf_name );  
    
}
