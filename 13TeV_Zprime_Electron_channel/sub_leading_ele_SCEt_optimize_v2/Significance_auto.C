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

#include <cstring>

using namespace std;

void Significance_auto(){


 //  prepare the weights for 4 background samples

const int N_background_points = 4;
double background_cross_section[N_background_points] = { 139.4 , 42.75 , 5.497 , 2.21 };
double background_number_of_events[N_background_points] = { 2377497 , 955972 , 1048047 , 987977 };
double background_weights[N_background_points];

for(int i=0;i<N_background_points;i++) 
{ background_weights[i] = background_cross_section[i] / background_number_of_events[i];  
}


 // prepare all thing used in below

  const int N_mass_points = 13;
  int Zprime_mass[N_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
  TString path = "/Users/index0192/13_TeV_Task/Zprime_Electron_channel/plot_SubLedaing_ele_pt_optimize/";

  TCanvas *c1[N_mass_points];
  TString c1_name;

  TString leg_name1 = "Significance";
  TString leg_name2 = "Signal efficiency";
  TString leg_name3 = "Background efficiency";


  //



  // now calulate the significance

  // loop in k, which mass point you want to know its Significance

  for(int k=0 ; k<N_mass_points ; k++){

	// c1 name	
  	cout<< "Zprime_mass[k]: " << Zprime_mass[k] << endl;
	c1_name  = Form("Significance_and_efficiency_for_Zprme_M_%d", Zprime_mass[k] );
        c1[k] = new TCanvas(c1_name,"Significance in different cut value",200,10,700,500);

	// open the signal ROOT file
  	TString signal_shape_file = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);
  	signal_shape_file = path + signal_shape_file ;
  	TFile *f_signal = new TFile (signal_shape_file);

	// open the signal histogram
  	TString histo_name= "h_ele_pT" ;
  	TH1D *h_2nd_ele_pT;
  	h_2nd_ele_pT = (TH1D*) f_signal -> Get(histo_name);

        // try to determine the highest cut value
  	int max_non_zero_bin = -1;
  	for( int m=1 ; m<= h_2nd_ele_pT->GetNbinsX() ;m++ ){
       		double bin_content = h_2nd_ele_pT->GetBinContent(m);
       		if( bin_content != 0 ){ max_non_zero_bin = m; }
  	}
 
 	int multipier = max_non_zero_bin/5;
  	int highest_cut =  multipier*5;
  	cout<< "highest_cut: " <<  highest_cut <<endl;

        // input the lowest cut value
//  	int lowest_cut = 35;
        int lowest_cut = 10;

	// save the cut point value for every 5 Gev BTW highest and lowest value 
  	int n_cut_points = (highest_cut - lowest_cut)/5 + 1;
  	const int N_cut_points = n_cut_points;
  	cout<< "N_cut_points: " << N_cut_points << endl<<endl;
  	int cut_points[N_cut_points];
 
  	for(int i=0;i<N_cut_points;i++){
  		cut_points[i] = lowest_cut + 5*i;
     	}

  	// TGraph for Significance  
  	const int Nbins = N_cut_points ;
  	double vx[Nbins] ;
  	double vy[Nbins] ;
  	double vy_eff[Nbins] ;
  	double vy_background_eff[Nbins] ;

	// highest significance
	int best_cut_value = -99;
	double max_significance = -999;

	// loop in j, which cut value you want to know its Significance 
  	for(int j=0; j< N_cut_points; j++){

   		int second_ele_pt_cut = cut_points[j];   
		vx[j] = cut_points[j];
 		cout<< "second_ele_pt_cut: "<< second_ele_pt_cut <<endl;

		// 1. calculate signal efficiency

	 	// note: my 2nd ele pT histo binwith=1,
		// require pT> second_ele_pt_cut means integral from (second_ele_pt_cut+1)-th bin to starts, 
		// and the 3000-th bin is the last bin when histogram saved  

 		double pass = h_2nd_ele_pT->Integral( second_ele_pt_cut+1 , 3000);
// 		double total = h_2nd_ele_pT->Integral( 36 , 3000);// the 2nd ele pT has already cut on 35 GeV   
                double total = h_2nd_ele_pT->Integral( lowest_cut+1 , 3000); 

 		double signal_eff = pass / total; 
 		cout<<"signal_eff: " << signal_eff<< endl;
		vy_eff[j] = signal_eff;



	 	// 2. cout the # of background(B) passing 2nd ele pT cut

 		TString background_shape_file[N_background_points];

		// prepare the background sample name 
 		for(int l=0 ; l<N_background_points ; l++ ){ 
   			if(l==0 ){ background_shape_file[l] = Form("background_shape_DYJets_HT100to200_in_Zprime_M-%d.root",Zprime_mass[k]);}
        		if(l==1 ){ background_shape_file[l] = Form("background_shape_DYJets_HT200to400_in_Zprime_M-%d.root",Zprime_mass[k]);}
        		if(l==2 ){ background_shape_file[l] = Form("background_shape_DYJets_HT400to600_in_Zprime_M-%d.root",Zprime_mass[k]);}
        		if(l==3 ){ background_shape_file[l] = Form("background_shape_DYJets_HT600toInf_in_Zprime_M-%d.root",Zprime_mass[k]);}

 		}

		// define counter   
 		double background_Number_after_weight[N_background_points] ;// background pass 2nd ele pT cut  
 		double background_total_Number_after_weight=0;

		double background_all[N_background_points] ;
                double background_all_after_weight=0;

		// loop 4 background sample
 		for(int i=0; i<N_background_points;i++){

			// open the sample 
      			background_shape_file[i] = path + background_shape_file[i];
      			TFile *f_background = new TFile ( background_shape_file[i] );
      			TH1D *h_background_2nd_ele_pT;
      			h_background_2nd_ele_pT = (TH1D*) f_background -> Get(histo_name);

			// count # of background passing the 2nd ele pT cut   
      			double background_Number = h_background_2nd_ele_pT -> Integral( second_ele_pt_cut+1 , 3000);
      			background_Number_after_weight[i] = background_Number * background_weights[i]; 
      			background_total_Number_after_weight = background_total_Number_after_weight +background_Number_after_weight[i] ; 

			// count # of background passing pre-selection
                        background_Number =0;// reset
			background_Number  = h_background_2nd_ele_pT -> Integral( lowest_cut+1 , 3000);
			background_all[i] = background_Number * background_weights[i];
			background_all_after_weight = background_all_after_weight + background_all[i];

      			delete f_background;
 		}// loop i background shape file


		// calculate background efficiency
                double background_eff = background_total_Number_after_weight/ background_all_after_weight;
		cout<< "background_eff: " << background_eff << endl;
  		cout<<"background_total_Number_after_weight:"<<  background_total_Number_after_weight << endl; 
		vy_background_eff[j] = background_eff;


 	 	// 3. calculate the significance
		double constant = 1000;// how many luminosity you use? Eiko say use 1/fb  
 		double Significance = signal_eff / (1+ sqrt( constant * background_total_Number_after_weight) );
 		cout<< "Significance: " << Significance << endl; 
 		cout<< endl;
		vy[j] = Significance;

		// find the cut with highest significance
		double temp = Significance;
		if( temp  > max_significance)
			{ max_significance = temp;
			  best_cut_value = second_ele_pt_cut;  
			}

		}// loop j cut-points

  // draw the Tgraph for significance, signal eff. and background eff.
  cout<<endl;
  cout<< "the final best cut is: "<< best_cut_value <<endl;
  cout<<endl;
  TString c1_title = Form("Significance_of_Zprme_M_%d_and_the_best_cut_is_%d_GeV", Zprime_mass[k], best_cut_value );


  TLegend *leg=new TLegend(0.4,0.7,0.9,0.9);

  c1[k]->cd();

  TGraph *gr = new TGraph(Nbins , vx , vy );
  TGraph *gr_eff = new TGraph(Nbins , vx , vy_eff );
  TGraph *gr_background_eff = new TGraph(Nbins , vx , vy_background_eff );

  gr->GetYaxis()->SetRangeUser(0, 1.1);
  gr->SetTitle(c1_title);
  gr->SetLineColor(2);
  gr_eff->SetLineColor(4);
  gr_background_eff->SetLineColor(3);

  gr->Draw();
  gr_eff->Draw("same");
  gr_background_eff->Draw("same");

  leg->AddEntry( gr , leg_name1 ,"L");
  leg->AddEntry( gr_eff , leg_name2 ,"L");
  leg->AddEntry( gr_background_eff , leg_name3 ,"L");
  leg->Draw();

  TString path_name = "/Users/index0192/13_TeV_Task/Zprime_Electron_channel/plot_SubLedaing_ele_pt_optimize/" ;
  c1_name = path_name + c1_name + ".png";
  c1[k]->SaveAs(c1_name);


//  delete h_2nd_ele_pT;
  delete f_signal;
  }// loop k Zprime mass points













  // show the 2nd ele pT distribution of different mass points
  // that is another loop

bool the_2nd_ele_pT_varies_mass = false; 
// the_2nd_ele_pT_varies_mass = true;
if( the_2nd_ele_pT_varies_mass ){

  // define used object
  TString c2_name = "2nd_ele_pT_distribuion_signal";
  TString c3_name = "2nd_ele_pT_distribuion_background";

  TCanvas *c2 = new TCanvas(c2_name,"2nd_ele_pT_distribuion_signal",200,10,700,500);
  TCanvas *c3 = new TCanvas(c3_name,"2nd_ele_pT_distribuion_background",200,10,700,500);
  TCanvas *c4 = new TCanvas("2nd_ele_pT_distribuion_background_zoom_in","2nd_ele_pT_distribuion_background_zoom_in",200,10,700,500);
  int  colorN = 1;
  TLegend *leg2 = new TLegend(0.585,0.3,0.9,0.9);
  TLegend *leg3 = new TLegend(0.585,0.3,0.9,0.9);
  TLegend *leg4 = new TLegend(0.585,0.3,0.9,0.9);
  TLegend *leg5[N_mass_points];// for input
  int rebin_times = 16;

  TCanvas *c5[N_mass_points];

  for(int k=0;k<13;k++){
//  for(int k=2;k<3;k++){
//continue;

        leg5[k] = new TLegend(0.50,0.8,0.9,0.9);// for input
        TString c5_name = Form("input_signal_and_background_in_Zprime_M-%d",Zprime_mass[k]);
	c5[k] = new TCanvas(c5_name,"input signal and background",200,10,700,500);
	
        // First for signal distribution

        TString signal_shape_file = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);
//        TString signal_shape_file = Form("no_zprime_cut_signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);


	// open the signal histogram
        signal_shape_file = path + signal_shape_file ;
        TFile *f_signal = new TFile (signal_shape_file);

        TString histo_name= "h_ele_pT" ;
//        TString histo_name= "h_Zprime_mass" ;

        TH1D *h_2nd_ele_pT;
        h_2nd_ele_pT = (TH1D*) f_signal -> Get(histo_name);


	// setting  
	h_2nd_ele_pT->Scale( 1/h_2nd_ele_pT->Integral() );
	h_2nd_ele_pT->SetTitle("2nd electron pT distribution");
	h_2nd_ele_pT->SetStats(0);

	if( k==0){colorN = kRed;}
	else if( k==3){colorN = kOrange;}
	else if( k==6){colorN = kYellow;}
	else if( k==9){colorN = kCyan;}

	h_2nd_ele_pT->SetLineColor(colorN);
	colorN = colorN + 1;

        TH1D *h_2nd_ele_pT_clone = (TH1D*) h_2nd_ele_pT ->Clone("");

        h_2nd_ele_pT->Rebin(rebin_times);


	// c2 is signal distribution varies with mass 
	c2->cd();
        if(k==0){h_2nd_ele_pT -> Draw(); h_2nd_ele_pT->GetXaxis()->SetRangeUser(0, 1250);}
//        if(k==0){h_2nd_ele_pT -> Draw(); h_2nd_ele_pT->GetXaxis()->SetRangeUser(0, 5000);}
        else {h_2nd_ele_pT -> Draw("same");}

	TString leg_singal_name =  Form("signal in Z' mass= %d",Zprime_mass[k]);
 	leg2->AddEntry( h_2nd_ele_pT ,leg_singal_name ,"L");
 	leg2->Draw();

        // c5[k] is the comparison of signal and background input shape
	// input signal
        c5[k]->cd();
        TH1D *input_signal = (TH1D*) h_2nd_ele_pT ->Clone("");
        input_signal->GetYaxis()->SetRangeUser(0, 0.51);
        input_signal->GetXaxis()->SetRangeUser(0, 1250);
        input_signal ->SetLineColor(2);
	input_signal -> Draw();

        TString leg_input_name =  Form("signal in Z' mass= %d",Zprime_mass[k]);
        leg5[k]->AddEntry( input_signal ,leg_input_name ,"L");
        leg5[k]->Draw();



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

        h_background_2nd_ele_pT_combine->Scale( 1/h_background_2nd_ele_pT_combine->Integral() );
        h_background_2nd_ele_pT_combine->Rebin(rebin_times);


	// c3 is background distribution varies with mass 
        c3->cd();
        if(k==0){
		h_background_2nd_ele_pT_combine->GetXaxis()->SetRangeUser(0, 1250);   
                h_background_2nd_ele_pT_combine->GetYaxis()->SetRangeUser(0, 1); 
		h_background_2nd_ele_pT_combine -> Draw(); 
		}
        else {h_background_2nd_ele_pT_combine -> Draw("same");}

        TString leg_background_name =  Form("background in Z' mass= %d",Zprime_mass[k]);
        leg3->AddEntry( h_background_2nd_ele_pT_combine ,leg_background_name ,"L");
        leg3->Draw();

	// c4 is background distribution varies with mass, and zoom in
        TH1D *h_background_2nd_ele_pT_combine_zoom_in = (TH1D*) h_background_2nd_ele_pT_combine ->Clone("");
        c4->cd();
        if(k==0){
                h_background_2nd_ele_pT_combine_zoom_in->GetXaxis()->SetRangeUser(0, 300);   
//                h_background_2nd_ele_pT_combine_zoom_in->GetYaxis()->SetRangeUser(0, 0.1);
//                h_background_2nd_ele_pT_combine_zoom_in->GetYaxis()->SetRangeUser(0, 1);
                h_background_2nd_ele_pT_combine_zoom_in -> Draw();
                }
        else {h_background_2nd_ele_pT_combine_zoom_in -> Draw("same");}

        leg4->AddEntry( h_background_2nd_ele_pT_combine_zoom_in ,leg_background_name ,"L");
        leg4->Draw();

        // c5[k] is the comparison of signal and background input shape
        // input background
        c5[k]->cd();
        TH1D *input_background = (TH1D*) h_background_2nd_ele_pT_combine ->Clone("");
        input_background ->SetLineColor(4);
        input_background -> Draw("same");

        leg_input_name =  Form("background in Z' mass= %d",Zprime_mass[k]);
        leg5[k]->AddEntry( input_background ,leg_input_name ,"L");
        leg5[k]->Draw();

        TString input_save_name =  Form("input_in_Zprime_mass_%d.png",Zprime_mass[k]);
	input_save_name = path + input_save_name ;
        c5[k]->SaveAs(input_save_name);

  }// loop k Zprime mass point


c2_name = path + c2_name + ".png";
c3_name = path + c3_name + ".png";

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
