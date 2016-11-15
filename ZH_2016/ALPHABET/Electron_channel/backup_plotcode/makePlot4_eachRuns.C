// g++ -Wall -o analyzer `root-config --cflags --glibs` analyzer.cpp
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>

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
#include "TProfile.h"

using namespace std;

TString amplify_string = "HighGain";
//TString amplify_string = "LowGain";

const int MAXSKIROCS = 2;
const int MAXChannel = 64;
const int MAXLAYERS  = 1;

const int MAX_runs = 6;
const int MAX_CellType =6;

//void Open_histo(int RunNumber ,TH1F* &histo , std::string h_name  );

class Open_histo{
  public:
    Open_histo(int RunNumber ,TH1F* &histo , std::string h_name  );
    Open_histo(int RunNumber ,TH2F* &histo , std::string h_name  );
};

class Draw_histo{
  public:
    Draw_histo(TCanvas* &c_draw, TH1D* &h0 ,TH1D* &h1 ,TH1D* &h2 ,TH1D* &h3 ,TH1D* &h4 ,TString title2,TString Xtitle,TString Ytitle , double Ylow,double Yhigh, double Rlow, double Rhigh );
};




void makePlot4_eachRuns(){

  // -------------------------------------
  // access to histgrams
  int run_number[MAX_runs] = {358,359,360,361,362,366}; 
  TString cell_type[MAX_CellType] = {"Full_Cell","Calib_Pads","Half_Cell","MB_Cell","Outer_Calib","Merged_Cell"};

  TH1F  *h_rest_noise [MAX_runs][MAXSKIROCS][MAXChannel][MAXLAYERS];
  TH2F  *h2_ADC_vs_COM [MAX_runs][MAXSKIROCS][MAXChannel][MAXLAYERS];
  TH1F  *h_COM [MAX_runs][MAXLAYERS][MAX_CellType];

  char name[50]; std::string h_name_; std::string Tdir_name = "hgcaltbrechitsplotter_highgain_correlation_cm/"; TString h_name__;

  for(int iRun=0 ; iRun<MAX_runs ; iRun++){
    for(int ILayer=0;ILayer<MAXLAYERS;ILayer++){

      for(int iType=0; iType<MAX_CellType; iType++){
          sprintf(name, "_Layer_%i",ILayer);  h_name_ =  name; h_name_ = Tdir_name + cell_type[iType]+ h_name_;
	  // histogram COM
          Open_histo( run_number[iRun] , h_COM [iRun][ILayer][iType] , h_name_  );
      }

      for(int ISkiroc = 1;ISkiroc<=MAXSKIROCS;ISkiroc++){
        for(int Channel=0; Channel<MAXChannel;Channel++  ){

          // histogram intrinsic noise	
  	  sprintf(name, "Ski_%i_Channel_%i_Layer_%i",ISkiroc,Channel,ILayer);  h_name_ =  name; h_name_ = Tdir_name + h_name_;
  	  Open_histo( run_number[iRun] , h_rest_noise[iRun][ISkiroc-1][Channel][ILayer] , h_name_  );
	  // histogram 2D COM v.s ADC
          sprintf(name, "Ski_%i_Channel_%i_Layer_%i_ADC_com",ISkiroc,Channel,ILayer);  h_name_ =  name; h_name_ = Tdir_name + h_name_;
          Open_histo( run_number[iRun] , h2_ADC_vs_COM[iRun][ISkiroc-1][Channel][ILayer] , h_name_  );

        }
      }
    }
  }


//  TCanvas *c_ = new TCanvas("c_","c_",10,10,800,600); c_->cd(); 
//  h_rest_noise[2][1][20][0] ->Draw();   
//  h2_ADC_vs_COM[2][1][20][0] ->Draw(); 
//  h_COM[2][0][0]->Draw();


  // -------------------------------------
  // get RMS and RMS Error of histogram 


  // get COM of each runs
  double COM_RMS      [MAX_runs][MAXLAYERS][MAX_CellType]; 
  double COM_RMSError [MAX_runs][MAXLAYERS][MAX_CellType];

  for(int iRun=0 ; iRun<MAX_runs ; iRun++){
    for(int ILayer=0;ILayer<MAXLAYERS;ILayer++){
      for(int iType=0; iType<MAX_CellType; iType++){

        COM_RMS[iRun][ILayer][iType]      = h_COM [iRun][ILayer][iType] ->GetRMS();
        COM_RMSError[iRun][ILayer][iType] = h_COM [iRun][ILayer][iType] ->GetRMSError(); 
      }
    }
  }

//  cout<<"COM_RMS[2][0][0]: "<< COM_RMS[2][0][0] <<endl;
//  cout<<"COM_RMS[2][0][5]: "<< COM_RMS[2][0][5] <<endl;// Merged Cell


  // get intrinsic noise of each channels, each runs,
  double intrinsic_Mean      [MAX_runs][MAXLAYERS][MAXSKIROCS][MAXChannel];
  double intrinsic_MeanError [MAX_runs][MAXLAYERS][MAXSKIROCS][MAXChannel];
  double intrinsic_RMS       [MAX_runs][MAXLAYERS][MAXSKIROCS][MAXChannel];
  double intrinsic_RMSError  [MAX_runs][MAXLAYERS][MAXSKIROCS][MAXChannel];

  for(int iRun=0 ; iRun<MAX_runs ; iRun++){
    for(int ILayer=0;ILayer<MAXLAYERS;ILayer++){

      for(int ISkiroc = 1;ISkiroc<=MAXSKIROCS;ISkiroc++){
        for(int Channel=0; Channel<MAXChannel;Channel++  ){

          intrinsic_Mean     [iRun][ILayer][ISkiroc-1][Channel]= h_rest_noise [iRun][ISkiroc-1][Channel][ILayer]->GetMean();
	  intrinsic_MeanError[iRun][ILayer][ISkiroc-1][Channel]= h_rest_noise [iRun][ISkiroc-1][Channel][ILayer]->GetMeanError();
	  intrinsic_RMS      [iRun][ILayer][ISkiroc-1][Channel]= h_rest_noise [iRun][ISkiroc-1][Channel][ILayer]->GetRMS();
	  intrinsic_RMSError [iRun][ILayer][ISkiroc-1][Channel]= h_rest_noise [iRun][ISkiroc-1][Channel][ILayer]->GetRMSError();

        }
      }
    }
  }

//  cout<<"intrinsic_Mean[1][0][1][30]: "     << intrinsic_Mean[1][0][1][30] << endl;
//  cout<<"intrinsic_MeanError[1][0][1][30]: "<< intrinsic_MeanError[1][0][1][30] << endl;
//  cout<<"intrinsic_RMS[1][0][1][30]: "      << intrinsic_RMS[1][0][1][30] << endl;
//  cout<<"intrinsic_RMSError[1][0][1][30]: " << intrinsic_RMSError[1][0][1][30] << endl;


  // -------------------------------------
  // Set histogram Bin Content and Error 

  // COM v.s run
  TH1D* h_COM_of_runs [MAXLAYERS][MAX_CellType]; 

  for(int ILayer=0;ILayer<MAXLAYERS;ILayer++){
    for(int iType=0; iType<MAX_CellType; iType++){

      sprintf(name, "h_COM_of_runs_Layer_%i",ILayer); h_name_ =  name; 
      h_name_ = h_name_ + "_" + cell_type[iType]; h_name__ = h_name_ ;  
      h_COM_of_runs [ILayer][iType] = new TH1D(h_name__, h_name__ ,10, 357.5, 367.5);

      for(int iRun=0 ; iRun<MAX_runs ; iRun++){        
        int bin_number = h_COM_of_runs[ILayer][iType] ->GetXaxis()->FindBin( run_number[iRun] );
        h_COM_of_runs [ILayer][iType]-> SetBinContent( bin_number , COM_RMS[iRun][ILayer][iType] );        
        h_COM_of_runs [ILayer][iType]-> SetBinError( bin_number , COM_RMSError[iRun][ILayer][iType] );        
      }
     
      h_COM_of_runs [ILayer][iType]->Sumw2();
    }
  }

//    h_COM_of_runs[0][0] -> Draw();

  // intrinsic noise v.s run
                                  // Full Cali Half MouseBite Outer Merged
  int skiroc_number [MAX_CellType] = {1   , 1 , 1    , 1     , 1   , 2};
  int channel_number[MAX_CellType] = {25  , 26, 39   , 19    , 40  , 0};

//  channel_number[2] = 33;
//  channel_number[2] = 17;
//  channel_number[2] = 59;
//  channel_number[2] = 60;

//  cout<<"skiroc_number[2] : "<< skiroc_number[2] << endl;
//  cout<<"channel_number[2]: "<< channel_number[2]<< endl;


  TH1D* h_intrinsic_mean_of_runs [MAXLAYERS][MAX_CellType];
  TH1D* h_intrinsic_rms_of_runs  [MAXLAYERS][MAX_CellType];

  for(int ILayer=0;ILayer<MAXLAYERS;ILayer++){
    for(int iType=0; iType<MAX_CellType; iType++){

      if(iType==5)continue;// not show Merged Cell

      sprintf(name, "h_intrinsic_mean_of_runs_Layer_%i",ILayer); h_name_ =  name;
      h_name_ = h_name_ + "_" + cell_type[iType]; h_name__ = h_name_ ;
      h_intrinsic_mean_of_runs [ILayer][iType] = new TH1D(h_name__, h_name__ ,10, 357.5, 367.5);

      sprintf(name, "h_intrinsic_rms_of_runs_Layer_%i",ILayer); h_name_ =  name;
      h_name_ = h_name_ + "_" + cell_type[iType]; h_name__ = h_name_ ;
      h_intrinsic_rms_of_runs [ILayer][iType] = new TH1D(h_name__, h_name__ ,10, 357.5, 367.5);


      for(int iRun=0 ; iRun<MAX_runs ; iRun++){
        int bin_number = h_intrinsic_mean_of_runs[ILayer][iType] ->GetXaxis()->FindBin( run_number[iRun] );
        
        h_intrinsic_mean_of_runs [ILayer][iType]-> SetBinContent( bin_number , intrinsic_Mean     [iRun][ILayer][skiroc_number[iType]-1][channel_number[iType]] );
        h_intrinsic_mean_of_runs [ILayer][iType]-> SetBinError  ( bin_number , intrinsic_MeanError[iRun][ILayer][skiroc_number[iType]-1][channel_number[iType]] );

        h_intrinsic_rms_of_runs [ILayer][iType]-> SetBinContent( bin_number , intrinsic_RMS     [iRun][ILayer][skiroc_number[iType]-1][channel_number[iType]] );
        h_intrinsic_rms_of_runs [ILayer][iType]-> SetBinError  ( bin_number , intrinsic_RMSError[iRun][ILayer][skiroc_number[iType]-1][channel_number[iType]] );

      }

      h_intrinsic_mean_of_runs [ILayer][iType]->Sumw2();
      h_intrinsic_rms_of_runs  [ILayer][iType]->Sumw2();
    }
  }

//  TCanvas *c_ = new TCanvas("c_","c_",10,10,800,600); c_->cd(); 
//  h_intrinsic_mean_of_runs[0][1]->Draw();
//  h_intrinsic_rms_of_runs[0][0]->Draw();

  // ------------------------------------------
  // Draw

  TString title, Xtitle, Ytitle;
  double Ylow, Yhigh, Rlow, Rhigh ;

  // COM v.s run

  TCanvas *c1 = new TCanvas("c1","c1",10,10,800,600);
  title = "Common mode noise v.s runs ("; title = title + amplify_string + ")";
  Xtitle ="run number"; Ytitle ="Common mode noise[ADC]";
  Ylow = 0; Yhigh = 13; Rlow=0; Rhigh=1.5;

  Draw_histo( c1, h_COM_of_runs[0][0], h_COM_of_runs[0][1], h_COM_of_runs[0][2], h_COM_of_runs[0][3] ,h_COM_of_runs[0][4], title, Xtitle, Ytitle , Ylow, Yhigh, Rlow, Rhigh);

  // intrinsic noise v.s run  

  TCanvas *c2 = new TCanvas("c2","c2",10,10,800,600);
  title = "Intrinsic noise mean v.s runs ("; title = title + amplify_string + ")";
  Xtitle ="run number"; Ytitle ="Intrinsic noise mean [ADC]";
  Ylow = -3; Yhigh = 1; Rlow=-10; Rhigh=40;

  Draw_histo( c2, h_intrinsic_mean_of_runs[0][0], h_intrinsic_mean_of_runs[0][1], h_intrinsic_mean_of_runs[0][2], h_intrinsic_mean_of_runs[0][3] ,h_intrinsic_mean_of_runs[0][4], title, Xtitle, Ytitle , Ylow, Yhigh, Rlow, Rhigh );


  TCanvas *c3 = new TCanvas("c3","c3",10,10,800,600);
  title = "Intrinsic noise rms v.s runs ("; title = title + amplify_string + ")";
  Xtitle ="run number"; Ytitle ="Intrinsic noise rms [ADC]";
  Ylow = 0; Yhigh = 2.5; Rlow= 0; Rhigh= 1.2;

  Draw_histo( c3, h_intrinsic_rms_of_runs[0][0], h_intrinsic_rms_of_runs[0][1], h_intrinsic_rms_of_runs[0][2], h_intrinsic_rms_of_runs[0][3] ,h_intrinsic_rms_of_runs[0][4], title, Xtitle, Ytitle , Ylow, Yhigh,Rlow, Rhigh );


  // 2D histogram, COM to RecHit ADC



  TCanvas *c4 = new TCanvas("c4","c4",10,10,800,600);










  // ----------------------------
  // Save

  TString save_name;

  save_name ="pedestal_study_COM_vs_run_"; save_name = save_name + amplify_string +".pdf";
  save_name = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/AugustTB_pedestal_study/" + save_name;
  c1->Print(save_name);

  save_name ="pedestal_study_IntrinsicNoise_vs_run_"; save_name = save_name + amplify_string +".pdf";
  save_name = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/AugustTB_pedestal_study/" + save_name;
  c2->Print(save_name + "(");
  c3->Print(save_name + ")");


}


