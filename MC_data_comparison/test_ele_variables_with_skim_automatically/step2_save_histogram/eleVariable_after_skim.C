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
//#include "untuplizer.h"
#include "untuplizer_noTDirectory.h"
//#include "readSample.h"
//#include "dataFilter.h"
//#include "correctMCweight.h"
#include "TCanvas.h"
#include "TString.h"

void eleVariable_after_skim(std::string inputFile, std::string outputFile){



  
//  TreeReader data(infiles);
  TreeReader data( inputFile.data() );



  // try save TTree for skim sample

/*
*/


  // Declare the histogram (barrel,endcap)

  TH1D* h_eleEtaseedAtVtx[2]; 
  TH1D* h_eledPhiAtVtx[2];
  TH1D* h_eleHoverE[2];  
  TH1D* h_eleSigmaIEtaIEtaFull5x5[2];
  TH1D* h_eleFull5x5E2x5dvE5x5[2];
  TH1D* h_eleFull5x5E1x5dvE5x5[2]; 
  TH1D* h_eleMissHits[2]; 
  TH1D* h_eleD0[2];   
  TH1D* h_eleMiniIsoEA[2]; 
  TH1D* h_eventWeight[2]; 

  // for h_eventWeight 
  //cout<< "inputFile: "<< inputFile << endl;
  TString InputFile = (TString) inputFile;// convert string to TString
  TFile *file = new TFile( InputFile , "READ");
  TH1D* h_eventWeight_pass = (TH1D*) file -> Get( "eventWeight" );

  for(Int_t i = 0; i < 2; i++){

    h_eleEtaseedAtVtx[i]         = new TH1D(Form("h_eleEtaseedAtVtx%d",i),         "eleEtaseedAtVtx",         20,  -0.01,  0.01);
    h_eledPhiAtVtx[i]            = new TH1D(Form("h_eledPhiAtVtx%d",i),            "eledPhiAtVtx",            20,  -0.03,  0.03);
    h_eleHoverE[i]               = new TH1D(Form("h_eleHoverE%d",i),               "eleHoverE",               20,      0,  0.05);
    h_eleSigmaIEtaIEtaFull5x5[i] = new TH1D(Form("h_eleSigmaIEtaIEtaFull5x5%d",i), "eleSigmaIEtaIEtaFull5x5", 40,      0,  0.06);
    h_eleFull5x5E2x5dvE5x5[i]    = new TH1D(Form("h_eleFull5x5E2x5dvE5x5%d",i),    "eleFull5x5E2x5dvE5x5",    20,      0,     1);
    h_eleFull5x5E1x5dvE5x5[i]    = new TH1D(Form("h_eleFull5x5E1x5dvE5x5%d",i),    "eleFull5x5E1x5dvE5x5",    20,      0,     1);
    h_eleMissHits[i]             = new TH1D(Form("h_eleMissHits%d",i),             "eleMissHits",              6,   -0.5,   5.5);
    h_eleD0[i]                   = new TH1D(Form("h_eleD0%d",i),                   "eleD0",                   20, -0.015, 0.015);  
    h_eleMiniIsoEA[i]            = new TH1D(Form("h_eleMiniIsoEA%d",i),            "eleMiniIsoEA",            20,      0,  0.12);
//    h_eventWeight[i]             = new TH1D(Form("h_eventWeight%d",i),             "eventWeight",              2,     -1,     1);

    h_eventWeight[i]= (TH1D*) h_eventWeight_pass ->Clone( Form("h_eventWeight%d",i) );

    h_eleEtaseedAtVtx[i]        ->Sumw2();
    h_eledPhiAtVtx[i]           ->Sumw2();
    h_eleHoverE[i]              ->Sumw2();
    h_eleSigmaIEtaIEtaFull5x5[i]->Sumw2();
    h_eleFull5x5E2x5dvE5x5[i]   ->Sumw2();
    h_eleFull5x5E1x5dvE5x5[i]   ->Sumw2();
    h_eleMissHits[i]            ->Sumw2(); 
    h_eleD0[i]                  ->Sumw2();
    h_eleMiniIsoEA[i]           ->Sumw2();

    h_eleEtaseedAtVtx[i]        ->GetXaxis()->SetTitle("eleEtaseedAtVtx"); 
    h_eledPhiAtVtx[i]           ->GetXaxis()->SetTitle("eledPhiAtVtx");   
    h_eleHoverE[i]              ->GetXaxis()->SetTitle("eleHoverE");    
    h_eleSigmaIEtaIEtaFull5x5[i]->GetXaxis()->SetTitle("eleSigmaIEtaIEtaFull5x5");  
    h_eleFull5x5E2x5dvE5x5[i]   ->GetXaxis()->SetTitle("eleFull5x5E2x5dvE5x5");
    h_eleFull5x5E1x5dvE5x5[i]   ->GetXaxis()->SetTitle("eleFull5x5E1x5dvE5x5");   
    h_eleMissHits[i]            ->GetXaxis()->SetTitle("eleMissHits"); 
    h_eleD0[i]                  ->GetXaxis()->SetTitle("eleD0");      
    h_eleMiniIsoEA[i]           ->GetXaxis()->SetTitle("eleMiniIsoEA"); 

  }

  // define for cut flow
/*
*/
  // begin of event loop

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){

    if( ev % 1000000 == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

    data.GetEntry(ev);

    Float_t* eleScEn                 = data.GetPtrFloat("eleScEn_pass");

    Float_t* eleScEta                = data.GetPtrFloat("eleScEta_pass");
    Float_t* eleEtaseedAtVtx         = data.GetPtrFloat("eleEtaseedAtVtx_pass");     
    Float_t* eledPhiAtVtx            = data.GetPtrFloat("eledPhiAtVtx_pass");
    Float_t* eleHoverE               = data.GetPtrFloat("eleHoverE_pass");
    Float_t* eleSigmaIEtaIEtaFull5x5 = data.GetPtrFloat("eleSigmaIEtaIEtaFull5x5_pass");
    Float_t* eleE1x5Full5x5          = data.GetPtrFloat("eleE1x5Full5x5_pass");
    Float_t* eleE2x5Full5x5          = data.GetPtrFloat("eleE2x5Full5x5_pass");
    Float_t* eleE5x5Full5x5          = data.GetPtrFloat("eleE5x5Full5x5_pass");   
    Float_t* eleD0                   = data.GetPtrFloat("eleD0_pass");
    Float_t* eleMiniIsoEA            = data.GetPtrFloat("eleMiniIsoEA_pass");
    Int_t*   eleMissHits             = data.GetPtrInt("eleMissHits_pass");

    Double_t eventWeight             = data.GetDouble("eventWeight_pass"); 


/*
*/

/*
*/
    // electron selections and cuts

    int eleId[2];// for convenient because previous skim just save the two electrons 
    eleId[0] = 0;    eleId[1] = 1;

    for(Int_t ie = 0; ie < 2; ie++){

      Float_t E = eleScEn[eleId[ie]];

      if( fabs(eleScEta[eleId[ie]]) < 1.4442 ){ // barrel selections and cuts

	for(Int_t flag = 0; flag <= 7; flag++){

	  if( fabs(eleEtaseedAtVtx[eleId[ie]])   >= 0.004     && flag != 0 ) continue;
	  if( fabs(eledPhiAtVtx[eleId[ie]])      >= 0.06      && flag != 1 ) continue;
	  if( eleHoverE[eleId[ie]]               >= 1/E+0.05  && flag != 2 ) continue;
	  if( eleMissHits[eleId[ie]]             >  1         && flag != 3 ) continue;
	  if( fabs(eleD0[eleId[ie]])             >= 0.02      && flag != 4 ) continue;
	  if( eleMiniIsoEA[eleId[ie]]            >= 0.1       && flag != 5 ) continue;
	  if( (eleE2x5Full5x5[eleId[ie]]/eleE5x5Full5x5[eleId[ie]] <= 0.94  &&
	       eleE1x5Full5x5[eleId[ie]]/eleE5x5Full5x5[eleId[ie]] <= 0.83) && flag != 6 )
	    continue;
	  	    
	  switch(flag){

	  case 0: h_eleEtaseedAtVtx[0] ->Fill(eleEtaseedAtVtx[eleId[ie]],eventWeight); break;
	  case 1: h_eledPhiAtVtx[0]    ->Fill(eledPhiAtVtx[eleId[ie]],eventWeight);    break;
	  case 2: h_eleHoverE[0]       ->Fill(eleHoverE[eleId[ie]],eventWeight);       break;
	  case 3: h_eleMissHits[0]     ->Fill(eleMissHits[eleId[ie]],eventWeight);     break;
	  case 4: h_eleD0[0]           ->Fill(eleD0[eleId[ie]],eventWeight);           break;
	  case 5: h_eleMiniIsoEA[0]    ->Fill(eleMiniIsoEA[eleId[ie]],eventWeight);    break;	 
	  case 6:
	    h_eleFull5x5E2x5dvE5x5[0]  ->Fill(eleE2x5Full5x5[eleId[ie]]/eleE5x5Full5x5[eleId[ie]],eventWeight);
	    h_eleFull5x5E1x5dvE5x5[0]  ->Fill(eleE1x5Full5x5[eleId[ie]]/eleE5x5Full5x5[eleId[ie]],eventWeight);
	    break;
	  case 7: h_eleSigmaIEtaIEtaFull5x5[0] ->Fill(eleSigmaIEtaIEtaFull5x5[eleId[ie]],eventWeight); break;
	    
	  } // end of switch
    
	} // end of flag loop

      } // end of barrel


      if( fabs(eleScEta[eleId[ie]]) > 1.566 && fabs(eleScEta[eleId[ie]]) < 2.5 ){ // endcap selections and cuts

	for(Int_t flag = 0; flag <= 7; flag++){

	  if( fabs(eleEtaseedAtVtx[eleId[ie]])   >= 0.006    && flag != 0 ) continue;
	  if( fabs(eledPhiAtVtx[eleId[ie]])      >= 0.06     && flag != 1 ) continue;
	  if( eleHoverE[eleId[ie]]               >= 5/E+0.05 && flag != 2 ) continue;
	  if( eleSigmaIEtaIEtaFull5x5[eleId[ie]] >= 0.03     && flag != 3 ) continue;
	  if( eleMissHits[eleId[ie]]             >  1        && flag != 4 ) continue;
	  if( fabs(eleD0[eleId[ie]])             >= 0.05     && flag != 5 ) continue;
	  if( eleMiniIsoEA[eleId[ie]]            >= 0.1      && flag != 6 ) continue;
	  	  	    
	  switch(flag){

	  case 0: h_eleEtaseedAtVtx[1] ->Fill(eleEtaseedAtVtx[eleId[ie]],eventWeight); break;
	  case 1: h_eledPhiAtVtx[1]    ->Fill(eledPhiAtVtx[eleId[ie]],eventWeight);    break;
	  case 2: h_eleHoverE[1]       ->Fill(eleHoverE[eleId[ie]],eventWeight);       break;
	  case 3: h_eleSigmaIEtaIEtaFull5x5[1] ->Fill(eleSigmaIEtaIEtaFull5x5[eleId[ie]],eventWeight); break;
	  case 4: h_eleMissHits[1]     ->Fill(eleMissHits[eleId[ie]],eventWeight);     break;
	  case 5: h_eleD0[1]           ->Fill(eleD0[eleId[ie]],eventWeight);           break;
	  case 6: h_eleMiniIsoEA[1]    ->Fill(eleMiniIsoEA[eleId[ie]],eventWeight);    break;	  
	  case 7: 
	    h_eleFull5x5E2x5dvE5x5[1]  ->Fill(eleE2x5Full5x5[eleId[ie]]/eleE5x5Full5x5[eleId[ie]],eventWeight);
	    h_eleFull5x5E1x5dvE5x5[1]  ->Fill(eleE1x5Full5x5[eleId[ie]]/eleE5x5Full5x5[eleId[ie]],eventWeight);
	    break;
		    
	  } // end of switch
	
	} // end of flag loop

      } // end of endcap
	
    } // end of two electrons loop


      
  } // end of event loop

  fprintf(stderr, "Processed all events\n");
    
  TFile* outFile[2];
  
  std::string region[2] = {"barrel","endcap"};

  for(Int_t i = 0; i < 2; i++){

    outFile[i] = new TFile(Form("%s_%s.root",outputFile.c_str(),region[i].c_str()), "recreate");
      
    h_eleEtaseedAtVtx[i]        ->Write("eleEtaseedAtVtx");
    h_eledPhiAtVtx[i]           ->Write("eledPhiAtVtx");
    h_eleHoverE[i]              ->Write("eleHoverE");
    h_eleSigmaIEtaIEtaFull5x5[i]->Write("eleSigmaIEtaIEtaFull5x5");
    h_eleFull5x5E2x5dvE5x5[i]   ->Write("eleFull5x5E2x5dvE5x5");
    h_eleFull5x5E1x5dvE5x5[i]   ->Write("eleFull5x5E1x5dvE5x5");
    h_eleMissHits[i]            ->Write("eleMissHits");
    h_eleD0[i]                  ->Write("eleD0");
    h_eleMiniIsoEA[i]           ->Write("eleMiniIsoEA");
    h_eventWeight[i]            ->Write("eventWeight");

    outFile[i]->Write();

  }


  // save root file for skim 

/*
*/


  // for cut flow
/*
*/
    
}
