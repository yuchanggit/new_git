#include <TH1.h>
#include <iostream>

using namespace std;

void efficiency(float& eff, float& err, const TH1F* hinput, 
		const int firstBinForTheCut= -1 , const int lastBinForTheCut=-1, int mode=0,  
		const int firstBinForTotal= -1, const int lastBinForTotal=-1);
void event_number(float& eff, float& err, const TH1F* hinput, 
		  const int firstBinForTheCut=-1, const int lastBinForTheCut=-1, int mode=0,  
		  const int firstBinForTotal=-1, const int lastBinForTotal=-1);
void significance(float& eff, float& err, const TH1F* hinput_sig, const TH1F* hinput_bkg,
		  const int firstBinForTheCut=-1, const int lastBinForTheCut=-1, int mode=0,  
		  const int firstBinForTotal=-1, const int lastBinForTotal=-1);


void efficiency(float& eff, float& err, const TH1F* hinput, 
		const int firstBinForTheCut, const int lastBinForTheCut, int mode,  
		const int firstBinForTotal, const int lastBinForTotal)
// mode 0: minimum threshold, mode 1: maximum threshold, mode 2: a window
{

  int bstart_total=firstBinForTotal;
  int bend_total  =lastBinForTotal;

  // use the input if it's greater than zero
  // start from the underflow bin if not set
  if(bstart_total<0)
    bstart_total=0;

  // use the input if it's greater than zero
  // finish at the overflow bin if not set
  if(bend_total<0)
    bend_total=hinput->GetNbinsX()+1;

  if(bstart_total>=bend_total)
    {
      cout << "Error!! firstBinForTotal and lastBinForTotal are not set properly" << endl;
      return;
    }

  cout << "Efficiency denominator Integrating from bin "<<  bstart_total << " to bin " << bend_total << endl;

  int bstart1=firstBinForTheCut;
  int bend1  =lastBinForTheCut;



  switch(mode)
    {
    case 0:
      cout << "Mode 0: applying minimum threshold " << endl;
      // use the input if it's greater than zero
      if(firstBinForTheCut<0)
	{
	  cout << "Error! firstBinForTheCut must be set properly" << endl;
	  return;
	}
      if(lastBinForTheCut<0)
	bend1=bend_total;
      break;
    case 1:
      cout << "Mode 1: applying maximum threshold " << endl;
      // use the input if it's greater than zero
      if(lastBinForTheCut<0)
	{
	  cout << "Error! lastBinForTheCut must be set properly" << endl;
	  return;
	}
      if(firstBinForTheCut<0)
	bstart1=bstart_total;
      break;
    case 2:
      cout << "Mode 1: applying a window cut " << endl;
      if(firstBinForTheCut<0)
	{
	  cout << "Error! firstBinForTheCut must be set properly" << endl;
	  return;
	}
      if(lastBinForTheCut<0)
	{
	  cout << "Error! lastBinForTheCut must be set properly" << endl;
	  return;
	}
      break;

    default:
      cout << "Mode must be 0-2" << endl;
      cout << "Mode 0: applying minimum threshold " << endl;
      cout << "Mode 1: applying maximum threshold " << endl;
      cout << "Mode 2: applying a window" << endl;
      return;
      break;


    }


  if( (bstart1 >=bend1) || (bstart1< bstart_total) || (bend1 > bend_total) )
    {
      cout << "Error!! firstBinForTheCut and lastBinForTheCut are not set properly" << endl;
      return;
    }


  cout << "Efficiency numerator Integrating from bin "<<  bstart1 << " to bin " << bend1 << endl;


  // denominator, integral from the bstart_total to bend_total
  float n = hinput->Integral(bstart_total,bend_total);
  float nerr = 0;
  for(int i=bstart_total; i<= bend_total; i++)
    nerr += pow(hinput->GetBinError(i),2);

    // numerator, integral from the bstart1 to bend1
  float n1 = hinput->Integral(bstart1,bend1);
  float nerr1 = 0;
  for(int i=bstart1; i<= bend1; i++)
    nerr1 += pow(hinput->GetBinError(i),2);


  // denominator-numerator
  float nerr2 = nerr-nerr1;

  eff = n1/n;
  err = pow(n1/n/n,2)*nerr2 + pow(-n1/n/n + 1/n,2)*nerr1;
  err = sqrt(err);

  cout << "efficiency of " << hinput->GetName() << " = " << eff << " +- " << err << endl;


  return;


}


void event_number(float& n, float& nerr, const TH1F* hinput, 
		  const int firstBinForTheCut, const int lastBinForTheCut, int mode,  
		  const int firstBinForTotal, const int lastBinForTotal)
