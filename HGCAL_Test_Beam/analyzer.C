// g++ -Wall -o analyzer `root-config --cflags --glibs` analyzer.cpp
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include "TROOT.h"
#include "TSystem.h"
#include "TKey.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TString.h"
#include "TCut.h"
#include "TMath.h"
#include "TApplication.h"
#include "TError.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TPad.h"
#include "TStyle.h"
#include <TString.h>
#include <TPaveStats.h>
#include <TLegend.h>
#include "TGraph.h"

using namespace std;

int analyzer() 
{
//  gROOT->Macro("/afs/cern.ch/user/a/amartell/public/setStyle.C");
  
  // need to set these configurable from cfg and change into a vector
  std::string inputFolder = "/store/group/upgrade/HGCAL/TimingTB_H2_Apr2016/recoTrees/";
//  std::string runN = "3772";// d=200 micrometer
  std::string runN = "3737";// d=120 micrometer


  TChain* tree = new TChain("H4treeReco");
  tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN+".root").c_str());

  runN = "3751"; tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN+".root").c_str());
  runN = "3752"; tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN+".root").c_str());
  runN = "3753"; tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN+".root").c_str());

  Long64_t nentries = tree->GetEntries();
  std::cout << " Tree loaded events = " << nentries << std::endl;

  //Tree variables
  UInt_t nwc;
  Float_t wc_recox[16], wc_recoy[16];
  UInt_t maxch;
  Float_t group[100],ch[100];
  Float_t pedestal[100], pedestalRMS[100], pedestalSlope[100];
  Float_t wave_max[100], wave_max_aft[100], wave_aroundmax[100][50], time_aroundmax[100][50];
  Float_t charge_integ[100], charge_integ_max[100], charge_integ_fix[100];
  Float_t charge_integ_smallw[100], charge_integ_smallw_noise[100], charge_integ_largew[100], charge_integ_largew_noise[100];
  Float_t t_max[100], t_max_frac30[100], t_max_frac50[100], t_at_threshold[100], t_over_threshold[100];

  //Read tree
  tree->SetBranchAddress("nwc",       &nwc);
  tree->SetBranchAddress("wc_recox",   wc_recox);
  tree->SetBranchAddress("wc_recoy",   wc_recoy);

  tree->SetBranchAddress("maxch",               &maxch);
  tree->SetBranchAddress("group",                group);
  tree->SetBranchAddress("ch",                   ch);
  tree->SetBranchAddress("pedestal",             pedestal);
  tree->SetBranchAddress("pedestalRMS",          pedestalRMS);
  tree->SetBranchAddress("pedestalSlope",        pedestalSlope);
  tree->SetBranchAddress("wave_max",             wave_max);
  tree->SetBranchAddress("wave_max_aft",         wave_max_aft);
  tree->SetBranchAddress("wave_aroundmax",       wave_aroundmax);
  tree->SetBranchAddress("time_aroundmax",       time_aroundmax);

  tree->SetBranchAddress("charge_integ",         charge_integ);
  tree->SetBranchAddress("charge_integ_max",     charge_integ_max);
  tree->SetBranchAddress("charge_integ_fix",     charge_integ_fix);
  tree->SetBranchAddress("charge_integ_smallw",  charge_integ_smallw);
  tree->SetBranchAddress("charge_integ_largew",  charge_integ_largew);
  tree->SetBranchAddress("charge_integ_smallw_noise",  charge_integ_smallw_noise);
  tree->SetBranchAddress("charge_integ_largew_noise",  charge_integ_largew_noise);
  tree->SetBranchAddress("t_max",                t_max);
  tree->SetBranchAddress("t_max_frac30",         t_max_frac30);
  tree->SetBranchAddress("t_max_frac50",         t_max_frac50);
  tree->SetBranchAddress("t_at_threshold",       t_at_threshold);
  tree->SetBranchAddress("t_over_threshold",     t_over_threshold);

  //Histos => needs to expand

  const int N_channel = 8; // maxch = 8

  TString SiPad_name[N_channel] = {"Trigger","SiPad6","SiPad5","SiPad4","SiPad1","SiPad2","SiPad3","Not_Revelent"};

  TH1F* h_wave_max[N_channel];
  TH1F* h_charge_integ[N_channel];

  TH2F* h_WaveMax_to_ChargeInteg[N_channel];
  TH2F* h_WC_0[N_channel];

  for(int channel=0; channel<N_channel; channel++){

     TString h_name1 = "h_wave_max_"              + SiPad_name[channel] ;
     TString h_name2 = "h_charge_integ_"          + SiPad_name[channel] ;
     TString h_name3 = "h_WaveMax_to_ChargeInteg_"+ SiPad_name[channel] ;
     TString h_name4 = "h_WireChamber_0_weighted_to_"  + SiPad_name[channel] ;

     int NBins_wave_max = 75    ; double L_wave_max = -50      ; double H_wave_max = 700;
     int NBins_charge_integ = 55; double L_charge_integ = -1000; double H_charge_integ = 10000;

     h_wave_max[channel]     = new TH1F(h_name1, h_name1, NBins_wave_max     , L_wave_max    , H_wave_max  );
     h_charge_integ[channel] = new TH1F(h_name2, h_name2, NBins_charge_integ , L_charge_integ,H_charge_integ );
     h_WaveMax_to_ChargeInteg[channel] = new TH2F(h_name3 ,h_name3,  NBins_wave_max    , L_wave_max    , H_wave_max    , 
								     NBins_charge_integ, L_charge_integ, H_charge_integ);

       h_WC_0[channel] = new TH2F(h_name4 ,h_name4, 60, -12, 18, 48, -20, 4);


  }// end channel loop

  int channel_fix =4;// fix channel-4 for SiPad-1 in time measurement
