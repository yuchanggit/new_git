#include <iostream>
#include <fstream>
#include <TString.h>
#include <TH1D.h>
#include <TFile.h>
#include <string>
#include "TCanvas.h"
#include "xAna_ele_selection.C"

void Control_auto(){

int signal_background_flag =-1;



const int N_mass_points = 13;


TString file_name[N_mass_points] = {
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-600_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-800_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-1000_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-1200_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-1400_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-1600_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-1800_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-2000_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-2500_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-3000_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-3500_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-4000_13TeV-madgraph.root",
"ZprimeToZhToZlephbb_25ns/ZprimeToZhToZlephbb_narrow_M-4500_13TeV-madgraph.root"
                        };





const int N_background_points = 4;


TString background_file_name[N_background_points] = {
"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",
"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",
"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",
"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"
                        };



TString path = "/Users/index0192/13_TeV_Task/jet_CMSSW747/";

for(int i=0;i<N_mass_points;i++)
{ file_name[i] = path + file_name[i];      }

for(int i=0;i<N_background_points;i++)
{ background_file_name[i] = path + background_file_name[i];      }



  int mass_point[N_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};

TCanvas *c1[N_mass_points];
TCanvas *c2[N_mass_points];
TCanvas *c3[N_mass_points];
TCanvas *c4[N_mass_points];
TCanvas *c5[N_mass_points];
TCanvas *c6[N_mass_points];

int dir_flag =0;// choose which Cut you want




 // sub_leading electron pT optimize study

bool sub_leading_ele_flag= false; 
sub_leading_ele_flag=true;

if(sub_leading_ele_flag){

// now we don't use HEEPNoIso flag, but use ElectronSelection instead
  dir_flag = 1; // use passHEEPID
//  dir_flag = 2; // use passLoose


//  signal_background_flag = 0; // Zprime signal
// signal_background_flag = 1; // DYJets_HT background

for (int signal_background_index =0; signal_background_index<2; signal_background_index++  ){// signal_background_flag
signal_background_flag = signal_background_index ;
if( signal_background_index!= 0 )continue;// run signal sample only



  for(int file_index=0;file_index<13;file_index++){// which signal mass points you want ?
//if( file_index!= 2 && file_index!= 7 && file_index!= 9 )continue;
if( file_index!= 2 )continue;

  TString dir_name;
  if(dir_flag==1){dir_name = "plot_SubLedaing_ele_pt_optimize/" ;}


  double eff =0, eff_err=0;

  int i = file_index;// i = file_index for convenience

  TString cut_flow_name = Form("Zprime_Cut_Flow_M_%d",mass_point[i]);
  TString ele_pT_name = Form("Zprime_ele_pT_M_%d",mass_point[i]);
  TString ll_pT_name = Form("Zprime_ll_pT_M_%d",mass_point[i]);
  TString SD_mass_name = Form("Zprime_SD_mass_M_%d",mass_point[i]);
  TString Z_mass_name = Form("Zprime_Z_mass_M_%d",mass_point[i]);
  TString Zprime_mass_name = Form("Zprime_Zprime_mass_M_%d",mass_point[i]);

  c1[i] = new TCanvas(cut_flow_name,"try to show cut flow ",200,10,700,500);
  c2[i] = new TCanvas(ele_pT_name,"ele pT distribution ",200,10,700,500);
  c3[i] = new TCanvas(ll_pT_name,"ll pT distribution ",200,10,700,500);
  c4[i] = new TCanvas(SD_mass_name,"SD mass distribution ",200,10,700,500);
  c5[i] = new TCanvas(Z_mass_name,"Z mass distribution ",200,10,700,500);
  c6[i] = new TCanvas(Zprime_mass_name,"Zprime mass distribution ",200,10,700,500);




  if(signal_background_flag == 0 )// read signal sample
      { 

  	cout<< "dir_name: " << dir_name <<endl;
  	cout<< "file_index: "<< file_index << endl;
  	cout<< "file_name[file_index]: "<< file_name[file_index] << endl;
  	cout<< "mass_point[file_index]: "<< mass_point[file_index]<<endl;
  	cout<< "dir_flag: "<< dir_flag <<endl;

  	int background_file_index = -1;// not use background  

	xAna_ele_selection(file_name[file_index] , c1[file_index] , c2[file_index] , c3[file_index] , c4[file_index] , c5[file_index] , c6[file_index] , mass_point[file_index], eff, eff_err, dir_name , dir_flag , signal_background_flag , background_file_index ); 

      }// end if




  if(signal_background_flag == 1 )// read background sample
      { 

	    // file_index: signal mass points
 	    // background_file_index: which background sample 
	    // dir_name: name of directory to save ROOT file 
	    // dir_flag: HEEP id 

        for (int background_file_index=0; background_file_index<4;background_file_index++){// which background sample you want to read


  		cout<< "dir_name: " << dir_name <<endl;
  		cout<< "file_index: "<< file_index << endl;
  		cout<< "file_name[file_index]: "<< file_name[file_index] << endl;
  		cout<< "mass_point[file_index]: "<< mass_point[file_index]<<endl;
  		cout<< "dir_flag: "<< dir_flag <<endl;
  		cout<< "background_file_index: "<< background_file_index <<endl;
  		cout<< "background_file_name[background_file_index]: "<< background_file_name[background_file_index] <<endl;

	xAna_ele_selection( background_file_name[background_file_index] , c1[file_index] , c2[file_index] , c3[file_index] , c4[file_index] , c5[file_index] , c6[file_index] , mass_point[file_index], eff, eff_err, dir_name , dir_flag , signal_background_flag , background_file_index );

            }// end background_file_index loop
      }// end if





//  TString png1_name = Form("Zprime_Cut_Flow_M_%d.png",mass_point[i]);
//  png1_name = dir_name + png1_name;
//  c1[i]->cd();  c1[i]->SaveAs(png1_name);

  }// loop file_index

}// signal_background_flag

}// end if
















}
