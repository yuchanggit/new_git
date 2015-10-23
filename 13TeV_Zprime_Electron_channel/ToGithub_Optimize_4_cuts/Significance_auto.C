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
#include <vector>


using namespace std;

double uncertainty_calculate( double , double );


void Significance_auto(){


int variable_flag=-1; 

//variable_flag=1; // 1st ele pt
//variable_flag=2; // 2nd ele pt
//variable_flag=3; // dEta
//variable_flag=4; // dRapidity

// to draw all figures automatically
for(int v=1;v<=4;v++){
//if(v!=)continue;

variable_flag= v;



TString histo_name;
TString figure_path ;

	     if (variable_flag==1){ histo_name= "h_ele_1st_pT" ;       figure_path="plot_1st_pt/";}
	else if (variable_flag==2){ histo_name= "h_ele_2nd_pT" ;       figure_path="plot_2nd_pt/";}
	else if (variable_flag==3){ histo_name= "h_abs_dEta_ZH" ;      figure_path="plot_dEta/";}
	else if (variable_flag==4){ histo_name= "h_abs_dRapidity_ZH" ; figure_path="plot_dRapidity/";}


cout<<"variable_flag:"<< variable_flag <<endl;
cout<<"histo_name: "<< histo_name <<endl;


//set NCU figure style
bool gridOn = true;
setNCUStyle(gridOn);
// additional_style();


double LabelSize = 0.04;
double TitleSize = 0.04;
double TitleFont = 42;
double TitleOffset = 1.3;


 //  prepare the weights for 4 background samples

const int N_background_points = 4;
//double background_cross_section[N_background_points] = { 139.4 , 42.75 , 5.497 , 2.21 };
double background_cross_section[N_background_points] = { 171.462 , 52.5825 , 6.76131 , 2.7183 };// times the K=1.23
//double background_number_of_events[N_background_points] = { 2377497 , 955972 , 1048047 , 987977 };
double background_number_of_events[N_background_points] =   { 2327916 , 955972 , 1038512 , 974623 };
double background_weights[N_background_points];

for(int i=0;i<N_background_points;i++) 
{

 background_weights[i] = background_cross_section[i] / background_number_of_events[i];  

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



 // define vector to save the [best cut]/[no cut] [significance]/[sig eff]/[bkg eff]  and their error  



    vector<double> Mass_Point;
    vector<double> Mass_Point_error;// set to zero

    vector<double> significance_best_cut;
    vector<double> significance_error_best_cut;
    vector<double> signal_eff_best_cut;
    vector<double> signal_eff_error_best_cut;
    vector<double> background_eff_best_cut;
    vector<double> background_eff_error_best_cut;

    vector<double> significance_no_cut;
    vector<double> significance_error_no_cut;



/*    vector<double> Mass_Point;
    vector<double> Mass_Point_error;// set to zero

    vector<double> significance_best_cut;
    vector<double> significance_error_best_cut;
    vector<double> signal_eff_best_cut;
    vector<double> signal_eff_error_best_cut;
    vector<double> background_eff_best_cut;
    vector<double> background_eff_error_best_cut;

    vector<double> significance_no_cut;
    vector<double> significance_error_no_cut;
*/
//    vector<double> signal_eff_no_cut;
//    vector<double> signal_eff_error_no_cut;
//    vector<double> background_eff_no_cut;
//    vector<double> background_eff_error_no_cut;


  // now calulate the significance

  // loop in k, which mass point you want to know its Significance

  for(int k=0 ; k<N_mass_points ; k++){
//if( k!= 2 && k!= 7 && k!= 9)continue;
//if( k !=2 )continue;
//continue;

	// c1 name	
  	cout<< "Zprime_mass[k]: " << Zprime_mass[k] << endl;
	Mass_Point.push_back(Zprime_mass[k]);// save mass points
	Mass_Point_error.push_back(0);//set to zero
	c1_name  = Form("Significance_and_efficiency_for_Zprme_M_%d", Zprime_mass[k] );
//        c1_name_zoom_in  = Form("Significance_and_efficiency_for_Zprme_M_%d_zoom_in", Zprime_mass[k] );
// 	c1_zoom_in[k] = new TCanvas(c1_name_zoom_in,"",600,600);
        c1[k] = new TCanvas(c1_name,"Significance in different cut value",200,10,700,500);

	// open the signal ROOT file
  	TString signal_shape_file = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);
  	signal_shape_file = path + signal_shape_file ;
  	TFile *f_signal = new TFile (signal_shape_file);

	// open the signal histogram
//  	TString histo_name= "h_ele_2nd_pT" ;
//        TString histo_name= "h_abs_dEta_ZH" ;
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
//        double scan_width = 0.05;
//        double scan_width = 0.5;
//	scan_width = 100;

        // input the lowest cut value
//      int lowest_cut = 35; // for sub-leading electron pt
//        int lowest_cut = 10;
//        int lowest_cut = 35; // for leading electron pt 
//        double lowest_cut = 0; // for |dEta| and |d Rapidity| 
        double lowest_cut = 999;
	double first_bin_value = -999;
        double scan_width = 999;

             if (variable_flag==1){ lowest_cut=115 ; first_bin_value = 0;  scan_width = 5;}
        else if (variable_flag==2){ lowest_cut=35 ;  first_bin_value = 0;  scan_width = 5;}
        else if (variable_flag==3){ lowest_cut=0 ;   first_bin_value =-1;  scan_width = 0.05;}
        else if (variable_flag==4){ lowest_cut=0 ;   first_bin_value =-1;  scan_width = 0.05;}


//        int first_bin_value = 0;// the lower bound of histogram




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

	double legx1,legy1,legx2,legy2;

             if (variable_flag==1){ legx1=0.6; legy1=0.35; legx2=0.99; legy2=0.5; }
        else if (variable_flag==2){ legx1=0.6; legy1=0.3; legx2=0.99; legy2=0.5; }
        else if (variable_flag==3){ legx1=0.5; legy1=0.6; legx2=0.99; legy2=0.8; }
        else if (variable_flag==4){ legx1=0.5; legy1=0.6; legx2=0.99; legy2=0.8; }

  	TLegend *leg=new TLegend(legx1,legy1,legx2,legy2);
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
				cout<<"open background: "<< background_shape_file[i] << endl;
                		background_shape_file[i] = path + background_shape_file[i];
                		TFile *f_background = new TFile ( background_shape_file[i] );
                		TH1D *h_background_2nd_ele_pT;
                		h_background_2nd_ele_pT = (TH1D*) f_background -> Get(histo_name);
				double background_number_event =0;
				background_number_event = h_background_2nd_ele_pT->Integral();
				cout<<"background_number_event: "<< background_number_event << endl;

                		// weight
                                h_background_2nd_ele_pT->Sumw2();
          		      	h_background_2nd_ele_pT->Scale( background_weights[i] );
                                background_number_event = h_background_2nd_ele_pT->Integral();
                                cout<<"background_number_event after weight: "<< background_number_event << endl;



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

				int FirstBinForCut; int LastBinForCut; int mode; int FirstBinForTotal; int LastBinForTotal;


                                if (variable_flag==1 || variable_flag==2){ 
                                   FirstBinForCut = (cut_points[i] - lowest_cut)/bin_width + min_bin -1   ;
                                   LastBinForCut =  -1     ;
                                   mode = 0;
                                   FirstBinForTotal = min_bin -1  ;
                                   LastBinForTotal = -1;
				}

                                if (variable_flag==3 || variable_flag==4){
                                   FirstBinForCut = min_bin -2    ;
                                   LastBinForCut = (cut_points[i] - lowest_cut)/bin_width + min_bin -1 ;
                                   mode = 0;
                                   FirstBinForTotal = min_bin -2  ;
                                   LastBinForTotal = -1;
                                }



/*                                int FirstBinForCut = (cut_points[i] - lowest_cut)/bin_width + min_bin -1   ;
                                cout<< "FirstBinForCut: "<< FirstBinForCut <<endl;
                                int LastBinForCut =  -1     ;
                                cout<< "LastBinForCut: "<< LastBinForCut <<endl;

                                int mode = 0;
                                int FirstBinForTotal = min_bin -1  ;
                                int LastBinForTotal = -1;
*/


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

  // save the best cut value
  significance_best_cut.push_back(         vy_significance[        hightest_bin  ] );
  significance_error_best_cut.push_back(   vy_significance_erry[   hightest_bin  ] );
  signal_eff_best_cut.push_back(           vy_sig_eff[             hightest_bin  ] );
  signal_eff_error_best_cut.push_back(     vy_sig_eff_erry[        hightest_bin  ] );
  background_eff_best_cut.push_back(       vy_background_eff[      hightest_bin  ] );
  background_eff_error_best_cut.push_back( vy_background_eff_erry[ hightest_bin  ] );

  significance_no_cut.push_back(        sig_noCut      );
  significance_error_no_cut.push_back(  sig_err_NoCut  );


  // cout 
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

  TString gr_x_label;
  double gr_x_UpBound;

  if (variable_flag==1){ gr_x_label = "Minimum p_{T} threshold of leading electron [ GeV]";    gr_x_UpBound=1.1;  }  
  if (variable_flag==2){ gr_x_label = "Minimum p_{T} threshold of sub-leading electron [ GeV]";gr_x_UpBound=1.1;  }
  if (variable_flag==3){ gr_x_label = "Maximum |  #Delta #eta_{ZH} | threshold";               gr_x_UpBound=2.0;  }
  if (variable_flag==4){ gr_x_label = "Maximum |  #Delta Rapidity_{ZH} | threshold";           gr_x_UpBound=2.0;  }

  gr->GetXaxis()->SetTitle(gr_x_label);
  gr->GetYaxis()->SetRangeUser(0, gr_x_UpBound);
  gr->SetTitle(c1_title);

  gr->GetXaxis()->SetLabelSize(LabelSize);
  gr->GetXaxis()->SetTitleSize(TitleSize);
  gr->GetXaxis()->SetTitleFont(TitleFont);
  gr->GetXaxis()->SetTitleOffset(TitleOffset);

  gr->GetYaxis()->SetLabelSize(LabelSize);
  gr->GetYaxis()->SetTitleSize(TitleSize);
  gr->GetYaxis()->SetTitleFont(TitleFont);
  gr->GetYaxis()->SetTitleOffset(TitleOffset);


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

  float xmin=-99 ;
  float xmax=-99 ;
  float ymin=-99 ;
  float ymax=-99 ;

if (variable_flag==1){
  if(k==2){xmin=150; xmax=250 ; ymin=0.34 ; ymax=0.42 ;}
  if(k==7){xmin=300; xmax=500 ; ymin=0.6 ; ymax=0.8 ;}
  if(k==9){xmin=300; xmax=600 ; ymin=0.8 ; ymax=1.0 ;}
}

if (variable_flag==2){
  if(k==2){xmin=30; xmax=100 ; ymin=0.34 ; ymax=0.40 ;}
  if(k==7){xmin=50; xmax=150 ; ymin=0.61 ; ymax=0.69 ;}
  if(k==9){xmin=60; xmax=180 ; ymin=0.78 ; ymax=0.90 ;}
}

if (variable_flag==3 || variable_flag==4){
  if(k==2){xmin=1.3; xmax=1.8 ; ymin=0.35 ; ymax=0.39 ;}
  if(k==7){xmin=1.6; xmax=2.6 ; ymin=0.67 ; ymax=0.77 ;}
  if(k==9){xmin=2.4; xmax=3.4 ; ymin=0.85 ; ymax=0.95 ;}
}


bool two_pad_flag = false;
two_pad_flag = true;
if(two_pad_flag){

  c1[k]->cd();

  float canvassize;
  float x1;
  float y1;

  if (variable_flag==1 || variable_flag==2){ canvassize=0.4 ; x1=0.55; y1=0.50;}
  if (variable_flag==3 || variable_flag==4){ canvassize=0.35 ; x1=0.14; y1=0.525;}

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
  c1_name = figure_path + c1_name + ".pdf";
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

        myFile->Close();
	delete myFile;
  }//end if



//  delete h_2nd_ele_pT;
  }// loop k Zprime mass points









  // best cut and no cut comaprison
  const int N_Point = Mass_Point.size();

  double Mass_Point_A[N_Point];// Array
  double Mass_Point_error_A[N_Point];
  double significance_best_cut_A[N_Point];
  double significance_error_best_cut_A[N_Point];
  double signal_eff_best_cut_A[N_Point];
  double signal_eff_error_best_cut_A[N_Point];
  double background_eff_best_cut_A[N_Point];
  double background_eff_error_best_cut_A[N_Point];
  double significance_no_cut_A[N_Point];
  double significance_error_no_cut_A[N_Point];

  double significance_best_cut_to_no_cut_ratio_A[N_Point];

  // test the saved best cut value
  for(int i=0; i<Mass_Point.size();i++ ){
/*
	cout<<"i: "<<i<<endl;
	cout<<"Mass_Point[i]: "<<			Mass_Point[i] <<endl;
        cout<<"significance_best_cut[i]: "<<		significance_best_cut[i] <<endl;
        cout<<"significance_error_best_cut[i]: "<<	significance_error_best_cut[i] <<endl;
        cout<<"signal_eff_best_cut[i]: "<<		signal_eff_best_cut[i] <<endl;
        cout<<"signal_eff_error_best_cut[i]: "<<	signal_eff_error_best_cut[i] <<endl;
        cout<<"background_eff_best_cut[i]: "<<		background_eff_best_cut[i] <<endl;
        cout<<"background_eff_error_best_cut[i]: "<<	background_eff_error_best_cut[i] <<endl;
        cout<<"significance_no_cut[i]: "<<		significance_no_cut[i] <<endl;
        cout<<"significance_error_no_cut[i]: "<< 	significance_error_no_cut[i]<<endl;
*/

  // transform vector to array

  Mass_Point_A[i]=Mass_Point[i]; 
  significance_best_cut_A[i] =significance_best_cut[i];
  Mass_Point_error_A[i]= Mass_Point_error[i];
  significance_error_best_cut_A[i]= significance_error_best_cut[i];

  signal_eff_best_cut_A[i]=signal_eff_best_cut[i];
  signal_eff_error_best_cut_A[i]=signal_eff_error_best_cut[i];

  background_eff_best_cut_A[i]=background_eff_best_cut[i];
  background_eff_error_best_cut_A[i]=background_eff_error_best_cut[i];

  significance_no_cut_A[i]=significance_no_cut[i];
  significance_error_no_cut_A[i]=significance_error_no_cut[i];

  significance_best_cut_to_no_cut_ratio_A[i] = significance_best_cut_A[i]/significance_no_cut_A[i];

  }





  //TGraphErrors for best cut 
  TGraphErrors *gr_best_cut_significance = new TGraphErrors( N_Point  ,Mass_Point_A  , significance_best_cut_A , Mass_Point_error_A  ,significance_error_best_cut_A  );
  TGraphErrors *gr_best_cut_signal_eff = new TGraphErrors( N_Point  ,Mass_Point_A  , signal_eff_best_cut_A , Mass_Point_error_A  , signal_eff_error_best_cut_A );
  TGraphErrors *gr_best_cut_background_eff  = new TGraphErrors( N_Point  ,Mass_Point_A  , background_eff_best_cut_A , Mass_Point_error_A  ,background_eff_error_best_cut_A  );

  // draw setting
  gr_best_cut_significance->GetYaxis()->SetRangeUser(0, 1.1);
  gr_best_cut_significance->SetTitle("best cut significance and efficiency");
  gr_best_cut_significance->GetXaxis()->SetTitle(" M_{Z'} ");

  gr_best_cut_significance->GetXaxis()->SetLabelSize(LabelSize);
  gr_best_cut_significance->GetXaxis()->SetTitleSize(TitleSize);
  gr_best_cut_significance->GetXaxis()->SetTitleFont(TitleFont);
  gr_best_cut_significance->GetXaxis()->SetTitleOffset(TitleOffset);

  gr_best_cut_significance->GetYaxis()->SetLabelSize(LabelSize);
  gr_best_cut_significance->GetYaxis()->SetTitleSize(TitleSize);
  gr_best_cut_significance->GetYaxis()->SetTitleFont(TitleFont);
  gr_best_cut_significance->GetYaxis()->SetTitleOffset(TitleOffset);

  gr_best_cut_significance->SetLineColor(2);
  gr_best_cut_signal_eff->SetLineColor(kBlue);
  gr_best_cut_background_eff->SetLineColor(kGreen+2);

  gr_best_cut_significance->SetLineStyle(1);
  gr_best_cut_signal_eff->SetLineStyle(1);
  gr_best_cut_background_eff->SetLineStyle(1);

  gr_best_cut_significance->SetLineWidth(3);
  gr_best_cut_signal_eff->SetLineWidth(3);
  gr_best_cut_background_eff->SetLineWidth(3);

  gr_best_cut_significance->SetMarkerColor(2);
  gr_best_cut_signal_eff->SetMarkerColor(kBlue);
  gr_best_cut_background_eff->SetMarkerColor(kGreen+2);

  gr_best_cut_significance->SetMarkerStyle(4);
  gr_best_cut_signal_eff->SetMarkerStyle(5);
  gr_best_cut_background_eff->SetMarkerStyle(8);

  gr_best_cut_significance->SetMarkerSize(1);
  gr_best_cut_signal_eff->SetMarkerSize(1);
  gr_best_cut_background_eff->SetMarkerSize(1);

  //legend
  TLegend *leg_best_cut=new TLegend(0.2,0.15,0.59,0.35);
  leg_best_cut->AddEntry( gr_best_cut_significance ,"significance"  ,"pl");
  leg_best_cut->AddEntry( gr_best_cut_signal_eff ,"signal efficiency"  ,"pl");
  leg_best_cut->AddEntry( gr_best_cut_background_eff ,"background efficiency"  ,"pl");
  leg_best_cut->SetFillStyle(0);

{
  //TLatex test
  TLatex *lar = new TLatex(0.13, 0.94, "CMS");
  lar->SetNDC(kTRUE);
  lar->SetTextSize(0.050);
  lar->SetTextFont(62);
  lar->SetLineWidth(5);

  TLatex *lar2 = new TLatex(0.25, 0.94, "Simulation");
  lar2->SetNDC(kTRUE);
  lar2->SetTextSize(0.050);
  lar2->SetTextFont(52);
  lar2->SetLineWidth(5);

  TLatex *lar3 = new TLatex(0.45, 0.94, "Best Cut Significance and Efficiency" );
  lar3->SetNDC(kTRUE);
  lar3->SetTextSize(0.050);
  lar3->SetTextFont(52);
  lar3->SetLineWidth(5);

  // draw
  TCanvas *c7 = new TCanvas("c7","c7",200,10,700,500);

  c7->cd();

  gr_best_cut_significance ->Draw("ALP");
  gr_best_cut_signal_eff->Draw("same lp");
  gr_best_cut_background_eff->Draw("same lp");

  leg_best_cut->Draw();

  lar->Draw("");
  lar2->Draw("");
  lar3->Draw("");

  TString c7_name = "best_cut_significance_and_efficiency";
  c7_name = figure_path + c7_name + ".pdf";

  c7->SaveAs(c7_name);

}


  //TGraph for ratio 
  TGraph *gr_ratio = new TGraph( N_Point  ,Mass_Point_A  , significance_best_cut_to_no_cut_ratio_A  );

  // draw setting
gr_ratio->GetYaxis()->SetRangeUser(0.90, 1.2);
gr_ratio->SetTitle("best cut to no cut ratio");
gr_ratio->GetXaxis()->SetTitle(" M_{Z'} ");

gr_ratio->GetXaxis()->SetLabelSize(LabelSize);
gr_ratio->GetXaxis()->SetTitleSize(TitleSize);
gr_ratio->GetXaxis()->SetTitleFont(TitleFont);
gr_ratio->GetXaxis()->SetTitleOffset(TitleOffset);

gr_ratio->GetYaxis()->SetLabelSize(LabelSize);
gr_ratio->GetYaxis()->SetTitleSize(TitleSize);
gr_ratio->GetYaxis()->SetTitleFont(TitleFont);
gr_ratio->GetYaxis()->SetTitleOffset(TitleOffset);


gr_ratio->SetLineColor(2);
gr_ratio->SetLineStyle(1);
gr_ratio->SetLineWidth(3);
gr_ratio->SetMarkerColor(2);
gr_ratio->SetMarkerStyle(4);
gr_ratio->SetMarkerSize(1);

  //legend
  TLegend *leg_ratio=new TLegend(0.3,0.20,0.69,0.50);
  leg_ratio->AddEntry( gr_ratio ,"significance ratio"  ,"pl");
  leg_ratio->SetFillStyle(0);

{
  //TLatex test
  TLatex *lar = new TLatex(0.13, 0.94, "CMS");
  lar->SetNDC(kTRUE);
  lar->SetTextSize(0.050);
  lar->SetTextFont(62);
  lar->SetLineWidth(5);

  TLatex *lar2 = new TLatex(0.25, 0.94, "Simulation");
  lar2->SetNDC(kTRUE);
  lar2->SetTextSize(0.050);
  lar2->SetTextFont(52);
  lar2->SetLineWidth(5);

  TLatex *lar3 = new TLatex(0.45, 0.94, "Ratio of Best Cut to No Cut" );
  lar3->SetNDC(kTRUE);
  lar3->SetTextSize(0.050);
  lar3->SetTextFont(52);
  lar3->SetLineWidth(5);


  // draw
  TCanvas *c8 = new TCanvas("c8","c8",200,10,700,500);

  c8->cd();

  gr_ratio ->Draw("ALP");

  leg_ratio->Draw();

  lar->Draw("");
  lar2->Draw("");
  lar3->Draw("");

  TString c8_name = "significance_ratio_of_best_cut_to_no_cut";
  c8_name = figure_path + c8_name + ".pdf";

  c8->SaveAs(c8_name);

}











  // show the 2nd ele pT distribution of different mass points
  // that is another loop

bool the_2nd_ele_pT_varies_mass = false; 
// the_2nd_ele_pT_varies_mass = true;
if( the_2nd_ele_pT_varies_mass ){




TString input_signal_x_title; 
//double input_signal_x_UpBound;
//double input_signal_y_UpBound;
double input_leg_x1,input_leg_y1,input_leg_x2,input_leg_y2;
double distri_x_UpBound;
double distri_y_signal_UpBound;
double distri_y_background_UpBound;
double sig_leg_x1,sig_leg_y1,sig_leg_x2,sig_leg_y2;
double bkg_leg_x1,bkg_leg_y1,bkg_leg_x2,bkg_leg_y2;
  int rebin_times;

  if (variable_flag==1){

input_signal_x_title="Leading electron p_{T} [ GeV ]";
input_leg_x1=0.5 ; input_leg_y1=0.75 ; input_leg_x2=0.9 ; input_leg_y2=0.9 ;
distri_x_UpBound=1600;
distri_y_signal_UpBound=0.12;
distri_y_background_UpBound=0.15;
sig_leg_x1=.4 ;sig_leg_y1=.5 ;sig_leg_x2=.9 ;sig_leg_y2=.9 ; 
bkg_leg_x1=.4 ;bkg_leg_y1=.5 ;bkg_leg_x2=.9 ;bkg_leg_y2=.9 ;
rebin_times =16;
   }

  if (variable_flag==2){ 
 
input_signal_x_title="Sub-leading electron p_{T} [ GeV ]";
input_leg_x1=0.5 ; input_leg_y1=0.75 ; input_leg_x2=0.9 ; input_leg_y2=0.9 ;
distri_x_UpBound=810;
distri_y_signal_UpBound=.12;
distri_y_background_UpBound=.26;
sig_leg_x1=.4 ;sig_leg_y1=.5 ;sig_leg_x2=.9 ;sig_leg_y2=.9 ;
bkg_leg_x1=.4 ;bkg_leg_y1=.5 ;bkg_leg_x2=.9 ;bkg_leg_y2=.9 ;
rebin_times =16;
   }

  if (variable_flag==3){ 
 
input_signal_x_title="Maximum |  #Delta #eta_{ZH} | threshold";
input_leg_x1=.25 ; input_leg_y1=.75 ; input_leg_x2=.65 ; input_leg_y2=.9 ;
distri_x_UpBound=5;
distri_y_signal_UpBound=.2;
distri_y_background_UpBound=.2;
sig_leg_x1=.4 ;sig_leg_y1=.4 ;sig_leg_x2=.9;sig_leg_y2=.8 ; 
bkg_leg_x1=.15 ;bkg_leg_y1=.60 ;bkg_leg_x2=.65 ;bkg_leg_y2=.85 ;
rebin_times =4;
   }

  if (variable_flag==4){ 
input_signal_x_title="Maximum |  #Delta Rapidity_{ZH} | threshold";
input_leg_x1=.25 ; input_leg_y1=.75 ; input_leg_x2=.65 ; input_leg_y2=.9 ;
distri_x_UpBound=5;
distri_y_signal_UpBound=.2;
distri_y_background_UpBound=.2;
sig_leg_x1=.4 ;sig_leg_y1=.4 ;sig_leg_x2=.9;sig_leg_y2=.8 ;
bkg_leg_x1=.15 ;bkg_leg_y1=.60 ;bkg_leg_x2=.65 ;bkg_leg_y2=.85 ;
rebin_times =4;
   }



  // define used object
  TString c2_name = "2nd_ele_pT_distribuion_of_signal_varies_mass";
  TString c3_name = "2nd_ele_pT_distribuion_of_background_varies_mass";

  TCanvas *c2 = new TCanvas(c2_name,"2nd_ele_pT_distribuion_signal",200,10,700,500);
  TCanvas *c3 = new TCanvas(c3_name,"2nd_ele_pT_distribuion_background",200,10,700,500);
//  TCanvas *c4 = new TCanvas("2nd_ele_pT_distribuion_background_zoom_in","2nd_ele_pT_distribuion_background_zoom_in",200,10,700,500);
  int  colorN = 1;
  int  styleN = 3001;
  TLegend *leg2 = new TLegend(sig_leg_x1,sig_leg_y1,sig_leg_x2,sig_leg_y2);// sig distri
  TLegend *leg3 = new TLegend(bkg_leg_x1,bkg_leg_y1,bkg_leg_x2,bkg_leg_y2);// bkg distri
  TLegend *leg4 = new TLegend(0.585,0.3,0.9,0.9);
  TLegend *leg5[N_mass_points];// for input
//  int rebin_times = 16;
//  int rebin_times = 1;
//  int rebin_times = 4;

  TCanvas *c5[N_mass_points];

  for(int k=0;k<13;k++){
if( k!= 2 && k!= 7 && k!= 9)continue;
//if( k!= 7 )continue;
//  for(int k=2;k<3;k++){
//continue;

        leg5[k] = new TLegend(input_leg_x1,input_leg_y1,input_leg_x2,input_leg_y2);// for input
        TString c5_name = Form("input_signal_and_background_in_Zprime_M-%d",Zprime_mass[k]);
	c5[k] = new TCanvas(c5_name,"input signal and background",200,10,700,500);
	
// First for signal distribution

	// prepare background sample name
        TString signal_shape_file = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);
//        TString signal_shape_file = Form("no_zprime_cut_signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);

	// open the signal histogram
        signal_shape_file = path + signal_shape_file ;
        TFile *f_signal = new TFile (signal_shape_file);

//        TString histo_name= "h_ele_2nd_pT" ;
//        TString histo_name= "h_Zprime_mass" ;
//        TString histo_name= "h_abs_dEta_ZH" ;
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

                        f_background->Close();
                        delete f_background;

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

	input_signal->GetXaxis()->SetLabelSize(LabelSize);
	input_signal->GetXaxis()->SetTitleSize(TitleSize);
	input_signal->GetXaxis()->SetTitleFont(TitleFont);
	input_signal->GetXaxis()->SetTitleOffset(TitleOffset);

        input_signal->GetYaxis()->SetLabelSize(LabelSize);
        input_signal->GetYaxis()->SetTitleSize(TitleSize);
        input_signal->GetYaxis()->SetTitleFont(TitleFont);
        input_signal->GetYaxis()->SetTitleOffset(TitleOffset);

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
      input_signal->GetXaxis()->SetTitle(input_signal_x_title);
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
        input_save_name = figure_path + input_save_name ;
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

        h_signal_varies_mass->GetXaxis()->SetLabelSize(LabelSize);
        h_signal_varies_mass->GetXaxis()->SetTitleSize(TitleSize);
        h_signal_varies_mass->GetXaxis()->SetTitleFont(TitleFont);
        h_signal_varies_mass->GetXaxis()->SetTitleOffset(TitleOffset);

        h_signal_varies_mass->GetYaxis()->SetLabelSize(LabelSize);
        h_signal_varies_mass->GetYaxis()->SetTitleSize(TitleSize);
        h_signal_varies_mass->GetYaxis()->SetTitleFont(TitleFont);
        h_signal_varies_mass->GetYaxis()->SetTitleOffset(TitleOffset);



        h_signal_varies_mass->GetXaxis()->SetTitle(input_signal_x_title);
//        h_signal_varies_mass->GetXaxis()->SetTitle("| delta eta |");
        h_signal_varies_mass->Rebin(rebin_times);
//	h_signal_varies_mass->GetXaxis()->SetRangeUser(0, 4.0);
	double X_up_range = distri_x_UpBound;
	double Y_up_range_signal = distri_y_signal_UpBound;
        double Y_up_range_background = distri_y_background_UpBound;

        h_signal_varies_mass->GetXaxis()->SetRangeUser(0,X_up_range);
        h_signal_varies_mass->GetYaxis()->SetRangeUser(0, Y_up_range_signal);

        c2->cd();
        if(k==0){h_signal_varies_mass -> Draw();/* h_signal_varies_mass->GetXaxis()->SetRangeUser(0, 1250);*/}
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

        h_background_varies_mass->GetXaxis()->SetLabelSize(LabelSize);
        h_background_varies_mass->GetXaxis()->SetTitleSize(TitleSize);
        h_background_varies_mass->GetXaxis()->SetTitleFont(TitleFont);
        h_background_varies_mass->GetXaxis()->SetTitleOffset(TitleOffset);

        h_background_varies_mass->GetYaxis()->SetLabelSize(LabelSize);
        h_background_varies_mass->GetYaxis()->SetTitleSize(TitleSize);
        h_background_varies_mass->GetYaxis()->SetTitleFont(TitleFont);
        h_background_varies_mass->GetYaxis()->SetTitleOffset(TitleOffset);


        h_background_varies_mass->SetLineColor(colorN);
        colorN = colorN + 1;// afer used in signal and background color+1
	styleN = styleN + 5;

        h_background_varies_mass->Rebin(rebin_times);
        h_background_varies_mass->GetXaxis()->SetTitle(input_signal_x_title);
//        h_background_varies_mass->GetXaxis()->SetTitle("| delta eta |");

//        h_background_varies_mass->GetXaxis()->SetRangeUser(0, 4.0);
        h_background_varies_mass->GetXaxis()->SetRangeUser(0, X_up_range);
        h_background_varies_mass->GetYaxis()->SetRangeUser(0, Y_up_range_background);

        c3->cd();
        if(k==0){
        //        h_background_varies_mass->GetXaxis()->SetRangeUser(0, 1250);   
          //      h_background_varies_mass->GetYaxis()->SetRangeUser(0, 1); 
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
c2_name = figure_path + c2_name + ".pdf";
c3_name = figure_path + c3_name + ".pdf";

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
//        TString histo_name= "h_Zprime_mass" ;
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

                        f_background->Close();
                        delete f_background;

        }// loop i background shape file

        TCanvas *c6 = new TCanvas("background_Zprime_mass","",200,10,700,500);
	c6->cd();
	h_background_2nd_ele_pT_combine->Rebin(8);
	h_background_2nd_ele_pT_combine->Draw();

  }// end if


}// end v


}


double uncertainty_calculate( double pass, double total)
{
double fail = total - pass;

double uncertainty = sqrt(pass*fail*(pass+fail))/pow(pass+fail,2);

return uncertainty;
}



