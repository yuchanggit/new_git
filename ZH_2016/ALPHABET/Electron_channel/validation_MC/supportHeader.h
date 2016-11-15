// fit region in [ Xmin1 , Xmax1 ] + [ Xmin2 , Xmax2 ]

double Xmin1= 30;  

double Xmax1= 65;
//double Xmax1=105;
//double Xmax1= 45;

double Xmin2=135;
//double Xmin2=165;

double Xmax2=200;


// define TF1 fit function

Bool_t reject;

// TF1 function
Double_t fline_Exp3(Double_t *x, Double_t *par)// Exponential with 3 parameters
{
    if (reject && x[0] > Xmax1 && x[0] < Xmin2) {
      TF1::RejectPoint();
      return 0;
   }
      return par[0]*TMath::Exp(par[1]*x[0])+par[2];
}


Double_t fline_Exp2(Double_t *x, Double_t *par)// Exponential with 2 parameters
{
    if (reject && x[0] > Xmax1 && x[0] < Xmin2) {
      TF1::RejectPoint();
      return 0;
   }
      return par[0]*TMath::Exp(par[1]*x[0]) ;
}

Double_t fline_Quadric(Double_t *x, Double_t *par)// Polynomial with 3 parameters
{
    if (reject && x[0] > Xmax1 && x[0] < Xmin2) {
      TF1::RejectPoint();
      return 0;
   }
      return par[0]*pow(x[0],2)+ par[1]*x[0] + par[2];
}

Double_t fline_Gaussian(Double_t *x, Double_t *par)// Gaussian with 3 parameters
{
    if (reject && x[0] > Xmax1 && x[0] < Xmin2) {
      TF1::RejectPoint();
      return 0;
   }

   return par[2]*TMath::Gaus(x[0],par[0],par[1]);

}

Double_t fline_ExpTail(Double_t *x, Double_t *par)// Exponential Tail with 3 parameters
{
    if (reject && x[0] > Xmax1 && x[0] < Xmin2) {
      TF1::RejectPoint();
      return 0;
   }

   return par[2]*TMath::Exp( -1*x[0]/(par[0]*x[0]+par[1]) ) ;

}






// divide two functions

Double_t flineDivide_Exp2_Exp2(Double_t *x, Double_t *par)
{
    if (reject && x[0] > Xmax1 && x[0] < Xmin2) {
      TF1::RejectPoint();
      return 0;
   }
      return  ( par[0]*TMath::Exp(par[1]*x[0]) )/( par[2]*TMath::Exp(par[3]*x[0]) ) ;
}




// --------------------------------------------
// defined function

void Fit_TwoRange(TH1F* &histo1D,
                  TF1*  &fn, TString fn_name,
                  double parameters[]  ){

  if( fn->GetNpar() ==2 ) fn->SetParameters( parameters[0], parameters[1]);
  if( fn->GetNpar() ==3 ) fn->SetParameters( parameters[0], parameters[1], parameters[2]);
  if( fn->GetNpar() ==4 ) fn->SetParameters( parameters[0], parameters[1], parameters[2], parameters[3]);

  reject = true;
  histo1D->Fit(fn,"0");


  double chi2 = fn->GetChisquare();
  double ndf  = fn->GetNDF();

  for(int index=0; index<fn->GetNpar(); index++){
    parameters[index] = fn->GetParameter( index );
    cout<<"index: "<< index <<" parameters[index]: "<< parameters[index]<< endl;
  }


  cout<<endl<<"fit histogram: "<< histo1D->GetTitle()<< endl;
  cout<<"chi2: "<< chi2 << endl;
  cout<<"Ndf: "<< ndf << endl;

  double xmin1= Xmin1; double xmax1= Xmax1;
  double xmin2= Xmin2; double xmax2= Xmax2;
  double ymin=-1000; double ymax=1000;

  xmin2= 30; xmax1=200; reject = false;// draw signal region

  TF1 *fnLeft;  TF1 *fnRight;


  if( fn_name =="Exp3" ){
    fnLeft  = new TF1("fnLeft" , fline_Exp3,30,200,3);
    fnRight = new TF1("fnRight", fline_Exp3,30,200,3);
  }

  if( fn_name =="Exp2" ){

    fnLeft  = new TF1("fnLeft" , fline_Exp2,30,200,2);
    fnRight = new TF1("fnRight", fline_Exp2,30,200,2);
  }

  if( fn_name =="Quadric" ){

    fnLeft  = new TF1("fnLeft" , fline_Quadric ,30,200,3);
    fnRight = new TF1("fnRight", fline_Quadric ,30,200,3);
  }

  if( fn_name =="Gaussian" ){

    fnLeft  = new TF1("fnLeft" , fline_Gaussian ,30,200,3);
    fnRight = new TF1("fnRight", fline_Gaussian ,30,200,3);
  }
  if( fn_name =="ExpTail" ){

    fnLeft  = new TF1("fnLeft" , fline_ExpTail ,30,200,3);
    fnRight = new TF1("fnRight", fline_ExpTail ,30,200,3);
  }


/*
  if( fn_name =="Linear" ){

    fnLeft  = new TF1("fnLeft" , fline_Linear ,30,200,2);
    fnRight = new TF1("fnRight", fline_Linear ,30,200,2);
  }

  if( fn_name =="Power3" ){

    fnLeft  = new TF1("fnLeft" , fline_Power3 ,30,200,4);
    fnRight = new TF1("fnRight", fline_Power3 ,30,200,4);

  }

  if( fn_name =="ErfExp" ){

    fnLeft  = new TF1("fnLeft" , fline_ErfExp ,30,200,3);
    fnRight = new TF1("fnRight", fline_ErfExp ,30,200,3);
  }
*/


  fnLeft ->SetParameters(fn->GetParameters());
  fnRight->SetParameters(fn->GetParameters());

  fnLeft ->SetRange( xmin1 , ymin , xmax1 , ymax );
  fnRight->SetRange( xmin2 , ymin , xmax2 , ymax );

  fnLeft ->Draw("same");
  fnRight->Draw("same");

}

