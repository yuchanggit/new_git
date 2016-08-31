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

//TString root_dir = "root_files/";
//TString root_dir = "root_files_April_recoTrees/";
TString root_dir = "root_files_April_recoTrees_vSlope0/";
//TString root_dir = "root_files_April_recoTrees_v3/";

  TString save_path = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study_2016April/";


void plot_each_run();
void plot_SiPad(TString SiPad_name ,const int N_SiPad,int N_runs_SiPad[], std::string runN_SiPad[][5] );
void check_two_run();

void SetStyle_histo (TH1F* h          , TString variable_name );
void SetStyle_histo2(TH1F* h          , TString variable_name );
void SetStyle_gr    ( TGraphErrors* gr, TString variable_name );

void step2_plot()// main function
{

  cout<<"Hello"<< endl;

  check_two_run();

  // plot each run individually
  plot_each_run();

  // ------- for SiPad-1 --------

  TString SiPad_name = "SiPad1";  

  const int   N_SiPad1 = 3;// number of configrations for SiPad-1
  int         N_runs_SiPad1[N_SiPad1]={0};// number of run of that configuration
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

  plot_SiPad(SiPad_name, N_SiPad1, N_runs_SiPad1, runN_SiPad1  );

  // ------- for SiPad-3 --------

  SiPad_name = "SiPad3";

  const int   N_SiPad3 = 7;// number of configrations for SiPad-3
  int         N_runs_SiPad3[N_SiPad3]={0};// number of run of that configuration
  std::string runN_SiPad3[N_SiPad3][5];

  // run numbers
  N_runs_SiPad3[0] = 3;
  runN_SiPad3[0][0] = "3656";
  runN_SiPad3[0][1] = "3683";
  runN_SiPad3[0][2] = "3688";
  runN_SiPad3[0][3] = "";
  runN_SiPad3[0][4] = "";

  N_runs_SiPad3[1] = 1;
  runN_SiPad3[1][0] = "3693";
  runN_SiPad3[1][1] = "";
  runN_SiPad3[1][2] = "";
  runN_SiPad3[1][3] = "";
  runN_SiPad3[1][4] = "";

  N_runs_SiPad3[2] = 1;
  runN_SiPad3[2][0] = "3697";
  runN_SiPad3[2][1] = "";
  runN_SiPad3[2][2] = "";
  runN_SiPad3[2][3] = "";
  runN_SiPad3[2][4] = "";

  N_runs_SiPad3[3] = 1;
  runN_SiPad3[3][0] = "3666";
  runN_SiPad3[3][1] = "";
  runN_SiPad3[3][2] = "";
  runN_SiPad3[3][3] = "";
  runN_SiPad3[3][4] = "";

  N_runs_SiPad3[4] = 2;
  runN_SiPad3[4][0] = "3663";
  runN_SiPad3[4][1] = "3670";
  runN_SiPad3[4][2] = "";
  runN_SiPad3[4][3] = "";
  runN_SiPad3[4][4] = "";

  N_runs_SiPad3[5] = 1;
  runN_SiPad3[5][0] = "3675";
  runN_SiPad3[5][1] = "";
  runN_SiPad3[5][2] = "";
  runN_SiPad3[5][3] = "";
  runN_SiPad3[5][4] = "";

  N_runs_SiPad3[6] = 1;
  runN_SiPad3[6][0] = "3679";
  runN_SiPad3[6][1] = "";
  runN_SiPad3[6][2] = "";
  runN_SiPad3[6][3] = "";
  runN_SiPad3[6][4] = "";

  plot_SiPad(SiPad_name, N_SiPad3, N_runs_SiPad3, runN_SiPad3  );

}

// ------------------------------------

