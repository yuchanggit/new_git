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

void CutFlow_auto(){

const int N_mass_points = 13;

  char* file_name[N_mass_points] = {
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

  int mass_point[N_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};

TCanvas *c1[N_mass_points];
TCanvas *c2[N_mass_points];
TCanvas *c3[N_mass_points];
TCanvas *c4[N_mass_points];
TCanvas *c5[N_mass_points];

int dir_flag =0;// choose which Cut you want

for(int j=0;j<10;j++){

continue;

dir_flag = j;

if(j!=7 && j!=8 && j!=9 )continue;

TString dir_name; 
if (dir_flag ==0){ dir_name = "plot_NoCuts/";}
if (dir_flag ==1){ dir_name = "plot_TurnOff3Cuts/";}
if (dir_flag ==2){ dir_name = "plot_Cut_SD40to140_ElePt85_llPt200/"; }
if (dir_flag ==3){ dir_name = "plot_Cut_SD50to140_ElePt85_llPt200/";}
if (dir_flag ==4){ dir_name = "plot_Cut_SD60to140_ElePt100_llPt200/";}
if (dir_flag ==5){ dir_name = "plot_Cut_SD60to140_ElePt115_llPt200/";}
if (dir_flag ==6){ dir_name = "plot_Cut_SD60to140_ElePt85_llPt200/";}

if (dir_flag ==7){ dir_name = "plot_Cut_SD93to143_ElePt115_llPt200/";}
if (dir_flag ==8){ dir_name = "plot_Cut_SD95to145_ElePt115_llPt200/";}
if (dir_flag ==9){ dir_name = "plot_Cut_SD91to141_ElePt115_llPt200/";}

  double eff, eff_err;

for (int i=0;i<13;i++){// 13 mass points

    if (i!=2) continue;// M= 1000
//  if(i!=0 && i!= 12){continue;}
  cout<<"i: "<<i <<"  mass_point[i]: "<< mass_point[i]<<endl;

  eff=-99; eff_err=-99;

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

//  TString ROOT_name = Form("plot_Cut_SD60to140_ElePt85_llPt200/Zprime_shape_M-%d.root",mass_point[i]);

// this will decide the directory where ROOT file to be saved  
cout<< "dir_flag: " << dir_flag << endl;
cout<< "dir_name: " << dir_name << endl;

if (dir_flag !=0){
  xAna_ele( file_name[i] , c1[i] , c2[i] , c3[i] , c4[i] , c5[i] , mass_point[i], eff, eff_err, dir_name , dir_flag );}
else if (dir_flag ==0){
  xAna_ele_noCuts( file_name[i] , c1[i] , c2[i] , c3[i] , c4[i] , c5[i] , mass_point[i], eff, eff_err, dir_name);}


  TString png1_name = Form("Zprime_Cut_Flow_M_%d.png",mass_point[i]);
  TString png2_name = Form("Zprime_ele_pT_M_%d.png",mass_point[i]);
  TString png3_name = Form("Zprime_ll_pT_M_%d.png",mass_point[i]);
  TString png4_name = Form("Zprime_SD_mass_M_%d.png",mass_point[i]);
  TString png5_name = Form("Zprime_Z_mass_M_%d.png",mass_point[i]);

png1_name = dir_name + png1_name;
png2_name = dir_name + png2_name;
png3_name = dir_name + png3_name;
png4_name = dir_name + png4_name;
png5_name = dir_name + png5_name;


  c1[i]->cd();  c1[i]->SaveAs(png1_name);
  c2[i]->cd();  c2[i]->SaveAs(png2_name);
  c3[i]->cd();  c3[i]->SaveAs(png3_name);
  c4[i]->cd();  c4[i]->SaveAs(png4_name);
  c5[i]->cd();  c5[i]->SaveAs(png5_name);



 }// loop i

}// loop j



  // ask the match rate  

  // file_name[0] is M-600 ROOT file, 
  // file_name[2] is M-1000 ROOT file,
  // file_name[12] is M-4500 ROOT file,

  cout<< "ask the match rate"<<endl;
  TString dir_name = "plot_TurnOff3Cuts" ; 
  dir_flag = 1; // N-3 cuts
  double eff =0, eff_err=0;


  int file_index = 12;
  cout<< "dir_name: " << dir_name <<endl;
  cout<< "file_name[i]: "<< file_name[file_index] << endl;
 
  xAna_ele_match_rate( file_name[file_index] ,/* c1 , c2 , c3 , c4 , c5 ,*/  mass_point[file_index], eff, eff_err, dir_name , dir_flag );


  //  compare ChingWei's SD window efficiency  

  cout<< "compare ChingWei's SD window efficiency  "<<endl;
//  TString dir_name = "plot_TurnOff3Cuts" ;
  dir_flag = 1; // N-1 Cut, I will turn all cuts except SD mass
//  double eff =0, eff_err=0;


  file_index = 2;
  cout<< "dir_name: " << dir_name <<endl;
  cout<< "file_name[i]: "<< file_name[file_index] << endl;


  xAna_ele_compare_ChingWei( file_name[file_index] ,/* c1 , c2 , c3 , c4 , c5 ,*/  mass_point[file_index], eff, eff_err, dir_name , dir_flag );




}
