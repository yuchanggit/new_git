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

int analyzer_timing() 
{
  
  // need to set these configurable from cfg and change into a vector
  std::string inputFolder = "/store/group/upgrade/HGCAL/TimingTB_H2_Apr2016/recoTrees/";

  std::string runN;
  TChain* tree = new TChain("H4treeReco"); 

  // April TB, Ele beam 100 GeV, 120 um, 600V/800V 
  runN = "3737"; tree->Add(("root://eoscms/"+inputFolder+"RECO_"+runN+".root").c_str());
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


  int channel_fix =4;// fix channel-4 for SiPad-1 in time measurement

  TH1F* h_TimeFrac30_Diff_Xto1[N_channel];
  int N_bin_TimeDiff = 400; double time_low = -20;  double time_high = 20;
//  int N_bin_TimeDiff = 40000; double time_low = -20;  double time_high = 20;

  TH2F* h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[N_channel];

  for(int channel=0; channel<N_channel; channel++){

     if(channel==0 || channel==7){continue;}
     if(channel == channel_fix  ){continue;}

     TString h_name5 = "h_TimeFrac30_Diff_" + SiPad_name[channel] + "_to_" + SiPad_name[channel_fix];
     h_TimeFrac30_Diff_Xto1[channel] = new TH1F(h_name5, h_name5, N_bin_TimeDiff ,time_low ,time_high );

     TString h_name6 = "h_TimeFrac30_Diff_" + SiPad_name[channel] + "_to_" + SiPad_name[channel_fix] + "_vs_WaveMax_" + SiPad_name[channel];  
     h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel] = new TH2F(h_name6,h_name6, N_bin_TimeDiff, time_low, time_high,
										75, -50, 700);
  }




  //TGraph for wave/time around max

  const int nTGraph = 16; 
  TGraph* gr[nTGraph][N_channel]; 

  int fill_times =0;
  int channel_around_max = 4;// show wave/time around max of SiPad-1
  int event_index[nTGraph] = {0};

  int Max_event_times_to_read ;
//  Max_event_times_to_read = 1000;
  Max_event_times_to_read = -1;

  if (Max_event_times_to_read==-1){
           cout<<"number of events used: "<< nentries  << endl;}
  else{    cout<<"number of events used: "<< Max_event_times_to_read << endl;}

  double WC_X_mean_diff = -3.351; // Binghuan's value
  double WC_Y_mean_diff = -0.706; // Binghuan's value

  cout<<"WC_X_mean_diff: "<< WC_X_mean_diff << endl;
  cout<<"WC_Y_mean_diff: "<< WC_Y_mean_diff << endl;

  //loop over entries
  for (Long64_t jentry=0; jentry<nentries; ++jentry){

    if(jentry> Max_event_times_to_read && Max_event_times_to_read!=-1 ) break;

    if (jentry % 5000 == 0)
         fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries );

    //readout the event                                                                                                                
    tree->GetEntry(jentry);


    // selection to be in the high acceptance region of both wire chambers
    bool fiducial_cut_basic = false;
    if(abs(wc_recox[0]-wc_recox[1] - WC_X_mean_diff ) <1 && abs(wc_recoy[0]-wc_recoy[1] - WC_Y_mean_diff) < 1){ fiducial_cut_basic = true;  }

    // -------------------------------------------------
    // time measurement v.s wave_max

    double wave_max_threshold;