void Draw_DivideTwoFunctions(TCanvas* &c_ ,TF1* &f_divide ,TString divide_name ,TF1* fa,TF1* fb,int ColorNumber ){

  c_->cd();

  TF1 *f_divideLeft;   TF1 *f_divideRight;


  if(divide_name == "flineDivide_Exp2_Exp2" ){
    f_divide ->SetParameters(  fa->GetParameter(0), fa->GetParameter(1),
                               fb->GetParameter(0), fb->GetParameter(1));

    f_divideLeft  = new TF1("f_divideLeft",  flineDivide_Exp2_Exp2 ,30,200,4);
    f_divideRight = new TF1("f_divideRight", flineDivide_Exp2_Exp2 ,30,200,4);
  }


  double xmin1= Xmin1; double xmax1= Xmax1;
  double xmin2= Xmin2; double xmax2= Xmax2;
  double ymin=-1000; double ymax=1000;

  xmin2= 30; xmax1=200; reject = false;// draw signal region

  f_divideLeft ->SetParameters(f_divide->GetParameters());
  f_divideLeft ->SetRange( xmin1 , ymin , xmax1 , ymax );

  f_divideRight ->SetParameters(f_divide->GetParameters());
  f_divideRight ->SetRange(xmin2 , ymin , xmax2 , ymax);

  f_divideLeft  ->SetLineColor(ColorNumber);   f_divideLeft  ->Draw("same");
  f_divideRight ->SetLineColor(ColorNumber);   f_divideRight ->Draw("same");
  f_divide      ->SetLineColor(ColorNumber);

}


double GetMyChisquare(TH1F* histo1D, TF1* fn){

  cout<<endl<<"get my chi2: "<< histo1D->GetTitle()<< endl;

  double xmin1= Xmin1; double xmax1= Xmax1;
  double xmin2= Xmin2; double xmax2= Xmax2;

  int Nbins = histo1D ->GetNbinsX();
  int nbins_in_range = 0;
  double Chisquare = 0;

  for(int i=1;i<=Nbins; i++){

    double xValue = histo1D->GetBinCenter(i);
    if( !( (xValue>xmin1 && xValue<xmax1) || (xValue>xmin2 && xValue<xmax2) )  ) continue;

    double BinContent = histo1D -> GetBinContent(i);
    double BinError   = histo1D -> GetBinError(i);
    double fn_value   = fn->Eval( xValue ) ;

    double Delta = (BinContent - fn_value)/BinError;
    Chisquare = Chisquare + (Delta * Delta);
    nbins_in_range++;
  }

//  int Npar = fn->GetNpar();
//  cout<<"my chi2/Ndf= "<< Chisquare<<"/"<< nbins_in_range-Npar << endl;

  cout<<endl;

  return Chisquare;
}



int GetMyNbins(TH1F* histo1D ){

  int Nbins = histo1D ->GetNbinsX();
  int nbins_in_range = 0;

  double xmin1= Xmin1; double xmax1= Xmax1;
  double xmin2= Xmin2; double xmax2= Xmax2;

  for(int i=1;i<=Nbins; i++){

    double xValue = histo1D->GetBinCenter(i);
    if( !( (xValue>xmin1 && xValue<xmax1) || (xValue>xmin2 && xValue<xmax2) )  ) continue;

    nbins_in_range++;
  }

  return nbins_in_range;
}



double GetMyHisto_Area(TH1F* histo1D, double XLow, double XHigh ){

  int BinLow  = histo1D ->GetXaxis()->FindBin(XLow )    ;
  int BinHigh = histo1D ->GetXaxis()->FindBin(XHigh) -1 ;

  int Nbins = histo1D ->GetNbinsX();
  double totalArea = 0;

  for(int i=1;i<=Nbins; i++){
    if( i<BinLow || i>BinHigh ) continue;
    
    double temp = ( histo1D ->GetBinContent(i) ) * histo1D ->GetBinWidth(i);   
    totalArea = totalArea + temp;
  }

  return totalArea;
}



void Set_h1_Style(TH1F* &histo1D,
                  double Xmin,double Xmax,double Ymin,double Ymax,
                  TString  XTitle, TString YTitle ){

  Ymax = histo1D->GetMaximum()  *1.3 ;

  bool findSmallestNonZero = false;
  double temp = 9999;

  for(int i=1;i<=histo1D ->GetNbinsX() ; i++){
    double BinContent = histo1D -> GetBinContent(i);
    if( BinContent!=0 && BinContent<temp) {temp = BinContent; findSmallestNonZero = true;}
  }

  if (findSmallestNonZero) Ymin = temp * 0.7;
  else Ymin = 0.1;// to avoid use zero in log scale

  if(Ymax >3 && Ymax <20 ){
    Ymax = Ymax+ 10; Ymin = 0.001;
  }

//  else if(Ymax <1 ){// for ratio 
//    Ymax = histo1D->GetMaximum()  *1.3; Ymin = 0.07;
//  }

//  histo1D->SetStats(0);
  histo1D->GetXaxis ()->SetRangeUser(Xmin ,Xmax );
  histo1D->GetYaxis ()->SetRangeUser(Ymin ,Ymax );
  histo1D->GetXaxis ()->SetTitle(XTitle);
  histo1D->GetYaxis ()->SetTitle(YTitle);
  histo1D->GetYaxis ()->SetTitleOffset(1.6);


}








