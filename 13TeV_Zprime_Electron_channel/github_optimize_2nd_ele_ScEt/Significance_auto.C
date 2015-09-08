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


 // 1. prepare the weights for 4 background samples

const int N_background_points = 4;

double background_cross_section[N_background_points] = { 139.4 , 42.75 , 5.497 , 2.21 };
double background_number_of_events[N_background_points] = { 2377497 , 955972 , 1048047 , 987977 };

double background_weights[N_background_points];

for(int i=0;i<N_background_points;i++) 
{ background_weights[i] = background_cross_section[i] / background_number_of_events[i];  
//  cout<<"background_weights[i]: "<< background_weights[i] <<endl;
}









 // now calulate the significance

  const int N_mass_points = 13;
  int Zprime_mass[N_mass_points]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
  TString path = "/Users/index0192/13_TeV_Task/Zprime_Electron_channel/plot_SubLedaing_ele_pt_optimize/";

TCanvas *c1[N_mass_points];
TString c1_name;

 TString leg_name1 = "Significance";
 TString leg_name2 = "Signal efficiency";
 TString leg_name3 = "Background efficiency";


for(int k=0 ; k<N_mass_points ; k++){
//  for(int k=0 ; k<1 ; k++){
continue;

  	cout<< "Zprime_mass[k]: " << Zprime_mass[k] << endl;
	c1_name  = Form("Significance_and_efficiency_for_Zprme_M_%d", Zprime_mass[k] );
        c1[k] = new TCanvas(c1_name,"Significance in different cut value",200,10,700,500);

  	TString signal_shape_file = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);
// 	cout<< "signal_shape_file: " << signal_shape_file << endl;

  	signal_shape_file = path + signal_shape_file ;
  	TFile *f_signal = new TFile (signal_shape_file);

  	TString histo_name= "h_ele_pT" ;
  	TH1D *h_2nd_ele_pT;
  	h_2nd_ele_pT = (TH1D*) f_signal -> Get(histo_name);
// 	h_2nd_ele_pT -> Draw();

  // try to determine the highest_cut
  	int max_non_zero_bin = -1;
  	for( int m=1 ; m<= h_2nd_ele_pT->GetNbinsX() ;m++ ){
       		double bin_content = h_2nd_ele_pT->GetBinContent(m);
       		if( bin_content != 0 ){ max_non_zero_bin = m; }
  	}
// 	cout<< "max_non_zero_bin: "<< max_non_zero_bin <<endl;
  	int multipier = max_non_zero_bin/5;
// 	cout<<"multipier: " << multipier <<endl;

// 	int highest_cut = 50; // input should be the multiplier of 5
  	int highest_cut =  multipier*5;
  	cout<< "highest_cut: " <<  highest_cut <<endl;
  	int lowest_cut = 35;
        double highest_cut_minus_15percent = highest_cut*85/100;
        cout<< "highest_cut_minus_15percent: " <<  highest_cut_minus_15percent <<endl;
