#include <iostream>
#include <fstream>
#include <TString.h>
#include <TH1D.h>
#include <TFile.h>
#include <string>
#include "TCanvas.h"
#include "xAna_ele.C"
#include "xAna_ele_noCuts.C"
#include "xAna_ele_match_rate.C"
#include "xAna_ele_compare_ChingWei.C"
#include "xAna_ele_subleading_ele_study.C"
#include "xAna_ele_subleading_ele_study_v2.C"
#include "xAna_ele_subleading_ele_study_v3.C"

void CutFlow_auto(){

const int N_mass_points = 13;


TString file_name[N_mass_points] = {
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-600_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-800_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-1000_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-1200_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-1400_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-1600_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-1800_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-2000_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-2500_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-3000_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-3500_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-4000_13TeV-madgraph.root",
"ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-4500_13TeV-madgraph.root"
                        };

TString path = "/Users/index0192/13_TeV_Task/";

for(int i=0;i<N_mass_points;i++)
{ file_name[i] = path + file_name[i];      }

  int mass_point[N_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};

TCanvas *c1[N_mass_points];
TCanvas *c2[N_mass_points];
TCanvas *c3[N_mass_points];
TCanvas *c4[N_mass_points];
TCanvas *c5[N_mass_points];

int dir_flag =0;// choose which Cut you want


















 // sub_leading electron pT study

bool sub_leading_ele_flag= false; 
sub_leading_ele_flag=true;

if(sub_leading_ele_flag){

  // file_name[0] is M-600 ROOT file, 
  // file_name[2] is M-1000 ROOT file,
  // file_name[12] is M-4500 ROOT file,

  dir_flag = 1; // use passHEEPID
//  dir_flag = 2; // use passLoose

//  int file_index = 2;// which mass points  '2' is M=1000

  for(int file_index=0;file_index<13;file_index++){

//  TString dir_name = "plot_SubLedaing_ele/" ;
  TString dir_name;

  if(dir_flag==1){dir_name = "plot_SubLedaing_ele_pt0_passHEEPID/" ;}
  if(dir_flag==2){dir_name = "plot_SubLedaing_ele_pt0_passLoose/" ;}

  cout<< "dir_name: " << dir_name <<endl;
  cout<< "file_index: "<< file_index << endl;
  cout<< "file_name[file_index]: "<< file_name[file_index] << endl;
  cout<< "mass_point[file_index]: "<< mass_point[file_index]<<endl;
  cout<< "dir_flag: "<< dir_flag <<endl;


  double eff =0, eff_err=0;

  int i = file_index;// i = file_index for convenience

  TString cut_flow_name = Form("Zprime_Cut_Flow_M_%d",mass_point[i]);
  TString ele_pT_name = Form("Zprime_ele_pT_M_%d",mass_point[i]);
  TString ll_pT_name = Form("Zprime_ll_pT_M_%d",mass_point[i]);
  TString SD_mass_name = Form("Zprime_SD_mass_M_%d",mass_point[i]);
  TString Z_mass_name = Form("Zprime_Z_mass_M_%d",mass_point[i]);

  c1[i] = new TCanvas(cut_flow_name,"try to show cut flow ",200,10,700,500);
  c2[i] = new TCanvas(ele_pT_name,"ele pT distribution ",200,10,700,500);
  c3[i] = new TCanvas(ll_pT_name,"ll pT distribution ",200,10,700,500);
  c4[i] = new TCanvas(SD_mass_name,"SD mass distribution ",200,10,700,500);
  c5[i] = new TCanvas(Z_mass_name,"Z mass distribution ",200,10,700,500);


//xAna_ele_subleading_ele_study(file_name[file_index] , c1[file_index] , c2[file_index] , c3[file_index] , c4[file_index] , c5[file_index] , mass_point[file_index], eff, eff_err, dir_name , dir_flag );

//xAna_ele_subleading_ele_study_v2(file_name[file_index] , c1[file_index] , c2[file_index] , c3[file_index] , c4[file_index] , c5[file_index] , mass_point[file_index], eff, eff_err, dir_name , dir_flag );

xAna_ele_subleading_ele_study_v3(file_name[file_index] , c1[file_index] , c2[file_index] , c3[file_index] , c4[file_index] , c5[file_index] , mass_point[file_index], eff, eff_err, dir_name , dir_flag );

  TString png1_name = Form("Zprime_Cut_Flow_M_%d.png",mass_point[i]);
  png1_name = dir_name + png1_name;
  c1[i]->cd();  c1[i]->SaveAs(png1_name);

  }// loop file_index



}
















}