//    wave_max_threshold = 0;
//    wave_max_threshold = 150;
//    wave_max_threshold = 250;
//    wave_max_threshold = 350;
//    wave_max_threshold = 450;
//    wave_max_threshold = 550;
//    wave_max_threshold = 650;
//    wave_max_threshold = 750;
//    wave_max_threshold = 850;

    wave_max_threshold = 270;

    for(int channel=0; channel<N_channel; channel++){

       if(channel==0 || channel==7){continue;}
       if(channel == channel_fix){continue;}

       if (!fiducial_cut_basic)continue;

       if(wave_max[ channel_fix ]< wave_max_threshold){continue;}

       double t_frac30_diff = t_max_frac30[channel] - t_max_frac30[channel_fix] ;
//       double t_frac30_diff = t_max_frac50[channel] - t_max_frac50[channel_fix] ;

       h_TimeFrac30_Diff_Xto1[channel]->Fill( t_frac30_diff );
       h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->Fill( t_frac30_diff , wave_max[ channel ]   );
    }


    // -------------------------------------------------
    // fill 10 event's wave/time around max (plot channel 1 )

    if (fill_times < nTGraph 
 
        && wave_max[channel_around_max]>0
        && fiducial_cut_basic
//        && wave_max[channel_around_max]>150
//        && SiPad_region_cut
//        && (wave_max[channel_around_max]<150 && !SiPad_region_cut) // inverted cut
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

  TString path_name = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/timing_study/" ;

  double newx1 = 0.5;  double newx2 = 0.7;   double newy1 = 0.7;  double newy2 = 0.9;


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


  //------------------------


  TString save_name4 = "time_frac30_diff_to_wavemax";
  save_name4 = path_name + save_name4 + ".pdf";

  TCanvas *c4 = new TCanvas("c4","",200,10,700,500);
  gStyle->SetOptFit(1111);

  int counter_plot =1;
  
  for(int channel=0; channel<N_channel; channel++){

    if(channel==0 || channel==7 || channel== channel_fix) continue;

//       cout<<"counter_plot: "<< counter_plot << endl;
//       cout<<"channel: "<< channel << endl;

    h_TimeFrac30_Diff_Xto1[channel]->GetXaxis()->SetRangeUser(-3, 3);
    h_TimeFrac30_Diff_Xto1[channel]->GetXaxis()->SetTitle("timefrac30diff [ns]");
    h_TimeFrac30_Diff_Xto1[channel]->GetYaxis()->SetTitle("number of events");
    h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetXaxis()->SetTitle("timefrac30diff [ns]");
    h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetYaxis()->SetTitle("wave_max");    

    c4->cd();

    double cor_factor2 = h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetCorrelationFactor();
    TString cor_legend_text2 = Form("correlation= %.3f" , cor_factor2 );

    if(counter_plot==1){
    	h_TimeFrac30_Diff_Xto1[channel]->Draw();
        h_TimeFrac30_Diff_Xto1[channel]->Fit("gaus");
        c4->Print(save_name4 +"(");
    	h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->Draw("colz");
        c4->Update(); 
        TPaveStats *st =(TPaveStats*) h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetListOfFunctions()->FindObject("stats");
        st->SetX1NDC(newx1); st->SetX2NDC(newx2); st->SetY1NDC(newy1); st->SetY2NDC(newy2);

        TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
        leg->SetHeader(cor_legend_text2);        leg->Draw();
        c4->Print(save_name4 );
    }

    if(counter_plot==5){

    	h_TimeFrac30_Diff_Xto1[channel]->Draw();
        h_TimeFrac30_Diff_Xto1[channel]->Fit("gaus");
        c4->Print(save_name4 );
    	h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->Draw("colz");
        c4->Update();    
        TPaveStats *st =(TPaveStats*) h_TimeFrac30_Diff_Xto1_vs_WaveMax_ch1[channel]->GetListOfFunctions()->FindObject("stats");
        st->SetX1NDC(newx1); st->SetX2NDC(newx2); st->SetY1NDC(newy1); st->SetY2NDC(newy2);

        TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
        leg->SetHeader(cor_legend_text2);        leg->Draw();
        c4->Print(save_name4 +")");

    }

    if(counter_plot!=1 && counter_plot!=5){
    	h_TimeFrac30_Diff_Xto1[channel]->Draw();
        h_TimeFrac30_Diff_Xto1[channel]->Fit("gaus");
        c4->Print(save_name4 );
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


  // end
  return 0;     

}

