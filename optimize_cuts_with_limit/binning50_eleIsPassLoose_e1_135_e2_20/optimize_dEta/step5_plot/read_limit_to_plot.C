#include "TGraph.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TString.h>
#include <map>
#include <TH1D.h>
#include "TTree.h"
#include <TFile.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <string>
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

using namespace std;

void read_limit_to_plot(){

  TString variable_name = "Abs_dEta_ZH" ;// "Ele_1st_pt" ;
  cout<<"variable_name: " << variable_name << endl;

  const float intLumi = 3.0;

  int plot_flag = 0;
//  plot_flag=1; // plot r-value without times theory cross section
  plot_flag=2; // plot expected limit of cross section


  // define mass
  const int N_signal_mass_points = 11;
  int Zprime_mass[N_signal_mass_points]={800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000};

  int mass_point_to_read ;

  // define cut
  const int N_cut_points = 10;
  double cut_point[N_cut_points];

  double lowest_cut=0.5 ;
  double scan_width = 0.5;

  for(int i=0;i<N_cut_points;i++){

        cut_point[i] = lowest_cut + scan_width*i;
        cout<<"cut_point[i]: "<< cut_point[i] << endl;
  }




  // define Array used in TGraph
  const int Nbins = N_cut_points ;
  double vx[Nbins] ;
  double vy_limit[Nbins][N_signal_mass_points] ;




  // define ROOT file

TString dir_name = "Datacards_text_and_ROOT_files";







  // open ROOT file to read the limit 
for(int mass_index=0;mass_index<N_signal_mass_points;mass_index++){

  mass_point_to_read = Zprime_mass[mass_index]; 
  cout<< endl;
//  cout<<"mass point to read: "<< mass_point_to_read << endl;

  for(int i=0;i<N_cut_points;i++){

//	cout<<"cut "<<variable_name <<": " << cut_point[i] << endl; 
        vx[i] = cut_point[i];

	TString midlle_dir_name = Form("_cut_%f",cut_point[i]); 
	midlle_dir_name = "YuHsiang_DY_" + variable_name + midlle_dir_name;

	TString ROOT_name = Form("higgsCombineTest.Asymptotic.mH%d.root",mass_point_to_read); 
	ROOT_name = dir_name + "/" + midlle_dir_name + "/" + ROOT_name;
//	cout<<"read ROOT file: "<< ROOT_name << endl;

        TFile *file = new TFile( ROOT_name , "READ");
	TTree *tree = (TTree*) file -> Get("limit");

        double limit;
//	float limit;
        float quant;

	tree->SetBranchAddress("limit", &limit);
	tree->SetBranchAddress("quantileExpected", &quant);

        for (int j = 0; j < tree->GetEntries(); j++) {

	  tree->GetEntry(j);
 	  if (quant < 0.49 || quant > 0.51)continue; 
//          cout<<"j: "<< j <<" quant : "<<quant<<" limit : " <<limit<<endl;
	  vy_limit[i][mass_index] = limit; 
	}

	delete tree;
	file->Close();
	delete file;
  }// cut
}// mass


  // input the theory cross section 
//  string xsect_file_th = "./13TeV_xsec_Zhllbb.txt";
  string xsect_file_th = "./13TeV_xsec_Zh.txt";

  ifstream xsect_file(xsect_file_th.c_str(), ios::in);
  if (! xsect_file.is_open()) {
    cout << "Failed to open file with xsections: " << xsect_file_th << endl;
  }

  float mZprime, CS;
  vector<float> v_mZprime, v_xs;


  int loop_counter =1;
  while (xsect_file.good() ) {
    if(loop_counter>N_signal_mass_points)break;
    xsect_file >> mZprime >> CS;

    v_mZprime.push_back(mZprime);
    v_xs.push_back(CS);
    loop_counter = loop_counter +1;
  }
  cout << "Size of theory Zprime xsects vector " << v_mZprime.size() << endl;
  xsect_file.close();






  // TGraph

  TGraph *gr[N_signal_mass_points];


  double vy_limit_in_certain_mass[N_cut_points];

  for(int mass_index=0;mass_index<N_signal_mass_points;mass_index++){

//     if(mass_index!=0)continue;

  cout<< endl;
  cout<<"mass point to read: "<< Zprime_mass[mass_index] << endl;
  cout<< endl;


     for(int cut_index=0;cut_index<N_cut_points;cut_index++){

      cout<<"cut "<<variable_name <<": " << cut_point[cut_index] << endl;

        vy_limit_in_certain_mass[cut_index] = vy_limit[cut_index][mass_index];
	if(plot_flag==2){vy_limit_in_certain_mass[cut_index] = vy_limit_in_certain_mass[cut_index] * v_xs[mass_index];} // r-value times theory cross section

        cout<<"       limit:           "<< vy_limit_in_certain_mass[cut_index] << endl;
     }
     gr[mass_index] = new TGraph(Nbins , vx , vy_limit_in_certain_mass);

  }






  // setting

  TLegend *leg=new TLegend(0.85,0.4,1.0,1.0);
  TString leg_name[N_signal_mass_points];
  int colorN = 1;

  double gr_y_UpBound;double gr_y_DownBound;
  if(plot_flag==1){ gr_y_UpBound  =1E3;  gr_y_DownBound=1E0;}
  if(plot_flag==2){ gr_y_UpBound  =3E-1; gr_y_DownBound=4E-3;}

  TString lable_name_y;
  if(plot_flag==1){ lable_name_y = "r-value";}
  if(plot_flag==2){ lable_name_y = "#sigma_{Z',95%}xBR(Z'->ZH)xBR(Z->ll,H->bb) [pb]";}


  for(int mass_index=0;mass_index<N_signal_mass_points;mass_index++){

     leg_name[mass_index] = Form("M_{Z'}=%d", Zprime_mass[mass_index] );

        if (mass_index==0){colorN = kRed;}
        if (mass_index==3){colorN = kGreen;}
        if (mass_index==6){colorN = kBlue;}
        if (mass_index==9){colorN = kCyan;}

     gr[mass_index]->GetYaxis()->SetRangeUser(gr_y_DownBound, gr_y_UpBound);
     gr[mass_index]->SetLineStyle(1);
     gr[mass_index]->SetLineColor(colorN);
     colorN = colorN +2 ;
     gr[mass_index]->SetLineWidth(3);
     gr[mass_index]->SetMarkerColor(2);
     gr[mass_index]->SetMarkerStyle(4);
     gr[mass_index]->SetMarkerSize(1);
     gr[mass_index]->GetYaxis()->SetTitle(lable_name_y);
     gr[mass_index]->GetXaxis()->SetTitle("Minimum p_{T} threshold of leading electron [GeV]");
     gr[mass_index]->SetTitle("");
     gr[mass_index]->GetXaxis()->SetTitleOffset(1.3);
     gr[mass_index]->GetYaxis()->SetTitleOffset(1.3);
  }





  // plot

  TCanvas *c1 = new TCanvas("c1", "c 1", 630, 600);
  c1->cd();
  gPad->SetLogy();
  c1->SetGridx(1);
  c1->SetGridy(1);

  for(int mass_index=0;mass_index<N_signal_mass_points;mass_index++){

	if(mass_index==0){gr[mass_index]->Draw("ALP");}
  	else {gr[mass_index]->Draw("same lp");}

        leg->AddEntry( gr[mass_index] , leg_name[mass_index] ,"pl");
        leg->Draw();
  }


  // TLatex
    TLatex * latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->SetTextAlign(11);

    latex->DrawLatex(0.15, 0.91, "CL_{S} Expected Limit, cut electron leading pt");
    latex->DrawLatex(0.05, 0.96, "CMS preliminary 2015");
    latex->DrawLatex(0.45, 0.96, Form("L=%.1f fb^{-1} at #sqrt{s} = 13 TeV", intLumi));




  // save

  TString path_to_save = "/afs/cern.ch/user/y/yuchang/www/set_limit_optimize_leading_pt/" ;

  TString save_name ;

  if(plot_flag==1){save_name = "limit_in_r_value";}
  if(plot_flag==2){save_name = "limit_in_cross_section";}

  save_name = path_to_save + save_name + ".pdf";
  c1->SaveAs( save_name );





}// end codes