//  int channel_fix =1;// SiPad-6

  TH1F* h_TimeFrac30_Diff_Xto1[N_channel];
  int N_bin_TimeDiff = 400; double time_low = -20;  double time_high = 20;

  TH2F* h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[N_channel];

  for(int channel=0; channel<N_channel; channel++){

     if(channel==0 || channel==7){continue;}
     if(channel == channel_fix  ){continue;}

//     TString h_name5 = Form("h_TimeFrac30_Diff_Pad%d_to_Pad%d",channel,channel_fix );
     TString h_name5 = "h_TimeFrac30_Diff_" + SiPad_name[channel] + "_to_" + SiPad_name[channel_fix];
     h_TimeFrac30_Diff_Xto1[channel] = new TH1F(h_name5, h_name5, N_bin_TimeDiff ,time_low ,time_high );

//     TString h_name6 = Form("h_TimeFrac30_Diff_Pad%d_to_Pad%d_vs_WaveMax_Pad%d",channel,channel_fix,channel );
     TString h_name6 = "h_TimeFrac30_Diff_" + SiPad_name[channel] + "_to_" + SiPad_name[channel_fix] + "_vs_WaveMax_" + SiPad_name[channel];  
//     TString h_name6 = "h_TimeFrac30_Diff_" + SiPad_name[channel] + "_to_" + SiPad_name[channel_fix] + "_vs_WaveMax_" + SiPad_name[channel_fix]; 
     h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel] = new TH2F(h_name6,h_name6, N_bin_TimeDiff, time_low, time_high,
										75, -50, 700);
  }


  TH2F* h_WC_0_no_weight = new TH2F("h_WC_0_no_weight" ,"h_WC_0_no_weight", 60,-12,18,  48,-20,4); 
  TH2F* h_WC_1_no_weight = new TH2F("h_WC_1_no_weight" ,"h_WC_1_no_weight", 60,-12,18,  48,-20,4);


  //TGraph for wave/time around max

  const int nTGraph = 16; 
  TGraph* gr[nTGraph][N_channel]; 

  int fill_times =0;
  int channel_around_max = 4;// show wave/time around max of SiPad-1
  int event_index[nTGraph] = {0};

  int Max_event_times_to_read ;
  Max_event_times_to_read = 1000;
//  Max_event_times_to_read = -1;

  if (Max_event_times_to_read==-1){
           cout<<"number of events used: "<< nentries  << endl;}
  else{    cout<<"number of events used: "<< Max_event_times_to_read << endl;}

