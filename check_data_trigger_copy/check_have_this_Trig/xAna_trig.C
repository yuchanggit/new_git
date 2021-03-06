#include <vector>
#include <string>
#include <iostream>

#include <TH1D.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TF1.h>
#include <TCanvas.h>
#include "TMath.h"

#include "untuplizer.h"


void xAna_trig(std::string inputFile, std::string outputFolder, std::string outputFile){

  // ----------- open ntuple, read TTree ----------------

  TString file_path = inputFile ;  
  TFile* file_sample = TFile::Open( file_path );

  TTree* tree = (TTree*) file_sample->Get("tree/treeMaker");
//  TTree* tree = (TTree*) file_sample->Get("treeMaker");

  cout<<"tree->GetEntries(): "<< tree->GetEntries() << endl<<endl;
  TreeReader data( tree );


  // ----------- Declare the histogram ----------------

  TH1D* h_totalEvents        = new TH1D("h_totalEv"           , "totalEvents"        ,   5,  -0.5,  4.5);
  TH1D* h_nTrigger           = new TH1D("h_nTrigger"          , "number of triggers"                ,   1000,  -0.5,  999.5);
  TH1D* h_nTrigger_PreScale1 = new TH1D("h_nTrigger_PreScale1", "number of triggers with prescale=1",   1000,  -0.5,  999.5);


  const int N_myTrig = 16;

  TString my_trigger    [N_myTrig];
  TH1D* h_trig_Result   [N_myTrig]; 
  TH1D* h_trig_PreScale [N_myTrig];

  my_trigger[0] = "HLT_Ele105_CaloIdVT_GsfTrkIdT_v" ;
  my_trigger[1] = "HLT_Ele115_CaloIdVT_GsfTrkIdT_v" ;
  my_trigger[2] = "HLT_Ele27_WPTight_Gsf_v" ;
  my_trigger[3] = "HLT_Ele32_WPTight_Gsf_v" ;

  my_trigger[4] = "HLT_Mu50_v" ;
  my_trigger[5] = "HLT_TkMu50_v" ;

  my_trigger[6]  = "HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_v" ;
  my_trigger[7]  = "HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v" ;
  my_trigger[8]  = "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v" ;
  my_trigger[9]  = "HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight" ;
  my_trigger[10] = "HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight" ;
  my_trigger[11] = "HLT_PFMET110_PFMHT110_IDTight" ;
  my_trigger[12] = "HLT_PFMET120_PFMHT120_IDTight" ;
  my_trigger[13] = "HLT_PFMET170_NoiseCleaned" ;
  my_trigger[14] = "HLT_PFMET170_HBHECleaned" ;
  my_trigger[15] = "HLT_PFMET170_HBHE_BeamHaloCleaned" ;

  for (int myTrig = 0; myTrig<N_myTrig; myTrig++){

    TString h_name,  h_title;

    h_name = Form("h_trig%i_Result"  ,myTrig+1 );
    h_title = my_trigger[myTrig] + " result";
    h_trig_Result[myTrig] = new TH1D( h_name, h_title ,   6,  -1.5,  4.5);

    h_name = Form("h_trig%i_PreScale",myTrig+1 );
    h_title = my_trigger[myTrig] + " PreScale";
    h_trig_PreScale[myTrig] = new TH1D( h_name, h_title ,   6,  -1.5,  4.5);

  }


  // ----------- begin of event loop ---------------------------------

  int counter_0=0;
  Long64_t ev_allTriggerOR = 0;
  Long64_t ev_Ele105_OR_Ele115 = 0;

  int Number_to_print =  10000; int Max_number_to_read =  10;
  cout<<"starting loop events"<< endl<<endl;

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){// event loop

    if( ev %   Number_to_print == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
//    if( ev > Max_number_to_read ) break;

//    cout<<"this is event: "<< ev << endl;
//    h_totalEvents->Fill(1.0);

    data.GetEntry(ev);

    // get variable Branch 

    std::string*  trigName     =                   data.GetPtrString("hlt_trigName"    );
    vector<bool>& trigResult   = *((vector<bool>*) data.GetPtr      ("hlt_trigResult"  ));
    Int_t*        trigPreScale =                   data.GetPtrInt   ("hlt_trigPrescale");
    Int_t         trigNumber   =                   data.GetInt      ("hlt_nTrigs");

    h_totalEvents->Fill(1.0);

//    cout<<"data.GetPtrStringSize(): "<< data.GetPtrStringSize() << endl;
//    cout<<"trigNumber: "<< trigNumber << endl;

    h_nTrigger->Fill(trigNumber);
    int nTrig_PreScale1 = 0;

    for(int iTrig = 0; iTrig < data.GetPtrStringSize(); iTrig++){ // HLT loop

      std::string thisTrigName = trigName[iTrig];

/*
      if( counter_0 < 1 ) { // print the 1st event's infomation
        cout<<"it: "              << iTrig               << endl;
        cout<<"thisTrigName: "    << thisTrigName        << endl;
        cout<<"results: "         << trigResult[iTrig]   << endl;
        cout<<"trigPreScale[it]: "<< trigPreScale[iTrig] << endl;
      }
*/

      if( trigPreScale[iTrig] == 1 ) nTrig_PreScale1++; 

    }// end HLT loop

    h_nTrigger_PreScale1 ->Fill( nTrig_PreScale1 );




   // for N-myTrig

    bool findTrigger[N_myTrig];

    for (int myTrig = 0; myTrig<N_myTrig; myTrig++){// myTrig loop

      findTrigger[myTrig] = false;
      std::string TRIGGERNAME = (std::string) my_trigger[myTrig]; 

      for(int iTrig = 0; iTrig < data.GetPtrStringSize(); iTrig++){ // HLT loop

        std::string thisTrigName = trigName[iTrig];

        if (thisTrigName.find(TRIGGERNAME) == std::string::npos) continue;

        findTrigger[myTrig] = true;
        h_trig_PreScale[myTrig]-> Fill ( trigPreScale[iTrig] );

        bool results = trigResult[iTrig];
        if   (results) h_trig_Result[myTrig] -> Fill(1.0);
        else           h_trig_Result[myTrig] -> Fill(0.0);

        break;

      }// end HLT loop

      if( !findTrigger[myTrig] ){// if don't find myTrig

        h_trig_PreScale[myTrig] ->Fill(-1.0); 
        h_trig_Result[myTrig]   ->Fill(-1.0);

      }// end if

    }// end myTrig loop




    // ask event with OR ALL triggers   

    bool FindOR_AllTrigger = false;

    for (int myTrig = 0; myTrig<N_myTrig; myTrig++){// myTrig loop
      if( findTrigger[myTrig] ) { FindOR_AllTrigger = true; break;}
    }

    if ( FindOR_AllTrigger ) ev_allTriggerOR++;


    // ask event with OR Ele105, Ele115

    if ( findTrigger[0] || findTrigger[1] ) ev_Ele105_OR_Ele115 ++;

    counter_0++;

  } // ------------------ end of event loop ------------------

  cout<<"counter_0: "<< counter_0 << endl;
  fprintf(stderr, "Processed all events\n");

  // --------- histo for event with trigger whose prescale=1 ------

  TH1D* h_Event_with_Trigger = new TH1D("h_Event_with_Trigger","Events with the prescale=1 trigger ", N_myTrig+2, 0, N_myTrig+2);

  for (int iBin = 1; iBin <= N_myTrig+1; iBin++){

    if( iBin == 1 ){
      h_Event_with_Trigger->SetBinContent(iBin, h_totalEvents->GetBinContent(2) );
      h_Event_with_Trigger->GetXaxis()->SetBinLabel( iBin , "total events" );
    }

    else{
      h_Event_with_Trigger->SetBinContent(iBin, h_trig_PreScale[iBin-2]->GetBinContent(3) );
      h_Event_with_Trigger->GetXaxis()->SetBinLabel( iBin , my_trigger[iBin-2] );
    }
  }

  h_Event_with_Trigger->SetBinContent( N_myTrig+2 , ev_allTriggerOR );
  h_Event_with_Trigger->GetXaxis()->SetBinLabel( N_myTrig+2 ,"OR all triggers" );

  h_Event_with_Trigger ->GetYaxis()->SetTitle("");
  h_Event_with_Trigger ->SetStats(0);

  // histo for event with trigger Ele105 OR Ele115

  TH1D* h_Event_OR_Ele105_Ele115 = new TH1D("h_Event_OR_Ele105_Ele115","Events with Ele105 OR Ele115 whose prescale=1", 4 , 0, 4);

  for (int iBin = 1; iBin <= 4; iBin++){

    if( iBin == 1 ){
      h_Event_OR_Ele105_Ele115->SetBinContent(iBin, h_totalEvents->GetBinContent(2) );
      h_Event_OR_Ele105_Ele115->GetXaxis()->SetBinLabel( iBin , "total events" );
    }

    if( iBin == 2 || iBin == 3 ){
      h_Event_OR_Ele105_Ele115->SetBinContent(iBin, h_trig_PreScale[iBin-2]->GetBinContent(3) ); // Ele105 and Ele115
      h_Event_OR_Ele105_Ele115->GetXaxis()->SetBinLabel( iBin , my_trigger[iBin-2] );
    }

    if( iBin == 4 ){
      h_Event_OR_Ele105_Ele115          ->SetBinContent( iBin , ev_Ele105_OR_Ele115 );
      h_Event_OR_Ele105_Ele115->GetXaxis()->SetBinLabel( iBin , "Ele105 OR Ele115" );
    }
  }

  h_Event_OR_Ele105_Ele115 ->GetYaxis()->SetTitle("");
  h_Event_OR_Ele105_Ele115 ->SetStats(0);


  //---------- root file to save ----------

  std::string root_name = Form("%s.root",outputFile.c_str() ) ;
  TString save_path = outputFolder +"/"+  root_name;
  TFile* outFile = new TFile( save_path , "recreate");

  h_totalEvents        -> Write();   

  h_nTrigger           -> Write();
  h_nTrigger_PreScale1 -> Write();


  for (int myTrig = 0; myTrig<N_myTrig; myTrig++){

    h_trig_PreScale[myTrig] -> Write(); 
    h_trig_Result[myTrig]   -> Write(); 
  }

  h_Event_with_Trigger -> Write();
  h_Event_OR_Ele105_Ele115 -> Write();

  cout<<endl<<"save ROOT file in: "<< save_path << endl;

//  h_Event_with_Trigger->Draw();

}

