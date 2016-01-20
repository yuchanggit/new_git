#include <stdio.h>
#include <iostream>
#include <fstream>
#include <TString.h>
#include <TH1D.h>
#include <TFile.h>
#include <string>
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include <cstring>
#include "TLatex.h"

using namespace std;

void plot_mass2(TString variable_name, TString histo_name_to_open ,const int N_cut_points, double lowest_cut ,double scan_width ){

// cout
cout<<endl;
cout<<"inside plot_mass2.C "<< endl;
cout<< variable_name<<" "
<< histo_name_to_open << " "<<N_cut_points<<
" "<< lowest_cut<< " "<< scan_width<<endl;
cout<<endl;

// samples and cut-variable

TString samples_type;
if ( histo_name_to_open =="DYJETS" ) samples_type = "DYJets sample";
if ( histo_name_to_open =="SIG_M1000" ) samples_type = "Z' sample at M=1000";
if ( histo_name_to_open =="SIG_M2000" ) samples_type = "Z' sample at M=2000";
if ( histo_name_to_open =="SIG_M3000" ) samples_type = "Z' sample at M=3000";

TString cut_variable;
if ( variable_name=="Ele_1st_pt") cut_variable = "electron leading pt";
if ( variable_name=="Abs_dEta_ZH") cut_variable = "|#Delta#eta_{ZH}|";

// cuts
  double cut_point[N_cut_points];
  for(int i=0;i<N_cut_points;i++){

        cut_point[i] = lowest_cut + scan_width*i;
//        cout<<"cut_point[i]: "<< cut_point[i] << endl;
  }

// TFile and histogram

  TFile *file[N_cut_points] ;
  TH1D * h_histo_for_cut_index[N_cut_points];

TString dir_get_file = "text_and_ROOT_files" ;


  for(int i=0;i<N_cut_points;i++){

	TString ROOT_file_path = Form("_cut_%f.root",cut_point[i]);
	ROOT_file_path = dir_get_file + "/" + "Zprime_shape_" + variable_name + ROOT_file_path ;

	file[i] = new TFile ( ROOT_file_path );
	h_histo_for_cut_index[i] = (TH1D*) file[i] -> Get(histo_name_to_open); 
  }

// test
//  TCanvas *c1 = new TCanvas("c1", "c 1", 630, 600);
//  c1->cd();
//  h_histo_for_cut_index[2]->Draw();
//  TString test_save_path = "/afs/cern.ch/user/y/yuchang/www/set_limit_optimize_leading_pt/test.pdf";
//  c1->SaveAs( test_save_path ); 


// setting

  TLegend *leg=new TLegend(0.60,0.20,1.0,0.85);
  TString leg_name[N_cut_points];
  TH1D * h_histo_for_cut_index_clone_original[N_cut_points];

  int colorN = 1;
  for(int i=0;i<N_cut_points;i++){

        if (i==0){colorN = kRed;}
        if (i==3){colorN = kOrange;}
        if (i==6){colorN = kCyan;}
        if (i==9){colorN = kBlue;}

     	h_histo_for_cut_index[i]->SetLineColor(colorN);
     	colorN = colorN +1 ;

        h_histo_for_cut_index_clone_original[i] = (TH1D*) h_histo_for_cut_index[i]->Clone("");// Clone for original

        h_histo_for_cut_index[i]->Sumw2();
        h_histo_for_cut_index[i]->Scale(1/h_histo_for_cut_index[i]->Integral() );

        h_histo_for_cut_index[i]->SetStats(0);
//        h_histo_for_cut_index[i]->GetYaxis()->SetRangeUser(0, 0.8);
//        h_histo_for_cut_index[i]->GetXaxis()->SetRangeUser(500, 1700);
        h_histo_for_cut_index[i]->GetXaxis()->SetRangeUser(500, 2500);
        h_histo_for_cut_index[i]->SetLineWidth(2);
        h_histo_for_cut_index[i]->GetYaxis()->SetTitle("Arbitrary Unit");
        h_histo_for_cut_index[i]->GetXaxis()->SetTitle("M_{Z'} [GeV]");
        h_histo_for_cut_index[i]->GetYaxis()->SetTitleOffset(1.5);
        h_histo_for_cut_index[i]->GetXaxis()->SetTitleOffset(1.3);

        leg_name[i] = Form(" < %f", cut_point[i]  );
        leg_name[i] = variable_name + leg_name[i];

  }


// draw
  TCanvas *c1 = new TCanvas("c1", "c 1", 630, 600);
  for(int i=0;i<N_cut_points;i++){

	c1->cd();
  	h_histo_for_cut_index[i]->Draw("same hist e");

        leg->AddEntry( h_histo_for_cut_index[i] , leg_name[i] ,"pl");
//        leg->SetFillStyle(0);
        leg->Draw();


  }


// TLatex

    TLatex * latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->SetTextAlign(11);
    
    TString latex_content = " ,cut on ";
    latex_content = samples_type + latex_content + cut_variable;
    latex->DrawLatex(0.1, 0.94, latex_content);



// save ZH mass in different cut in one canvas in pdf

  TString save_dir;
  if(variable_name == "Ele_1st_pt") save_dir = "set_limit_optimize_leading_pt/";
  if(variable_name == "Abs_dEta_ZH" || variable_name=="Abs_dRapidity_ZH") save_dir = "set_limit_optimize_dRapidity_and_dEta/";


  TString save_path = "/afs/cern.ch/user/y/yuchang/www/";
  save_path = save_path + save_dir + histo_name_to_open +"_cut_" + variable_name + ".pdf";
  c1->SaveAs( save_path );



// save many histogram of ZH mass in different cut in ROOT file

  TString ROOT_file_save_name = "ZH_mass_of_";
  ROOT_file_save_name = ROOT_file_save_name + histo_name_to_open +"_cut_" + variable_name + ".root";
  TFile *myFile = new TFile(ROOT_file_save_name,"recreate");

  TString histo_name_to_save[N_cut_points];

  for(int i=0;i<N_cut_points;i++){
	myFile->cd();
	histo_name_to_save[i] = Form("_LessThan_%f", cut_point[i]);
        histo_name_to_save[i] = variable_name + histo_name_to_save[i];
	h_histo_for_cut_index_clone_original[i]->SetName( histo_name_to_save[i] );	
        h_histo_for_cut_index_clone_original[i]->Write();
  }

}// end code
