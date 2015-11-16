#include <Riostream.h>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveText.h"

void plot_ratio()
{


// define 
const int N_mass_points = 11;
int Xmass[N_mass_points]={800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000};

const int N_cut_points = 10;
int cut_value[N_cut_points]={115,136,157,178,199,220,241,262,283,304};

TString dir_path = "txt_files/";
TString txt_path[N_cut_points];
TString leg_name[N_cut_points] ;

for(int i=0;i<N_cut_points;i++){
   txt_path[i] = Form( "YuHsiang_DY_h_ele_1st_pT_cut_%d.txt", cut_value[i]); 
   txt_path[i] = dir_path + txt_path[i];
//   cout<<"txt_path[i]: " << txt_path[i] << endl;

   leg_name[i] = Form( "cut pt>%d", cut_value[i]);
}

TGraphAsymmErrors *Ratio_sig_over_bkg[N_cut_points];




  TCanvas *c1 = new TCanvas("c1", "c 1", 630, 600);

   c1->cd();
   gPad->SetLogy();
  c1->SetGridx(1);
  c1->SetGridy(1);


   double fr_left = 500.0, fr_down = 1E-5, fr_right = 4500.0, fr_up = 1E0;
   TH1F *hr = c1->DrawFrame(fr_left, fr_down, fr_right, fr_up, "");

  hr->SetXTitle("M_{Z'} [GeV]");
  hr->SetYTitle("Ratio = signal yield/background yield");
  double TitleOffset = 1.3;
  hr->GetYaxis()->SetTitleOffset(TitleOffset);

// for each cut points
for (int i=0;i<N_cut_points;i++){
//if(i!=0)continue;

  cout<<"cut value: " << cut_value[i] << endl; 

  string Txt_Path  =(std::string) txt_path[i] ;

  ifstream event_yield_file(Txt_Path.c_str(), ios::in);

  string Name; double Event_Yield;
  vector<string> name;  vector<double> event_yield; 

  while (event_yield_file.good()) {
    event_yield_file >> Name >> Event_Yield  ;
    name.push_back(Name); 
    event_yield.push_back(Event_Yield); 
  }

  event_yield_file.close();

//cout<<"name size: " << name.size() << endl;  

//  for (int j=0;j<name.size();j++){
//    cout<<"j:"<< j; 
//    cout<<" name[j] : " << name[j]; 
//    cout<<" event_yield[j]: " << event_yield[j] << endl;
//  }

  double mass[N_mass_points];
  double ratio[N_mass_points]; // signal yield over background yield
 
  for (int j=0;j<N_mass_points;j++){
     mass[j] = Xmass[j];
     ratio[j] = event_yield[j+2]/ event_yield[1]; // 1 is background, 2~12 is signal 
     cout<<"mass[j]: "<< mass[j] <<" ratio[j]: "<< ratio[j] << endl; 
  }// loop N_mass_points j

   Ratio_sig_over_bkg[i] = new TGraphAsymmErrors( N_mass_points , mass, ratio );



}// loop N_cut_points i

  TLegend *leg = new TLegend(.65, .55, .85, .85);
  leg->SetFillColor(0);
  leg->SetShadowColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);

   int colorN = 1;

for (int i=0;i<N_cut_points;i++){

        if (i==0){colorN = kRed;}
        if (i==3){colorN = kOrange;}
        if (i==6){colorN = kYellow;}
        if (i==9){colorN = kCyan;}

   Ratio_sig_over_bkg[i]->SetLineColor(colorN);
   Ratio_sig_over_bkg[i]->SetLineWidth(3);

   c1->cd();
   if(i==0)Ratio_sig_over_bkg[i] ->Draw();
   else if(i!=0) Ratio_sig_over_bkg[i] ->Draw("same");

   leg->AddEntry(Ratio_sig_over_bkg[i],leg_name[i] , "L");
   leg->Draw();

   colorN = colorN +1 ;

}// loop N_cut_points i


 TString save_png_name ="ratio.png" ;
 c1->SaveAs(save_png_name);



}
