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

double errorfuncThreePar(double*v, double* p) {
  double x= v[0];
  return p[2]/(1+exp(-p[0]*(x-p[1])));
}


void myCalculator(TH1D* h_trigMu_Result_, TH1D* h_leadingMu_pt_){

  cout<<"h_trigMu_Result_->GetEntries(): "    << h_trigMu_Result_->GetEntries() << endl;
  cout<<"h_trigMu_Result_->GetBinContent(2): "<< h_trigMu_Result_->GetBinContent(2) << endl;
  cout<<"h_trigMu_Result_->GetBinContent(3): "<< h_trigMu_Result_->GetBinContent(3) << endl;
  cout<<"total trigger eff: "<< (double) h_trigMu_Result_->GetBinContent(3)/(h_trigMu_Result_->GetBinContent(3) + h_trigMu_Result_->GetBinContent(2))<< endl;

  cout<<"h_leadingMu_pt_->Integral(): "     << h_leadingMu_pt_->Integral() << endl;
  cout<<"h_leadingMu_pt_ overFlow bin events: "<< h_leadingMu_pt_->GetBinContent(  h_leadingMu_pt_->GetNbinsX()+1) << endl;
  cout<<"h_leadingMu_pt_->GetEntries() : "     << h_leadingMu_pt_->GetEntries()  << endl;
  cout<<"h_leadingMu_pt_->Integral(0,10): " << h_leadingMu_pt_->Integral(0,10) << endl;
  cout<<"h_leadingMu_pt_->Integral(11,20): "<< h_leadingMu_pt_->Integral(11,20) << endl;
  cout<<"how many percentage of events with pt<50: "<< (double) h_leadingMu_pt_->Integral(0,10)/(h_leadingMu_pt_->Integral(0,10)+h_leadingMu_pt_->Integral(11,20) )<< endl;

}


