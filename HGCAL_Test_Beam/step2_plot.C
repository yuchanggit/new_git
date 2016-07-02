// for April TB, see pedestal, pedestalRMS, wavemax of pedestal run

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

void plot_each_run();
void plot_SiPad1  ();

void SetStyle_histo (TH1F* h          , TString variable_name );
void SetStyle_histo2(TH1F* h          , TString variable_name );
void SetStyle_gr    ( TGraphErrors* gr, TString variable_name );

void step2_plot()// main function
{

  cout<<"Hello"<< endl;

//  plot_each_run();

  plot_SiPad1();



}

// ------------------------------------

void plot_SiPad1(){

  cout<<"hello plot_SiPad"<< endl;

  TString variable_name[3] = {"pedestal","pedestalRMS","wave_max"} ;

  const int   N_SiPad1 = 3;// number of configrations for SiPad-1

  int         N_runs_SiPad1[N_SiPad1]={0};

  std::string runN_SiPad1[N_SiPad1][5];

  // run numbers
  N_runs_SiPad1[0] = 5;
  runN_SiPad1[0][0] = "3656";
  runN_SiPad1[0][1] = "3683";
  runN_SiPad1[0][2] = "3688";
  runN_SiPad1[0][3] = "3693";
  runN_SiPad1[0][4] = "3697";

  N_runs_SiPad1[1] = 3;
  runN_SiPad1[1][0] = "3666";
  runN_SiPad1[1][1] = "3663";
  runN_SiPad1[1][2] = "3670";
  runN_SiPad1[1][3] = "";
  runN_SiPad1[1][4] = "";

  N_runs_SiPad1[2] = 2;
  runN_SiPad1[2][0] = "3675";
  runN_SiPad1[2][1] = "3679";
  runN_SiPad1[2][2] = "";
  runN_SiPad1[2][3] = "";
  runN_SiPad1[2][4] = "";


  TH1F* h_variable[N_SiPad1][5][3];// configuration index, runs index, variables index

  for(int i=0;i<N_SiPad1;i++){

    for(int j=0;j<N_runs_SiPad1[i];j++){

      TString path = "root_files/" + runN_SiPad1[i][j] + ".root" ;	
      TFile *f = TFile::Open( path );

      for(int k=0;k<3;k++){
        TString h_name = "h_" + variable_name[k] + "_SiPad1" ;
        h_variable[i][j][k] = (TH1F*)f->FindObjectAny(h_name);
      }
    }
  }

  // combine histogram
  TH1F* h_variable_combine[N_SiPad1][3];// config index, variables index

  for(int i=0;i<N_SiPad1;i++){
    for(int k=0;k<3;k++){

      h_variable_combine[i][k] = (TH1F*) h_variable[i][0][k]->Clone("hnew"); 

      for(int j=0;j<N_runs_SiPad1[i];j++){
        if(j==0)continue;
        h_variable_combine[i][k]->Add ( h_variable[i][j][k],1);  
      }
    }
  }

  // draw combine 

  TCanvas *c_[3];
  c_[0] = new TCanvas("c1","c1",200,10,700,500);
  c_[1] = new TCanvas("c2","c2",200,10,700,500);
  c_[2] = new TCanvas("c3","c3",200,10,700,500);


  // set style 
  gStyle->SetOptStat(0);

  for(int k=0;k<3;k++){
    for(int i=0;i<N_SiPad1;i++){
      SetStyle_histo2(h_variable_combine[i][k] , variable_name[k]   );
      h_variable_combine[i][k]->SetLineColor(i+1);
    }
  }


  // draw

  TString leg_name[3]; 
  leg_name[0] = "120 #mu m,600V";
  leg_name[1] = "200 #mu m,600V";
  leg_name[2] = "300 #mu m,600V";

  for(int k=0;k<3;k++){

    TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
    leg->SetHeader("SiPad-1, un-irradiated");

    c_[k]->cd();

    for(int i=0;i<N_SiPad1;i++){
      if(i==0){h_variable_combine[i][k]->Draw()      ;}
      else    {h_variable_combine[i][k]->Draw("same");}
      
      leg->AddEntry( h_variable_combine[i][k] , leg_name[i] ,"l");
      leg->Draw();
    }
  }

  // save pdf
  TString save_path = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study/";
  TString save_name = save_path + "combine_histo_SiPad1.pdf";

  c_[0]->Print(save_name +"(");
  c_[1]->Print(save_name     );
  c_[2]->Print(save_name +")");

  // ----  Now start to plot TGraphError of different run ------

  TGraphErrors* gr_SiPad1[N_SiPad1][3];// number of config, number of variables

  for(int i=0;i<N_SiPad1;i++){// number of configurations

    for(int k=0;k<3;k++){// number of variables

      int N_runs = N_runs_SiPad1[i];
      double mean[N_runs];
      double rms[N_runs];
      double Nentries[N_runs];
      double error_x[N_runs];

      for(int j=0;j<N_runs_SiPad1[i];j++){// numbers of runs

        mean[j] = h_variable[i][j][k]->GetMean();
        rms[j]  = h_variable[i][j][k]->GetRMS();
        Nentries[j] = h_variable[i][j][k]->GetEntries();
        error_x[j] = 0;
      }
      gr_SiPad1[i][k] = new TGraphErrors( N_runs , Nentries , mean, error_x, rms );

    }
  }

  // fake gr to help to control the range 
  double x_array[2]={0}; double y_array[2]={0}; double x_err_array[2]={0}; double y_err_array[2]={0};
  x_array[0] = 9000 ; x_array[1] = 24000; y_array[0] = 0 ; y_array[1] = 500;

  TGraphErrors* gr_fake[3];

  for(int k=0;k<3;k++){  
    gr_fake[k] = new TGraphErrors(2, x_array, y_array, x_err_array, y_err_array );
    gr_fake[k]->GetXaxis()->SetRangeUser(10000 ,23000 );

    if(variable_name[k] == "pedestal")   { gr_fake[k]->GetYaxis()->SetRangeUser(180 , 210); }
    if(variable_name[k] == "pedestalRMS"){ gr_fake[k]->GetYaxis()->SetRangeUser(0   , 30 ); }
    if(variable_name[k] == "wave_max")   { gr_fake[k]->GetYaxis()->SetRangeUser(0   , 60); }

  }

  // set style

  for(int k=0;k<3;k++){
    for(int i=0;i<N_SiPad1;i++){ 
      SetStyle_gr ( gr_fake[k] , variable_name[k] );
      SetStyle_gr ( gr_SiPad1[i][k] , variable_name[k] );
      gr_SiPad1[i][k]->SetMarkerColor(i+1);
    } 
  }

  // draw
  TCanvas *c__[3];
  c__[0] = new TCanvas("c4","c4",200,10,700,500);
  c__[1] = new TCanvas("c5","c5",200,10,700,500);
  c__[2] = new TCanvas("c6","c6",200,10,700,500);


  for(int k=0;k<3;k++){

    TLegend *leg = new TLegend(0.5,0.7,0.8,0.9);
    leg->SetHeader("SiPad-1, un-irradiated");

    c__[k]->SetGrid();
    c__[k]->cd();

    gr_fake[k]->Draw("AP");

    for(int i=0;i<N_SiPad1;i++){
      gr_SiPad1[i][k]->Draw("P");
      leg->AddEntry(gr_SiPad1[i][k]  ,leg_name[i]  ,"pl");
    }    
    leg->Draw();

  }

  // save pdf

  save_name = save_path + "different_run_SiPad1.pdf";

  c__[0]->Print(save_name +"(");
  c__[1]->Print(save_name     );
  c__[2]->Print(save_name +")");


}// end plot_SiPad1()


