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

/*
TString file_name[N_mass_points] = {
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-600_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-800_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-1000_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-1200_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-1400_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-1600_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-1800_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-2000_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-2500_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-3000_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-3500_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-4000_13TeV-madgraph",
"ZprimeToZhToZlephbb_ReMiniAOD/ZprimeToZhToZlephbb_narrow_M-4500_13TeV-madgraph"
                        };
*/
TString file_name[N_mass_points] = {
"ZprimeToZhToZlephbb_narrow_M-600_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-800_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-1000_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-1200_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-1400_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-1600_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-1800_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-2000_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-2500_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-3000_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-3500_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-4000_13TeV-madgraph",
"ZprimeToZhToZlephbb_narrow_M-4500_13TeV-madgraph"
                        };






const int N_background_points = 4;


TString background_file_name[N_background_points] = {
"DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
"DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
"DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
"DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
                        };

//DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
//DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8


//TString path = "/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/";
//TString path = "/data7/khurana/NCUGlobalTuples/SPRING15_ReMiniAODSIM/";
TString path = "/data7/syu/NCUGlobalTuples/Spring15_ReMiniAODSim/9b33d00/";

for(int i=0;i<N_mass_points;i++)
{ file_name[i] = path + "ZprimeToZhToZlephbb/" + file_name[i];      }

for(int i=0;i<N_background_points;i++)
//{ background_file_name[i] = path + "DYJetsToLL_M-50_HT_ReMiniAOD/"  + background_file_name[i];      }
{ background_file_name[i] = path  + background_file_name[i];      }


  int mass_point[N_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};



for (int signal_background_index =0; signal_background_index<2; signal_background_index++  ){// signal_background_flag
signal_background_flag = signal_background_index ;
//if( signal_background_index!= 0 )continue;// run signal sample only
//if( signal_background_index!= 1 )continue;// run bkg sample only


  for(int file_index=0;file_index<13;file_index++){// which signal mass points you want ?
//if( file_index!= 2 && file_index!= 7 && file_index!= 9 )continue;
//if( file_index!= 2 )continue;

  TString dir_name = "plot/" ;

  double eff =0, eff_err=0;

  int i = file_index;// i = file_index for convenience

  if(signal_background_flag == 0 )// read signal sample
      { 

  	cout<< "dir_name: " << dir_name <<endl;
  	cout<< "file_index: "<< file_index << endl;
  	cout<< "file_name[file_index]: "<< file_name[file_index] << endl;
  	cout<< "mass_point[file_index]: "<< mass_point[file_index]<<endl;

  	int background_file_index = -1;// not use background  

	xAna_ele_selection(file_name[file_index] ,
 mass_point[file_index], eff, eff_err, dir_name , signal_background_flag , background_file_index );



      }// end if




  if(signal_background_flag == 1 )// read background sample
      { 

	if( file_index!= 0 )continue; // read background only once

	    // file_index: signal mass points
 	    // background_file_index: which background sample 
	    // dir_name: name of directory to save ROOT file 

        for (int background_file_index=0; background_file_index<4;background_file_index++){// which background sample you want to read


  		cout<< "dir_name: " << dir_name <<endl;
  		cout<< "file_index: "<< file_index << endl;
  		cout<< "file_name[file_index]: "<< file_name[file_index] << endl;
  		cout<< "mass_point[file_index]: "<< mass_point[file_index]<<endl;
  		cout<< "background_file_index: "<< background_file_index <<endl;
  		cout<< "background_file_name[background_file_index]: "<< background_file_name[background_file_index] <<endl;

	xAna_ele_selection( background_file_name[background_file_index] ,
 mass_point[file_index], eff, eff_err, dir_name  , signal_background_flag , background_file_index );


            }// end background_file_index loop
      }// end if



  }// loop file_index

}// signal_background_flag

















}
