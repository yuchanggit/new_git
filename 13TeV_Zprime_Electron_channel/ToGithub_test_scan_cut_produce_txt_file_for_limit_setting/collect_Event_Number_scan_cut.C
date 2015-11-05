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



void collect_Event_Number_scan_cut(){

// basic definition
TString path = "plot/";
double corresponding_luminosity = 3000;// 3000/pb


// define for scan cut 
TString variable_name = "h_ele_1st_pT" ;

double lowest_cut=115 ;
double first_bin_value = 0;
double scan_width = 95;


// define cut points
const int N_cut_points = 20;
int cut_point[N_cut_points];

for(int i=0;i<N_cut_points;i++){

cut_point[i] = lowest_cut + scan_width*i;
}

// txt file name
TString txt_name[N_cut_points];

for(int i=0;i<N_cut_points;i++){

txt_name[i] = Form("cut_%d", cut_point[i] );
txt_name[i] = "YuHsiang_DY_" + variable_name + "_" + txt_name[i] + ".txt";
}






// big loop on cut points
for(int cut_point_index = 0 ; cut_point_index < N_cut_points ; cut_point_index++){
//  if(cut_point_index>1)continue;




  // data
  TString data_name = "DATA";
  double n_Fianl_data = 0;// put zero by hand  









  // Zprime the signal

  const int N_signal_mass_points = 13;
  int Zprime_mass[N_signal_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};

  TString signal_name[N_signal_mass_points];

  double n_Total_signal[N_signal_mass_points];
  TString ROOT_name_signal[N_signal_mass_points];

  double n_Pass_signal[N_signal_mass_points];

  double cross_section_signal[N_signal_mass_points]={ // unit in pb
0  //  M=600 I don't have 
,0.0282665
,0.0153743
,0.00790857
,0.00421385
,0.00233319
,0.00133522
,0.000785119
,0.000227178
,7.1426e-05
,2.35715e-05
,7.97489e-06
,0}; // M=4500 I don't have

  double n_Fianl_signal[N_signal_mass_points];

  for(int i=0;i<N_signal_mass_points;i++){

  	signal_name[i] = Form("M%d",Zprime_mass[i]);

	ROOT_name_signal[i] = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[i]); 
	ROOT_name_signal[i] = path + ROOT_name_signal[i];

        TFile *f_1 = new TFile ( ROOT_name_signal[i] );

        TString histo_name1= "h_eventWeight" ;
        TH1D *h_1 = (TH1D*) f_1 -> Get(histo_name1);
	n_Total_signal[i] = h_1 ->Integral();// total number of event


        TString histo_name2= variable_name ;
        TH1D *h_2 = (TH1D*) f_1 -> Get(histo_name2);

        double bin_width = h_2 ->GetBinWidth(1);
        int min_bin = ( lowest_cut - first_bin_value )/ bin_width + 1;// bin for lowest_cut 
	int startBin = (cut_point[cut_point_index] - lowest_cut)/bin_width + min_bin    ;
	int endBin = h_2 ->GetNbinsX()+1;
        n_Pass_signal[i] = h_2 ->Integral(startBin , endBin );// number of event passing, and pass the cut points
 
	n_Fianl_signal[i] = n_Pass_signal[i] * cross_section_signal[i] / n_Total_signal[i] * corresponding_luminosity; 

	delete h_1; 
	delete h_2;

	f_1->Close();
 	delete f_1;

  }// loop signal








  // DYJetsHTbin background
  const int N_DYJetsHTbin_background_points = 4;

  TString background_DYJets_name = "DYJETS";

  double n_Total_background_DYJets[N_DYJetsHTbin_background_points];
  TString ROOT_name_background_DYJets[N_DYJetsHTbin_background_points];

  double n_Pass_background_DYJets[N_DYJetsHTbin_background_points];

  double cross_section_background_DYJets[N_DYJetsHTbin_background_points]={ // unit in pb
  139.4 , 42.75 , 5.497 , 2.21};

  double n_Fianl_background_DYJets;
  double n_temp_background_DYJets = 0;// for combine # of 4 DYJets HT samples

  for(int i=0;i<N_DYJetsHTbin_background_points;i++){

     if(i==0 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT100to200_in_Zprime_M-600.root";}
     if(i==1 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT200to400_in_Zprime_M-600.root";}
     if(i==2 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT400to600_in_Zprime_M-600.root";}
     if(i==3 ){ ROOT_name_background_DYJets[i] = "background_shape_DYJets_HT600toInf_in_Zprime_M-600.root";}

     ROOT_name_background_DYJets[i] = path + ROOT_name_background_DYJets[i];

     TFile *f_1 = new TFile ( ROOT_name_background_DYJets[i] );

     TString histo_name1= "h_eventWeight" ;
     TH1D *h_1 = (TH1D*) f_1 -> Get(histo_name1);
     n_Total_background_DYJets[i] = h_1 ->Integral();// total number of event


     TString histo_name2= variable_name ;
     TH1D *h_2 = (TH1D*) f_1 -> Get(histo_name2);

     double bin_width = h_2 ->GetBinWidth(1);
     int min_bin = ( lowest_cut - first_bin_value )/ bin_width + 1;// bin for lowest_cut 
     int startBin = (cut_point[cut_point_index] - lowest_cut)/bin_width + min_bin    ;
     int endBin = h_2 ->GetNbinsX()+1;
     n_Pass_background_DYJets[i] = h_2 ->Integral(startBin , endBin );// number of event passing, and pass the cut points

     cross_section_background_DYJets[i] = cross_section_background_DYJets[i] * 1.23 ;// apply the k-factor

     n_temp_background_DYJets = n_temp_background_DYJets + (n_Pass_background_DYJets[i]*cross_section_background_DYJets[i]/n_Total_background_DYJets[i]); 

     delete h_1;
     delete h_2;

     f_1->Close();
     delete f_1;

  }// loop background

  n_Fianl_background_DYJets = n_temp_background_DYJets * corresponding_luminosity ;








  // save number to txt file

  txt_name[cut_point_index] = "txt_files/" + txt_name[cut_point_index] ;

  ofstream fout;
  fout.open( txt_name[cut_point_index] );
  cout << endl << txt_name[cut_point_index]  << endl<<endl;

  cout << data_name  << " " << n_Fianl_data  << endl;
  fout << data_name  << " " << n_Fianl_data  << endl;

  cout << background_DYJets_name << " " << n_Fianl_background_DYJets  << endl;
  fout << background_DYJets_name << " " << n_Fianl_background_DYJets  << endl;

  for(int i=0;i<N_signal_mass_points;i++){
	if(i==0)continue;
        if(i==12)continue;

        cout << signal_name[i]   << " " << n_Fianl_signal[i]  << endl;
	fout << signal_name[i]   << " " << n_Fianl_signal[i]  << endl;
  }

  fout.close();

}//end loop on cut points




}// end code





