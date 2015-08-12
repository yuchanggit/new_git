#include <stdio.h>
#include <iostream>
#include <fstream>
#include <TString.h>
#include <TH1D.h>
#include <TFile.h>
#include <string>
#include "TCanvas.h"
#include "xAna_ele.C"
#include "xAna_ele_noCuts.C"
#include "TLegend.h"
#include "TString.h"

#include <cstring>

using namespace std;

void Plot_macro(){


  // 1. draw the shape varies with mass points 

const int N_mass_points = 13;

  int mass_point[N_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};

string file_name[N_mass_points]={
"Zprime_shape_M-600.root",
"Zprime_shape_M-800.root",
"Zprime_shape_M-1000.root",
"Zprime_shape_M-1200.root",
"Zprime_shape_M-1400.root",
"Zprime_shape_M-1600.root",
"Zprime_shape_M-1800.root",
"Zprime_shape_M-2000.root",
"Zprime_shape_M-2500.root",
"Zprime_shape_M-3000.root",
"Zprime_shape_M-3500.root",
"Zprime_shape_M-4000.root",
"Zprime_shape_M-4500.root"
};
const int dirN=7;

string dir_name[dirN]={
"plot_NoCuts/",
"plot_TurnOff3Cuts/",
"plot_Cut_SD40to140_ElePt85_llPt200/",
"plot_Cut_SD50to140_ElePt85_llPt200/",
"plot_Cut_SD60to140_ElePt100_llPt200/",
"plot_Cut_SD60to140_ElePt115_llPt200/",
"plot_Cut_SD60to140_ElePt85_llPt200/"
};

string dir_name_no_slash[dirN]={
"plot_NoCuts",
"plot_TurnOff3Cuts",
"plot_Cut_SD40to140_ElePt85_llPt200",
"plot_Cut_SD50to140_ElePt85_llPt200",
"plot_Cut_SD60to140_ElePt100_llPt200",
"plot_Cut_SD60to140_ElePt115_llPt200",
"plot_Cut_SD60to140_ElePt85_llPt200"
};

const int variableN =4;
TString variable_name[variableN]={"h_SD","h_ele_pT","h_lepton_pair_pT","h_Z_mass"};

TH1D *h_var[N_mass_points];
TString title1[N_mass_points];

TCanvas *c1[dirN][variableN];
//TCanvas *c1 = new TCanvas("c1","try overlap TH1D",200,10,700,500);
//c1->SetFillColor(0);
//TLegend *leg=new TLegend(0.7,0.3,0.9,0.9);
//leg->SetFillColor(10);

double Max_y=0;
int  colorN = 1;
bool first_time = true;

for(int j=0;j<3;j++){ // variables

  for(int k=0;k<2;k++){ // dir name

TString c1_name = "_shape_vary_with_mass";
c1_name = variable_name[j] + c1_name + "_of_" + dir_name[k] ;

c1[k][j] = new TCanvas(c1_name,"shape varies with mass points",200,10,700,500);

TLegend *leg=new TLegend(0.7,0.3,0.9,0.9);

  for(int i=0; i<13; i++){ // mass point

//   if(i!=12 && i!=0 ) continue;

title1[i] = Form("Zprime M=%d GeV",mass_point[i]);
TString destination = dir_name[k] + file_name[i] ; 

TFile *f1 = new TFile (destination);
h_var[i] = (TH1D*) f1->Get(variable_name[j]);

h_var[i]->Scale( 1/h_var[i]->Integral() );
h_var[i]->SetTitle(c1_name);
h_var[i]->SetStats(0);

     if( i==0){colorN = kRed;}
else if( i==3){colorN = kOrange;}
else if( i==6){colorN = kYellow;}
else if( i==9){colorN = kCyan;}

 h_var[i]->SetLineColor(colorN);
 colorN = colorN + 1;


c1[k][j]->cd();

if(first_time) 
{ h_var[i]->Draw(); 
//h_var[i]->GetYaxis()->SetRangeUser(0, 0.15); 
//h_var[i]->GetXaxis()->SetRangeUser(0, 160);
first_time = false;  }
else {h_var[i]->Draw("same");}
 
 leg->AddEntry( h_var[i] , title1[i] ,"L");
 leg->Draw();

c1[k][j]->Update();


   }// loop i

 c1[k][j]->cd();
 TString png_name1 = variable_name[j] ;
 png_name1 = "Plot_macro_dir/"+ png_name1 +"_in_" + dir_name_no_slash[k]   + ".png";

// cout<< "png_name1: "<< png_name1 <<endl;
 c1[k][j]->SaveAs(png_name1);

}// loop k


  // 2. draw the shapes in different cut-level of the same mass point 

  // example, take M-2000, var is SD

//const int variableN =4;
//TString variable_name[variableN]={"h_SD","h_ele_pT","h_lepton_pair_pT","h_Z_mass"};

TCanvas *c2[N_mass_points][variableN];


//for(int j=0;j<4;j++){
//continue;

  for(int i=0; i<13; i++){
//continue;

//   if(i!=12 && i!=0 ) continue;

TString c2_name = Form("different_cuts_level_of_M_%d",mass_point[i]);
c2_name = variable_name[j] + "_in_" + c2_name; 

c2[i][j] = new TCanvas(c2_name,"different cut level",200,10,700,500);

TString ROOT_name = Form("Zprime_shape_M-%d.root",mass_point[i]);

TString destination1, destination2 ,destination3 ;

destination1 = "plot_NoCuts/" + ROOT_name ;
TFile *f2 = new TFile (destination1);
TH1D  *h_var_NoCut = (TH1D*) f2->Get(variable_name[j]);

destination2 = "plot_TurnOff3Cuts/" + ROOT_name ;
TFile *f3 = new TFile (destination2);
TH1D  *h_var_TurnOff3Cuts = (TH1D*) f3->Get(variable_name[j]);

destination3 = "plot_Cut_SD60to140_ElePt115_llPt200/" + ROOT_name ;
TFile *f4 = new TFile (destination3);
TH1D  *h_var_Cut_SD60to140_ElePt115_llPt200 = (TH1D*) f4->Get(variable_name[j]);

 h_var_NoCut->SetStats(0);
 h_var_TurnOff3Cuts->SetStats(0);
 h_var_Cut_SD60to140_ElePt115_llPt200->SetStats(0);

 h_var_NoCut->SetLineColor(1);
 h_var_TurnOff3Cuts->SetLineColor(2);
 h_var_Cut_SD60to140_ElePt115_llPt200->SetLineColor(4);

 c2[i][j]->cd();
// h_var_NoCut->Draw();
 h_var_TurnOff3Cuts->Draw("same");
 h_var_Cut_SD60to140_ElePt115_llPt200->Draw("same");

 TLegend *leg2=new TLegend(0.7,0.6,0.9,0.9);
// leg2->AddEntry( h_var_NoCut ,"No Cuts" ,"L");
 leg2->AddEntry( h_var_TurnOff3Cuts ,"N-3 Cuts" ,"L");
 leg2->AddEntry( h_var_Cut_SD60to140_ElePt115_llPt200 ,"N Cuts" ,"L");
 leg2->Draw();

 c2[i][j]->Update();

 TString png_name = c2_name;
 png_name = "Plot_macro_dir/"+ png_name + ".png";
 c2[i][j]->SaveAs(png_name);

  }// loop i

}//loop j


}
