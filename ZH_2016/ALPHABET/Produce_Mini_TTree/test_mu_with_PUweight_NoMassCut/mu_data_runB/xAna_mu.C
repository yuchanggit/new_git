#include <vector>
#include <string>
#include <iostream>
#include <TH1D.h>
#include <TMath.h>
#include <TFile.h>
#include <TChain.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TF1.h>

#include "interface/untuplizer.h"
#include "interface/isPassZmumu.h"
#include "interface/readSample.h"
#include "interface/mu_Cert_271036-277148-MinBiasXsec_69200/standalone_LumiReWeighting.cc"
#include "interface/dataFilter.h"
#include "interface/PuppiSDmassCorr/getPUPPIweight.h"

void xAna_mu(std::string inputFile, std::string outputFolder, std::string outputFile){

  cout<<"finish compiling and start to run macro"<< endl;
  // --------  open  ntuples ------------ 

  // get paths of every root files
  std::vector<string> infiles; 
  readSample(inputFile, infiles);

  cout<<"infiles.size():"<< infiles.size() << endl;

  // combine TTree
  TChain* tree = new TChain("tree/treeMaker");

  for(unsigned int i=0 ; i<infiles.size() ; i++ ){
    std::string open_root="root://" + infiles[i] ;
    tree->Add( open_root.c_str()  );
  }

  cout<<"tree->GetEntries(): "<< tree->GetEntries() << endl;

  // read the TTree

  TreeReader data( tree );
  cout<<"finish TreeReader data( tree );"<< endl; 

  // -------- Add new TTree ----------

  TTree* new_tree = new TTree("new_tree", "TreeForALPHABET");

  double Event_Weight;
  double PRmass, PRmass_L2L3Corrected, SDmass, SDmass_TheaCorrected;
  double Double_bTagger;
  double Tau21;
  double ZHmass;

  new_tree->Branch("Event_Weight",        &Event_Weight,        "Event_Weight/D");
  new_tree->Branch("PRmass",              &PRmass,              "PRmass/D");
  new_tree->Branch("PRmass_L2L3Corrected",&PRmass_L2L3Corrected,"PRmass_L2L3Corrected/D");
  new_tree->Branch("SDmass",              &SDmass,              "SDmass/D");
  new_tree->Branch("SDmass_TheaCorrected",&SDmass_TheaCorrected,"SDmass_TheaCorrected/D");
  new_tree->Branch("Double_bTagger",      &Double_bTagger,      "Double_bTagger/D");
  new_tree->Branch("Tau21",               &Tau21,               "Tau21/D");
  new_tree->Branch("ZHmass",              &ZHmass,              "ZHmass/D");


  // ------- Declare the histogram ----------------

  TH1D* h_totalEvents      = new TH1D("h_totalEv",          "totalEvents",       10,     0,   10);

/*
  TH1D* h_pu_nTrueInt      = new TH1D("h_pu_nTrueInt",      "h_pu_nTrueInt",     60,     0,   60);
  TH1D* h_nVtx             = new TH1D("h_nVtx",             "nVtx",              30,  -0.5, 29.5); 

  TH1D* h_leadMuPt     = new TH1D("h_leadMuPt",     "leadMuPt",     32,  5,  805);
  TH1D* h_leadMuEta    = new TH1D("h_leadMuEta",    "leadMuEta",    40, -4,    4);
  TH1D* h_subleadMuPt  = new TH1D("h_subleadMuPt",  "subleadMuPt",  25,  0,  500);
  TH1D* h_subleadMuEta = new TH1D("h_subleadMuEta", "subleadMuEta", 40, -4,    4);

  TH1D* h_Zmass            = new TH1D("h_Zmass",            "Zmass",             30,    60,  120);
  TH1D* h_Zpt              = new TH1D("h_Zpt",              "Zpt",               50,     0, 1000);
  TH1D* h_Zeta             = new TH1D("h_Zeta",             "Zeta",              40,    -4,    4);
  TH1D* h_ZRapidity        = new TH1D("h_ZRapidity",        "ZRapidity",         40,    -4,    4);

  TH1D* h_FATjetPt         = new TH1D("h_FATjetPt",         "FATjetPt",           50,    0, 1000);
  TH1D* h_FATjetEta        = new TH1D("h_FATjetEta",        "FATjetEta",          20,   -4,    4);
  TH1D* h_FATjetCISVV2     = new TH1D("h_FATjetCISVV2",     "FATjetCISVV2",       20,    0,  1.2);
  TH1D* h_FATjetSDmass     = new TH1D("h_FATjetSDmass",     "FATjetSDmass",       20,    0,  200);
  TH1D* h_FATjetSDmassCorr = new TH1D("h_FATjetSDmassCorr", "FATjetSDmassCorr",   20,    0,  200);
  TH1D* h_FATjetPRmass     = new TH1D("h_FATjetPRmass",     "FATjetPRmass",       20,    0,  200);
  TH1D* h_FATjetPRmassCorr = new TH1D("h_FATjetPRmassCorr", "FATjetPRmassCorr",   20,    0,  200);
  TH1D* h_FATjetTau1       = new TH1D("h_FATjetTau1",       "FATjetTau1",         20,    0,    1);
  TH1D* h_FATjetTau2       = new TH1D("h_FATjetTau2",       "FATjetTau2",         20,    0,    1);
  TH1D* h_FATjetTau2dvTau1 = new TH1D("h_FATjetTau2dvTau1", "FATjetTau2dvTau1",   20,    0,    1);

  TH1D* h_FATnSubjet                 = new TH1D("h_FATnSubjet",              "FATnSubjet",                 5, -0.5,  4.5);
  TH1D* h_FATsubjetLeadingPt         = new TH1D("h_FATsubjetLeadingPt",      "FATsubjetLeadingPt",        20,    0,  800);
  TH1D* h_FATsubjetLeadingEta        = new TH1D("h_FATsubjetLeadingEta",     "h_FATsubjetLeadingEta",     20,   -4,    4);
  TH1D* h_FATsubjetLeadingSDCSV      = new TH1D("h_FATsubjetLeadingSDCSV",   "h_FATsubjetLeadingSDCSV",   20,    0,  1.2);
  TH1D* h_FATsubjetSubLeadingPt      = new TH1D("h_FATsubjetSubLeadingPt",   "FATsubjetSubLeadingPt",     20,    0,  800);
  TH1D* h_FATsubjetSubLeadingEta     = new TH1D("h_FATsubjetSubLeadingEta",  "h_FATsubjetSubLeadingEta",  20,   -4,    4);
  TH1D* h_FATsubjetSubLeadingSDCSV   = new TH1D("h_FATsubjetSubLeadingSDCSV","h_FATsubjetSubLeadingSDCSV",20,    0,  1.2);

  TH1D* h_ADDjet_DoubleSV            = new TH1D("h_ADDjet_DoubleSV",              "ADDjet_DoubleSV",      20,    -1,   1);

  TH1D* h_ZHmass           = new TH1D("h_ZHmass",           "ZHmass",             50,    0, 5000);

  h_pu_nTrueInt     ->Sumw2();
  h_nVtx            ->Sumw2();

  h_leadMuPt    ->Sumw2();
  h_leadMuEta   ->Sumw2();
  h_subleadMuPt ->Sumw2();
  h_subleadMuEta->Sumw2(); 


  h_Zmass           ->Sumw2();
  h_Zpt             ->Sumw2();
  h_Zeta            ->Sumw2();
  h_ZRapidity       ->Sumw2();

  h_FATjetPt        ->Sumw2();   
  h_FATjetEta       ->Sumw2();
  h_FATjetCISVV2    ->Sumw2();
  h_FATjetSDmass    ->Sumw2();
  h_FATjetSDmassCorr->Sumw2();
  h_FATjetPRmass    ->Sumw2();
  h_FATjetPRmassCorr->Sumw2();
  h_FATjetTau1      ->Sumw2();
  h_FATjetTau2      ->Sumw2();
  h_FATjetTau2dvTau1->Sumw2();

  h_FATnSubjet 		     ->Sumw2();
  h_FATsubjetLeadingPt       ->Sumw2();
  h_FATsubjetLeadingEta      ->Sumw2();
  h_FATsubjetLeadingSDCSV    ->Sumw2();
  h_FATsubjetSubLeadingPt    ->Sumw2();
  h_FATsubjetSubLeadingEta   ->Sumw2();
  h_FATsubjetSubLeadingSDCSV ->Sumw2();

  h_ADDjet_DoubleSV ->Sumw2();

  h_ZHmass          ->Sumw2();
*/

  // ---- TF1 for Thea's SD mass correction ----------

  TFile *f3;
  f3=TFile::Open("interface/PuppiSDmassCorr/puppiCorr.root");
  TF1* tf1[3];
  tf1[0]=(TF1 *) f3->FindObjectAny("puppiJECcorr_gen");
  tf1[1]=(TF1 *) f3->FindObjectAny("puppiJECcorr_reco_0eta1v3");
  tf1[2]=(TF1 *) f3->FindObjectAny("puppiJECcorr_reco_1v3eta2v5");

  // -----------------------------------------

  int counter_0=0;
  int counter_1=0;
  int counter_2=0;    
  int counter_3=0;

  cout<<"finish define Histogram"<< endl;

  // ------ begin of event loop ---------------

  int Number_to_print    =  100000;
//  int Number_to_print    =  5000;

//  int Max_number_to_read = 1000000;
  int Max_number_to_read = 30000;

  bool PU_weight_flag = true;
//  PU_weight_flag = false; // turn off the PU weight

  if( PU_weight_flag ) cout<<"Will use Pile Up weight"<<endl;
  else cout<<"Will not use Pile Up weight"<<endl;


  cout<<"staring loop events"<< endl;

  for( Long64_t ev = 0; ev < data.GetEntriesFast(); ev++ ){

    if( ev %   Number_to_print == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

//    if( ev > Max_number_to_read) break;

    data.GetEntry(ev);


    // get Branch

    Bool_t   isData                  = data.GetBool("isData");
    Float_t  ntrue                   = data.GetFloat("pu_nTrueInt");
    Int_t    nVtx                    = data.GetInt("nVtx");

    TClonesArray* muP4  = (TClonesArray*) data.GetPtrTObject("muP4");

    Int_t          FATnJet           = data.GetInt("FATnJet");    
    Int_t*         FATnSubSDJet      = data.GetPtrInt("FATnSubSDJet");
    Float_t*       FATjetCISVV2      = data.GetPtrFloat("FATjetCISVV2");
    Float_t*       FATjetSDmass      = data.GetPtrFloat("FATjetSDmass");
    Float_t*       FATjetPRmass      = data.GetPtrFloat("FATjetPRmass");
    Float_t*       FATjetPRmassCorr  = data.GetPtrFloat("FATjetPRmassL2L3Corr");
    Float_t*       FATjetTau1        = data.GetPtrFloat("FATjetTau1");
    Float_t*       FATjetTau2        = data.GetPtrFloat("FATjetTau2");
    TClonesArray*  FATjetP4          = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    vector<bool>&  FATjetPassIDLoose = *((vector<bool>*) data.GetPtr("FATjetPassIDLoose"));
    vector<float>* FATsubjetSDPx     = data.GetPtrVectorFloat("FATsubjetSDPx", FATnJet);
    vector<float>* FATsubjetSDPy     = data.GetPtrVectorFloat("FATsubjetSDPy", FATnJet);
    vector<float>* FATsubjetSDPz     = data.GetPtrVectorFloat("FATsubjetSDPz", FATnJet);
    vector<float>* FATsubjetSDE      = data.GetPtrVectorFloat("FATsubjetSDE", FATnJet);
    vector<float>* FATsubjetSDCSV    = data.GetPtrVectorFloat("FATsubjetSDCSV", FATnJet);

    Int_t ADDnJet        = data.GetInt("ADDnJet");
    TClonesArray* ADDjetP4 = (TClonesArray*) data.GetPtrTObject("ADDjetP4");
    Float_t*  ADDjet_DoubleSV = data.GetPtrFloat("ADDjet_DoubleSV");

    // get Pile-Up weight 
    

    double PU_weight_central =1;// weight=1 for data

    if(!isData && PU_weight_flag){// for MC
      standalone_LumiReWeighting LumiWeights_central(0);
      PU_weight_central = LumiWeights_central.weight(ntrue);

    }

    double eventWeight = PU_weight_central;   

    h_totalEvents->Fill(1,eventWeight);
//    h_pu_nTrueInt   ->Fill(ntrue , eventWeight);

    // data filter 

    bool CSCT       = FilterStatus(data, "Flag_CSCTightHaloFilter");
    bool eeBadSc    = FilterStatus(data, "Flag_eeBadScFilter");
    bool Noise      = FilterStatus(data, "Flag_HBHENoiseFilter");
    bool NoiseIso   = FilterStatus(data, "Flag_HBHENoiseIsoFilter");

    bool filter_pass = false; 
    if( isData && CSCT && eeBadSc && Noise && NoiseIso ) filter_pass = true;// Data 
    else if (!isData) filter_pass = true; // MC, doesn't apply data filter

    if( !filter_pass ) continue;



    //  apply HLT 

    bool muTrigger1 = TriggerStatus(data, "HLT_Mu45_eta2p1_v");


    bool HLT_pass = false;
    if( isData && muTrigger1 ) HLT_pass= true;// Data
    else if (!isData) HLT_pass = true; // MC, doesn't apply HLT

//    if( !HLT_pass ) continue;

    counter_0++;



    //  nVtx>=1 

    if( nVtx < 1 ) continue;

    counter_1++;



    // select good muons and Z boson 

    vector<Int_t> goodMuID;
    if( !isPassZmumu(data, goodMuID) ) continue;

    counter_2++;


    TLorentzVector* thisMu = (TLorentzVector*)muP4->At(goodMuID[0]);
    TLorentzVector* thatMu = (TLorentzVector*)muP4->At(goodMuID[1]);

 
    // select Fat jet for Higgs 

    Int_t goodFATJetID = -1;
    TLorentzVector* thisJet = NULL;

    for(Int_t ij = 0; ij < FATnJet; ++ij){

      thisJet = (TLorentzVector*)FATjetP4->At(ij);

      if( thisJet->Pt() < 200 ) continue;
      if( fabs(thisJet->Eta()) > 2.4 ) continue;
      if( !FATjetPassIDLoose[ij] ) continue;
      if( thisJet->DeltaR(*thisMu) < 0.8 || thisJet->DeltaR(*thatMu) < 0.8 ) continue;
//      if( !( FATjetPRmassCorr[ij] < 65 || FATjetPRmassCorr[ij] > 135) ) continue;// side band region

      goodFATJetID = ij;
      break;

    }

    if( goodFATJetID < 0 ) continue;

    counter_3++;


/*
    // ---------------------------------------
    // fill histogram in physical object level 

    // nVtx

    h_nVtx            ->Fill(nVtx,eventWeight);

    // Leading and SubLeading Electron 

    if( thisMu->Pt() > thatMu->Pt() ){

      h_leadMuPt    ->Fill(thisMu->Pt(),eventWeight);
      h_leadMuEta   ->Fill(thisMu->Eta(),eventWeight);
      h_subleadMuPt ->Fill(thatMu->Pt(),eventWeight);
      h_subleadMuEta->Fill(thatMu->Eta(),eventWeight);

    }else{

      h_leadMuPt    ->Fill(thatMu->Pt(),eventWeight);
      h_leadMuEta   ->Fill(thatMu->Eta(),eventWeight);
      h_subleadMuPt ->Fill(thisMu->Pt(),eventWeight);
      h_subleadMuEta->Fill(thisMu->Eta(),eventWeight);

    }

    // Z boson

    TLorentzVector l4_Z = (*thisMu+*thatMu);

    h_Zmass    ->Fill( l4_Z.M()       ,eventWeight);
    h_Zpt      ->Fill( l4_Z.Pt()      ,eventWeight);
    h_Zeta     ->Fill( l4_Z.Eta()     ,eventWeight);
    h_ZRapidity->Fill( l4_Z.Rapidity(),eventWeight);

    // Fat Jet for Higgs

    double FATjetPuppiSDmassThea = -99;
    FATjetPuppiSDmassThea = ( FATjetSDmass[goodFATJetID] )*getPUPPIweight(thisJet->Pt(),thisJet->Eta(),tf1);

    h_FATjetPt        ->Fill(thisJet->Pt(),eventWeight);
    h_FATjetEta       ->Fill(thisJet->Eta(),eventWeight);
    h_FATjetCISVV2    ->Fill(FATjetCISVV2[goodFATJetID],eventWeight);
    h_FATjetSDmass    ->Fill(FATjetSDmass[goodFATJetID],eventWeight);
    h_FATjetSDmassCorr->Fill( FATjetPuppiSDmassThea ,eventWeight);
    h_FATjetPRmass    ->Fill(FATjetPRmass[goodFATJetID],eventWeight);
    h_FATjetPRmassCorr->Fill(FATjetPRmassCorr[goodFATJetID],eventWeight);
    h_FATjetTau1      ->Fill(FATjetTau1[goodFATJetID],eventWeight);
    h_FATjetTau2      ->Fill(FATjetTau2[goodFATJetID],eventWeight);
    h_FATjetTau2dvTau1->Fill(FATjetTau2[goodFATJetID]/FATjetTau1[goodFATJetID],eventWeight);

    // SubJet 

    int nSubJet = FATnSubSDJet[goodFATJetID];
    h_FATnSubjet->Fill( nSubJet , eventWeight  );

    std::vector<double> subjetPt;  subjetPt.clear();
    std::vector<double> subjetEta; subjetEta.clear();

    for(Int_t is = 0; is < FATnSubSDJet[goodFATJetID]; ++is){


      TLorentzVector l4_subjet(0,0,0,0);

      l4_subjet.SetPxPyPzE(FATsubjetSDPx[goodFATJetID][is],
			   FATsubjetSDPy[goodFATJetID][is],
			   FATsubjetSDPz[goodFATJetID][is],
			   FATsubjetSDE [goodFATJetID][is]);

      subjetPt.push_back( l4_subjet.Pt() );
      subjetEta.push_back( l4_subjet.Eta() );

    }


    if( nSubJet == 1 ){    
      h_FATsubjetLeadingPt     ->Fill( subjetPt[0]  , eventWeight);
      h_FATsubjetLeadingEta    ->Fill( subjetEta[0]  , eventWeight);
      h_FATsubjetLeadingSDCSV  ->Fill( FATsubjetSDCSV[goodFATJetID][0]  , eventWeight);
    }

    if( nSubJet > 1 ){

      double leading_pt_temp =-99; double subleading_pt_temp =-99;
      unsigned int leading_index =-1;     unsigned  int subleading_index =-1;

      for(unsigned int is=0; is<subjetPt.size() ; is++){        

        if( subjetPt[is] > leading_pt_temp ){leading_pt_temp = subjetPt[is] ; leading_index=is; } 
      }
      
      for(unsigned int is=0; is<subjetPt.size() ; is++){
        if( is == leading_index) continue;
        if( subjetPt[is] > subleading_pt_temp ){subleading_pt_temp = subjetPt[is] ; subleading_index=is; }
      }


      h_FATsubjetLeadingPt       ->Fill( subjetPt[leading_index]     , eventWeight);    
      h_FATsubjetLeadingEta    ->Fill( subjetEta[leading_index]  , eventWeight);
      h_FATsubjetLeadingSDCSV  ->Fill( FATsubjetSDCSV[goodFATJetID][leading_index]  , eventWeight);

      h_FATsubjetSubLeadingPt    ->Fill( subjetPt[subleading_index]  , eventWeight);
      h_FATsubjetSubLeadingEta    ->Fill( subjetEta[subleading_index]  , eventWeight);
      h_FATsubjetSubLeadingSDCSV  ->Fill( FATsubjetSDCSV[goodFATJetID][subleading_index]  , eventWeight);


    }

*/
    // ADDjet

    Int_t goodADDjetID = -1;

    for(int iADD=0 ; iADD<ADDnJet ; iADD++){
      
      TLorentzVector* thisADDjet = (TLorentzVector*) ADDjetP4 ->At(iADD);
      double dR_ADDFat = thisADDjet->DeltaR(*thisJet);
      
      if(dR_ADDFat<0.3){
        goodADDjetID = iADD; break;
      }
    }

//    h_ADDjet_DoubleSV->Fill( ADDjet_DoubleSV[goodADDjetID], eventWeight );

    // ZH invariant mass
   
    TLorentzVector l4_Z = (*thisMu+*thatMu);
    TLorentzVector l4_ZH = l4_Z + ( *thisJet );     

//    h_ZHmass ->Fill( l4_ZH.M()   ,eventWeight);


    // -----------------------------------------------
    // save variable in TTree in Physical object level
    

    Event_Weight = eventWeight;
    Tau21 = FATjetTau2[goodFATJetID]/FATjetTau1[goodFATJetID];
    PRmass = FATjetPRmass[goodFATJetID];
    PRmass_L2L3Corrected= FATjetPRmassCorr[goodFATJetID];
    SDmass =  FATjetSDmass[goodFATJetID];
    SDmass_TheaCorrected = ( FATjetSDmass[goodFATJetID] )*getPUPPIweight(thisJet->Pt(),thisJet->Eta(),tf1);
    Double_bTagger = ADDjet_DoubleSV[goodADDjetID];
    ZHmass = l4_ZH.M() ;

    new_tree->Fill();


  } // ------------------ end of event loop ------------------

  cout<<"counter_0: "<< counter_0 << endl;
  cout<<"counter_1: "<< counter_1 << endl;
  cout<<"counter_2: "<< counter_2 << endl;
  cout<<"counter_3: "<< counter_3 << endl;


  fprintf(stderr, "Processed all events\n");

  std::string root_name = Form("%s.root",outputFile.c_str() ) ;
  TString save_path = outputFolder +"/"+  root_name;

  TFile* outFile = new TFile( save_path , "recreate");

/*
  h_pu_nTrueInt     ->Write("pu_nTrueInt");
  h_nVtx            ->Write("nVtx");

  h_leadMuPt    ->Write("leadMuPt");
  h_leadMuEta   ->Write("leadMuEta");
  h_subleadMuPt ->Write("subleadMuPt");
  h_subleadMuEta->Write("subleadMuEta");

  h_Zmass           ->Write("Zmass");
  h_Zpt             ->Write("Zpt");
  h_Zeta            ->Write("Zeta");
  h_ZRapidity       ->Write("ZRapidity");
 
  h_FATjetPt        ->Write("FATjetPt");
  h_FATjetEta       ->Write("FATjetEta");
  h_FATjetCISVV2    ->Write("FATjetCISVV2");
  h_FATjetSDmass    ->Write("FATjetSDmass");
  h_FATjetSDmassCorr->Write("FATjetSDmassCorr");
  h_FATjetPRmass    ->Write("FATjetPRmass");
  h_FATjetPRmassCorr->Write("FATjetPRmassCorr");
  h_FATjetTau1      ->Write("FATjetTau1");
  h_FATjetTau2      ->Write("FATjetTau2");
  h_FATjetTau2dvTau1->Write("FATjetTau2dvTau1");

  h_FATnSubjet            ->Write("FATnSubjet");
  h_FATsubjetLeadingPt    ->Write("FATsubjetLeadingPt");    
  h_FATsubjetLeadingEta   ->Write("FATsubjetLeadingEta");
  h_FATsubjetLeadingSDCSV ->Write("FATsubjetLeadingSDCSV");
  h_FATsubjetSubLeadingPt    ->Write("FATsubjetSubLeadingPt");
  h_FATsubjetSubLeadingEta   ->Write("FATsubjetSubLeadingEta");
  h_FATsubjetSubLeadingSDCSV ->Write("FATsubjetSubLeadingSDCSV");

  h_ADDjet_DoubleSV ->Write("ADDjet_DoubleSV");

  h_ZHmass          ->Write("ZHmass");
*/

  h_totalEvents     ->Write("totalEvents");
  new_tree->Write();

  outFile->Write();  
  delete outFile;


}




