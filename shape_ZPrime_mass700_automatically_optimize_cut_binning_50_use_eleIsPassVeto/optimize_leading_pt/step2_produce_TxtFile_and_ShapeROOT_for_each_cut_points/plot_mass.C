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

using namespace std;

void plot_mass(TString variable_name ,   int cut_point   ){
 
cout<<endl;
cout<<"inside plot_mass.C "<<"variable_name: "<< variable_name << " cut_point: "<< cut_point << endl; 
cout<<endl;

// define
  const int N_signal_mass_points = 11;

//  TString variable_name = "Ele_1st_pt";   //"Abs_dEta_ZH" ;

//TString ROOT_file_path = "_cut_115.root";
TString ROOT_file_path = Form("_cut_%d.root",cut_point);
ROOT_file_path = "Zprime_shape_" + variable_name + ROOT_file_path ;
//TString ROOT_file_path = "Zprime_shape_Abs_dEta_ZH_cut_0.400000.root";

TString dir_get_file = "text_and_ROOT_files" ;
ROOT_file_path = dir_get_file + "/" + ROOT_file_path;

  int Zprime_mass[N_signal_mass_points]={800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000};

  TString ROOT_name_signal[N_signal_mass_points];
  TH1D *h_signal[N_signal_mass_points];
  TH1D *h_DYJet;

  TH1D *h_signal_original[N_signal_mass_points];





// open histogram 
TFile *f1 = new TFile ( ROOT_file_path );

  for(int i=0;i<N_signal_mass_points;i++){
         ROOT_name_signal[i] = Form("SIG_M%d",Zprime_mass[i]);
         h_signal[i] = (TH1D*) f1 -> Get( ROOT_name_signal[i] );

//         h_signal[i]->Draw("same");
  }

  h_DYJet = (TH1D*) f1 -> Get("DYJETS"); 
//  h_DYJet->Draw("same");









// setting
  int colorN = 1;

  for(int i=0;i<N_signal_mass_points;i++){

        if (i==0){colorN = kRed;}
        if (i==3){colorN = kOrange;}
        if (i==6){colorN = kCyan;}
        if (i==9){colorN = kBlue;}
        if (i==12){colorN = kGreen;}

     h_signal[i]->SetLineColor(colorN);
     colorN = colorN +1 ;

     h_signal_original[i] = (TH1D*) h_signal[i]->Clone("");

     h_signal[i] ->Sumw2();
//     h_signal[i] ->Scale(1/h_signal[i]->Integral() );

     h_signal[i]->SetStats(0);
//     h_signal[i]->GetYaxis()->SetRangeUser(0, 0.5);
     h_signal[i]->GetXaxis()->SetRangeUser(500, 4500);
     h_signal[i]->SetLineWidth(2);
//     h_signal[i]->GetYaxis()->SetTitle("Arbitrary Unit");
     h_signal[i]->GetXaxis()->SetTitle("M_{Z'} [GeV]");
     h_signal[i]->GetYaxis()->SetTitleOffset(1.3);
  }

  h_DYJet ->SetLineColor(1);
  h_DYJet ->Sumw2();
  h_DYJet ->GetXaxis()->SetRangeUser(500, 4500);
//  h_DYJet ->GetYaxis()->SetRangeUser(0, 5.0);
//  h_DYJet ->GetYaxis()->SetRangeUser(0, 4.5);
//  h_DYJet ->GetYaxis()->SetRangeUser(0, 1.1);
  h_DYJet ->GetYaxis()->SetRangeUser(0, 0.35);
//  h_DYJet ->GetYaxis()->SetRangeUser(0, 0.68);
  h_DYJet ->SetStats(0);
  h_DYJet ->GetXaxis()->SetTitle("M_{Z'} [GeV]");
  h_DYJet ->GetYaxis()->SetTitle("Event yield in L= 3/fb");
  h_DYJet ->GetYaxis()->SetTitleOffset(1.3);
  h_DYJet ->GetXaxis()->SetTitleOffset(1.3);

  TH1D *h_DYJet_original = (TH1D*) h_DYJet->Clone("");

//  h_DYJet ->Scale(1/h_DYJet->Integral() );
  h_DYJet ->SetLineWidth(2);






// draw in one canvas

  TCanvas *c1 = new TCanvas("c1", "c 1", 630, 600);

  TLegend *leg=new TLegend(0.8,0.4,1.0,1.0);
  TString leg_signal_name[N_signal_mass_points];

  c1->cd();
  h_DYJet->Draw("same hist e");

  leg->AddEntry( h_DYJet , "DYJets" ,"pl");
  leg->Draw();



  for(int i=0;i<N_signal_mass_points;i++){
  	c1->cd();
        h_signal[i]->Draw("same hist e");

     leg_signal_name[i] = Form("M_{Z'}=%d", Zprime_mass[i] );
     leg->AddEntry( h_signal[i] , leg_signal_name[i] ,"pl");
//     leg->SetFillStyle(0);
     leg->Draw();

  }

//  c1->cd();
//  h_DYJet->Draw("same hist e");

//  leg->AddEntry( h_DYJet , "DYJets" ,"pl");
//  leg->Draw();




// save
TString path_to_save = "/afs/cern.ch/user/y/yuchang/www/" ;
//TString dir_name ="set_limit_optimize_leading_pt/";
TString dir_name ="optimize_cut_with_limit_use_eleIsPassVeto/leading_pt/";
TString save_name = "Zprime_mass";

TString cut_value = Form("%d",cut_point);

save_name = path_to_save + dir_name+ save_name + "_for_"+ variable_name + "_cut_"+ cut_value +".pdf";
c1->SaveAs( save_name );







// cout the range

int First_NonZero_bin_signal[N_signal_mass_points]; 
int Last_NonZero_bin_signal[N_signal_mass_points];

int First_NonZero_bin_DYJet;
int Last_NonZero_bin_DYJet;

double bin_width = h_signal[0]->GetBinWidth(1);

  // signal
  for(int i=0;i<N_signal_mass_points;i++){

        // First_NonZero_bin_signal
        for( int m=1 ; m<= h_signal[i]->GetNbinsX() ;m++ ){
                double bin_content = h_signal[i]->GetBinContent(m);
                if( bin_content != 0 ){ First_NonZero_bin_signal[i] = m; break; }
        }

	// Last_NonZero_bin_signal
	Last_NonZero_bin_signal[i] = 0;
        for( int m=1 ; m<= h_signal[i]->GetNbinsX() ;m++ ){
                double bin_content = h_signal[i]->GetBinContent(m);
                if( bin_content != 0 ){ 
			if( m > Last_NonZero_bin_signal[i] ){Last_NonZero_bin_signal[i] = m;}	
		}
        }

        cout<<"signal Zprime mass:" << Zprime_mass[i] 
	<<" First non zero bin value: " << (First_NonZero_bin_signal[i]-1)*bin_width  
	<<" Last non zero bin value: " << Last_NonZero_bin_signal[i]*bin_width
	<< endl; 


  }

  // DYJet

  // fist
  for( int m=1 ; m<= h_DYJet->GetNbinsX() ;m++ ){
          double bin_content = h_DYJet->GetBinContent(m);
          if( bin_content != 0 ){ First_NonZero_bin_DYJet = m; break; }
  }

  // last
  Last_NonZero_bin_DYJet = 0;
  for( int m=1 ; m<= h_DYJet->GetNbinsX() ;m++ ){
          double bin_content = h_DYJet->GetBinContent(m);
          if( bin_content != 0 ){
                if( m > Last_NonZero_bin_DYJet ){Last_NonZero_bin_DYJet = m;}
          }
  }

        cout<<"DYJet: " 
        <<" First non zero bin value: " << (First_NonZero_bin_DYJet-1)*bin_width
        <<" Last non zero bin value: " << Last_NonZero_bin_DYJet*bin_width
        << endl;





// cout the DYJets event yield in the signal range


cout<<endl;
cout<<"cout DYJets event yield in the signal range"<< endl;

  for(int i=0;i<N_signal_mass_points;i++){

        cout<<"M= "<< Zprime_mass[i] << endl;       
	double signal_yield = 0;
        double Background_yield_in_signal_range =0;
                double Background_yield_all =0;
 
        for( int m=1 ; m<= h_signal[i]->GetNbinsX() ;m++ ){

	 	signal_yield = h_signal_original[i] ->Integral();
                double temp_bkg = h_DYJet_original ->GetBinContent(m);

		if(h_signal[i]->GetBinContent(m) >0){
		  Background_yield_in_signal_range = Background_yield_in_signal_range + temp_bkg;	
		}

		Background_yield_all = Background_yield_all + temp_bkg;
        }
        cout<<"Background_yield_all: "<< Background_yield_all<< endl;
	cout<<"signal_yield: " << signal_yield << endl;
	cout<<"background event yield: " << Background_yield_in_signal_range<< endl;
	cout<<"ratio: "<< signal_yield/Background_yield_in_signal_range << endl;


  }



}// end code