/*
  // first event loop to find the X_mean_diff and Y_mean_diff
  for (Long64_t jentry=0; jentry<nentries; ++jentry){

    if(jentry> Max_event_times_to_read && Max_event_times_to_read!=-1 ) break;

    if (jentry % 5000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries );

    tree->GetEntry(jentry);

    // find acceptance region
    h_WC_0_no_weight->Fill(wc_recox[0], wc_recoy[0]);
    h_WC_1_no_weight->Fill(wc_recox[1], wc_recoy[1]);
 
  }// end event loop

  cout<<"WC_0_X_mean: "<< h_WC_0_no_weight->GetMean(1) << endl;
  cout<<"WC_0_Y_mean: "<< h_WC_0_no_weight->GetMean(2) << endl;
  cout<<"WC_1_X_mean: "<< h_WC_1_no_weight->GetMean(1) << endl;
  cout<<"WC_1_Y_mean: "<< h_WC_1_no_weight->GetMean(2) << endl;

  double WC_X_mean_diff = h_WC_0_no_weight->GetMean(1) - h_WC_1_no_weight->GetMean(1);
  double WC_Y_mean_diff = h_WC_0_no_weight->GetMean(2) - h_WC_1_no_weight->GetMean(2);
*/
  double WC_X_mean_diff = -3.15949;
  double WC_Y_mean_diff = -0.726348;
  cout<<"WC_X_mean_diff: "<< WC_X_mean_diff << endl;
  cout<<"WC_Y_mean_diff: "<< WC_Y_mean_diff << endl;

  //loop over entries
  for (Long64_t jentry=0; jentry<nentries; ++jentry){

    if(jentry> Max_event_times_to_read && Max_event_times_to_read!=-1 ) break;

    if (jentry % 5000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries );

    //readout the event                                                                                                                
    tree->GetEntry(jentry);

//    cout<<"pedestal[4]: "<< pedestal[4]<< endl;
//    cout<<"pedestalRMS[4]: "<< pedestalRMS[4]<< endl;

    // selection to be in the high acceptance region of both wire chambers
    bool fiducial_cut_basic = false;
    if(abs(wc_recox[0]-wc_recox[1] - WC_X_mean_diff ) <1 && abs(wc_recoy[0]-wc_recoy[1] - WC_Y_mean_diff) < 1){ fiducial_cut_basic = true;  }

    // cut on SiPad region
    bool SiPad_region_cut = false;
    if(  wc_recox[0] >-4  && wc_recox[0] <16 && wc_recoy[0] >-19 && wc_recoy[0] <-7  ){ SiPad_region_cut = true;} 

    // -------------------------------------------------
    // wave_max v.s charge correlation
    for(int channel=0; channel<N_channel; channel++){

        if(channel==0 || channel==7){continue;}

//        if (!fiducial_cut_basic)continue;

//        if(wave_max[channel]<0){
//	   cout<<"jentry: "<< jentry << endl;
//           cout<<"channel: "<< channel << endl;
//	   cout<<"wave_max[channel]: "<< wave_max[channel] << endl;
//	   }

        if(wave_max[channel]<0)continue;
//        if(wave_max[channel]<150)continue;
//        if(wave_max[channel]>150)continue;

//	if(! SiPad_region_cut ) {continue;} // inside  the region
        if(  SiPad_region_cut ) {continue;} // outside the region

        h_WC_0[channel] -> Fill( wc_recox[0] , wc_recoy[0] , wave_max[channel] );

//        if(! SiPad_region_cut ) {continue;} // inside  the region
//        if(  SiPad_region_cut ) {continue;} // outside the region

//        if(wave_max[channel]<150)continue;


    	h_wave_max[channel]     ->Fill( wave_max[channel]      );
    	h_charge_integ[channel] ->Fill( charge_integ[channel]  );

   	h_WaveMax_to_ChargeInteg[channel] ->Fill( wave_max[channel] , charge_integ[channel] );

    }// end channel loop 



    // -------------------------------------------------
    // time measurement v.s wave_max
 

    for(int channel=0; channel<N_channel; channel++){

       if(channel==0 || channel==7){continue;}
       if(channel == channel_fix){continue;}

       if (!fiducial_cut_basic)continue;
//       if(wave_max[channel]<0)continue;

//       if(wave_max[ channel]<150)continue;
//       if(wave_max[ channel]<250)continue;
//       if(wave_max[ channel]<500)continue;

//       if(wave_max[ channel_fix ]<150)continue;
//       if(wave_max[ channel_fix ]<250)continue;
       if(wave_max[ channel_fix ]<500){continue;}

       double t_frac30_diff = t_max_frac30[channel] - t_max_frac30[channel_fix] ;

       h_TimeFrac30_Diff_Xto1[channel]->Fill( t_frac30_diff );
       h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->Fill( t_frac30_diff , wave_max[ channel ]   );
//       h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->Fill( t_frac30_diff , wave_max[ channel_fix ]   );
    }


    // -------------------------------------------------
    // fill 10 event's wave/time around max (plot channel 1 )

    if (fill_times < nTGraph 
 
        && wave_max[channel_around_max]>0
        && fiducial_cut_basic
//        && wave_max[channel_around_max]>150
//        && SiPad_region_cut
        && (wave_max[channel_around_max]<150 && !SiPad_region_cut) // inverted cut
     ){

    	double wave_around_max[50] = {0}; double time_around_max[50] = {0};

        for (int sample=0;sample<50;sample++){
            wave_around_max[sample] = wave_aroundmax[channel_around_max][sample];
            time_around_max[sample] = time_aroundmax[channel_around_max][sample];

	    time_around_max[sample] = time_around_max[sample] *1000000000;

        }// end sample loop

       
        gr[fill_times][channel_around_max] = new TGraph(50,time_around_max,wave_around_max);	
	event_index[fill_times] = jentry;  
//        cout<<"event_index[fill_times]: "<< event_index[fill_times] << endl;

        fill_times = fill_times + 1;
    }// end if


  }// end event loop


  // save 

  TString path_name = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/" ;
  TString save_name = "WaveMax_to_ChargeInteg_correlation";
  save_name = path_name + save_name + ".pdf";

  TCanvas *c1 = new TCanvas("c1","",200,10,700,500);
  double newx1 = 0.5;  double newx2 = 0.7;   double newy1 = 0.7;  double newy2 = 0.9;


  for(int channel=0; channel<N_channel; channel++){

    c1->cd();

    h_wave_max[channel]              ->GetXaxis()->SetTitle("wave_max");
    h_wave_max[channel]              ->GetYaxis()->SetTitle("number of events");

    h_charge_integ[channel]          ->GetXaxis()->SetTitle("charge_integ");
    h_charge_integ[channel]          ->GetYaxis()->SetTitle("number of events");

    h_WaveMax_to_ChargeInteg[channel]->GetXaxis()->SetTitle("wave_max");
    h_WaveMax_to_ChargeInteg[channel]->GetYaxis()->SetTitle("charge_integ");
    h_WaveMax_to_ChargeInteg[channel]->GetYaxis()->SetTitleOffset(1.3);

    double cor_factor = h_WaveMax_to_ChargeInteg[channel]->GetCorrelationFactor();    
    TString cor_legend_text = Form("correlation= %.3f" , cor_factor );


    if (channel==0 || channel==7) continue;

    if (channel==1){
    	h_wave_max[channel]     ->Draw();    c1->Print(save_name +"(");
    	h_charge_integ[channel] ->Draw();    c1->Print(save_name );
	
    	h_WaveMax_to_ChargeInteg[channel] ->Draw()      ;   
        c1->Update();
        TPaveStats *st =(TPaveStats*) h_WaveMax_to_ChargeInteg[channel]->GetListOfFunctions()->FindObject("stats");
        st->SetX1NDC(newx1); st->SetX2NDC(newx2); st->SetY1NDC(newy1); st->SetY2NDC(newy2);
        TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
        leg->SetHeader(cor_legend_text);        leg->Draw();
        c1->Update();        c1->Print(save_name);
        h_WaveMax_to_ChargeInteg[channel] ->Draw("colz");    
        leg->Draw();        c1->Update();        c1->Print(save_name);
    }

    if (channel!=1 && channel!=6){
        h_wave_max[channel]     ->Draw();    c1->Print(save_name );
        h_charge_integ[channel] ->Draw();    c1->Print(save_name );

        h_WaveMax_to_ChargeInteg[channel] ->Draw()      ;
        c1->Update();
        TPaveStats *st =(TPaveStats*) h_WaveMax_to_ChargeInteg[channel]->GetListOfFunctions()->FindObject("stats");
        st->SetX1NDC(newx1); st->SetX2NDC(newx2); st->SetY1NDC(newy1); st->SetY2NDC(newy2);
        TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
        leg->SetHeader(cor_legend_text);
        leg->Draw();
        c1->Update();        c1->Print(save_name);
        h_WaveMax_to_ChargeInteg[channel] ->Draw("colz");
        leg->Draw();        c1->Update();        c1->Print(save_name);

    }

    if (channel==6){
        h_wave_max[channel]     ->Draw();    c1->Print(save_name );
        h_charge_integ[channel] ->Draw();    c1->Print(save_name );

        h_WaveMax_to_ChargeInteg[channel] ->Draw()      ;
        c1->Update();
        TPaveStats *st =(TPaveStats*) h_WaveMax_to_ChargeInteg[channel]->GetListOfFunctions()->FindObject("stats");
        st->SetX1NDC(newx1); st->SetX2NDC(newx2); st->SetY1NDC(newy1); st->SetY2NDC(newy2);
        TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
        leg->SetHeader(cor_legend_text);
        leg->Draw();
        c1->Update();        c1->Print(save_name);
        h_WaveMax_to_ChargeInteg[channel] ->Draw("colz");
        leg->Draw();        c1->Update();        c1->Print(save_name +")");
    }

  }// end channel

  //------------------------

  TString save_name2 = "wave_and_time_aroundmax";
  save_name2 = path_name + save_name2 + ".pdf";


  for (int fill_times=0 ; fill_times < nTGraph ; fill_times++){
    TCanvas *c2 = new TCanvas("c2","",200,10,700,500);
    c2->cd();

    TString gr_title = "wave & time around max of " + SiPad_name[channel_around_max];
    gr[fill_times][channel_around_max]->GetYaxis()->SetRangeUser(-50, 500);
    gr[fill_times][channel_around_max]->SetTitle(gr_title);
    gr[fill_times][channel_around_max]->GetXaxis()->SetTitle("time [ns]");
    gr[fill_times][channel_around_max]->GetYaxis()->SetTitle("wave amplitude");
    gr[fill_times][channel_around_max]->Draw();

    TString event_number = Form("the %d-th event" , event_index[fill_times] );
    TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
    leg->SetHeader(event_number);        leg->Draw();

//    cout<<"fill_times:"<< fill_times<<endl;

    if(fill_times == 0) 				{c2->Print(save_name2 +"(");}
    if(fill_times == nTGraph-1)  			{c2->Print(save_name2 +")");}
    if(fill_times != 0 && fill_times != nTGraph-1)	{c2->Print(save_name2 );}

  }

  //------------------------


  TString save_name3 = "wire_chamber_0_weighted_position";
  save_name3 = path_name + save_name3 + ".pdf";

  newx1= 0.7 ;newx2 =0.9 ; newy1 =0.7 ;newy2 =0.9 ;
  double Color_high = 10;


  for(int channel=0; channel<N_channel; channel++){
    if(channel==0 || channel==7 )continue;
    double temp = h_WC_0[channel]->GetMaximum();  
//    cout<<"h_WC_0[channel]->GetMaximum(): "<< temp << endl;
    if(temp > Color_high){Color_high = temp;}
  }

  cout<<"Color_high: "<< Color_high << endl;

  TCanvas *c3 = new TCanvas("c3","",200,10,700,500);

  for(int channel=0; channel<N_channel; channel++){

    h_WC_0[channel]->GetXaxis()->SetTitle("wc_recox[0]  [mm]");
    h_WC_0[channel]->GetYaxis()->SetTitle("wc_recoy[0]  [mm]");

    c3->cd();
    h_WC_0[channel]->GetZaxis()->SetRangeUser(0, Color_high);
    h_WC_0[channel]->Draw("colz");
    c3->Update();
    TPaveStats *st =(TPaveStats*) h_WC_0[channel]->GetListOfFunctions()->FindObject("stats");
    st->SetX1NDC(newx1); st->SetX2NDC(newx2); st->SetY1NDC(newy1); st->SetY2NDC(newy2);

    if(channel==0 || channel==7) continue;
    if(channel==1){c3->Print(save_name3 +"(");}
    if(channel==6){c3->Print(save_name3 +")");}
    if(channel!=1 && channel!=6){c3->Print(save_name3 );}

  }

  //------------------------


  TString save_name4 = "time_frac30_diff_to_wavemax";
  save_name4 = path_name + save_name4 + ".pdf";

  TCanvas *c4 = new TCanvas("c4","",200,10,700,500);

  int counter_plot =1;
  
  for(int channel=0; channel<N_channel; channel++){

    if(channel==0 || channel==7 || channel== channel_fix) continue;

//       cout<<"counter_plot: "<< counter_plot << endl;
//       cout<<"channel: "<< channel << endl;

    h_TimeFrac30_Diff_Xto1[channel]->GetXaxis()->SetTitle("timefrac30diff [ns]");
    h_TimeFrac30_Diff_Xto1[channel]->GetYaxis()->SetTitle("number of events");
    h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetXaxis()->SetTitle("timefrac30diff [ns]");
    h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetYaxis()->SetTitle("wave_max");    

    c4->cd();

    double cor_factor2 = h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetCorrelationFactor();
    TString cor_legend_text2 = Form("correlation= %.3f" , cor_factor2 );

    if(counter_plot==1){
    	h_TimeFrac30_Diff_Xto1[channel]->Draw();c4->Print(save_name4 +"(");
    	h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->Draw("colz");
        c4->Update(); 
        TPaveStats *st =(TPaveStats*) h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetListOfFunctions()->FindObject("stats");
        st->SetX1NDC(newx1); st->SetX2NDC(newx2); st->SetY1NDC(newy1); st->SetY2NDC(newy2);

        TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
        leg->SetHeader(cor_legend_text2);        leg->Draw();
        c4->Print(save_name4 );
    }

    if(counter_plot==5){

    	h_TimeFrac30_Diff_Xto1[channel]->Draw();c4->Print(save_name4 );
    	h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->Draw("colz");
        c4->Update();    
        TPaveStats *st =(TPaveStats*) h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetListOfFunctions()->FindObject("stats");
        st->SetX1NDC(newx1); st->SetX2NDC(newx2); st->SetY1NDC(newy1); st->SetY2NDC(newy2);

        TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
        leg->SetHeader(cor_legend_text2);        leg->Draw();
        c4->Print(save_name4 +")");

    }

    if(counter_plot!=1 && counter_plot!=5){
    	h_TimeFrac30_Diff_Xto1[channel]->Draw();c4->Print(save_name4 );
    	h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->Draw("colz");
        c4->Update();    
        TPaveStats *st =(TPaveStats*) h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetListOfFunctions()->FindObject("stats");
        st->SetX1NDC(newx1); st->SetX2NDC(newx2); st->SetY1NDC(newy1); st->SetY2NDC(newy2);

        TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
        leg->SetHeader(cor_legend_text2);        leg->Draw();
        c4->Print(save_name4 );

    }

    counter_plot++;
  }

  //------------------------
  TString save_name5 = "wire_chamber_position_no_weight";
  save_name5 = path_name + save_name5 + ".pdf";

  newx1= 0.7 ;newx2 =0.9 ; newy1 =0.7 ;newy2 =0.9 ;

  double max_value1 = h_WC_0_no_weight->GetMaximum();
  double max_value2 = h_WC_1_no_weight->GetMaximum();

  if(max_value1 > max_value2 ){Color_high = max_value1 ;}
  if(max_value1 < max_value2 ){Color_high = max_value2 ;}


  h_WC_0_no_weight->GetXaxis()->SetTitle("wc_recox[0]  [mm]");
  h_WC_0_no_weight->GetYaxis()->SetTitle("wc_recoy[0]  [mm]");
  
  h_WC_1_no_weight->GetXaxis()->SetTitle("wc_recox[1]  [mm]");
  h_WC_1_no_weight->GetYaxis()->SetTitle("wc_recoy[1]  [mm]");


  TCanvas *c5 = new TCanvas("c5","",200,10,700,500);
  c5->cd();

  h_WC_0_no_weight->GetZaxis()->SetRangeUser(0, Color_high);
  h_WC_0_no_weight->Draw("colz"); c5->Update();
  TPaveStats *st_wc_1 =(TPaveStats*) h_WC_0_no_weight->GetListOfFunctions()->FindObject("stats");
  st_wc_1->SetX1NDC(newx1); st_wc_1->SetX2NDC(newx2); st_wc_1->SetY1NDC(newy1); st_wc_1->SetY2NDC(newy2);

  c5->Print(save_name5 +"(");

  h_WC_1_no_weight->GetZaxis()->SetRangeUser(0, Color_high);
  h_WC_1_no_weight->Draw("colz");  c5->Update();
  TPaveStats *st_wc_2 =(TPaveStats*) h_WC_1_no_weight->GetListOfFunctions()->FindObject("stats");
  st_wc_2->SetX1NDC(newx1); st_wc_2->SetX2NDC(newx2); st_wc_2->SetY1NDC(newy1); st_wc_2->SetY2NDC(newy2);
  c5->Print(save_name5 +")");



  // end
  return 0;     

}

