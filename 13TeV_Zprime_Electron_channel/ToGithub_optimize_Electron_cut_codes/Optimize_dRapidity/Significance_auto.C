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
#include "TGraph.h"
#include "TGraphErrors.h"
#include "utils_for_optimization.C"
#include "setNCUStyle.C"
//#include "additional_style.C"
#include "TLatex.h"
#include <cstring>
//#include "twopads.C"
#include <TPad.h>
#include <TStyle.h>


using namespace std;

double uncertainty_calculate( double , double );


void Significance_auto(){

//set NCU figure style
bool gridOn = true;
setNCUStyle(gridOn);
// additional_style();

 //  prepare the weights for 4 background samples

const int N_background_points = 4;
double background_cross_section[N_background_points] = { 139.4 , 42.75 , 5.497 , 2.21 };
//double background_number_of_events[N_background_points] = { 2377497 , 955972 , 1048047 , 987977 };
double background_number_of_events[N_background_points] =   { 2327916 , 955972 , 1038512 , 974623 };
double background_weights[N_background_points];

for(int i=0;i<N_background_points;i++) 
{ background_weights[i] = background_cross_section[i] / background_number_of_events[i];  
}


 // prepare all thing used in below

  const int N_mass_points = 13;
  int Zprime_mass[N_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
//  TString path = "/Users/index0192/13_TeV_Task/Zprime_Electron_channel/Optimize_2nd_pt/plot";
TString path = "plot/";

  TCanvas *c1[N_mass_points];
//  TCanvas *c1_zoom_in[N_mass_points];
  TString c1_name;
//  TString c1_name_zoom_in;

  TString leg_name1 = "Significance";
  TString leg_name2 = "Signal efficiency";
  TString leg_name3 = "Background efficiency";


  // save histogram for figure style

  TFile *myFile;

  bool save_flag = false;
//  save_flag = true;
  if(save_flag){

        myFile = new TFile("figure_style.root","recreate");

//        myFile->Close();
  }//end if






  // now calulate the significance

  // loop in k, which mass point you want to know its Significance

  for(int k=0 ; k<N_mass_points ; k++){
if( k!= 2 && k!= 7 && k!= 9)continue;
if( k!= 9 )continue;
//continue;

	// c1 name	
  	cout<< "Zprime_mass[k]: " << Zprime_mass[k] << endl;
	c1_name  = Form("Significance_and_efficiency_for_Zprme_M_%d", Zprime_mass[k] );
//        c1_name_zoom_in  = Form("Significance_and_efficiency_for_Zprme_M_%d_zoom_in", Zprime_mass[k] );
// 	c1_zoom_in[k] = new TCanvas(c1_name_zoom_in,"",600,600);
        c1[k] = new TCanvas(c1_name,"Significance in different cut value",200,10,700,500);

	// open the signal ROOT file
  	TString signal_shape_file = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);
  	signal_shape_file = path + signal_shape_file ;
  	TFile *f_signal = new TFile (signal_shape_file);

	// open the signal histogram
//  	TString histo_name= "h_ele_pT" ;
        TString histo_name= "h_abs_dEta_ZH" ;
  	TH1D *h_2nd_ele_pT;
  	h_2nd_ele_pT = (TH1D*) f_signal -> Get(histo_name);

//	  f_signal->Close();
//	  delete f_signal;


        // try to determine the highest cut value
  	int max_non_zero_bin = -1;
  	for( int m=1 ; m<= h_2nd_ele_pT->GetNbinsX() ;m++ ){
       		double bin_content = h_2nd_ele_pT->GetBinContent(m);
       		if( bin_content != 0 ){ max_non_zero_bin = m; }
  	}
	cout<<"max_non_zero_bin: "<< max_non_zero_bin <<endl;

        int min_non_zero_bin = -1;
        for( int m=1 ; m<= h_2nd_ele_pT->GetNbinsX() ;m++ ){
                double bin_content = h_2nd_ele_pT->GetBinContent(m);
                if( bin_content != 0 ){ min_non_zero_bin = m; break; }
        }
        cout<<"min_non_zero_bin: "<< min_non_zero_bin <<endl;

        double bin_width = h_2nd_ele_pT ->GetBinWidth(1);

//	double scan_width = 5; // how many unit you scan your cut points, default I use 5 GeV
        double scan_width = 0.05;
//        double scan_width = 0.5;
//	scan_width = 100;

        // input the lowest cut value
//      double lowest_cut = 35; // for sub-leading electron pt
//        double lowest_cut = 10;
//        double lowest_cut = 35; // for sub leading electron pt 
//        double lowest_cut = 115; // for leading electron pt 
        double lowest_cut = 0; // for |dEta| and |d Rapidity| 

//        double first_bin_value = 0;// the lower bound of histogram
        double first_bin_value = -1;// the lower bound of histogram
	int min_bin = ( lowest_cut - first_bin_value )/ bin_width + 1;// bin for lowest_cut 


	// decide the highest bin that can be divided by the scan-width	
 	int multipier = (max_non_zero_bin - min_bin ) * bin_width / scan_width;
        cout<<"multipier: "<< multipier <<endl;
  	double highest_cut =  lowest_cut  + multipier * scan_width ;
  	cout<< "highest_cut: " <<  highest_cut <<endl;


	// save the cut point value for every 5 Gev BTW highest and lowest value 
  	int n_cut_points = (highest_cut - lowest_cut)/scan_width + 1;
  	const int N_cut_points = n_cut_points;
  	cout<< "N_cut_points: " << N_cut_points << endl<<endl;
  	double cut_points[N_cut_points];
 
  	for(int i=0;i<N_cut_points;i++){
  		cut_points[i] = lowest_cut + scan_width*i;
     	}

  	// TGraph for Significance  
  	const int Nbins = N_cut_points ;
  	double vx[Nbins] ;

  	double vy_significance[Nbins] ;
        double vy_significance_errx[Nbins] ;
        double vy_significance_erry[Nbins] ;

  	double vy_sig_eff[Nbins] ;
        double vy_sig_eff_errx[Nbins] ;
        double vy_sig_eff_erry[Nbins] ;

  	double vy_background_eff[Nbins] ;
        double vy_background_eff_errx[Nbins] ;
        double vy_background_eff_erry[Nbins] ;

	for(int i=0;i<Nbins;i++){
		vy_significance_errx[i]=0;    vy_significance_erry[Nbins]=0; 
		vy_sig_eff_errx[i]=0;         vy_sig_eff_erry[i]=0;
		vy_background_eff_errx[i]=0;  vy_background_eff_erry[i]=0;
	}


  	// draw the Tgraph for significance, signal eff. and background eff.
  	TString c1_title = Form("M_{Z'}=%d GeV", Zprime_mass[k] );
  	TLegend *leg=new TLegend(0.5,0.60,0.99,0.80);
        TString leg_name = Form("leg_for_sig_and_eff_in_M_{Z'}=%d_GeV", Zprime_mass[k] );
	leg->SetName(leg_name);

  //

  float sig_noCut, sig_err_NoCut;

  // use Eiko's eff. fn
  bool Eiko_efficiency_function=false;
  Eiko_efficiency_function= true;
  if(Eiko_efficiency_function){


		// signal eff

		        TH1F *h_2nd_ele_pT_ = (TH1F*) h_2nd_ele_pT ->Clone("");
                        h_2nd_ele_pT_->Sumw2();

                        float eff[Nbins], eff_err[Nbins];


		// background eff

		        TH1F *h_background_2nd_ele_pT_combine = (TH1F*) h_2nd_ele_pT_ ->Clone("");
        		h_background_2nd_ele_pT_combine->Reset();
			h_background_2nd_ele_pT_combine->Sumw2();

                        // prepare background sample name
                        TString background_shape_file[N_background_points];
                        for(int l=0 ; l<N_background_points ; l++ ){
                                if(l==0 ){ background_shape_file[l] = Form("background_shape_DYJets_HT100to200_in_Zprime_M-%d.root",Zprime_mass[k]);}
                                if(l==1 ){ background_shape_file[l] = Form("background_shape_DYJets_HT200to400_in_Zprime_M-%d.root",Zprime_mass[k]);}
                                if(l==2 ){ background_shape_file[l] = Form("background_shape_DYJets_HT400to600_in_Zprime_M-%d.root",Zprime_mass[k]);}
                                if(l==3 ){ background_shape_file[l] = Form("background_shape_DYJets_HT600toInf_in_Zprime_M-%d.root",Zprime_mass[k]);}
                        }// loop l background shape file
     
        		// loop background sample, open histogram, weight it, and add together 
        		for(int i=0; i<N_background_points;i++){

                		// open
                		background_shape_file[i] = path + background_shape_file[i];
                		TFile *f_background = new TFile ( background_shape_file[i] );
                		TH1D *h_background_2nd_ele_pT;
                		h_background_2nd_ele_pT = (TH1D*) f_background -> Get(histo_name);

                		// weight
                                h_background_2nd_ele_pT->Sumw2();
          		      	h_background_2nd_ele_pT->Scale( background_weights[i] );

                		// add
                		h_background_2nd_ele_pT_combine ->Add(h_background_2nd_ele_pT);

			f_background->Close();
			delete f_background;
        		}// loop i background shape file

			// h_background_2nd_ele_pT_combine is ready for background


			//float background_eff[Nbins], background_eff_err[Nbins];

                        TH1F *h_background_2nd_ele_pT_combine_scale1 = (TH1F*) h_background_2nd_ele_pT_combine ->Clone("new");
                        double lumi = 1000;
//                        double lumi = 1;
                        h_background_2nd_ele_pT_combine_scale1->Scale( lumi );

                        float background_eff[Nbins], background_eff_err[Nbins];



                // significance

			cout<<endl;
                        cout<<"significance"<<endl;

                        TH1F *h_background_2nd_ele_pT_combine_scale2 = (TH1F*) h_background_2nd_ele_pT_combine ->Clone("new");
		        lumi = 1000;
			h_background_2nd_ele_pT_combine_scale2->Scale( lumi );

//                        float sig[Nbins], sig_err[Nbins];


//                        float eff[Nbins], eff_err[Nbins];
//                        float background_eff[Nbins], background_eff_err[Nbins];
                        float sig[Nbins], sig_err[Nbins];

                        for(int i=0;i<Nbins; i++)
                        {

                                vx[i] = cut_points[i];

//                              efficiency(eff[i],eff_err[i], h_2nd_ele_pT_, ( i * scan_width ) + lowest_cut + 1 );
//                              double bin_width = h_2nd_ele_pT_ ->GetBinWidth(1);

/*
                                int FirstBinForCut = min_non_zero_bin -2   ;
                                cout<< "FirstBinForCut: "<< FirstBinForCut <<endl;
                                int LastBinForCut = (cut_points[i] - lowest_cut)/bin_width + min_non_zero_bin -1     ;
                                cout<< "LastBinForCut: "<< LastBinForCut <<endl;

                                int mode = 0;
                                int FirstBinForTotal = min_non_zero_bin-2  ;
                                int LastBinForTotal = -1;
*/
                                int FirstBinForCut = min_bin -2    ;
                                cout<< "FirstBinForCut: "<< FirstBinForCut <<endl;
                                int LastBinForCut = (cut_points[i] - lowest_cut)/bin_width + min_bin -1 ;
                                cout<< "LastBinForCut: "<< LastBinForCut <<endl;

                                int mode = 0;
                                int FirstBinForTotal = min_bin -2  ;
                                int LastBinForTotal = -1;



                                efficiency(eff[i],eff_err[i], h_2nd_ele_pT_, FirstBinForCut , LastBinForCut, mode , FirstBinForTotal , LastBinForTotal );
                                vy_sig_eff[i] = eff[i];
                                vy_sig_eff_erry[i] = eff_err[i];


                                efficiency(background_eff[i] ,background_eff_err[i],h_background_2nd_ele_pT_combine_scale1 , FirstBinForCut , LastBinForCut, mode , FirstBinForTotal , LastBinForTotal );
                                vy_background_eff[i] = background_eff[i]; 
                                vy_background_eff_erry[i] = background_eff_err[i];


                                significance( sig[i] , sig_err[i] , h_2nd_ele_pT_  , h_background_2nd_ele_pT_combine_scale2  ,FirstBinForCut , LastBinForCut, mode , FirstBinForTotal , LastBinForTotal  );
                                vy_significance[i] = sig[i];
                                vy_significance_erry[i] = sig_err[i];




                              cout<<"i:  "<< i  <<endl;
                              cout<<"cut point vx[i]:  "<< vx[i]  <<endl;

//                              cout<<"vy_sig_eff[i]:  "<<vy_sig_eff[i]   <<endl;
//                              cout<<"vy_sig_eff_erry[i]:  "<<vy_sig_eff_erry[i]   <<endl;

 //                             cout<<"vy_background_eff[i]:  "<<vy_background_eff[i]   <<endl;
 //                             cout<<"vy_background_eff_erry[i]:  "<<vy_background_eff_erry[i]   <<endl;

                              cout<<"vy_significance[i]:  "<<vy_significance[i]   <<endl;
                              cout<<"vy_significance_erry[i]:  "<<vy_significance_erry[i]   <<endl;



                        }// end loop

  			// no cut


		    	int FirstBinForCut = min_bin -1   ;
    			int LastBinForCut =  -1     ;
    			int mode = 0;
    			int FirstBinForTotal = min_bin -1  ;
    			int LastBinForTotal = -1;

   	 		significance( sig_noCut , sig_err_NoCut , h_2nd_ele_pT_  , h_background_2nd_ele_pT_combine_scale2  ,FirstBinForCut , LastBinForCut, mode , FirstBinForTotal , LastBinForTotal  );


                }// end if



  // find the highest significance
  int hightest_bin =-9;
  double highest_sig=-99; 

  for(int i=0;i<Nbins; i++)
  {
  double temp = vy_significance[i] + vy_significance_erry[i]; 
  if(temp > highest_sig){highest_sig = temp; hightest_bin = i;}

  }
  cout<<endl;
  cout<< "Zprime_mass[k]: " << Zprime_mass[k] << endl;
  cout<<"hightest_bin : "<< hightest_bin << endl;  
  cout<<"highest_sig : "<<highest_sig << endl;
  cout<<"vx[hightest_bin] : "<< vx[hightest_bin] <<endl;
  cout<<"sig: "<< vy_significance[hightest_bin] <<" +/- "<< vy_significance_erry[hightest_bin] << endl;
  cout<<"no cut sig : "<< sig_noCut <<" +/- " << sig_err_NoCut << endl;
  cout<<"max_non_zero_bin: "<< max_non_zero_bin <<endl;
  cout<<"min_bin: "<< min_bin <<endl;
  cout<< "highest_cut: " <<  highest_cut <<endl;
  cout<<endl;



  // draw the TGraphError

  c1[k]->cd();

  TGraphErrors *gr 		  = new TGraphErrors(Nbins , vx , vy_significance, vy_significance_errx, vy_significance_erry );
  TGraphErrors *gr_eff 		  = new TGraphErrors(Nbins , vx , vy_sig_eff, vy_sig_eff_errx, vy_sig_eff_erry );
  TGraphErrors *gr_background_eff = new TGraphErrors(Nbins , vx , vy_background_eff, vy_background_eff_errx, vy_background_eff_erry );

  // name setting
  TString TGraph1 = Form("significance_in_M_{Z'}=%d_GeV", Zprime_mass[k] );
  TString TGraph2 = Form("signal_eff_in_M_{Z'}=%d_GeV", Zprime_mass[k] );
  TString TGraph3 = Form("background_eff_in_M_{Z'}=%d_GeV", Zprime_mass[k] );

  gr->SetName(TGraph1);
  gr_eff->SetName(TGraph2);
  gr_background_eff->SetName(TGraph3);

  // draw setting
  gr->GetYaxis()->SetRangeUser(0, 2.0);
  gr->SetTitle(c1_title);
//  gr->GetXaxis()->SetTitle("Minimum p_{T} threshold of sub-leading electron [ GeV]");
//  gr->GetXaxis()->SetTitle("Minimum p_{T} threshold of leading electron [ GeV]");
  gr->GetXaxis()->SetTitle("Maximum |  #Delta Rapidity_{ZH} | threshold");
//  gr->GetXaxis()->SetTitle("|  #Delta #eta_{ZH} | upper bound");

  gr->SetLineColor(2);
  gr_eff->SetLineColor(kBlue);
  gr_background_eff->SetLineColor(kGreen+2);

  gr->SetLineStyle(1);
  gr_eff->SetLineStyle(1);
  gr_background_eff->SetLineStyle(1);

  gr->SetLineWidth(3);
  gr_eff->SetLineWidth(3);
  gr_background_eff->SetLineWidth(3);

  gr->SetMarkerColor(2);
  gr_eff->SetMarkerColor(kBlue);
  gr_background_eff->SetMarkerColor(kGreen+2);

  gr->SetMarkerStyle(4);
  gr_eff->SetMarkerStyle(5);
  gr_background_eff->SetMarkerStyle(8);

  gr->SetMarkerSize(1);
  gr_eff->SetMarkerSize(1);
  gr_background_eff->SetMarkerSize(1);

  gr->Draw("ALP");
  gr_eff->Draw("same lp");
  gr_background_eff->Draw("same lp");

  leg->AddEntry( gr , leg_name1 ,"pl");
  leg->AddEntry( gr_eff , leg_name2 ,"pl");
  leg->AddEntry( gr_background_eff , leg_name3 ,"pl");
  leg->SetFillStyle(0);
  leg->Draw();

 //TLatex test
  TLatex *lar = new TLatex(0.13, 0.94, "CMS");
  lar->SetNDC(kTRUE);
  lar->SetTextSize(0.050);
  lar->SetTextFont(62);
  lar->SetLineWidth(5);
  lar->Draw("");

  TLatex *lar2 = new TLatex(0.25, 0.94, "Simulation");
  lar2->SetNDC(kTRUE);
  lar2->SetTextSize(0.050);
  lar2->SetTextFont(52);
  lar2->SetLineWidth(5);
  lar2->Draw("");

  TLatex *lar3 = new TLatex(0.55, 0.94, c1_title );
  lar3->SetNDC(kTRUE);
  lar3->SetTextSize(0.050);
  lar3->SetTextFont(52);
  lar3->SetLineWidth(5);
  lar3->Draw("");

  // zoom in test

//  float xmin= 250 ;
//  float xmax= 350 ;
//  float ymin= 0.3 ;
//  float ymax= 0.5 ;
  float xmin=-99 ;
  float xmax=-99 ;
  float ymin=-99 ;
  float ymax=-99 ;
if(k==2){xmin=1.2; xmax=2.5 ; ymin=0.38 ; ymax=0.41 ;}
if(k==7){xmin=1.6; xmax=2.6 ; ymin=0.67 ; ymax=0.77 ;}
if(k==9){xmin=2.4; xmax=3.4 ; ymin=0.85 ; ymax=0.95 ;}

//  twopads(TH1F* horiginal,  xmin,  xmax);
//  twopads( gr,  xmin,  xmax);
//  twopads( gr , gr_eff , gr_background_eff , xmin, xmax, ymin, ymax , c1_zoom_in[k]);

//  c1_name_zoom_in = path + c1_name_zoom_in + ".png";
//  c1_zoom_in[k]->SaveAs(c1_name_zoom_in);

bool two_pad_flag = false;
two_pad_flag = true;
if(two_pad_flag){

  c1[k]->cd();

//  float xlabelsize= gr->GetXaxis()->GetLabelSize(); 
//  float ylabelsize= gr->GetYaxis()->GetLabelSize();
  float canvassize = 0.35;
//  float canvassize = 0.35;
  float x1=0.14;
  float y1=0.525;
  TPad *subpad = new TPad("subpad","",
                          x1,y1,
                          x1+canvassize,y1+canvassize);

  subpad->Draw();
  subpad->cd();

  TGraphErrors* hzoom = (TGraphErrors*) gr->Clone("hzoom");
  TGraphErrors* hzoom2 = (TGraphErrors*) gr_eff->Clone("hzoom2");
  TGraphErrors* hzoom3 = (TGraphErrors*) gr_background_eff->Clone("hzoom3");

  hzoom->GetXaxis()->SetTitle("");
  hzoom2->GetXaxis()->SetTitle("");
  hzoom3->GetXaxis()->SetTitle("");

// hzoom->SetLabelSize(xlabelsize*0.7/canvassize,"X");
// hzoom->SetLabelSize(ylabelsize*0.7/canvassize,"Y");

// hzoom2->SetLabelSize(xlabelsize*0.7/canvassize,"X");
// hzoom2->SetLabelSize(ylabelsize*0.7/canvassize,"Y");

// hzoom3->SetLabelSize(xlabelsize*0.7/canvassize,"X");
// hzoom3->SetLabelSize(ylabelsize*0.7/canvassize,"Y");

  if(xmax>xmin)
{
    hzoom->GetXaxis()->SetRangeUser(xmin,xmax);
    hzoom->GetYaxis()->SetRangeUser(ymin,ymax);
}
  hzoom->Draw();
  hzoom2->Draw("same");
  hzoom3->Draw("same");

  c1[k]->Draw("Same");

}

// try to get Histogram from TGraph
//TH1D* h_test;
//h_test = (TGraphErrors*) gr-> GetHistogram(); 
//  TCanvas *c_test = new TCanvas("c_test","",200,10,70,500);
//c_test->cd();
//h_test->Draw("same");


//  TString path_name = "/Users/index0192/13_TeV_Task/Zprime_Electron_channel/plot_SubLedaing_ele_pt_optimize/" ;

//  c1_name = path + c1_name + ".png";
  c1_name = path + c1_name + ".pdf";
  c1[k]->SaveAs(c1_name);

  f_signal->Close();
  delete f_signal;

// save histogram for figure style
  if(save_flag){

        myFile->cd();

	c1[k]->Write();
	gr->Write();
	gr_eff->Write();
	gr_background_eff->Write();
	leg->Write();

//        myFile->Close();

  }//end if



//  delete h_2nd_ele_pT;
  }// loop k Zprime mass points













  // show the 2nd ele pT distribution of different mass points
  // that is another loop

bool the_2nd_ele_pT_varies_mass = false; 
// the_2nd_ele_pT_varies_mass = true;
if( the_2nd_ele_pT_varies_mass ){

  // define used object
  TString c2_name = "2nd_ele_pT_distribuion_of_signal_varies_mass";
  TString c3_name = "2nd_ele_pT_distribuion_of_background_varies_mass";

  TCanvas *c2 = new TCanvas(c2_name,"2nd_ele_pT_distribuion_signal",200,10,700,500);
  TCanvas *c3 = new TCanvas(c3_name,"2nd_ele_pT_distribuion_background",200,10,700,500);
//  TCanvas *c4 = new TCanvas("2nd_ele_pT_distribuion_background_zoom_in","2nd_ele_pT_distribuion_background_zoom_in",200,10,700,500);
  int  colorN = 1;
  int  styleN = 3001;
  TLegend *leg2 = new TLegend(0.4,0.4,0.9,0.8);
  TLegend *leg3 = new TLegend(0.15,0.60,0.65,0.85);
  TLegend *leg4 = new TLegend(0.585,0.3,0.9,0.9);
  TLegend *leg5[N_mass_points];// for input
//  int rebin_times = 16;
//  int rebin_times = 1;
  int rebin_times = 4;

  TCanvas *c5[N_mass_points];

  for(int k=0;k<13;k++){
if( k!= 2 && k!= 7 && k!= 9)continue;
//if( k!= 7 )continue;
//  for(int k=2;k<3;k++){
//continue;

        leg5[k] = new TLegend(0.25,0.75,0.65,0.9);// for input
        TString c5_name = Form("input_signal_and_background_in_Zprime_M-%d",Zprime_mass[k]);
	c5[k] = new TCanvas(c5_name,"input signal and background",200,10,700,500);
	
// First for signal distribution

	// prepare background sample name
        TString signal_shape_file = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);
//        TString signal_shape_file = Form("no_zprime_cut_signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);

	// open the signal histogram
        signal_shape_file = path + signal_shape_file ;
        TFile *f_signal = new TFile (signal_shape_file);

//        TString histo_name= "h_ele_pT" ;
//        TString histo_name= "h_Zprime_mass" ;
        TString histo_name= "h_abs_dEta_ZH" ;
//        TString histo_name= "h_abs_dPhi_ZH" ;
//        TString histo_name= "h_abs_dR_ZH" ;


        TH1D *h_2nd_ele_pT;
        h_2nd_ele_pT = (TH1D*) f_signal -> Get(histo_name);

        TH1D *h_2nd_ele_pT_clone = (TH1D*) h_2nd_ele_pT ->Clone("");// for later be template for background

// Second for background distribution

	// prepare background sample name
        TString background_shape_file[N_background_points];
        for(int l=0 ; l<N_background_points ; l++ ){
        	if(l==0 ){ background_shape_file[l] = Form("background_shape_DYJets_HT100to200_in_Zprime_M-%d.root",Zprime_mass[k]);}
                if(l==1 ){ background_shape_file[l] = Form("background_shape_DYJets_HT200to400_in_Zprime_M-%d.root",Zprime_mass[k]);}
                if(l==2 ){ background_shape_file[l] = Form("background_shape_DYJets_HT400to600_in_Zprime_M-%d.root",Zprime_mass[k]);}
                if(l==3 ){ background_shape_file[l] = Form("background_shape_DYJets_HT600toInf_in_Zprime_M-%d.root",Zprime_mass[k]);}
	}// loop l background shape file 

	TH1D *h_background_2nd_ele_pT_combine = (TH1D*) h_2nd_ele_pT_clone ->Clone("");
	h_background_2nd_ele_pT_combine->Reset();

	// loop background sample, open histogram, weight it, and add together 
        for(int i=0; i<N_background_points;i++){

		// open
                background_shape_file[i] = path + background_shape_file[i];
                TFile *f_background = new TFile ( background_shape_file[i] );
                TH1D *h_background_2nd_ele_pT;
                h_background_2nd_ele_pT = (TH1D*) f_background -> Get(histo_name);

		// weight
		h_background_2nd_ele_pT->Scale( background_weights[i] );

		// add
		h_background_2nd_ele_pT_combine ->Add(h_background_2nd_ele_pT);

        }// loop i background shape file


// Now
// h_2nd_ele_pT is ready for signal
// h_background_2nd_ele_pT_combine is ready for background






	// input signal and background shape
        // c5[k] is the comparison of signal and background input shape

       	// input signal

        TH1D *input_signal = (TH1D*) h_2nd_ele_pT ->Clone("");

        input_signal->Scale( 1/input_signal->Integral() );
        input_signal->SetTitle("2nd electron pT distribution");
        input_signal->SetStats(0);
        input_signal->Rebin(rebin_times);

        double bin_width = input_signal ->GetBinWidth(1);

        // input background

        TH1D *input_background = (TH1D*) h_background_2nd_ele_pT_combine ->Clone("");

        input_background->Scale( 1/input_background->Integral() );
        input_background->Rebin(rebin_times);

	// decide max-x and max-y
	double MaxX=0,MaxY=0; 

	int signal_max_bin=-9;
	double signal_max_content=-99;
        for( int m=1 ; m<= input_signal->GetNbinsX() ;m++ ){
                double bin_content = input_signal->GetBinContent(m);
		// seek the biggest non-zero bin  
                if( bin_content != 0 ){ signal_max_bin = m; }
		if( bin_content >= signal_max_content ){ signal_max_content = bin_content ; }
        }       

        int background_max_bin=-9;
        double background_max_content=-99;
        for( int m=1 ; m<= input_background->GetNbinsX() ;m++ ){
                double bin_content = input_background->GetBinContent(m);
                if( bin_content != 0 ){ background_max_bin = m; }
                if( bin_content >= background_max_content ){ background_max_content = bin_content ; }
        }
	// min non zero bin
        int min_non_zero_bin = -1;
        for( int m=1 ; m<= input_signal ->GetNbinsX() ;m++ ){
                double bin_content = input_signal->GetBinContent(m);
                if( bin_content != 0 ){ min_non_zero_bin = m; break; }
        }

	
	if( signal_max_bin >= background_max_bin ){ MaxX = signal_max_bin; }
	else{ MaxX = background_max_bin;}
//	MaxX = MaxX * rebin_times * 1.1  ;
        MaxX = (MaxX - min_non_zero_bin) * bin_width * 1.1  ;
        input_signal->GetXaxis()->SetRangeUser(0, MaxX );

        if( signal_max_content >= background_max_content ){ MaxY = signal_max_content; }
        else{ MaxY = background_max_content;}
        MaxY = MaxY * 1.1  ;
        input_signal->GetYaxis()->SetRangeUser(0, MaxY );

	// other setting
//	input_signal->GetXaxis()->SetTitle("Sub-leading electron p_{T} [ GeV]");
      input_signal->GetXaxis()->SetTitle("Maximum |  #Delta Rapidity_{ZH} | threshold");
//        input_signal->GetXaxis()->SetTitle("Leading electron p_{T} [ GeV]");
//        input_signal->GetXaxis()->SetTitle("|  #Delta #eta_{ZH} |");
//        input_signal->GetXaxis()->SetTitle("| delta Phi|");
//        input_signal->GetXaxis()->SetTitle("delta R");
        input_signal->GetYaxis()->SetTitle("Arbitrary Unit");
        input_signal ->SetFillColor(2);
	input_signal->SetFillStyle(1001);
 	input_signal ->SetLineColor(2);
        input_background->SetLineColor(4);
	input_background->SetLineWidth(3); 
 	input_signal->SetTitle("");
	input_background->SetTitle("");

	// draw
        c5[k]->cd();
        input_signal -> Draw();
        input_background -> Draw("same");

        TString leg_input_name =  Form("Signal, M_{Z'}=%d GeV",Zprime_mass[k]);
        leg5[k]->AddEntry( input_signal ,leg_input_name ,"lf");
        leg_input_name = "DY+jets";
        leg5[k]->AddEntry( input_background ,leg_input_name ,"lf");
        leg5[k]->SetFillStyle(0);
//        leg5[k]->SetFillColor(2);
        leg5[k]->Draw();

  //TLatex test
   TLatex *lar = new TLatex(0.13, 0.94, "CMS");
   lar->SetNDC(kTRUE);
   lar->SetTextSize(0.050);
   lar->SetTextFont(62);
   lar->SetLineWidth(5);
   lar->Draw("");
 
   TLatex *lar2 = new TLatex(0.25, 0.94, "Simulation");
   lar2->SetNDC(kTRUE);
   lar2->SetTextSize(0.050);
   lar2->SetTextFont(52);
   lar2->SetLineWidth(5);
   lar2->Draw("");

  // zoom in test

//  float xmin= 150 ;
//  float xmax= 250 ;
//  twopads( input_signal,  xmin,  xmax);
//  twopads( input_signal, input_background ,  xmin,  xmax);


	//save
//        TString input_save_name =  Form("input_in_Zprime_mass_%d.png",Zprime_mass[k]);
         TString input_save_name =  Form("input_in_Zprime_mass_%d.pdf",Zprime_mass[k]);
        input_save_name = path + input_save_name ;
        c5[k]->SaveAs(input_save_name);

	//name setting
	TString h_name1 = Form("signal_abs_dEta_in_M_{Z'}=%d_GeV", Zprime_mass[k] );
        TString h_name2 = Form("background_abs_dEta_in_M_{Z'}=%d_GeV", Zprime_mass[k] );
        TString leg5_name = Form("leg_for_abs_dEta_in_M_{Z'}=%d_GeV", Zprime_mass[k] );
 
        input_signal->SetName(h_name1);
        input_background->SetName(h_name2);
        leg5[k]->SetName(leg5_name);

// save histogram for figure style
  if(save_flag){

        myFile->cd();

	c5[k]->Write();
	input_signal->Write();
	input_background->Write();
	leg5[k]->Write();

//        myFile->Close();

  }//end if


//        input_signal ->SetFillColor(2);
//         input_signal->SetFillStyle(1001);
//         input_signal ->SetLineColor(2);
//         input_background->SetLineColor(4);
//         input_background->SetLineWidth(3);


	

	// signal shape varies with mass
        // c2 is signal distribution varies with mass
        TH1D *h_signal_varies_mass = (TH1D*) h_2nd_ele_pT ->Clone("");

        h_signal_varies_mass->Scale( 1/h_signal_varies_mass->Integral() );
//        h_signal_varies_mass->SetTitle("2nd electron pT distribution");
        h_signal_varies_mass->SetTitle("");
        h_signal_varies_mass->SetStats(0);

        if( k==0){colorN = kRed;}
        else if( k==3){colorN = kOrange;}
        else if( k==6){colorN = kYellow;}
        else if( k==9){colorN = kCyan;}

        h_signal_varies_mass->SetLineColor(colorN);
	h_signal_varies_mass->SetLineWidth(3);
	h_signal_varies_mass->SetFillColor(colorN);
	h_signal_varies_mass->SetFillStyle(styleN);

//        h_signal_varies_mass->GetXaxis()->SetTitle("Sub-leading electron p_{T} [ GeV]");
        h_signal_varies_mass->GetXaxis()->SetTitle("Maximum |  #Delta Rapidity_{ZH} | threshold");
//        h_signal_varies_mass->GetXaxis()->SetTitle("| delta eta |");
        h_signal_varies_mass->Rebin(rebin_times);
//	h_signal_varies_mass->GetXaxis()->SetRangeUser(0, 4.0);

	double X_up_range = 5;
	double Y_up_range_signal = 0.2;
        double Y_up_range_background = 0.2;

        h_signal_varies_mass->GetXaxis()->SetRangeUser(0,X_up_range);
        h_signal_varies_mass->GetYaxis()->SetRangeUser(0, Y_up_range_signal);

        c2->cd();
        if(k==0){h_signal_varies_mass -> Draw(); h_signal_varies_mass->GetXaxis()->SetRangeUser(0, 1250);}
        else {

		h_signal_varies_mass -> Draw("same");
	     }

        TString leg_singal_name =  Form("signal in Z' mass= %d",Zprime_mass[k]);
        leg2->AddEntry( h_signal_varies_mass ,leg_singal_name ,"lf");
        leg2->SetFillStyle(0);
        leg2->Draw();

   lar->Draw("");
   lar2->Draw("");



	// background shape varies with mass
        // c3 is background distribution varies with mass 
        TH1D *h_background_varies_mass = (TH1D*) h_background_2nd_ele_pT_combine ->Clone("");

        h_background_varies_mass->Scale( 1/h_background_varies_mass->Integral() );
        h_background_varies_mass->SetTitle("2nd electron pT distribution");
        h_background_varies_mass->SetTitle("");
        h_background_varies_mass->SetStats(0);

        h_background_varies_mass->SetLineColor(colorN);
        h_background_varies_mass->SetLineWidth(3);
        h_background_varies_mass->SetFillColor(colorN);
        h_background_varies_mass->SetFillStyle(styleN);


        h_background_varies_mass->SetLineColor(colorN);
        colorN = colorN + 1;// afer used in signal and background color+1
	styleN = styleN + 5;

        h_background_varies_mass->Rebin(rebin_times);
//        h_background_varies_mass->GetXaxis()->SetTitle("Sub-leading electron p_{T} [GeV]");
        h_background_varies_mass->GetXaxis()->SetTitle("Maximum |  #Delta Rapidity_{ZH} | threshold");
//        h_background_varies_mass->GetXaxis()->SetTitle("| delta eta |");

//        h_background_varies_mass->GetXaxis()->SetRangeUser(0, 4.0);
        h_background_varies_mass->GetXaxis()->SetRangeUser(0, X_up_range);
        h_background_varies_mass->GetYaxis()->SetRangeUser(0, Y_up_range_background);

        c3->cd();
        if(k==0){
                h_background_varies_mass->GetXaxis()->SetRangeUser(0, 1250);   
                h_background_varies_mass->GetYaxis()->SetRangeUser(0, 1); 
                h_background_varies_mass -> Draw(); 
                }
        else { h_background_varies_mass -> Draw("same");}

        TString leg_background_name =  Form("background in Z' mass= %d",Zprime_mass[k]);
        leg3->AddEntry( h_background_varies_mass ,leg_background_name ,"lf");
        leg3->SetFillStyle(0);
        leg3->Draw();

   lar->Draw("");
   lar2->Draw("");



  }// loop k Zprime mass point


//c2_name = path + c2_name + ".png";
//c3_name = path + c3_name + ".png";
c2_name = path + c2_name + ".pdf";
c3_name = path + c3_name + ".pdf";

c2->cd();
c2->SaveAs(c2_name);

c3->cd();
c3->SaveAs(c3_name);



}// end if




  // combine the 4 background shape to get the Zprime mass distribution 