// mode 0: minimum threshold, mode 1: maximum threshold, mode 2: a window
{

  int bstart_total=firstBinForTotal;
  int bend_total  =lastBinForTotal;

  // use the input if it's greater than zero
  // start from the underflow bin if not set
  if(bstart_total<0)
    bstart_total=0;

  // use the input if it's greater than zero
  // finish at the overflow bin if not set
  if(bend_total<0)
    bend_total=hinput->GetNbinsX()+1;

  if(bstart_total>=bend_total)
    {
      cout << "Error!! firstBinForTotal and lastBinForTotal are not set properly" << endl;
      return;
    }

  cout << "Maximum total events are integrated from bin "<<  bstart_total << " to bin " << bend_total << endl;


  int bstart1=firstBinForTheCut;
  int bend1  =lastBinForTheCut;


  switch(mode)
    {
    case 0:
      cout << "Mode 0: applying minimum threshold " << endl;
      // use the input if it's greater than zero
      if(firstBinForTheCut<0)
	{
	  cout << "Error! firstBinForTheCut must be set properly" << endl;
	  return;
	}
      if(lastBinForTheCut<0)
	bend1=bend_total;
      break;
    case 1:
      cout << "Mode 1: applying maximum threshold " << endl;
      // use the input if it's greater than zero
      if(lastBinForTheCut<0)
	{
	  cout << "Error! lastBinForTheCut must be set properly" << endl;
	  return;
	}
      if(firstBinForTheCut<0)
	bstart1=bstart_total;
      break;
    case 2:
      cout << "Mode 1: applying a window cut " << endl;
      if(firstBinForTheCut<0)
	{
	  cout << "Error! firstBinForTheCut must be set properly" << endl;
	  return;
	}
      if(lastBinForTheCut<0)
	{
	  cout << "Error! lastBinForTheCut must be set properly" << endl;
	  return;
	}
      break;
      
    default:
      cout << "Mode must be 0-2" << endl;
      cout << "Mode 0: applying minimum threshold " << endl;
      cout << "Mode 1: applying maximum threshold " << endl;
      cout << "Mode 2: applying a window" << endl;
      return;
      break;
     

    }


  if( (bstart1 >=bend1) || (bstart1< bstart_total) || (bend1 > bend_total) )
    {
      cout << "Error!! firstBinForTheCut and lastBinForTheCut are not set properly" << endl;
      return;
    }
  
  
  cout << "Computing number of events integrating from bin "<<  bstart1 << " to bin " << bend1 << endl;


  // denominator, integral from the bstart_total to bend_total
  n = hinput->Integral(bstart1,bend1);
  nerr = 0;
  for(int i=bstart1; i<= bend1; i++)
    nerr += pow(hinput->GetBinError(i),2);

  nerr = sqrt(nerr);
  
  cout << "Number of events in " << hinput->GetName() << " = " << n << " +- " << nerr << endl;


  return;


}


void significance(float& sig, float& sigerr, const TH1F* hinput_sig, const TH1F* hinput_bkg,
		  const int firstBinForTheCut, const int lastBinForTheCut, int mode,  
		  const int firstBinForTotal, const int lastBinForTotal)
{

  float sigeff=-1;
  float sigeff_err=-1;
  efficiency(sigeff, sigeff_err, hinput_sig, firstBinForTheCut, lastBinForTheCut, mode,  
	     firstBinForTotal, lastBinForTotal);

  if(sigeff<0 || sigeff_err <0)
    {
      cout << "Error! sigeff = " << sigeff << " \t sigeff_err = " << sigeff_err << endl;
      return;
    }

  float nbkg=-1;
  float nbkg_err=-1;
  event_number(nbkg, nbkg_err, hinput_bkg, firstBinForTheCut, lastBinForTheCut, mode,  
	       firstBinForTotal, lastBinForTotal);


  if(nbkg<0 || nbkg_err <0)
    {
      cout << "Error! sigeff = " << nbkg << " \t sigeff_err = " << nbkg_err << endl;
      return;
    }

  float deno=(1+sqrt(nbkg));
  sig = sigeff/deno;


  sigerr = pow(1/deno,2)*sigeff_err*sigeff_err + 
    pow(sigeff*0.5/deno/deno/sqrt(nbkg),2)*nbkg_err*nbkg_err;

  sigerr = sqrt(sigerr);

  cout << "significance of " << hinput_sig->GetName() << " = " << sig << " +- " << sigerr << endl;

}
