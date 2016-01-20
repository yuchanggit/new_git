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
#include "plot_Asymptotic.C"
#include "TString.h"

using namespace std;

void Control_all_cut_limit_auto(const int n_cut_index,   double lowest_cut,   double scan_width , 
TString input_dir, TString path_to_save  )
{

const float intLumi = 3.0;
//const int n_cut_index =11; // 10

//  TString variable_name = "Ele_1st_pt" ;
  TString variable_name = "Ele_2nd_pt" ;
  cout<<"variable_name: " << variable_name << endl;

  // define cuts
  
  int cut_value[n_cut_index];
//  double lowest_cut=115 ;
//  double scan_width = 20;// 21

  for(int i=0;i<n_cut_index ;i++){
        cut_value[i] = lowest_cut + scan_width*i;
        cout<<"cut_value[i]: "<< cut_value[i] << endl;
  }
  //

//int cut_value[n_cut_index] = 
//{115,136,157,178,199,220,241,262,283,304};

  TGraphAsymmErrors *grmedian_cls;
  TGraphAsymmErrors *grmedian_cls_new[n_cut_index];

  const int nMassEff = 11;
  double mass[nMassEff] = {0};
  double medianD[nMassEff] = {0};


  grmedian_cls = new TGraphAsymmErrors(nMassEff, mass, medianD);


//  TString dir_path = "Datacards_txt_files/YuHsiang_DY_h_ele_1st_pT_cut_115/";
  TString dir_path[n_cut_index] ;
  TString leg_name[n_cut_index] ;
//  TString input_dir = "Datacards_text_and_ROOT_files/";

  for(int i=0;i<n_cut_index;i++){
//  for(int i=0;i<5;i++){
//  dir_path[i] = Form("YuHsiang_DY_Ele_1st_pt_cut_%d/",cut_value[i] ) ;
  dir_path[i] = Form("_cut_%d/",cut_value[i] ) ;
  dir_path[i] =  "YuHsiang_DY_" + variable_name + dir_path[i];
//  dir_path[i] = Form("YuHsiang_DY_h_ele_1st_pT_cut_%d/",cut_value[i] ) ;
  dir_path[i] = input_dir + "/"  + dir_path[i];
//  dir_path[i] = "Datacards_text_and_ROOT_files/" + dir_path[i];
//  dir_path[i] = "Datacards_txt_files/" + dir_path[i];

  cout<<endl;
  cout<<"dir_path[i]: "<< dir_path[i] << endl;
   
  grmedian_cls_new[i] =  plot_Asymptotic( dir_path[i] ,grmedian_cls );

//  leg_name[i] = Form("CL_{S} Expected Limit for cut pt>%d",cut_value[i] ) ;
  leg_name[i] = Form("cut pt>%d",cut_value[i] ) ;
  }





  TCanvas *c1 = new TCanvas("c1", "canvas with limits for Asymptotic CLs", 630, 600);


//  TLegend *leg = new TLegend(.55, .35, .85, .85);
//  TLegend *leg = new TLegend(.15, .35, .40, .85);
  TLegend *leg = new TLegend(.75, .35, .95, .85);
//  TLegend *leg = new TLegend(.55, .35, .85, .85);
  leg->SetFillColor(0);
  leg->SetShadowColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);

  c1->SetGridx(1);
  c1->SetGridy(1);
    gPad->SetLogy();


  
  c1->cd();


//   double fr_left = 500.0, fr_down = 7E-2, fr_right = 4500.0, fr_up = 2E0;
//   double fr_left = 900.0, fr_down = 3E-1, fr_right = 1100.0, fr_up = 4E-1;
//   double fr_left = 1900.0, fr_down = 1E-1, fr_right = 2100.0, fr_up = 1.5E-1;
   double fr_left = 2900.0, fr_down = 10E-2, fr_right = 3100.0, fr_up = 1.25E-1;
  TH1F *hr = c1->DrawFrame(fr_left, fr_down, fr_right, fr_up, "");

  int colorN = 1;

// loop

  for(int i=0;i<n_cut_index;i++){

//	if (i==0){colorN = kRed;}
//        if (i==3){colorN = kOrange;}
//        if (i==6){colorN = kCyan;}
//        if (i==9){colorN = kBlue;}
//        if (i==12){colorN = kGreen;}

        if (i==0){colorN = kRed;}
        if (i==2){colorN = kOrange;}
        if (i==4){colorN = kCyan;}
        if (i==6){colorN = kBlue;}
        if (i==8){colorN = kGreen;}
        if (i==10){colorN = kMagenta;}
	
  	grmedian_cls_new[i]->SetLineColor(colorN);
        grmedian_cls_new[i]->SetLineStyle(1);
        grmedian_cls_new[i]->SetLineWidth(3);
  	grmedian_cls_new[i]->Draw();

//  	leg->AddEntry(grmedian_cls_new[i], "CL_{S} Expected Limit", "L");
        leg->AddEntry(grmedian_cls_new[i],leg_name[i] , "L");
  	leg->Draw();

	colorN = colorN+2;
  }
// end loop

  hr->SetXTitle("M_{Z'} [GeV]");
  hr->SetYTitle("95% #sigma_{Z'}xBR(Z'->ZH) [pb]");

    TLatex * latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->SetTextAlign(11);

    latex->DrawLatex(0.25, 0.87, "CL_{S} Expected Limit, cut electron subleading pt");
    latex->DrawLatex(0.18, 0.96, "CMS preliminary 2015");
    latex->DrawLatex(0.60, 0.96, Form("%.1f fb^{-1} at #sqrt{s} = 13 TeV", intLumi));


  TString save_name = "expected_limit_cut_";
  save_name = save_name + variable_name ;

  TString png_name = save_name + ".png";
  TString pdf_name = save_name + ".pdf";

//  c1->SaveAs(png_name);
//  c1->SaveAs(pdf_name);


//TString path_to_save = "/afs/cern.ch/user/y/yuchang/www/set_limit_optimize_leading_pt/" ;
//TString path_to_save = "/afs/cern.ch/user/y/yuchang/www/optimize_cut_with_limit_use_eleIsPassVeto/leading_pt/";
pdf_name = path_to_save + pdf_name;

c1->SaveAs( pdf_name );


}// end codes