// -----------------------------------------

void SetStyle_gr ( TGraphErrors* gr, TString variable_name ){

  if(variable_name == "pedestal"){
    gr->GetXaxis()->SetTitle("pedestal [ADC]");
  }

  if(variable_name == "pedestalRMS"){
    gr->GetXaxis()->SetTitle("pedestalRMS [ADC]");
  }

  if(variable_name == "wave_max"){
    gr->GetXaxis()->SetTitle("wave_max [ADC]");
  }

  gr->SetTitle("compare each runs");
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(2);
  gr->GetYaxis()->SetTitle("total number of events in that run");
  gr->SetLineWidth(2);

}

// -----------------------------------------

void SetStyle_histo2(TH1F* h, TString variable_name ){

  h->Scale(  1/h->Integral() );
  h->SetTitle("combine statistics of the same configuration");
  h->SetLineWidth(2);

  if(variable_name == "pedestal"){
    h->GetXaxis()->SetRangeUser(150 ,250 )  ;
    h->GetYaxis()->SetRangeUser(0 ,0.1 )  ;
    h->GetXaxis()->SetTitle("pedestal [ADC]");
  }

  if(variable_name == "pedestalRMS"){
    h->GetXaxis()->SetRangeUser(0 ,60 )  ;
    h->GetYaxis()->SetRangeUser(0 ,0.25 )  ;
    h->GetXaxis()->SetTitle("pedestalRMS [ADC]");
  }

  if(variable_name == "wave_max"){
    h->GetXaxis()->SetRangeUser(-10 ,100 )  ;
    h->GetYaxis()->SetRangeUser(0 ,0.1 )  ;
    h->GetXaxis()->SetTitle("wave_max [ADC]");
  }

  h->GetYaxis()->SetTitle("Arbitrary Unit");
  h->GetYaxis()->SetTitleOffset(1.3);
  h->GetXaxis()->SetTitleOffset(1.3);

}// end SetStyle_histo2()