//        int n_cut_points = (highest_cut_minus_15percent - lowest_cut)/5 + 1;
  	int n_cut_points = (highest_cut - lowest_cut)/5 + 1;
  	const int N_cut_points = n_cut_points;
  	cout<< "N_cut_points: " << N_cut_points << endl<<endl;
  	int cut_points[N_cut_points];
 
  	for(int i=0;i<N_cut_points;i++){
  		cut_points[i] = lowest_cut + 5*i;
// 		cout<< "cut_points[i]: " << cut_points[i] << endl;
     	}

  // for TGraph of sinificance  
  const int Nbins = N_cut_points ;
  double vx[Nbins] ;
  double vy[Nbins] ;
  double vy_eff[Nbins] ;
  double vy_background_eff[Nbins] ;

  	for(int j=0; j< N_cut_points; j++){

   		int second_ele_pt_cut = cut_points[j];   
		vx[j] = cut_points[j];
 		cout<< "second_ele_pt_cut: "<< second_ele_pt_cut <<endl;

 // 2. calculate signal efficiency


 // my 2nd ele pT histo binwith=1, require pT> second_ele_pt_cut means integral from (second_ele_pt_cut+1)-th bin to starts, and the 3000-th bin is the last bin when histogram saved  
 		double pass = h_2nd_ele_pT->Integral( second_ele_pt_cut+1 , 3000);
 		double total = h_2nd_ele_pT->Integral( 36 , 3000);// the 2nd ele pT has already cut on 35 GeV   
 		double signal_eff = pass / total; 
// 		cout<<"pass: " << pass << endl;
//		cout<<"total: " << total<< endl;
 		cout<<"signal_eff: " << signal_eff<< endl;
		vy_eff[j] = signal_eff;



 // 3. cout the # of background(B) passing 2nd ele pT cut


 		TString background_shape_file[N_background_points];
 		for(int l=0 ; l<N_background_points ; l++ ){ 
   			if(l==0 ){ background_shape_file[l] = Form("background_shape_DYJets_HT100to200_in_Zprime_M-%d.root",Zprime_mass[k]);}
        		if(l==1 ){ background_shape_file[l] = Form("background_shape_DYJets_HT200to400_in_Zprime_M-%d.root",Zprime_mass[k]);}
        		if(l==2 ){ background_shape_file[l] = Form("background_shape_DYJets_HT400to600_in_Zprime_M-%d.root",Zprime_mass[k]);}
        		if(l==3 ){ background_shape_file[l] = Form("background_shape_DYJets_HT600toInf_in_Zprime_M-%d.root",Zprime_mass[k]);}

//			cout<< "background_shape_file[l]: "<< background_shape_file[l] <<endl;
 		}



 		double background_Number_after_weight[N_background_points] ;// background pass 2nd ele pT cut  
 		double background_total_Number_after_weight=0;

		double background_all[N_background_points] ;
                double background_all_after_weight=0;

 		for(int i=0; i<N_background_points;i++){
 
      			background_shape_file[i] = path + background_shape_file[i];
      			TFile *f_background = new TFile ( background_shape_file[i] );
      			TH1D *h_background_2nd_ele_pT;
      			h_background_2nd_ele_pT = (TH1D*) f_background -> Get(histo_name);
      			double background_Number = h_background_2nd_ele_pT -> Integral( second_ele_pt_cut+1 , 3000);
//      		cout<<"background_Number: "<< background_Number << endl; 
      			background_Number_after_weight[i] = background_Number * background_weights[i]; 
      			background_total_Number_after_weight = background_total_Number_after_weight +background_Number_after_weight[i] ; 

                        background_Number =0;// reset
			background_Number  = h_background_2nd_ele_pT -> Integral( 36 , 3000);
			background_all[i] = background_Number * background_weights[i];
			background_all_after_weight = background_all_after_weight + background_all[i];

      			delete f_background;
//			delete h_background_2nd_ele_pT;
 		}// loop i background shape file

                double background_eff = background_total_Number_after_weight/ background_all_after_weight;
		cout<< "background_eff: " << background_eff << endl;
//  		cout<<"background_total_Number_after_weight:"<<  background_total_Number_after_weight << endl; 
		vy_background_eff[j] = background_eff;


 // 4. calculate the significance

 		double Significance = signal_eff / (1+ sqrt(background_total_Number_after_weight) );
 		cout<< "Significance: " << Significance << endl; 
 		cout<< endl;
		vy[j] = Significance;

		}// loop j cut-points

