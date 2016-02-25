#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TString.h>
#include <map>
#include <TH1D.h>
#include "TTree.h"
#include <TFile.h>
//#include "untuplizer.h"
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <string>
#include "TCanvas.h"

using namespace std;

void read_limit( int mass_points_index_to_read ){
// use root -l -q -b read_limit.C++\(mass_points_index_to_read\)
 
//  int mass_points_index_to_read = 1; 

  TString variable_name = "Ele_1st_pt" ;
  cout<<"variable_name: " << variable_name << endl;

  // define mass
  const int N_signal_mass_points = 11;
  int Zprime_mass[N_signal_mass_points]={800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000};
  
  int mass_point_to_read = Zprime_mass[mass_points_index_to_read];

  // define cut
  const int N_cut_points = 8;
  int cut_point[N_cut_points];

  double lowest_cut=135 ;
  double scan_width = 100;

  for(int i=0;i<N_cut_points;i++){

        cut_point[i] = lowest_cut + scan_width*i;
        cout<<"cut_point[i]: "<< cut_point[i] << endl;
  }

  // define ROOT file

TString dir_name = "Datacards_text_and_ROOT_files";

  cout<< endl;
  cout<<"mass point to read: "<< mass_point_to_read << endl; 

  // open ROOT file to read the limit 
  for(int i=0;i<N_cut_points;i++){

	cout<<"cut "<<variable_name <<": " << cut_point[i] << endl; 

	TString midlle_dir_name = Form("_cut_%d",cut_point[i]); 
	midlle_dir_name = "YuHsiang_DY_" + variable_name + midlle_dir_name;

	TString ROOT_name = Form("higgsCombineTest.Asymptotic.mH%d.root",mass_point_to_read); 
	ROOT_name = dir_name + "/" + midlle_dir_name + "/" + ROOT_name;
//	cout<<"read ROOT file: "<< ROOT_name << endl;

        TFile *file = new TFile( ROOT_name , "READ");
	TTree *tree = (TTree*) file -> Get("limit");

        double limit;
        float quant;

	tree->SetBranchAddress("limit", &limit);
	tree->SetBranchAddress("quantileExpected", &quant);

        for (int j = 0; j < tree->GetEntries(); j++) {

	  tree->GetEntry(j);
 	  if (quant < 0.49 || quant > 0.51)continue; 
          cout<<"j: "<< j <<" quant : "<<quant<<" limit : " <<limit<<endl;
	}
  }

}
