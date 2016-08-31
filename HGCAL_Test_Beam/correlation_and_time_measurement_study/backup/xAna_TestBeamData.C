#include <vector>
#include <iostream>
#include <fstream>
#include <TString.h>
#include <TH1D.h>
#include <TFile.h>
#include <string>
#include "TCanvas.h"
#include <TH2D.h>
#include "untuplizer.h"

using namespace std;

void xAna_TestBeamData(){

  // ----------------------------------- 
  // use untuplizer.h to read samples 

//  TreeReader data("recoTrees/RECO_3770.root");
//  TreeReader data("recoTest/RECO_3774.root");

  TreeReader data("root://eoscms.cern.ch//eos/cms/store/group/upgrade/HGCAL/TimingTB_H2_Apr2016/recoTest/RECO_3774.root");

//  data.Print();


 
  // ----------------------------------- 
  // define histogram

  TH1D* h_pedestalRMS = new TH1D("h_pedestalRMS","h_pedestalRMS",30 , 0,30 );
  TH1D* h_wave_max = new TH1D("h_wave_max","h_wave_max",75 , -50,700 );
  TH1D* h_charge_integ = new TH1D("h_charge_integ","h_charge_integ",700 ,-7000 ,7000 );

  TH2D* h_WaveMax_to_ChargeInteg = new TH2D("h_WaveMax_to_ChargeInteg", "h_WaveMax_to_ChargeInteg", 75,-50,700, 700,-7000,7000 ); 



  // ----------------------------------- 
  // Event loop
  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 1000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);


    // get variables that used later

    Int_t nwc          = data.GetInt("nwc");
    Float_t*  wc_recox = data.GetPtrFloat("wc_recox");
    Float_t*  wc_recoy = data.GetPtrFloat("wc_recoy");

    Int_t maxch        = data.GetInt("maxch");

    Float_t*  pedestal      = data.GetPtrFloat("pedestal");
    Float_t*  pedestalRMS   = data.GetPtrFloat("pedestalRMS");
    Float_t*  pedestalSlope = data.GetPtrFloat("pedestalSlope");

    Float_t*  wave_max      = data.GetPtrFloat("wave_max");
    Float_t*  wave_max_aft  = data.GetPtrFloat("wave_max_aft");

    Float_t*  charge_integ      = data.GetPtrFloat("charge_integ");
    Float_t*  charge_integ_max  = data.GetPtrFloat("charge_integ_max");


    // cout first 10 events

    if(jEntry< 10){

    	cout<<"jEntry: "<< jEntry << endl;

	cout<<"nwc: "<< nwc << endl;

    	cout<<"maxch: "<< maxch << endl;

	for(int wire=0 ; wire<nwc ; wire++){

		cout<<"wire: "<< wire << endl;
		cout<<"wc_recox[wire]: "<< wc_recox[wire] << endl;
                cout<<"wc_recox[wire]: "<< wc_recoy[wire] << endl;

	}

    	for(int channel=0 ; channel<maxch ; channel++){

		cout<<"channel: "<< channel << endl;

                cout<<"pedestal[channel]: "<< pedestal[channel] << endl;
		cout<<"pedestalRMS[channel]: "<< pedestalRMS[channel] << endl;
                cout<<"pedestalSlope[channel]: "<< pedestalSlope[channel] << endl;

                cout<<"wave_max[channel]: "<< wave_max[channel] << endl;
                cout<<"wave_max_aft[channel]: "<< wave_max_aft[channel] << endl;

                cout<<"charge_integ[channel]: "<< charge_integ[channel] << endl;
                cout<<"charge_integ_max[channel]: "<< charge_integ_max[channel] << endl;


    	}
    }

    // for test only 10 events
//    if(jEntry>10 ) break;
  
    // fill histogram
    // first to see channel-1 (the No6 pad )

    h_pedestalRMS ->Fill( pedestalRMS[1]   );
    h_wave_max    ->Fill( wave_max[1]      );
    h_charge_integ->Fill( charge_integ[1]  );

    h_WaveMax_to_ChargeInteg ->Fill( wave_max[1] , charge_integ[1] );

  }// end event loop



  // -----------------------------------   
  // Canvas, Draw and Save

  TString path_name = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/" ;
  TString save_name = "test_plot";
  save_name = path_name + save_name + ".pdf";

  TCanvas *c1 = new TCanvas("c1","",200,10,700,500);

  c1->cd();
  h_pedestalRMS  ->Draw();
  c1->Print(save_name + "(");

  c1->cd();
  h_wave_max     ->Draw();
  c1->Print(save_name );

  c1->cd();
  h_charge_integ ->Draw();
  c1->Print(save_name );

  c1->cd();
  h_WaveMax_to_ChargeInteg ->Draw();
  c1->Print(save_name + ")");


}