Open_histo::Open_histo(int RunNumber ,TH1F* &histo , std::string h_name  ){

  char file_name[50]; sprintf(file_name, "%i.root", RunNumber);
  std::string path = file_name; 
  path = "../output_root/RecHitPlotter_HighGain_Correlation_CM_"+amplify_string+"/Ped_Output_RecHitPlotter_HighGain_Correlation_CM_" + path;
  TFile* file = TFile::Open( path.c_str() );
  histo = (TH1F*)file->Get( h_name.c_str() );   

  histo->SetDirectory(0);// do this, so histogram will keep existing after close the TFile 
  file->Close(); delete file;// need to close to avoid crash due to opening too many files
  
}



Open_histo::Open_histo(int RunNumber ,TH2F* &histo , std::string h_name  ){

  char file_name[50]; sprintf(file_name, "%i.root", RunNumber);
  std::string path = file_name;
  path = "../output_root/RecHitPlotter_HighGain_Correlation_CM_"+amplify_string+"/Ped_Output_RecHitPlotter_HighGain_Correlation_CM_" + path;
  TFile* file = TFile::Open( path.c_str() );
  histo = (TH2F*)file->Get( h_name.c_str() );

  histo->SetDirectory(0);
  file->Close(); delete file;
}




Draw_histo::Draw_histo(TCanvas* &c_draw, TH1D* &h0 ,TH1D* &h1 ,TH1D* &h2 ,TH1D* &h3 ,TH1D* &h4 ,TString title2,TString Xtitle,TString Ytitle ,double Ylow,double Yhigh, double Rlow,double  Rhigh){

  c_draw->cd();

  TPad *pad1 = new TPad("pad1","pad1",0.0,0.3,1.0,1.0);
  pad1->Draw();
  pad1->cd();

  h0->SetStats(0);
  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  h4->SetStats(0);

  h0->SetTitle(title2);
  h0->GetXaxis ()->SetTitle(Xtitle);
  h0->GetYaxis ()->SetTitle(Ytitle);
  h0->GetYaxis ()->SetRangeUser(Ylow , Yhigh );

  h0->SetLineColor(2);
  h1->SetLineColor(3);
  h2->SetLineColor(4);
  h3->SetLineColor(kYellow-3);
  h4->SetLineColor(6);

  h0->SetLineWidth(3);
  h1->SetLineWidth(3);
  h2->SetLineWidth(3);
  h3->SetLineWidth(3);
  h4->SetLineWidth(3);

  h0-> Draw("same");
  h1-> Draw("same");
  h2-> Draw("same");
  h3-> Draw("same");
  h4-> Draw("same");

  TLegend *leg1 = new TLegend(0.83,0.4,1.,.9);
  leg1->AddEntry( h0  ,"Full Hex"   ,"lp");
  leg1->AddEntry( h1  ,"Cali Pad"   ,"lp");
  leg1->AddEntry( h2  ,"Helf Hex"   ,"lp");
  leg1->AddEntry( h3  ,"Mouse Bite"   ,"lp");
  leg1->AddEntry( h4  ,"Outer Cali"   ,"lp");

  leg1->Draw();

  c_draw->cd();
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->Draw();
  pad2->cd();


  TH1D* h_central = (TH1D*) h0 ->Clone("h_central");
  TH1D* h_clone[MAX_CellType];

  for(int iType=0; iType<MAX_CellType; iType++){

    if(iType==5) continue; // no Merged Cell 
//    if(iType!=0 && iType!=2 ) continue;

    if(iType==0) h_clone[iType] = (TH1D*) h0 ->Clone("");
    if(iType==1) h_clone[iType] = (TH1D*) h1 ->Clone("");
    if(iType==2) h_clone[iType] = (TH1D*) h2 ->Clone("");
    if(iType==3) h_clone[iType] = (TH1D*) h3 ->Clone("");
    if(iType==4) h_clone[iType] = (TH1D*) h4 ->Clone("");

    h_clone[iType]->Divide(h_central);
    h_clone[iType]->GetYaxis()->SetRangeUser(Rlow, Rhigh);
    h_clone[iType]->SetTitle("");
    h_clone[iType]->GetYaxis ()->SetTitle("Each Type / Full Hex");
    h_clone[iType]->GetYaxis()->SetTitleOffset(0.4);
    h_clone[iType]->SetLabelSize(0.1,"x");
    h_clone[iType]->SetLabelSize(0.1,"y");
    h_clone[iType]->SetTitleSize(0.1,"x");
    h_clone[iType]->SetTitleSize(0.1,"y");

    h_clone[iType]-> Draw("same");
  }

//  cout<<"h_clone[2]->GetBinContent(5):"<< h_clone[2]->GetBinContent(5) << endl;


}



