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

#include "../untuplizer.h"
#include "../PuppiSDmassCorr/getPUPPIweight.h"

#include "isZtoMM.h"

void xAna_CutFlow_Ele(std::string inputFile, std::string outputFolder, std::string outputFile){

  // TF1 for Thea's SD mass correction 

  TFile *f3;
  f3=TFile::Open("../PuppiSDmassCorr/puppiCorr.root");
  TF1* tf1[3];
  tf1[0]=(TF1 *) f3->FindObjectAny("puppiJECcorr_gen");
  tf1[1]=(TF1 *) f3->FindObjectAny("puppiJECcorr_reco_0eta1v3");
  tf1[2]=(TF1 *) f3->FindObjectAny("puppiJECcorr_reco_1v3eta2v5");

  // ----------- open ntuple, read TTree ----------------

  TString file_path = inputFile ;  
  TFile* file_sample = TFile::Open( file_path );

  TTree* tree = (TTree*) file_sample->Get("tree/treeMaker");
  cout<<"tree->GetEntries(): "<< tree->GetEntries() << endl<<endl;
  TreeReader data( tree );


  // ----------- begin of event loop ---------------------------------


  Long64_t nTotal=0;
  Long64_t nPass[20]={0};

//  const int N_myTrig = 16;
//  std::string my_trigger[N_myTrig];

  std::vector<string> my_trigger;   // For syn to Alberto

    my_trigger .push_back("HLT_Mu50_v");
    my_trigger .push_back("HLT_TkMu50_v");
    my_trigger .push_back("HLT_IsoMu27_v");
    my_trigger .push_back("HLT_IsoTkMu27_v");
    my_trigger .push_back("HLT_Mu27_TkMu8_v");
    my_trigger .push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    my_trigger .push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
    my_trigger .push_back("HLT_Ele105_CaloIdVT_GsfTrkIdT_v");
    my_trigger .push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
    my_trigger .push_back("HLT_Ele32_WPTight_Gsf_v");
    my_trigger .push_back("HLT_Ele32_eta2p1_WPTight_Gsf_v");
    my_trigger .push_back("HLT_Ele27_WPLoose_Gsf_v");
    my_trigger .push_back("HLT_Ele27_WPTight_Gsf_v");
    my_trigger .push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    my_trigger .push_back("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v");
    my_trigger .push_back("HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_v");
    my_trigger .push_back("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v");
    my_trigger .push_back("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v");
    my_trigger .push_back("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v");
    my_trigger .push_back("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v");
    my_trigger .push_back("HLT_MonoCentralPFJet80_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v");
    my_trigger .push_back("HLT_PFMET110_PFMHT110_IDTight_v");
    my_trigger .push_back("HLT_PFMET120_PFMHT120_IDTight_v");

    my_trigger .push_back("HLT_PFMET170_NoiseCleaned_v");
    my_trigger .push_back("HLT_PFMET170_HBHECleaned_v");
    my_trigger .push_back("HLT_PFMET170_HBHE_BeamHaloCleaned_v");
    my_trigger .push_back("HLT_PFJet450_v");
    my_trigger .push_back("HLT_AK8PFJet450_v");
    my_trigger .push_back("HLT_PFHT900_v");
    my_trigger .push_back("HLT_PFHT800_v");
    my_trigger .push_back("HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v");
    my_trigger .push_back("HLT_PFHT650_WideJetMJJ900_v");
    my_trigger .push_back("HLT_PFHT650_v");
    my_trigger .push_back("HLT_PFJet320_v");
    my_trigger .push_back("HLT_AK8PFJet360_TrimMass30_v");
    my_trigger .push_back("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v");
    my_trigger .push_back("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_v");
    my_trigger .push_back("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_v");
    my_trigger .push_back("HLT_PFJet320_v");


/*
  my_trigger.push_back("HLT_Ele105_CaloIdVT_GsfTrkIdT_v") ;
  my_trigger.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v") ;
  my_trigger.push_back("HLT_Ele27_WPTight_Gsf_v") ;
  my_trigger.push_back("HLT_Ele32_WPTight_Gsf_v") ;

  my_trigger.push_back("HLT_Mu50_v") ;
  my_trigger.push_back("HLT_TkMu50_v") ;

  my_trigger.push_back("HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_v") ;
  my_trigger.push_back("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v") ;
  my_trigger.push_back("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v") ;
  my_trigger.push_back("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight") ;
  my_trigger.push_back("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight") ;
  my_trigger.push_back("HLT_PFMET110_PFMHT110_IDTight") ;
  my_trigger.push_back("HLT_PFMET120_PFMHT120_IDTight") ;
  my_trigger.push_back("HLT_PFMET170_NoiseCleaned") ;
  my_trigger.push_back("HLT_PFMET170_HBHECleaned") ;
  my_trigger.push_back("HLT_PFMET170_HBHE_BeamHaloCleaned") ;
*/

/*
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
*/

  int Number_to_print =  5000; int Max_number_to_read =  1000;
  cout<<"starting loop events"<< endl<<endl;

  Long64_t nZtoMM=0;

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){// event loop

    if( ev %   Number_to_print == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
//    if( ev > Max_number_to_read ) break;

//    cout<<"this is event: "<< ev << endl;

    data.GetEntry(ev);
    nTotal ++;
 
    // get variable Branch 


    Bool_t   isData                  = data.GetBool("isData");
    Long64_t event                   = data.GetLong64("eventId");

    std::string*  trigName     =                   data.GetPtrString("hlt_trigName"    );
    vector<bool>& trigResult   = *((vector<bool>*) data.GetPtr      ("hlt_trigResult"  ));
    Int_t*        trigPreScale =                   data.GetPtrInt   ("hlt_trigPrescale");
    Int_t         trigNumber   =                   data.GetInt      ("hlt_nTrigs");


    const Int_t    nEle        = data.GetInt("nEle");
    const Int_t*   eleCharge   = data.GetPtrInt("eleCharge");
    const Float_t* eleScEta    = data.GetPtrFloat("eleScEta");
    const TClonesArray* eleP4  = (TClonesArray*) data.GetPtrTObject("eleP4");
    const vector<bool>& eleIsPassLoose = *((vector<bool>*) data.GetPtr("eleIsPassLoose"));


    Int_t          FATnJet           = data.GetInt("FATnJet");
    TClonesArray*  FATjetP4          = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    vector<bool>&  FATjetPassIDLoose = *((vector<bool>*) data.GetPtr("FATjetPassIDLoose"));
    Float_t*       FATjetPuppiSDmass = data.GetPtrFloat("FATjetPuppiSDmass");

    Int_t*         FATnSubSDJet      = data.GetPtrInt("FATnSubSDJet");
    vector<float>* FATsubjetSDCSV    = data.GetPtrVectorFloat("FATsubjetSDCSV", FATnJet);

    // HLT: not just (HLT_Mu50_v OR HLT_TkMu50_v)
    // OR all trigger listed in Alberto's AN 

    bool isPassHLT = false;

    for(int it = 0; it < data.GetPtrStringSize(); it++){ // HLT loop

      std::string thisTrig = trigName[it];
      bool results = trigResult[it];

      bool passOneHLT = false;

      for (int myTrig = 0; myTrig<my_trigger.size(); myTrig++){ // the trigger listed in AN 

        if( thisTrig.find( my_trigger[myTrig] ) != std::string::npos && results ) {passOneHLT=true; break;}

      }

      if (passOneHLT) {isPassHLT = true; break;}

    }

    if ( !isPassHLT ) continue;
    nPass[0]++;

 
    // Electron in acceptance

    std::vector<Int_t> AccElectrons;

    for (int ie=0; ie<nEle; ie++){

      double elePt = ( (TLorentzVector*) eleP4->At( ie ) ) ->Pt(); 
//      double eleEta = eleScEta[ie];
      double eleEta = ( (TLorentzVector*) eleP4->At( ie ) ) ->Eta(); // For syn to Alberto

//      if ( fabs( eleEta ) > 2.5 || ( fabs( eleEta ) > 1.4442 && fabs( eleEta ) < 1.566 ) ) continue;
      if ( fabs( eleEta ) > 2.5 ) continue;  // For syn to Alberto

      if ( elePt < 10 ) continue; 
//      if ( !eleIsPassLoose[ie] ) continue;

      AccElectrons.push_back( ie );

    }


    if ( AccElectrons.size() <2 ) continue;

    bool isZtoMM_flag = isZtoMM(data);

    if ( isZtoMM_flag ) { nZtoMM++; continue;}  // For syn to Alberto

    nPass[1]++;


    // Z(e e) candidate

    bool isPassZee = false;

    int leadingEleIndex    = -1; 
    int subleadingEleIndex = -1;

    double highestZpt = 0;

    for (int i=0; i< AccElectrons.size(); i++){
//    for (int ie=0; ie< nEle; ie++){

      for (int j=i+1; j< AccElectrons.size(); j++){
//      for (int je=ie+1; je< nEle; je++){

        int ie = AccElectrons[i]; int je = AccElectrons[j];

        TLorentzVector* thisEle = (TLorentzVector*) eleP4->At( ie );
        TLorentzVector* thatEle = (TLorentzVector*) eleP4->At( je );

        TLorentzVector thisZ =( *thisEle + *thatEle );

        double Zpt   = thisZ.Pt();
        double Zmass = thisZ.M(); 

        if ( eleCharge[ie] * eleCharge[je]>0 ) continue;
        if ( Zmass < 70 || Zmass >110 ) continue ; 

        if (Zpt > highestZpt ) { highestZpt = Zpt; leadingEleIndex = ie; subleadingEleIndex = je; isPassZee = true; }

      }
    }


    if(!isPassZee) continue;
    nPass[2]++;

    TLorentzVector* leadingEle    = (TLorentzVector*) eleP4->At( leadingEleIndex    );    
    TLorentzVector* subleadingEle = (TLorentzVector*) eleP4->At( subleadingEleIndex ); 

    TLorentzVector candidate_Z =( *leadingEle + *subleadingEle );

// For syn to Alberto
//    if (candidate_Z.M()>70 && candidate_Z.M()<110 && ( eleCharge[leadingEleIndex]*eleCharge[subleadingEleIndex]<0 ) ) isPassZee = true;

//    if(!isPassZee) continue;
//    nPass[2]++;



    // Electron pt

    bool isPassElePt = false;

    if ( leadingEle->Pt()>55 && subleadingEle->Pt()>20 ) isPassElePt = true;

    if ( !isPassElePt) continue;
    nPass[3]++;


    // Electron ID

    bool isPassEleID = false;

    if ( eleIsPassLoose[leadingEleIndex] && eleIsPassLoose[subleadingEleIndex] ) isPassEleID = true;

    if ( !isPassEleID) continue;
    nPass[4]++;

    // Electron Isolation has been included in ID cut


    // boosted Z boson

    bool isPassBoostedZ = false; 

    if ( candidate_Z.Pt()>200 ) isPassBoostedZ = true;

    if ( !isPassBoostedZ) continue;
    nPass[5]++;


    // AK8Jet

    Int_t goodFATJetID = -1;
    TLorentzVector* thisJet = NULL;

    for(Int_t ij = 0; ij < FATnJet; ++ij){

      thisJet = (TLorentzVector*)FATjetP4->At(ij);

      if( thisJet->Pt() < 200 ) continue;
      if( fabs(thisJet->Eta()) > 2.4 ) continue;
      if( !FATjetPassIDLoose[ij] ) continue;
      if( thisJet->DeltaR(*leadingEle) < 0.8 || thisJet->DeltaR(*subleadingEle) < 0.8 ) continue;

      goodFATJetID = ij;
      break;
    }

    if( goodFATJetID < 0 ) continue;
    nPass[6]++;


    // Event Cleaning

    bool isPassCleaning = false; 

    if ( ( candidate_Z.Eta() -  thisJet->Eta() )< 1.3 ) isPassCleaning = true;
    nPass[7]++;

    // X mass

    TLorentzVector l4_X = (*thisJet) + candidate_Z ;

    if (l4_X.M()< 750 ) continue;
    nPass[8]++;


    // Higgs mass

    double Jet_SDmass_corrected = ( FATjetPuppiSDmass[goodFATJetID] )*getPUPPIweight(thisJet->Pt(),thisJet->Eta(),tf1);

    if (Jet_SDmass_corrected <105 || Jet_SDmass_corrected >135  ) continue;
    nPass[9]++;


    // subjet b-tagging

    int NbTag = 0 ;

    for(Int_t is = 0; is < FATnSubSDJet[goodFATJetID]; ++is){
      if ( FATsubjetSDCSV[goodFATJetID][is] > 0.5426 ) NbTag++ ;
    }

    // has >=1 b-tagged subjet 

    if (NbTag >=1)
    nPass[10]++;

    // has >=2 b-tagged subjet 

    if (NbTag >=2)
    nPass[11]++;


    // test
    if (NbTag ==1)
    nPass[12]++;

    if (NbTag ==2)
    nPass[13]++;

    if (NbTag >2)
    nPass[14]++;


  } // ------------------ end of event loop ------------------

  fprintf(stderr, "Processed all events\n");

  cout<<endl;
  cout<<"nTotal: "                   << nTotal   << endl;
  cout<<"nPass[0] for HLT: "         << nPass[0] << endl;
  cout<<"nPass[1] for Acceptance: "  << nPass[1] << endl;
  cout<<"nPass[2] for Z(e e) candidate: "<< nPass[2] << endl;
  cout<<"nPass[3] for Electron Pt: "     << nPass[3] << endl;
  cout<<"nPass[4] for Electron ID: "     << nPass[4] << endl;
//  cout<<"nPass[5] for Electron Iso: "    << nPass[5] << endl;
  cout<<"nPass[5] for Boosted Z: "   << nPass[5] << endl;
  cout<<"nPass[6] for AK8Jet: "      << nPass[6] << endl;
  cout<<"nPass[7] for Event Cleaning: " << nPass[7] << endl;
  cout<<"nPass[8] for X mass: "      << nPass[8] << endl;
  cout<<"nPass[9] for Higgs mass: " << nPass[9] << endl;
  cout<<"nPass[10] for >= 1 b-tagged: " << nPass[10] << endl;
  cout<<"nPass[11] for >= 2 b-tagged: " << nPass[11] << endl;


  cout<<"nPass[12] for == 1 b-tagged: " << nPass[12] << endl;
  cout<<"nPass[13] for == 2 b-tagged: " << nPass[13] << endl;
  cout<<"nPass[14] for > 2 b-tagged: " << nPass[14] << endl;

  cout<< endl <<"number of events with AccElectrons.size() >=2 and isZ->MuMu: " << nZtoMM << endl <<endl;

  // histogram for events

  const int Nbins = 13; 

  TH1D* h_CutFlow = new TH1D("h_CutFlow","Yu-hsiang check events",Nbins , 0,Nbins );

  char* cut_name[Nbins] = {"All","Trigger","Ele in acc.","Z(ee) candidate","Ele P_{T}","Ele Id","Z boost","AK8 jet","Cleaning","X mass","H mass","1 b-tag","2 b-tag"};


  for(int i=1;i<=Nbins;i++){ // i is the index of column of cut flow plot 

		if(i==1) {h_CutFlow->SetBinContent(i,nTotal); }

        	else {h_CutFlow->SetBinContent(i,nPass[i-2]); }

		h_CutFlow->GetXaxis()->SetBinLabel( i , cut_name[i-1] );
  }


  // histogram for efficiency

  TH1D* h_CutFlow_eff = (TH1D* ) h_CutFlow -> Clone("h_CutFlow_eff");
  h_CutFlow_eff->Reset();

  h_CutFlow_eff->SetTitle("Yu-hsiang check efficiency");

  for(int i=1;i<=Nbins;i++){ // i is the index of column of cut flow plot 

    double eff; 
    if(i==1) { eff = (double) nTotal/nTotal     ; h_CutFlow_eff->SetBinContent(i,eff); }

    else     { eff = (double) nPass[i-2]/ nTotal; h_CutFlow_eff->SetBinContent(i,eff); }
  }


  // open histogram of Alberto events 

  TFile *f4 =TFile::Open("../ZprimeToEE.root");
  TH1D* h_CutFlow_Alberto = (TH1D*) f4->FindObjectAny("Events");

  h_CutFlow_Alberto->SetTitle("Alberto's events");

  // produce the eff plot of Alberto's events
  

  TH1D* h_CutFlow_eff_Alberto = (TH1D* ) h_CutFlow_Alberto -> Clone("h_CutFlow_eff_Alberto");
  h_CutFlow_eff_Alberto->Reset();

  h_CutFlow_eff_Alberto->SetTitle("Alberto's efficiency");

  Long64_t nTotal_Alberto = h_CutFlow_Alberto->GetBinContent(1);   

  for(int i=1;i<=Nbins;i++){ // i is the index of column of cut flow plot 

    double eff;
    if(i==1) { eff = (double) nTotal_Alberto/nTotal_Alberto     ; h_CutFlow_eff_Alberto->SetBinContent(i,eff); }

    else     { eff = (double) h_CutFlow_Alberto->GetBinContent(i)/ nTotal_Alberto; h_CutFlow_eff_Alberto->SetBinContent(i,eff); }
  }



  //---------- root file to save ----------



  std::string root_name = Form("%s.root",outputFile.c_str() ) ;
  TString save_path = outputFolder +"/"+  root_name;
  TFile* outFile = new TFile( save_path , "recreate");

  h_CutFlow     ->Write();
  h_CutFlow_eff ->Write();

  h_CutFlow_Alberto ->Write();
  h_CutFlow_eff_Alberto ->Write();

  outFile->Write();  
  delete outFile;

  cout<<endl<<"save ROOT file in: "<< save_path << endl;


}