void plot_SiPad(TString SiPad_name ,const int N_SiPad,int N_runs_SiPad[], std::string runN_SiPad[][5] ){

  cout<<"hello plot_SiPad: "<< SiPad_name << endl;

  // flag for diodes 
  int irradiated_flag = -1;// 0 for un-irradiated diodes, 1 for irradiated diodes 

  if( SiPad_name == "SiPad1" || SiPad_name == "SiPad2") { irradiated_flag =0;}
  if( SiPad_name == "SiPad3" || SiPad_name == "SiPad4" || SiPad_name == "SiPad5" || SiPad_name == "SiPad6" ) {irradiated_flag =1; }

  // variables
  const int N_variables = 3;
  TString variable_name[N_variables] = {"pedestal","pedestalRMS","wave_max"} ;

  // ----- open histogram  -----------------
  TH1F* h_variable[N_SiPad][5][N_variables];// configuration index, runs index, variables index

  for(int i=0;i<N_SiPad;i++){

    for(int j=0;j<N_runs_SiPad[i];j++){

      TString path = root_dir + runN_SiPad[i][j] + ".root" ;	
      TFile *f = TFile::Open( path );

      for(int k=0;k<N_variables;k++){
        TString h_name = "h_" + variable_name[k] + "_" + SiPad_name ;
        h_variable[i][j][k] = (TH1F*)f->FindObjectAny(h_name);
      }
    }
  }

  // ---- combine histogram ------------------
  TH1F* h_variable_combine[N_SiPad][N_variables];// config index, variables index

  for(int i=0;i<N_SiPad;i++){
    for(int k=0;k<N_variables;k++){

      h_variable_combine[i][k] = (TH1F*) h_variable[i][0][k]->Clone("hnew"); 

      for(int j=0;j<N_runs_SiPad[i];j++){
        if(j==0)continue;
        h_variable_combine[i][k]->Add ( h_variable[i][j][k],1);  
      }
    }
  }


  // set style 
//  gStyle->SetOptStat(0);

  for(int k=0;k<N_variables;k++){
    for(int i=0;i<N_SiPad;i++){
      SetStyle_histo2(h_variable_combine[i][k] , variable_name[k]   );
      h_variable_combine[i][k]->SetLineColor(i+1);
    }
  }


  // define legend 

  TString leg_name[N_SiPad];// number of configurations 
  TString header_name;

  if(irradiated_flag == 0){// un-irradiated diodes
    leg_name[0] = "120 #mu m,600V";
    leg_name[1] = "200 #mu m,600V";
    leg_name[2] = "300 #mu m,600V";

    std::string temp = (std::string ) SiPad_name; 
    char Pad_index = temp[  temp.size() -1 ] ;  TString temp2 = Pad_index;
    header_name = "SiPad-" + temp2 +", un-irradiated";
//    cout<< "header_name: "<< header_name << endl;
  }

  if(irradiated_flag == 1){// irradiated diodes
    leg_name[0] = "120 #mu m,600V";
    leg_name[1] = "120 #mu m,700V";
    leg_name[2] = "120 #mu m,800V";
    leg_name[3] = "200 #mu m,600V";
    leg_name[4] = "200 #mu m,800V";
    leg_name[5] = "300 #mu m,600V";
    leg_name[6] = "300 #mu m,800V";

    std::string temp = (std::string ) SiPad_name;
    char Pad_index = temp[  temp.size() -1 ] ;  TString temp2 = Pad_index;
    header_name = "SiPad-" + temp2 +", irradiated";

  }

  // draw
  TCanvas *c_[N_variables];
  c_[0] = new TCanvas("c1","c1",200,10,700,500);
  c_[1] = new TCanvas("c2","c2",200,10,700,500);
  c_[2] = new TCanvas("c3","c3",200,10,700,500);

  for(int k=0;k<N_variables;k++){

    TLegend *leg;
    if(h_variable_combine[0][k]->GetMean()>200){leg = new TLegend(0.15,0.6,0.45,0.9);}
    else {leg = new TLegend(0.6,0.6,0.9,0.9);}

    leg->SetHeader(header_name);

    c_[k]->cd();

    for(int i=0;i<N_SiPad;i++){
      if(i==0){h_variable_combine[i][k]->Draw()      ;}
      else    {h_variable_combine[i][k]->Draw("same");}
      
      leg->AddEntry( h_variable_combine[i][k] , leg_name[i] ,"l");
      leg->Draw();
    }
  }

  // save pdf
//  TString save_path = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study/";
  TString save_name = save_path + "combine_histo_" + SiPad_name + ".pdf";

  c_[0]->Print(save_name +"(");
  c_[1]->Print(save_name     );
  c_[2]->Print(save_name +")");


  // cout SiPad-x, configurations, variables, mean, RMS, factor

  cout<<endl;
  cout<<"which SiPad: "<< header_name << endl;

  for(int i=0;i<N_SiPad;i++){

    cout<<endl;
    cout<<"configurations"<< leg_name[i] << endl;

    cout<<"pedestalRMS"<<endl;
    cout<<"mean: "<< h_variable_combine[i][1]->GetMean()<<" RMS: "<< h_variable_combine[i][1]->GetRMS()<< endl;

    cout<<"wave_max"<<endl;
    cout<<"mean: "<< h_variable_combine[i][2]->GetMean()<<" RMS: "<< h_variable_combine[i][2]->GetRMS()<< endl;

    double factor1 = h_variable_combine[i][2]->GetMean() / h_variable_combine[i][1]->GetMean();  
    cout<<" wave_max mean/ ped_RMS mean= "<< factor1 << endl;

    double factor2 = h_variable_combine[i][2]->GetRMS() / h_variable_combine[i][1]->GetRMS();
    cout<<" wave_max RMS/ ped_RMS RMS= "<< factor2 << endl;
    cout<<endl;
  }

  // ----  Now start to plot TGraphError of different run ------

  TGraphErrors* gr_SiPad[N_SiPad][N_variables];// number of config, number of variables

  for(int i=0;i<N_SiPad;i++){// number of configurations

    for(int k=0;k<N_variables;k++){// number of variables

      int N_runs = N_runs_SiPad[i];
      double mean[N_runs];
      double rms[N_runs];
      double Nentries[N_runs];
      double error_x[N_runs];

      for(int j=0;j<N_runs_SiPad[i];j++){// numbers of runs

        mean[j] = h_variable[i][j][k]->GetMean();
        rms[j]  = h_variable[i][j][k]->GetRMS();
        Nentries[j] = h_variable[i][j][k]->GetEntries();
        error_x[j] = 0;
      }
      gr_SiPad[i][k] = new TGraphErrors( N_runs , Nentries , mean, error_x, rms );

    }
  }

  // fake gr to help to control the range 
  double x_array[2]={0}; double y_array[2]={0}; double x_err_array[2]={0}; double y_err_array[2]={0};
  x_array[0] = 9000 ; x_array[1] = 24000; y_array[0] = 0 ; y_array[1] = 500;

  TGraphErrors* gr_fake[N_variables];

  for(int k=0;k<N_variables;k++){  
    gr_fake[k] = new TGraphErrors(2, x_array, y_array, x_err_array, y_err_array );
    gr_fake[k]->GetXaxis()->SetRangeUser(10000 ,23000 );

    if(variable_name[k] == "pedestal" && irradiated_flag == 0)   { gr_fake[k]->GetYaxis()->SetRangeUser(180 , 210); }
    if(variable_name[k] == "pedestal" && irradiated_flag == 1)   { gr_fake[k]->GetYaxis()->SetRangeUser(190 , 230); }
    if(variable_name[k] == "pedestalRMS"){ gr_fake[k]->GetYaxis()->SetRangeUser(0   , 30 ); }
    if(variable_name[k] == "wave_max")   { gr_fake[k]->GetYaxis()->SetRangeUser(0   , 70); }

  }

  // set style

  for(int k=0;k<N_variables;k++){
    for(int i=0;i<N_SiPad;i++){ 
      SetStyle_gr ( gr_fake[k] , variable_name[k] );
      SetStyle_gr ( gr_SiPad[i][k] , variable_name[k] );
      gr_SiPad[i][k]->SetMarkerColor(i+1);
    } 
  }

  // draw
  TCanvas *c__[N_variables];
  c__[0] = new TCanvas("c4","c4",200,10,700,500);
  c__[1] = new TCanvas("c5","c5",200,10,700,500);
  c__[2] = new TCanvas("c6","c6",200,10,700,500);


  for(int k=0;k<N_variables;k++){

    TLegend *leg = new TLegend(0.5,0.6,0.8,0.9);
    leg->SetHeader(header_name);

    c__[k]->SetGrid();
    c__[k]->cd();

    gr_fake[k]->Draw("AP");

    for(int i=0;i<N_SiPad;i++){
      gr_SiPad[i][k]->Draw("P");
      leg->AddEntry(gr_SiPad[i][k]  ,leg_name[i]  ,"pl");
    }    
    leg->Draw();

  }

  // save pdf

  save_name = save_path + "different_run_"+ SiPad_name + ".pdf";

  c__[0]->Print(save_name +"(");
  c__[1]->Print(save_name     );
  c__[2]->Print(save_name +")");


}// end plot_SiPad()

