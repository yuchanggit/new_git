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
#include "PuppiSDmassCorr/getPUPPIweight.h"

void xAna_CutFlow_Mu(std::string inputFile, std::string outputFolder, std::string outputFile){

  // TF1 for Thea's SD mass correction 

  TFile *f3;
  f3=TFile::Open("PuppiSDmassCorr/puppiCorr.root");
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

  const int N_myTrig = 16;
  std::string my_trigger[N_myTrig];

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


  int Number_to_print =  5000; int Max_number_to_read =  10000;
  cout<<"starting loop events"<< endl<<endl;

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){// event loop

    if( ev %   Number_to_print == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
//    if( ev > Max_number_to_read ) break;

//    cout<<"this is event: "<< ev << endl;

    data.GetEntry(ev);
    nTotal ++;
 
    // get variable Branch 


    Bool_t   isData                  = data.GetBool("isData");
    std::string*  trigName     =                   data.GetPtrString("hlt_trigName"    );
    vector<bool>& trigResult   = *((vector<bool>*) data.GetPtr      ("hlt_trigResult"  ));
    Int_t*        trigPreScale =                   data.GetPtrInt   ("hlt_trigPrescale");
    Int_t         trigNumber   =                   data.GetInt      ("hlt_nTrigs");


    const Int_t    nMu          = data.GetInt("nMu");
    const TClonesArray* muP4    = (TClonesArray*) data.GetPtrTObject("muP4");
    const vector<bool>& isHighPtMuon        = *((vector<bool>*) data.GetPtr("isHighPtMuon"));
    const vector<bool>& isCustomTrackerMuon = *((vector<bool>*) data.GetPtr("isCustomTrackerMuon"));
    const Float_t* muTrkIso     = data.GetPtrFloat("muTrkIso");
    const Float_t* muInnerTrkPt = data.GetPtrFloat("muInnerTrkPt");
    const Int_t*   muCharge     = data.GetPtrInt("muCharge");

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

      for (int myTrig = 0; myTrig<N_myTrig; myTrig++){ // the trigger listed in AN 

        if( thisTrig.find( my_trigger[myTrig] ) != std::string::npos && results ) {passOneHLT=true; break;}

      }

      if (passOneHLT) {isPassHLT = true; break;}

    }

    if ( !isPassHLT ) continue;
    nPass[0]++;

 
    // Muon in acceptance

    std::vector<Int_t> AccMuons;

    for (int im=0; im<nMu; im++){

      double muPt = ( (TLorentzVector*) muP4->At( im ) ) ->Pt() ;
      double muEta =( (TLorentzVector*) muP4->At( im ) ) ->Eta();

      if ( fabs( muEta ) > 2.4 ) continue;
      if ( muPt < 10 ) continue;

      AccMuons.push_back( im );

    }


    if ( AccMuons.size() <2 ) continue;
    nPass[1]++;


    // Z(mu mu) candidate

    bool isPassZmumu = false;

    int leadingMuIndex    = -1;
    int subleadingMuIndex = -1;

    double highestZpt = 0;

    for (int i=0; i< AccMuons.size(); i++){
//    for (int im=0; im< nMu; im++){

      for (int j=i+1; j< AccMuons.size(); j++){
//      for (int jm=im+1; jm< nMu; jm++){

        int im = AccMuons[i]; int jm = AccMuons[j];

        TLorentzVector* thisMu = (TLorentzVector*) muP4->At( im );
        TLorentzVector* thatMu = (TLorentzVector*) muP4->At( jm );

        TLorentzVector thisZ =( *thisMu + *thatMu );

        double Zpt = thisZ.Pt();

        if (Zpt > highestZpt ) { highestZpt = Zpt; leadingMuIndex = im; subleadingMuIndex = jm;}

      }
    }


    TLorentzVector* leadingMu    = (TLorentzVector*) muP4->At( leadingMuIndex    );
    TLorentzVector* subleadingMu = (TLorentzVector*) muP4->At( subleadingMuIndex );

    TLorentzVector candidate_Z =( *leadingMu + *subleadingMu );

    if (candidate_Z.M()>70 && candidate_Z.M()<110 && ( muCharge[leadingMuIndex]*muCharge[subleadingMuIndex]<0 ) ) isPassZmumu = true;

    if(!isPassZmumu) continue;
    nPass[2]++;


    // Muon pt

    bool isPassMuonPt = false;

    if ( leadingMu->Pt()>55 && subleadingMu->Pt()>20 ) isPassMuonPt = true;

    if ( !isPassMuonPt) continue;
    nPass[3]++;


    // Muon ID

    bool isPassMuonID = false;

    if( (isHighPtMuon[leadingMuIndex] || isHighPtMuon[subleadingMuIndex]) && isCustomTrackerMuon[leadingMuIndex] && isCustomTrackerMuon[subleadingMuIndex] ) isPassMuonID=true; 
    if ( !isPassMuonID) continue;
    nPass[4]++;


    // Muon Isolation


    bool isPassMuonIso = false;

    if ( leadingMu->DeltaR(*subleadingMu) >0.3 ){ // if the two muons are far away, use regular isolation 
      if ( muTrkIso[leadingMuIndex]/leadingMu->Pt() <0.1 && muTrkIso[subleadingMuIndex]/subleadingMu->Pt()<0.1 ) isPassMuonIso = true; 
    }
    else if ( leadingMu->DeltaR(*subleadingMu) <0.3 ){ // if the two muons are close, use corrected isolation
      if( (muTrkIso[leadingMuIndex]-muInnerTrkPt[subleadingMuIndex])/leadingMu->Pt()<0.1 && (muTrkIso[subleadingMuIndex]-muInnerTrkPt[leadingMuIndex])/subleadingMu->Pt()<0.1)isPassMuonIso=true;
    }

    if ( !isPassMuonIso) continue;
    nPass[5]++;


    // boosted Z boson

    bool isPassBoostedZ = false; 

    if (  candidate_Z.Pt()>200 ) isPassBoostedZ = true;

    if ( !isPassBoostedZ) continue;
    nPass[6]++;


    // AK8Jet

    Int_t goodFATJetID = -1;
    TLorentzVector* thisJet = NULL;

    for(Int_t ij = 0; ij < FATnJet; ++ij){

      thisJet = (TLorentzVector*)FATjetP4->At(ij);

      if( thisJet->Pt() < 200 ) continue;
      if( fabs(thisJet->Eta()) > 2.4 ) continue;
      if( !FATjetPassIDLoose[ij] ) continue;
      if( thisJet->DeltaR(*leadingMu) < 0.8 || thisJet->DeltaR(*subleadingMu) < 0.8 ) continue;

      goodFATJetID = ij;
      break;
    }

    if( goodFATJetID < 0 ) continue;
    nPass[7]++;


    // Event Cleaning

    bool isPassCleaning = false; 

    if ( ( candidate_Z.Eta() -  thisJet->Eta() )< 1.3 ) isPassCleaning = true;
    nPass[8]++;

    // X mass

    TLorentzVector l4_X = (*thisJet) + candidate_Z ;

    if (l4_X.M()< 750 ) continue;
    nPass[9]++;


    // Higgs mass

    double Jet_SDmass_corrected = ( FATjetPuppiSDmass[goodFATJetID] )*getPUPPIweight(thisJet->Pt(),thisJet->Eta(),tf1);

    if (Jet_SDmass_corrected <105 || Jet_SDmass_corrected >135  ) continue;
    nPass[10]++;


    // subjet b-tagging

    int NbTag = 0 ;

    for(Int_t is = 0; is < FATnSubSDJet[goodFATJetID]; ++is){
      if ( FATsubjetSDCSV[goodFATJetID][is] > 0.5426 ) NbTag++ ;
    }

    // has >=1 b-tagged subjet 

    if (NbTag >=1)
    nPass[11]++;

    // has >=2 b-tagged subjet 

    if (NbTag >=2)
    nPass[12]++;


    // test
    if (NbTag ==1)
    nPass[13]++;

    if (NbTag ==2)
    nPass[14]++;

    if (NbTag >2)
    nPass[15]++;


  } // ------------------ end of event loop ------------------

  fprintf(stderr, "Processed all events\n");

  cout<<endl;
  cout<<"nTotal: "                   << nTotal   << endl;
  cout<<"nPass[0] for HLT: "         << nPass[0] << endl;
  cout<<"nPass[1] for Acceptance: "  << nPass[1] << endl;
  cout<<"nPass[2] for Z(mu mu) candidate: "<< nPass[2] << endl;
  cout<<"nPass[3] for Muon Pt: "     << nPass[3] << endl;
  cout<<"nPass[4] for Muon ID: "     << nPass[4] << endl;
  cout<<"nPass[5] for Muon Iso: "    << nPass[5] << endl;
  cout<<"nPass[6] for Boosted Z: "   << nPass[6] << endl;
  cout<<"nPass[7] for AK8Jet: "      << nPass[7] << endl;
  cout<<"nPass[8] for Event Cleaning: " << nPass[8] << endl;
  cout<<"nPass[9] for X mass: "      << nPass[9] << endl;
  cout<<"nPass[10] for Higgs mass: " << nPass[10] << endl;
  cout<<"nPass[11] for >= 1 b-tagged: " << nPass[11] << endl;
  cout<<"nPass[12] for >= 2 b-tagged: " << nPass[12] << endl;

  cout<<"nPass[13] for == 1 b-tagged: " << nPass[13] << endl;
  cout<<"nPass[14] for == 2 b-tagged: " << nPass[14] << endl;
  cout<<"nPass[15] for > 2  b-tagged: " << nPass[15] << endl;


  // histogram for events

  const int Nbins = 14; 

  TH1D* h_CutFlow = new TH1D("h_CutFlow","Yu-hsiang check events",Nbins , 0,Nbins );
  char* cut_name[Nbins] = {"All","Trigger","Muon in acc.","Z(#mu#mu) candidate","Muon P_{T}","Muon Id","Muon Iso","Z boost","AK8 jet","Cleaning","X mass","H mass","1 b-tag","2 b-tag"};  

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

  TFile *f4 =TFile::Open("ZprimeToMM.root");
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




