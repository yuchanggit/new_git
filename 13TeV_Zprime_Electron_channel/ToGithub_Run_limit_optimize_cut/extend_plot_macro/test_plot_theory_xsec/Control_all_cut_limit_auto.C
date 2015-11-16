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


void Control_all_cut_limit_auto()
{

const float intLumi = 3.0;
const int n_cut_index =10;

int cut_value[n_cut_index] = 
{115,136,157,178,199,220,241,262,283,304};

  TGraphAsymmErrors *grmedian_cls;
  TGraphAsymmErrors *grmedian_cls_new[n_cut_index];

  const int nMassEff = 10;
  double mass[nMassEff] = {0};
  double medianD[nMassEff] = {0};


  grmedian_cls = new TGraphAsymmErrors(nMassEff, mass, medianD);


//  TString dir_path = "Datacards_txt_files/YuHsiang_DY_h_ele_1st_pT_cut_115/";
  TString dir_path[n_cut_index] ;
  TString leg_name[n_cut_index] ;


  for(int i=0;i<n_cut_index;i++){
//  for(int i=0;i<5;i++){
if(i!=0)continue;
  dir_path[i] = Form("YuHsiang_DY_h_ele_1st_pT_cut_%d/",cut_value[i] ) ;
  dir_path[i] = "Datacards_txt_files/" + dir_path[i];
   
  grmedian_cls_new[i] =  plot_Asymptotic( dir_path[i] ,grmedian_cls );

//  leg_name[i] = Form("CL_{S} Expected Limit for cut pt>%d",cut_value[i] ) ;
  leg_name[i] = "theory cross section"  ;
  }





  TCanvas *c1 = new TCanvas("c1", "canvas with limits for Asymptotic CLs", 630, 600);


  TLegend *leg = new TLegend(.25, .25, .65, .35);
  leg->SetFillColor(0);
  leg->SetShadowColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);

  c1->SetGridx(1);
  c1->SetGridy(1);
    gPad->SetLogy();


  
  c1->cd();


   double fr_left = 500.0, fr_down = 1E-7, fr_right = 4500.0, fr_up = 1E-1;
  TH1F *hr = c1->DrawFrame(fr_left, fr_down, fr_right, fr_up, "");

  int colorN = 1;

// loop

  for(int i=0;i<n_cut_index;i++){
if(i!=0)continue;

	if (i==0){colorN = kRed;}
        if (i==3){colorN = kOrange;}
        if (i==6){colorN = kYellow;}
        if (i==9){colorN = kCyan;}
	
  	grmedian_cls_new[i]->SetLineColor(4);
        grmedian_cls_new[i]->SetLineStyle(1);
  	grmedian_cls_new[i]->Draw();

//  	leg->AddEntry(grmedian_cls_new[i], "CL_{S} Expected Limit", "L");
        leg->AddEntry(grmedian_cls_new[i],leg_name[i] , "L");
  	leg->Draw();

	colorN = colorN+1;
  }
// end loop

  hr->SetXTitle("M_{Z'} [GeV]");
//  hr->SetYTitle("#sigma_{95%} [pb]");
//  hr->SetYTitle("r-value");
  hr->SetYTitle("theory cross section [pb]");

    TLatex * latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.04);
    latex->SetTextAlign(31);
    latex->SetTextAlign(11);

    latex->DrawLatex(0.2, 0.90, "CL_{S} Expected Limit, cut electron leading pt");
    latex->DrawLatex(0.18, 0.96, "CMS preliminary 2015");
    latex->DrawLatex(0.60, 0.96, Form("%.1f fb^{-1} at #sqrt{s} = 13 TeV", intLumi));


  TString save_name = "theory_xsec";
  TString png_name = save_name + ".png";
  TString pdf_name = save_name + ".pdf";

  c1->SaveAs(png_name);
  c1->SaveAs(pdf_name);

}// end codes