void xAna_trig(std::string inputFile, std::string outputFolder, std::string outputFile){

  // ----------- open ntuple, read TTree ----------------

  TString file_path = inputFile ;  
  TFile* file_sample = TFile::Open( file_path );

  TTree* tree = (TTree*) file_sample->Get("tree/treeMaker");
  cout<<"tree->GetEntries(): "<< tree->GetEntries() << endl<<endl;
  TreeReader data( tree );


  // ----------- Declare the histogram ----------------

  TH1D* h_totalEvents        = new TH1D("h_totalEv"           , "totalEvents"        ,   5,  -0.5,  4.5);
  TH1D* h_nTrigger           = new TH1D("h_nTrigger"          , "number of triggers"                ,   1000,  -0.5,  999.5);
  TH1D* h_nTrigger_PreScale1 = new TH1D("h_nTrigger_PreScale1", "number of triggers with prescale=1",   1000,  -0.5,  999.5);

  TString histo_title1; TString histo_title2;
  TString Ele_trigger      = "HLT_Ele115_CaloIdVT_GsfTrkIdT_v";    
  histo_title1 = Ele_trigger + " result";  histo_title2 = Ele_trigger + " PreScale";

  TH1D* h_trigEle_Result   = new TH1D("h_trigEle_Result"  , histo_title1 ,   6,  -1.5,  4.5);
  TH1D* h_trigEle_PreScale = new TH1D("h_trigEle_PreScale", histo_title2 ,   6,  -1.5,  4.5);

  TString Mu_trigger      = "HLT_Mu50_v";                                    
  histo_title1 = Mu_trigger + " result";  histo_title2 = Mu_trigger + " PreScale";

  TH1D* h_trigMu_Result   = new TH1D("h_trigMu_Result"  , histo_title1 ,   6,  -1.5,  4.5);
  TH1D* h_trigMu_PreScale = new TH1D("h_trigMu_PreScale", histo_title2 ,   6,  -1.5,  4.5);

  double LeftBound =0; double RightBound =100;
  double BinWidth = 5;
  int Nbins = ( RightBound - LeftBound ) / BinWidth; 
  histo_title1 = "leading Mu pt passing trigger " + Mu_trigger;

  TH1D* h_leadingMu_pt          = new TH1D("h_leadingMu_pt"         , "leading Mu pt" , Nbins, LeftBound , RightBound );
  TH1D* h_leadingMu_pt_passTrig = new TH1D("h_leadingMu_pt_passTrig", histo_title1    , Nbins, LeftBound , RightBound );
 
  TH1D* h_leadingMu_pt_cut50            = new TH1D("h_leadingMu_pt_cut50"         , "leading Mu pt" , Nbins, LeftBound , RightBound );
  TH1D* h_leadingMu_pt_passTrig_cut50   = new TH1D("h_leadingMu_pt_passTrig_cut50", histo_title1    , Nbins, LeftBound , RightBound );
  TH1D* h_leadingMu_pt_passTrigOR_cut50 = new TH1D("h_leadingMu_pt_passTrigOR_cut50", "pass Mu50 OR TkMu50"    , Nbins, LeftBound , RightBound );

  TH1D* h_leadingMu_pt_cutSkim          = new TH1D("h_leadingMu_pt_cutSkim"         , "leading Mu pt" , Nbins, LeftBound , RightBound );
  TH1D* h_leadingMu_pt_passTrig_cutSkim = new TH1D("h_leadingMu_pt_passTrig_cutSkim", histo_title1    , Nbins, LeftBound , RightBound );


  h_leadingMu_pt          ->Sumw2();
  h_leadingMu_pt_passTrig ->Sumw2();

  h_leadingMu_pt_cut50           ->Sumw2();
  h_leadingMu_pt_passTrig_cut50  ->Sumw2();
  h_leadingMu_pt_passTrigOR_cut50->Sumw2();

  h_leadingMu_pt_cutSkim          ->Sumw2();
  h_leadingMu_pt_passTrig_cutSkim ->Sumw2();

  TH1D* h_trigMu_Result_cut50       = new TH1D("h_trigMu_Result_cut50"    , "h_trigMu_Result_cut50"     ,   6,  -1.5,  4.5);
  TH1D* h_trigMuOR_Result_cut50     = new TH1D("h_trigMuOR_Result_cut50"  , "h_trigMuOR_Result_cut50"   ,   6,  -1.5,  4.5);
  TH1D* h_trigMu_Result_cutSkim     = new TH1D("h_trigMu_Result_cutSkim"  , "h_trigMu_Result_cutSkim"   ,   6,  -1.5,  4.5);



  // ----------- begin of event loop ---------------------------------

  int counter_0=0;

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


    Bool_t   isData                  = data.GetBool("isData");
    std::string*  trigName     =                   data.GetPtrString("hlt_trigName"    );
    vector<bool>& trigResult   = *((vector<bool>*) data.GetPtr      ("hlt_trigResult"  ));
    Int_t*        trigPreScale =                   data.GetPtrInt   ("hlt_trigPrescale");
    Int_t         trigNumber   =                   data.GetInt      ("hlt_nTrigs");

    Int_t    nGenPar                    = data.GetInt("nGenPar");
    const TClonesArray* genParP4 = (TClonesArray*) data.GetPtrTObject("genParP4");
    Int_t*   genParQ     = data.GetPtrInt("genParQ");
    Int_t*   genParId    = data.GetPtrInt("genParId");
    Int_t*   genParSt    = data.GetPtrInt("genParSt");
    Int_t*   genMomParId = data.GetPtrInt("genMomParId");
    Int_t*   genParIndex = data.GetPtrInt("genParIndex");
    Int_t*   genMo1      = data.GetPtrInt("genMo1");
    Int_t*   genMo2      = data.GetPtrInt("genMo2");
    Int_t*   genDa1      = data.GetPtrInt("genDa1");
    Int_t*   genDa2      = data.GetPtrInt("genDa2");


    const Int_t    nMu          = data.GetInt("nMu");
    const TClonesArray* muP4    = (TClonesArray*) data.GetPtrTObject("muP4");

    Int_t          FATnJet           = data.GetInt("FATnJet");
    TClonesArray*  FATjetP4          = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    Float_t*       FATjetPuppiSDmass = data.GetPtrFloat("FATjetPuppiSDmass");

    // for signal MC sample, consider Z->mu mu only


    bool isGenZmumu = false;

    if(!isData){// for MC
      for ( int iGen=0; iGen<nGenPar; iGen++ ){
        TLorentzVector* thisGenPar = (TLorentzVector*) genParP4 ->At(iGen);

        if( genParId[iGen] == 23 && abs(genParId[ genDa1[iGen]]) == 13 && abs(genParId[ genDa2[iGen]]) == 13  )
        { isGenZmumu = true; break; }

      }
    }

    if ( !isData && !isGenZmumu ) continue;// for MC, only Z->mumu events pass, but data always pass here


    h_totalEvents->Fill(1.0);

//    cout<<"data.GetPtrStringSize(): "<< data.GetPtrStringSize() << endl;
//    cout<<"trigNumber: "<< trigNumber << endl;

    h_nTrigger->Fill(trigNumber);
    int nTrig_PreScale1 = 0;

    bool findEleTrigger = false; bool findMuTrigger = false;

    bool PassMuTrigger_Mu50 = false;
    bool PassMuTrigger_TkMu50 = false;

    for(int it = 0; it < data.GetPtrStringSize(); it++){ // HLT loop

      std::string thisTrig = trigName[it];
/*
      cout<<"it: "              << it               << endl;
      cout<<"thisTrig: "        << thisTrig         << endl;
      cout<<"results: "         << trigResult[it]   << endl;
      cout<<"trigPreScale[it]: "<< trigPreScale[it] << endl;
*/

      if( trigPreScale[it] == 1 ) nTrig_PreScale1++; 

      // Ele trigger
      std::string TRIGGERNAME = (std::string) Ele_trigger; 
      if( thisTrig.find(TRIGGERNAME) != std::string::npos ){

        findEleTrigger = true;
        h_trigEle_PreScale->Fill (trigPreScale[it]);

        bool results = trigResult[it];
        if   (results) h_trigEle_Result->Fill(1.0);
        else           h_trigEle_Result->Fill(0.0);

      }


      // Mu trigger
      TRIGGERNAME = (std::string) Mu_trigger;
      if( thisTrig.find(TRIGGERNAME) != std::string::npos ){

        findMuTrigger = true;
        h_trigMu_PreScale->Fill (trigPreScale[it]);

        bool results = trigResult[it];
        if   (results) {h_trigMu_Result->Fill(1.0);  PassMuTrigger_Mu50 = true;}
        else            h_trigMu_Result->Fill(0.0);

      }


      TRIGGERNAME = "HLT_TkMu50_v";
      if( thisTrig.find(TRIGGERNAME) != std::string::npos && trigResult[it] ){
        PassMuTrigger_TkMu50 = true;
      }


    }// end HLT loop

    h_nTrigger_PreScale1 ->Fill( nTrig_PreScale1 );

    if(!findEleTrigger){
      cout<<"cannot find "<< Ele_trigger <<" in this event"<<endl; 
      h_trigEle_PreScale ->Fill(-1.0); 
      h_trigEle_Result   ->Fill(-1.0);
    }

    if(!findMuTrigger){
      cout<<"cannot find "<< Mu_trigger <<" in this event"<<endl;
      h_trigMu_PreScale ->Fill(-1.0);
      h_trigMu_Result   ->Fill(-1.0);
    }



    // Muon part

//    for( int im = 0; im <nMu; im++ ){ // offline Muon loop 
//      TLorentzVector* myMu = (TLorentzVector*)muP4->At(im);
//    }

    if ( nMu >0){
      TLorentzVector* leadingMu = (TLorentzVector*) muP4->At(0);

      // no cut
      h_leadingMu_pt     			 ->Fill( leadingMu->Pt() );
      if (PassMuTrigger_Mu50) h_leadingMu_pt_passTrig ->Fill( leadingMu->Pt() );

      // cut pt>50
      if ( leadingMu->Pt() > 50 ){

        h_leadingMu_pt_cut50                              ->Fill( leadingMu->Pt() );

        if (PassMuTrigger_Mu50) {h_leadingMu_pt_passTrig_cut50 ->Fill( leadingMu->Pt() );
                            h_trigMu_Result_cut50 ->Fill(1.0);
        }
        else                h_trigMu_Result_cut50 ->Fill(0.0);

        if ( PassMuTrigger_Mu50 || PassMuTrigger_TkMu50){
          h_leadingMu_pt_passTrigOR_cut50 -> Fill(  leadingMu->Pt() );
          h_trigMuOR_Result_cut50         ->Fill(1.0);
        }
        else h_trigMuOR_Result_cut50      ->Fill(0.0);

      }

    } // end of offline Muon part





    // skim cut part

    bool skim_MuPass = false;
    if   ( nMu == 2 ){
      TLorentzVector* myMuon1   = (TLorentzVector*) muP4->At(0);
      TLorentzVector* myMuon2   = (TLorentzVector*) muP4->At(1);
      if ( myMuon1->Pt()>55 && myMuon2->Pt()>20 ) skim_MuPass = true;
    }

    else if( nMu > 2 ){
      TLorentzVector* myMuon1   = (TLorentzVector*) muP4->At(0);
      TLorentzVector* myMuon2   = (TLorentzVector*) muP4->At(1);
      TLorentzVector* myMuon3   = (TLorentzVector*) muP4->At(2);
      if ( (myMuon1->Pt()>55 && myMuon2->Pt()>20) || 
           (myMuon1->Pt()>55 && myMuon3->Pt()>20) ||
           (myMuon2->Pt()>55 && myMuon3->Pt()>20)
         ) skim_MuPass = true;        
    }

    bool skim_JetPass = false;
    if   ( FATnJet == 2 ){
      TLorentzVector* myJet1   = (TLorentzVector*) FATjetP4->At(0);
      TLorentzVector* myJet2   = (TLorentzVector*) FATjetP4->At(1);
      if ( ( myJet1->Pt()>200        || myJet2->Pt()>200         ) && 
           ( FATjetPuppiSDmass[0]>40 || FATjetPuppiSDmass[1]>40  )    ) skim_JetPass = true ; 
    }

    else if ( FATnJet > 2 ){
        TLorentzVector* myJet1   = (TLorentzVector*) FATjetP4->At(0);
        TLorentzVector* myJet2   = (TLorentzVector*) FATjetP4->At(1);
        TLorentzVector* myJet3   = (TLorentzVector*) FATjetP4->At(2); 
      if ( ( myJet1->Pt()>200        || myJet2->Pt()>200        || myJet3->Pt()>200        ) &&
           ( FATjetPuppiSDmass[0]>40 || FATjetPuppiSDmass[1]>40 || FATjetPuppiSDmass[2]>40 )    ) 
        skim_JetPass = true;
    }

    if ( skim_MuPass && skim_JetPass){ // if pass skim cut 
      TLorentzVector* leadingMu = (TLorentzVector*) muP4->At(0); 
      h_leadingMu_pt_cutSkim                              ->Fill( leadingMu->Pt() );
      if (PassMuTrigger_Mu50) {h_leadingMu_pt_passTrig_cutSkim ->Fill( leadingMu->Pt() );
                          h_trigMu_Result_cutSkim ->Fill(1.0);
      }else               h_trigMu_Result_cutSkim ->Fill(0.0);

    }
    // end skim part


    counter_0++;

  } // ------------------ end of event loop ------------------

  cout<<"counter_0: "<< counter_0 << endl;
  fprintf(stderr, "Processed all events\n");


  // ---------- Mu Trigger efficiency v.s pt ----------

  TH1D* h_MuTriggerEff = (TH1D*)  h_leadingMu_pt_passTrig->Clone("h_MuTriggerEff"); 
  h_MuTriggerEff ->Sumw2();
  h_MuTriggerEff ->Divide( h_leadingMu_pt );

  TH1D* h_MuTriggerEff_cut50 = (TH1D*)  h_leadingMu_pt_passTrig_cut50->Clone("h_MuTriggerEff_cut50");
  h_MuTriggerEff_cut50 ->Sumw2();
  h_MuTriggerEff_cut50 ->Divide( h_leadingMu_pt_cut50 );

  TH1D* h_MuTriggerOREff_cut50 = (TH1D*)  h_leadingMu_pt_passTrigOR_cut50->Clone("h_MuTriggerOREff_cut50");
  h_MuTriggerOREff_cut50 ->Sumw2();
  h_MuTriggerOREff_cut50 ->Divide( h_leadingMu_pt_cut50 );

  TH1D* h_MuTriggerEff_cutSkim = (TH1D*)  h_leadingMu_pt_passTrig_cutSkim->Clone("h_MuTriggerEff_cutSkim");
  h_MuTriggerEff_cutSkim ->Sumw2();
  h_MuTriggerEff_cutSkim ->Divide( h_leadingMu_pt_cutSkim );



  // ---------- Fit the efficiency plot ----------

  cout<<"start to fit the efficiency plot"<< endl;  

  // initial par
  double p0 =  0.1; // steep or slow to grow up
  double p1 = 50  ; // the turning point position in x axis
  double p2 =  1  ; // change the height of plateau

  TF1* f_fittrigg1 = new TF1("f_fittrigg1",errorfuncThreePar,0,100,3);

  f_fittrigg1 ->SetParameter(0, p0 );
  f_fittrigg1 ->SetParameter(1, p1 );
  f_fittrigg1 ->SetParameter(2, p2 );

  h_MuTriggerEff ->Fit(f_fittrigg1);

  TF1* f_fittrigg1_cut50 = new TF1("f_fittrigg1_cut50",errorfuncThreePar,0,100,3);

  f_fittrigg1_cut50 ->SetParameter(0, p0 );
  f_fittrigg1_cut50 ->SetParameter(1, p1 );
  f_fittrigg1_cut50 ->SetParameter(2, p2 );

  h_MuTriggerEff_cut50 ->Fit(f_fittrigg1_cut50);


  TF1* f_fittrigg1OR_cut50 = new TF1("f_fittrigg1OR_cut50",errorfuncThreePar,0,100,3);

  f_fittrigg1OR_cut50 ->SetParameter(0, p0 );
  f_fittrigg1OR_cut50 ->SetParameter(1, p1 );
  f_fittrigg1OR_cut50 ->SetParameter(2, p2 );

  h_MuTriggerOREff_cut50 ->Fit(f_fittrigg1OR_cut50);


  TF1* f_fittrigg1_cutSkim = new TF1("f_fittrigg1_cutSkim",errorfuncThreePar,0,100,3);

  f_fittrigg1_cutSkim ->SetParameter(0, p0 );
  f_fittrigg1_cutSkim ->SetParameter(1, p1 );
  f_fittrigg1_cutSkim ->SetParameter(2, p2 );

  h_MuTriggerEff_cutSkim ->Fit(f_fittrigg1_cutSkim);


  // ---------- draw -------------------  

  h_MuTriggerEff         ->GetXaxis ()->SetRangeUser(0 ,100 );
  h_MuTriggerEff_cut50   ->GetXaxis ()->SetRangeUser(0 ,100 );
  h_MuTriggerOREff_cut50 ->GetXaxis ()->SetRangeUser(0 ,100 );
  h_MuTriggerEff_cutSkim ->GetXaxis ()->SetRangeUser(0 ,100 );



  h_MuTriggerEff->GetYaxis ()->SetRangeUser(-0.1 ,1.2 );
  h_MuTriggerEff->GetYaxis ()->SetTitle("Efficiency");
  h_MuTriggerEff->GetXaxis ()->SetTitle("Offline leading Mu pt");

  TCanvas* c1 = new TCanvas("c1","c1",10,10,800,600); c1->cd();
  h_MuTriggerEff -> Draw();


  h_MuTriggerEff_cut50->GetYaxis ()->SetRangeUser(-0.1 ,1.2 );
  h_MuTriggerEff_cut50->GetYaxis ()->SetTitle("Efficiency");
  h_MuTriggerEff_cut50->GetXaxis ()->SetTitle("Offline leading Mu pt");

  TCanvas* c2 = new TCanvas("c2","c2",10,10,800,600); c2->cd();
  h_MuTriggerEff_cut50 -> Draw();


  h_MuTriggerEff_cutSkim->GetYaxis ()->SetRangeUser(-0.1 ,1.2 );
  h_MuTriggerEff_cutSkim->GetYaxis ()->SetTitle("Efficiency");
  h_MuTriggerEff_cutSkim->GetXaxis ()->SetTitle("Offline leading Mu pt");

  TCanvas* c3 = new TCanvas("c3","c3",10,10,800,600); c3->cd();
  h_MuTriggerEff_cutSkim -> Draw();


  h_MuTriggerOREff_cut50->GetYaxis ()->SetRangeUser(-0.1 ,1.2 );
  h_MuTriggerOREff_cut50->GetYaxis ()->SetTitle("Efficiency");
  h_MuTriggerOREff_cut50->GetXaxis ()->SetTitle("Offline leading Mu pt");

  TCanvas* c4 = new TCanvas("c4","c4",10,10,800,600); c4->cd();
  h_MuTriggerOREff_cut50 -> Draw();



  // ---------- calculator region ------------


  cout<<endl<<"no cut sample"<< endl;  
  myCalculator( h_trigMu_Result, h_leadingMu_pt );


  cout<<endl<<"cut Mu50 sample"<< endl;
  myCalculator( h_trigMu_Result_cut50, h_leadingMu_pt_cut50 );


  cout<<endl<<"cut Mu50 sample, trigger Mu50 OR TkMu50"<< endl;
  myCalculator( h_trigMuOR_Result_cut50, h_leadingMu_pt_cut50 );


  cout<<endl<<"cut skimming sample"<< endl;
  myCalculator( h_trigMu_Result_cutSkim, h_leadingMu_pt_cutSkim );


  //---------- root file to save ----------


  std::string root_name = Form("%s.root",outputFile.c_str() ) ;
  TString save_path = outputFolder +"/"+  root_name;
  TFile* outFile = new TFile( save_path , "recreate");

  h_totalEvents      -> Write();   

  h_nTrigger         -> Write();
  h_nTrigger_PreScale1 -> Write();

  h_trigEle_Result   -> Write();  
  h_trigEle_PreScale -> Write();  

  h_trigMu_Result    -> Write();
  h_trigMu_PreScale  -> Write(); 

  // no cut

  h_leadingMu_pt          -> Write(); 
  h_leadingMu_pt_passTrig -> Write();
  h_MuTriggerEff          -> Write();

  f_fittrigg1 ->Write();
  c1          ->Write();

  // cut mu 50

  h_leadingMu_pt_cut50          -> Write();
  h_leadingMu_pt_passTrig_cut50 -> Write();
  h_MuTriggerEff_cut50          -> Write();

  f_fittrigg1_cut50 ->Write();
  c2                ->Write();

  h_leadingMu_pt_passTrigOR_cut50 ->Write();
  h_MuTriggerOREff_cut50          ->Write();
  f_fittrigg1OR_cut50             ->Write();
  c4                ->Write();

  // cut skim
  h_leadingMu_pt_cutSkim          -> Write();
  h_leadingMu_pt_passTrig_cutSkim -> Write();
  h_MuTriggerEff_cutSkim          -> Write();

  f_fittrigg1_cutSkim ->Write();
  c3                  ->Write();

  h_trigMu_Result_cut50->Write();
  h_trigMuOR_Result_cut50->Write();

  h_trigMu_Result_cutSkim->Write();


  outFile->Write();  
  delete outFile;

  cout<<endl<<"save ROOT file in: "<< save_path << endl;


}




