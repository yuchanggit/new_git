#include <vector>
#include <iostream>
#include <string>

#include <TH1D.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TF1.h>
#include <TCanvas.h>
#include "TMath.h"

#include "../untuplizer.h"


bool isZtoMM(TreeReader &data){

    // define HLT

    std::vector<string> my_trigger;

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


    // get variables

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

    // HLT cut

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

    if ( !isPassHLT ) return false ;



    // Muon in acceptance

    std::vector<Int_t> AccMuons;

    for (int im=0; im<nMu; im++){

      double muPt = ( (TLorentzVector*) muP4->At( im ) ) ->Pt() ;
      double muEta =( (TLorentzVector*) muP4->At( im ) ) ->Eta();

      if ( fabs( muEta ) > 2.4 ) continue;
      if ( muPt < 10 ) continue;

      AccMuons.push_back( im );

    }


    if ( AccMuons.size() <2 ) return false ;



    // Z(mu mu) candidate

    bool isPassZmumu = false;

    int leadingMuIndex    = -1;
    int subleadingMuIndex = -1;

    double highestZpt = 0;

    for (int i=0; i< AccMuons.size(); i++){
      for (int j=i+1; j< AccMuons.size(); j++){

        int im = AccMuons[i]; int jm = AccMuons[j];

        TLorentzVector* thisMu = (TLorentzVector*) muP4->At( im );
        TLorentzVector* thatMu = (TLorentzVector*) muP4->At( jm );

        TLorentzVector thisZ =( *thisMu + *thatMu );

        double Zpt   = thisZ.Pt();
        double Zmass = thisZ.M();

        if ( muCharge[im] * muCharge[jm]>0 ) continue;
        if ( Zmass < 70 || Zmass >110 ) continue;

        if (Zpt > highestZpt ) { highestZpt = Zpt; leadingMuIndex = im; subleadingMuIndex = jm; isPassZmumu = true; }

      }
    }

    if(!isPassZmumu) return false ;

    TLorentzVector* leadingMu    = (TLorentzVector*) muP4->At( leadingMuIndex    );
    TLorentzVector* subleadingMu = (TLorentzVector*) muP4->At( subleadingMuIndex );

    TLorentzVector candidate_Z =( *leadingMu + *subleadingMu );

    // Muon pt

    bool isPassMuonPt = false;

    if ( leadingMu->Pt()>55 && subleadingMu->Pt()>20 ) isPassMuonPt = true;

    if ( !isPassMuonPt) return false ;


    // Muon ID

    bool isPassMuonID = false;

    if( (isHighPtMuon[leadingMuIndex] || isHighPtMuon[subleadingMuIndex]) && isCustomTrackerMuon[leadingMuIndex] && isCustomTrackerMuon[subleadingMuIndex] ) isPassMuonID=true;
    if ( !isPassMuonID) return false ;


    // Muon Isolation


    bool isPassMuonIso = false;

    if ( leadingMu->DeltaR(*subleadingMu) >0.3 ){ // if the two muons are far away, use regular isolation 
      if ( muTrkIso[leadingMuIndex]/leadingMu->Pt() <0.1 && muTrkIso[subleadingMuIndex]/subleadingMu->Pt()<0.1 ) isPassMuonIso = true;
    }
    else if ( leadingMu->DeltaR(*subleadingMu) <0.3 ){ // if the two muons are close, use corrected isolation
      if( (muTrkIso[leadingMuIndex]-muInnerTrkPt[subleadingMuIndex])/leadingMu->Pt()<0.1 && (muTrkIso[subleadingMuIndex]-muInnerTrkPt[leadingMuIndex])/subleadingMu->Pt()<0.1)isPassMuonIso=true;
    }

    if ( !isPassMuonIso) return false ;


    // boosted Z boson

    bool isPassBoostedZ = false;

    if (  candidate_Z.Pt()>200 ) isPassBoostedZ = true;

    if ( !isPassBoostedZ) return false ;


    // if this event can go here

    return true;


}