// -----------------------------------------


void SetStyle_gr ( TGraphErrors* gr, TString variable_name ){

  if(variable_name == "pedestal"){
    gr->GetYaxis()->SetTitle("pedestal [ADC]");
  }

  if(variable_name == "pedestalRMS"){
    gr->GetYaxis()->SetTitle("pedestalRMS [ADC]");
  }

  if(variable_name == "wave_max"){
    gr->GetYaxis()->SetTitle("wave_max [ADC]");
  }

  gr->SetTitle("compare each runs");
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(2);
  gr->GetXaxis()->SetTitle("total number of events in that run");
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

//  TString save_path = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study/"; 
  TString save_name = save_path + "each_run.pdf"; 

  // loop for each run
  for (int i=0;i<N_runs;i++){

    TString path = root_dir + runN[i] + ".root" ; 
    TFile *f = TFile::Open( path ); 

    for(int j=1;j<7;j++){// loop on SiPad

      for(int k=0;k<3;k++){// loop on variable

        TString h_name = "h_" + variable_name[k] + "_" + pad_name[j];
        TH1F *h = (TH1F*)f->FindObjectAny(h_name);

        TString title = "run= " + runN[i]; 
        h->SetTitle( title );

	SetStyle_histo(h, variable_name[k] );

        gStyle->SetOptStat(1);
 
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


  // ------ open and save 2D plot for wave_max vs pedestalRMS ---------


  TCanvas *c2 = new TCanvas("c2","c2",200,10,700,500);
  save_name = save_path + "each_run_2D.pdf";

  for (int i=0;i<N_runs;i++){

    TString path = root_dir + runN[i] + ".root" ;
    TFile *f = TFile::Open( path );

    for(int j=1;j<7;j++){// loop on SiPad

        TString h_name = "h_wave_max_vs_pedestalRMS_"  + pad_name[j];
        TH2F *h = (TH2F*)f->FindObjectAny(h_name);
        h->GetXaxis()->SetTitle("wave_max [ADC]");
        h->GetYaxis()->SetTitle("pedestalRMS [ADC]");

        TString title = "run= " + runN[i] + "," + pad_name[j] ;
        h->SetTitle( title );

        gStyle->SetOptStat(0);

        double cor_factor = h->GetCorrelationFactor();    
        TString cor_legend_text = Form("correlation= %.3f" , cor_factor );


        c2->cd();
        h->Draw("colz");

        TLegend *leg = new TLegend(0.1,0.8,0.4,0.9);
        leg->SetHeader(cor_legend_text);        leg->Draw();

        if     (i==0 && j==1 )         {c2->Print(save_name +"(");}
        else if(i==N_runs-1 && j==6 )  {c2->Print(save_name +")");}
        else {c2->Print(save_name     );}

    }

  }


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



void check_two_run(){

  cout<<"hello check two run"<< endl;

  TString variable_name[3] = {"pedestal","pedestalRMS","wave_max"} ;

  std::string runN[2];

  runN[0]= "3663";
  runN[1]= "3670";

  TH1F *h_variable[2][3];// runs, variables (check SiPad3) 

  // find histogram

  for(int i=0;i<2;i++){// runs

    TString path = root_dir + runN[i] + ".root" ; 
    TFile *f = TFile::Open( path );

    for(int k=0;k<3;k++){// variables

      TString h_name = "h_" + variable_name[k] + "_SiPad3";
      h_variable[i][k] = (TH1F*)f->FindObjectAny(h_name); 

    }
  }
  // combine histogram

  TH1F *h_combine[3];  

  for(int k=0;k<3;k++){

    h_combine[k] = (TH1F*) h_variable[0][k]->Clone("hnew"); 
    h_combine[k] -> Add( h_variable[1][k] );
  }

  // set style

  gStyle->SetOptStat(0);

    // pedestalRMS
  h_combine[1]->SetTitle("compare two runs");

  h_combine[1]->SetLineColor(kYellow+2);
  h_variable[0][1]->SetLineColor(2);
  h_variable[1][1]->SetLineColor(4);

  h_combine[1]->SetLineWidth(3);
  h_variable[0][1]->SetLineWidth(3);
  h_variable[1][1]->SetLineWidth(3);

  h_combine[1]->GetXaxis()->SetTitle("pedestalRMS [ADC]");
  h_combine[1]->GetYaxis()->SetTitle("number of events");
  h_combine[1]->GetYaxis()->SetTitleOffset(1.3);

    // wave_max
  h_combine[2]->SetTitle("compare two runs");

  h_combine[2]->SetLineColor(kYellow+2);
  h_variable[0][2]->SetLineColor(2);
  h_variable[1][2]->SetLineColor(4);

  h_combine[2]->SetLineWidth(3);
  h_variable[0][2]->SetLineWidth(3);
  h_variable[1][2]->SetLineWidth(3);

  h_combine[2]->GetXaxis()->SetTitle("wave_max [ADC]");
  h_combine[2]->GetYaxis()->SetTitle("number of events");
  h_combine[2]->GetYaxis()->SetTitleOffset(1.3);

  h_combine[2]->GetXaxis()->SetRangeUser(-10 , 100);

  // draw

    // pedestalRMS
  TCanvas *c1 = new TCanvas("c1","c1",200,10,700,500);
  c1->cd();
  h_combine[1]->Draw();
  h_variable[0][1]->Draw("same");
  h_variable[1][1]->Draw("same");
  h_combine[1]->Draw("same");

  TLegend *leg = new TLegend(0.6,0.7,0.9,0.9) ;
  leg->AddEntry( h_combine[1] , "add two runs" ,"l");
  leg->AddEntry( h_variable[0][1], "run=3663" ,"l");
  leg->AddEntry( h_variable[1][1], "run=3670" ,"l");
  leg->Draw();

    // wave_max
  TCanvas *c2 = new TCanvas("c2","c2",200,10,700,500);
  c2->cd();
  h_combine[2]->Draw();
  h_variable[0][2]->Draw("same");
  h_variable[1][2]->Draw("same");
  h_combine[2]->Draw("same");

  TLegend *leg2 = new TLegend(0.6,0.7,0.9,0.9) ;
  leg2->AddEntry( h_combine[2] , "add two runs" ,"l");
  leg2->AddEntry( h_variable[0][2], "run=3663" ,"l");
  leg2->AddEntry( h_variable[1][2], "run=3670" ,"l");
  leg2->Draw();

  // save

//  TString save_path = "/afs/cern.ch/user/y/yuchang/www/HGCAL_TestBeam/noise_study/";
  TString save_name = save_path + "check_two_runs.pdf";

  c1->Print( save_name +"(");
  c2->Print( save_name +")");

}