// -----------------------------------------

void plot_each_run(){

  const int N_runs = 10;

  std::string runN[N_runs];

  runN[0]= "3656";
  runN[1]= "3683";
  runN[2]= "3688";
  runN[3]= "3693";
  runN[4]= "3697";
  runN[5]= "3666";
  runN[6]= "3663";
  runN[7]= "3670";
  runN[8]= "3675";
  runN[9]= "3679";

  // pre define
  TString pad_name[7] = {"Trigger","SiPad6","SiPad5","SiPad4","SiPad1","SiPad2","SiPad3"};

  TString variable_name[3] = {"pedestal","pedestalRMS","wave_max"} ;

  TCanvas *c1 = new TCanvas("c1","c1",200,10,700,500);

  TString save_path = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study/"; 
  TString save_name = save_path + "each_run.pdf"; 

  // loop for each run
  for (int i=0;i<N_runs;i++){

    TString path = "root_files/" + runN[i] + ".root" ; 
    TFile *f = TFile::Open( path ); 

    for(int j=1;j<7;j++){// loop on SiPad

      for(int k=0;k<3;k++){// loop on variable

        TString h_name = "h_" + variable_name[k] + "_" + pad_name[j];
        TH1F *h = (TH1F*)f->FindObjectAny(h_name);

        TString title = "run= " + runN[i]; 
        h->SetTitle( title );

	SetStyle_histo(h, variable_name[k] );
 
        c1->cd();
        h->Draw(); 

        if (k==0 && h->GetMean() >210){
		c1->Update();
		TPaveStats *st =(TPaveStats*)h->GetListOfFunctions()->FindObject("stats");
		st->SetX1NDC(0.15); st->SetX2NDC(0.45); c1->Update();
	} 

        if     (i==0 && j==1 && k==0)         {c1->Print(save_name +"(");}
        else if(i==N_runs-1 && j==6 && k==2)  {c1->Print(save_name +")");}
        else {c1->Print(save_name     );}

      }//  end loop variables

    }// end loop SiPad

  }// end loop run

}// end plot_each_run

// -----------------------------------------

void SetStyle_histo(TH1F* h, TString variable_name ){

  TString X_lable;
  if (variable_name == "pedestal")    X_lable = variable_name + " [ADC]";
  if (variable_name == "pedestalRMS") X_lable = variable_name + " [ADC]";
  if (variable_name == "wave_max")    X_lable = variable_name + " [ADC]";

  h->GetXaxis()->SetTitle(X_lable);
  h->GetYaxis()->SetTitle("number of events");
  h->GetYaxis()->SetTitleOffset(1.3);

  if (variable_name == "wave_max")  h->Rebin(2);

  if (variable_name == "pedestal")  h->GetXaxis()->SetRangeUser(150 ,250 )  ;
  if (variable_name == "wave_max")  h->GetXaxis()->SetRangeUser(-50 ,200 )  ;

  if (variable_name == "pedestal" || variable_name == "wave_max" ) 
	{ gStyle->SetOptFit(1111); h->Fit("gaus"); }

}