TLegend *leg=new TLegend(0.4,0.7,0.9,0.9);


  c1[k]->cd();
  TGraph *gr = new TGraph(Nbins , vx , vy );
  TGraph *gr_eff = new TGraph(Nbins , vx , vy_eff );
  TGraph *gr_background_eff = new TGraph(Nbins , vx , vy_background_eff );

  gr->SetTitle(c1_name);
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

  TCanvas *c2 = new TCanvas("2nd_ele_pT_distribuion_signal","2nd_ele_pT_distribuion_signal",200,10,700,500);
  TCanvas *c3 = new TCanvas("2nd_ele_pT_distribuion_background","2nd_ele_pT_distribuion_background",200,10,700,500);
  TCanvas *c4 = new TCanvas("2nd_ele_pT_distribuion_background_zoom_in","2nd_ele_pT_distribuion_background_zoom_in",200,10,700,500);
  int  colorN = 1;
  TLegend *leg2 = new TLegend(0.585,0.3,0.9,0.9);
  TLegend *leg3 = new TLegend(0.585,0.3,0.9,0.9);
  TLegend *leg4 = new TLegend(0.585,0.3,0.9,0.9);
  TLegend *leg5[N_mass_points];// for input
  int rebin_times = 16;

  TCanvas *c5[N_mass_points];

  for(int k=0;k<1;k++){
//continue;

        leg5[k] = new TLegend(0.50,0.8,0.9,0.9);// for input
        TString c5_name = Form("input_signal_and_background_in_Zprime_M-%d",Zprime_mass[k]);
	c5[k] = new TCanvas(c5_name,"input signal and background",200,10,700,500);
	
        // first for signal distribution
        TString signal_shape_file = Form("signal_shape_in_Zprime_M-%d.root",Zprime_mass[k]);
//      cout<< "signal_shape_file: " << signal_shape_file << endl;

//        TString path = "/Users/index0192/13_TeV_Task/Zprime_Electron_channel/plot_SubLedaing_ele_pt_optimize/";
        signal_shape_file = path + signal_shape_file ;
        TFile *f_signal = new TFile (signal_shape_file);

        TString histo_name= "h_ele_pT" ;
        TH1D *h_2nd_ele_pT;
        h_2nd_ele_pT = (TH1D*) f_signal -> Get(histo_name);

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


	c2->cd();
        if(k==0){h_2nd_ele_pT -> Draw(); h_2nd_ele_pT->GetXaxis()->SetRangeUser(0, 1250);}
        else {h_2nd_ele_pT -> Draw("same");}

	TString leg_singal_name =  Form("signal in Z' mass= %d",Zprime_mass[k]);
 	leg2->AddEntry( h_2nd_ele_pT ,leg_singal_name ,"L");
 	leg2->Draw();

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


//	c2->Update();

        // second for background distribution
        TString background_shape_file[N_background_points];
        for(int l=0 ; l<N_background_points ; l++ ){
        	if(l==0 ){ background_shape_file[l] = Form("background_shape_DYJets_HT100to200_in_Zprime_M-%d.root",Zprime_mass[k]);}
                if(l==1 ){ background_shape_file[l] = Form("background_shape_DYJets_HT200to400_in_Zprime_M-%d.root",Zprime_mass[k]);}
                if(l==2 ){ background_shape_file[l] = Form("background_shape_DYJets_HT400to600_in_Zprime_M-%d.root",Zprime_mass[k]);}
                if(l==3 ){ background_shape_file[l] = Form("background_shape_DYJets_HT600toInf_in_Zprime_M-%d.root",Zprime_mass[k]);}

//              cout<< "background_shape_file[l]: "<< background_shape_file[l] <<endl;              
	}// loop l background shape file 

	TH1D *h_background_2nd_ele_pT_combine = (TH1D*) h_2nd_ele_pT_clone ->Clone("");
	h_background_2nd_ele_pT_combine->Reset();

        for(int i=0; i<N_background_points;i++){
//        for(int i=0; i<2;i++){

                background_shape_file[i] = path + background_shape_file[i];
                TFile *f_background = new TFile ( background_shape_file[i] );
                TH1D *h_background_2nd_ele_pT;
                h_background_2nd_ele_pT = (TH1D*) f_background -> Get(histo_name);
		double tmp = h_background_2nd_ele_pT->Integral();
                if( tmp !=0 ){h_background_2nd_ele_pT->Scale( 1/h_background_2nd_ele_pT->Integral() );}

		h_background_2nd_ele_pT_combine ->Add(h_background_2nd_ele_pT);
        }// loop i background shape file

        h_background_2nd_ele_pT_combine->Scale( 1/h_background_2nd_ele_pT_combine->Integral() );
        h_background_2nd_ele_pT_combine->Rebin(rebin_times);
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


        TH1D *h_background_2nd_ele_pT_combine_zoom_in = (TH1D*) h_background_2nd_ele_pT_combine ->Clone("");
//        h_background_2nd_ele_pT_combine_zoom_in->Rebin(rebin_times);
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

        c5[k]->cd();
        TH1D *input_background = (TH1D*) h_background_2nd_ele_pT_combine ->Clone("");
        input_background ->SetLineColor(4);
        input_background -> Draw("same");

	// input background
        leg_input_name =  Form("background in Z' mass= %d",Zprime_mass[k]);
        leg5[k]->AddEntry( input_background ,leg_input_name ,"L");
        leg5[k]->Draw();

        TString input_save_name =  Form("input_in_Zprime_mass_%d.png",Zprime_mass[k]);
	input_save_name = path + input_save_name ;
        c5[k]->SaveAs(input_save_name);

  }// loop k Zprime mass point





  // combine the 4 background shape to get the Zprime mass distribution 

  {     // Zprime_mass[0] is M = 600 
        TString background_shape_file[N_background_points];
        for(int l=0 ; l<N_background_points ; l++ ){
                if(l==0 ){ background_shape_file[l] = Form("no_zprime_cut_background_shape_DYJets_HT100to200_in_Zprime_M-%d.root",Zprime_mass[0]);}
                if(l==1 ){ background_shape_file[l] = Form("no_zprime_cut_background_shape_DYJets_HT200to400_in_Zprime_M-%d.root",Zprime_mass[0]);}
                if(l==2 ){ background_shape_file[l] = Form("no_zprime_cut_background_shape_DYJets_HT400to600_in_Zprime_M-%d.root",Zprime_mass[0]);}
                if(l==3 ){ background_shape_file[l] = Form("no_zprime_cut_background_shape_DYJets_HT600toInf_in_Zprime_M-%d.root",Zprime_mass[0]);}
//              cout<< "background_shape_file[l]: "<< background_shape_file[l] <<endl;              
        }// loop l background shape file 

        TString template_name = path + background_shape_file[0] ;
        TFile *f_template = new TFile ( template_name );
        TString histo_name= "h_Zprime_mass" ;
        TH1D *h_template;
        h_template = (TH1D*) f_template -> Get(histo_name);

        TH1D *h_background_2nd_ele_pT_combine = (TH1D*) h_template ->Clone("");
        h_background_2nd_ele_pT_combine->Reset();

        for(int i=0; i<N_background_points;i++){
//        for(int i=0; i<2;i++){

                background_shape_file[i] = path + background_shape_file[i];
                TFile *f_background = new TFile ( background_shape_file[i] );
                TH1D *h_background_2nd_ele_pT;
                h_background_2nd_ele_pT = (TH1D*) f_background -> Get(histo_name);
                double tmp = h_background_2nd_ele_pT->Integral();
                if( tmp !=0 ){h_background_2nd_ele_pT->Scale( 1/h_background_2nd_ele_pT->Integral() );}

                h_background_2nd_ele_pT_combine ->Add(h_background_2nd_ele_pT);
        }// loop i background shape file

        TCanvas *c6 = new TCanvas("background_Zprime_mass","",200,10,700,500);
	c6->cd();
	h_background_2nd_ele_pT_combine->Rebin(8);
	h_background_2nd_ele_pT_combine->Draw();

  }


}