bool Zprime_mass_combined_background = false;
//Zprime_mass_combined_background = true;
if(Zprime_mass_combined_background)
  {     // Zprime_mass[0] is M = 600 

	// prepare the background sample name
        TString background_shape_file[N_background_points];
        for(int l=0 ; l<N_background_points ; l++ ){
                if(l==0 ){ background_shape_file[l] = Form("no_zprime_cut_background_shape_DYJets_HT100to200_in_Zprime_M-%d.root",Zprime_mass[0]);}
                if(l==1 ){ background_shape_file[l] = Form("no_zprime_cut_background_shape_DYJets_HT200to400_in_Zprime_M-%d.root",Zprime_mass[0]);}
                if(l==2 ){ background_shape_file[l] = Form("no_zprime_cut_background_shape_DYJets_HT400to600_in_Zprime_M-%d.root",Zprime_mass[0]);}
                if(l==3 ){ background_shape_file[l] = Form("no_zprime_cut_background_shape_DYJets_HT600toInf_in_Zprime_M-%d.root",Zprime_mass[0]);}
        }// loop l background shape file 

	// prepare a template histogram and reset it 
        TString template_name = path + background_shape_file[0] ;
        TFile *f_template = new TFile ( template_name );
        TString histo_name= "h_Zprime_mass" ;
        TH1D *h_template;
        h_template = (TH1D*) f_template -> Get(histo_name);

        TH1D *h_background_2nd_ele_pT_combine = (TH1D*) h_template ->Clone("");
        h_background_2nd_ele_pT_combine->Reset();

	// loop background sample, open, weight, and add
        for(int i=0; i<N_background_points;i++){

		// open
                background_shape_file[i] = path + background_shape_file[i];
                TFile *f_background = new TFile ( background_shape_file[i] );
                TH1D *h_background_2nd_ele_pT;
                h_background_2nd_ele_pT = (TH1D*) f_background -> Get(histo_name);

		// weight
		h_background_2nd_ele_pT->Scale(background_weights[i]  );

		// add
                h_background_2nd_ele_pT_combine ->Add(h_background_2nd_ele_pT);
        }// loop i background shape file

        TCanvas *c6 = new TCanvas("background_Zprime_mass","",200,10,700,500);
	c6->cd();
	h_background_2nd_ele_pT_combine->Rebin(8);
	h_background_2nd_ele_pT_combine->Draw();

  }// end if


}


double uncertainty_calculate( double pass, double total)
{
double fail = total - pass;

double uncertainty = sqrt(pass*fail*(pass+fail))/pow(pass+fail,2);

return uncertainty;
}



