#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Tools/BinnedHistogram.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/Thrust.hh"
#include "Rivet/Projections/LeadingParticlesFinalState.hh"

namespace Rivet {

  float ZPeak_counter_muon = 0;
  float ZPeak_counter_ele = 0;
  float ZPeak_counter_combine = 0;
  float mass30to45_counter = 0;

  int muon_counter=0;
  int electron_counter=0;

  class SMP_13_003 : public Analysis {
  public:

    /// Constructor
    SMP_13_003()
      : Analysis("SMP_13_003")
    { //      needsCrossSection(true);   
     }
  public:

    void init() {

      // Full final state
       const FinalState fs(-5.0, 5.0);
       addProjection(fs, "FS");
      
       // Z finders for muons
//       const ZFinder zfm(fs, -2.4, 2.4, 0*GeV, PID::MUON, 15*GeV, 1500*GeV);

       const ZFinder zfm(fs, -2.4, 2.4, 0*GeV, PID::MUON, 15*GeV, 1500*GeV,0.0);// postFS
//       const ZFinder zfm(fs, -2.4, 2.4, 0*GeV, PID::MUON, 15*GeV, 1500*GeV,12.56);// preFSR
       const ZFinder zfe(fs, -2.5, 2.5, 0*GeV, PID::ELECTRON, 15*GeV, 1500*GeV, 0.0 );// postFSR
//       const ZFinder zfe(fs, -2.5, 2.5, 0*GeV, PID::ELECTRON, 15*GeV, 1500*GeV, 12.56 );// preFSR
       addProjection(zfe, "ZFE");
       addProjection(zfm, "ZFM");

       // leading muon 
       LeadingParticlesFinalState muonfs(FinalState(-2.4, 2.4, 14.0*GeV));
       muonfs.addParticleId(PID::MUON);
       addProjection(muonfs, "LeadingMuon");


      // Histograms
//      _hist1MZ_of_MuMu            = bookHisto1D(2, 1, 1);// preFSR full acc
      _hist1MZ_of_MuMu            = bookHisto1D(2, 1, 3);// preFSR detector acc
//      _hist1MZ_of_EleEle          = bookHisto1D(3, 1, 1);// preFSR full acc
      _hist1MZ_of_EleEle          = bookHisto1D(3, 1, 3);// preFSR detector acc
      _hist1MZ_of_Combine         = bookHisto1D(4, 1, 1);
      _hist2YZ_of_MuMu_M20to30    = bookHisto1D(5, 1, 1);
      _hist2YZ_of_MuMu_M30to45    = bookHisto1D(6, 1, 1);
      _hist2YZ_of_MuMu_M45to60    = bookHisto1D(7, 1, 1);
      _hist2YZ_of_MuMu_M60to120   = bookHisto1D(8, 1, 1);
      _hist2YZ_of_MuMu_M120to200  = bookHisto1D(9, 1, 1);
      _hist2YZ_of_MuMu_M200to1500 = bookHisto1D(10, 1, 1);

      //electron 2D
      _hist2YZ_of_EleEle_M20to30    = bookHisto1D(11, 1, 1);
      _hist2YZ_of_EleEle_M30to45    = bookHisto1D(12, 1, 1);
      _hist2YZ_of_EleEle_M45to60    = bookHisto1D(13, 1, 1);
      _hist2YZ_of_EleEle_M60to120   = bookHisto1D(14, 1, 1);
      _hist2YZ_of_EleEle_M120to200  = bookHisto1D(15, 1, 1);
      _hist2YZ_of_EleEle_M200to1500 = bookHisto1D(16, 1, 1);

    }

    void makeCut(const Event& event) {

      // Apply the Z finders and veto if no Z found
      const ZFinder& zfm = applyProjection<ZFinder>(event, "ZFM");
      const ZFinder& zfe = applyProjection<ZFinder>(event, "ZFE");

      //leading muon
      const FinalState& muonfs = applyProjection<FinalState>(event, "LeadingMuon");

      if (!zfm.empty()) { muon_counter = muon_counter+1 ;}
      if (!zfe.empty()) { electron_counter = electron_counter+1 ;}

      if (zfe.empty() && zfm.empty()) vetoEvent;

      // Choose the Z candidate

//	if(!zfm.empty()){cout<<"# of leading muon: "<< muonfs.particles().size()<<endl;}

      // di-muon
//      if (!zfm.empty() && (muonfs.particles().size() >= 1)  ){
      if (!zfm.empty() ){

      const ParticleVector& z = zfm.bosons();
      const ParticleVector& mu = zfm.constituents();
	  if(  (mu[0].pT()>14 && mu[1].pT()>9) || (mu[1].pT()>14 && mu[0].pT()>9) ){

      const Particle& leadingMu = muonfs.particles().front();

	cout<< "# of leading muon:"<< muonfs.particles().size()<<endl;
	if (muonfs.particles().size()>0){ cout<< "leading muon pT:"<< leadingMu.pT()<<endl;}

        cout<< "# of Z boson:" << z.size()<<endl;
	cout<< "# of muon from Z:" << mu.size()<<endl;
	for(unsigned int i=0;i<mu.size();i++)
		{cout<<"i:"<< i <<"  i-th muon pT:"<<mu[i].pT()<<endl;}

      // Fill histos
      const double weight = event.weight();
      const double mass_z = z[0].mass();
      const double y_z = z[0].rapidity();

//cout<<"cout weight:"<<weight<<endl;

      _hist1MZ_of_MuMu->fill(mass_z, weight);
      _hist1MZ_of_Combine->fill(mass_z, weight);

      if( (mass_z >20) && (mass_z <30) ){
           _hist2YZ_of_MuMu_M20to30->fill(fabs(y_z), weight);
          }

      if( (mass_z >30) && (mass_z <45) ){
	   mass30to45_counter +=weight;
           _hist2YZ_of_MuMu_M30to45->fill(fabs(y_z), weight);
	  }
	
      if( (mass_z >45) && (mass_z <60) ){
           _hist2YZ_of_MuMu_M45to60->fill(fabs(y_z), weight);
          }

      if( (mass_z >60) && (mass_z <120) ){
	   ZPeak_counter_muon+=weight;
	   ZPeak_counter_combine+=weight;
           _hist2YZ_of_MuMu_M60to120->fill(fabs(y_z), weight);
          }

      if( (mass_z >120) && (mass_z <200) ){
           _hist2YZ_of_MuMu_M120to200->fill(fabs(y_z), weight);
          }

      if( (mass_z >200) && (mass_z <1500) ){
           _hist2YZ_of_MuMu_M200to1500->fill(fabs(y_z), weight);
          }
	}
      }//di-muon

      // di-ele
      if (!zfe.empty()){
      const ParticleVector& z = zfe.bosons();
      const ParticleVector& ele = zfe.constituents();
//          if(  (ele[0].pT()>20 && ele[1].pT()>10) || (ele[1].pT()>20 && ele[0].pT()>10) ){
          if(  (ele[0].pT()>14 && ele[1].pT()>9) || (ele[1].pT()>14 && ele[0].pT()>9) ){

      // Fill histos
      const double weight = event.weight();
      const double mass_z = z[0].mass();
      const double y_z = z[0].rapidity();
      //cout<<"cout weight:"<<weight<<endl;
      
      _hist1MZ_of_EleEle->fill(mass_z, weight);
      _hist1MZ_of_Combine->fill(mass_z, weight);

      if( (mass_z >20) && (mass_z <30) ){
           _hist2YZ_of_EleEle_M20to30->fill(fabs(y_z), weight);
          }

      if( (mass_z >30) && (mass_z <45) ){
           //mass30to45_counter +=weight;
           _hist2YZ_of_EleEle_M30to45->fill(fabs(y_z), weight);
          }

      if( (mass_z >45) && (mass_z <60) ){
           _hist2YZ_of_EleEle_M45to60->fill(fabs(y_z), weight);
          }

      if( (mass_z >60) && (mass_z <120) ){
           ZPeak_counter_ele+=weight;
           ZPeak_counter_combine+=weight;
           _hist2YZ_of_EleEle_M60to120->fill(fabs(y_z), weight);
          }

      if( (mass_z >120) && (mass_z <200) ){
           _hist2YZ_of_EleEle_M120to200->fill(fabs(y_z), weight);
          }

      if( (mass_z >200) && (mass_z <1500) ){
           _hist2YZ_of_EleEle_M200to1500->fill(fabs(y_z), weight);
          }

    	}
      }//di-Ele

    }

    void analyze(const Event& event) {

      makeCut(event);
    }

    void finalize() {

    	std::cout << " Sum of weights : " <<  sumOfWeights() <<endl;//
//cout<< " Cross Section " << crossSection() <<std:: endl;
cout<<"cout ZPeak_counter_muon: "<< ZPeak_counter_muon <<endl;
cout<<"cout mass30to45_counter: "<< mass30to45_counter <<endl;
cout<<"muon_counter: "<< muon_counter <<endl;
cout<<"electron_counter: "<< electron_counter <<endl;
//cout<<"cout test"<<endl;
//cout<<"_hist1MZ_of_MuMu bin width(0):"<< _hist1MZ_of_MuMu->bin(0).width() <<endl;
//cout<<"_hist1MZ_of_MuMu bin width(1):"<< _hist1MZ_of_MuMu->bin(1).width() <<endl;
//cout<<"_hist1MZ_of_MuMu bin width(9):"<< _hist1MZ_of_MuMu->bin(9).width() <<endl;
//cout<<"_hist1MZ_of_MuMu bin width(10):"<< _hist1MZ_of_MuMu->bin(10).width() <<endl;

//      normalizeByContents(_hist1MZ_of_MuMu);
//      normalizeByContents(_hist2YZ_of_MuMu_M20to30);

//      scale(_hist1MZ_of_MuMu,1/ZPeak_counter);
//      scale(_hist1MZ_of_MuMu,10);
//      scale(_hist1MZ_of_MuMu,0.0044);
      scale(_hist1MZ_of_MuMu,(1/ZPeak_counter_muon));
      scale(_hist2YZ_of_MuMu_M20to30,(1/ZPeak_counter_muon));
      scale(_hist2YZ_of_MuMu_M30to45,(1/ZPeak_counter_muon));
      scale(_hist2YZ_of_MuMu_M45to60,(1/ZPeak_counter_muon));
      scale(_hist2YZ_of_MuMu_M60to120,(1/ZPeak_counter_muon));
      scale(_hist2YZ_of_MuMu_M120to200,(1/ZPeak_counter_muon));
      scale(_hist2YZ_of_MuMu_M200to1500,(1/ZPeak_counter_muon));

      scale(_hist1MZ_of_EleEle,(1/ZPeak_counter_ele));
      scale(_hist2YZ_of_EleEle_M20to30,(1/ZPeak_counter_ele));
      scale(_hist2YZ_of_EleEle_M30to45,(1/ZPeak_counter_ele));
      scale(_hist2YZ_of_EleEle_M45to60,(1/ZPeak_counter_ele));
      scale(_hist2YZ_of_EleEle_M60to120,(1/ZPeak_counter_ele));
      scale(_hist2YZ_of_EleEle_M120to200,(1/ZPeak_counter_ele));
      scale(_hist2YZ_of_EleEle_M200to1500,(1/ZPeak_counter_ele));

      scale(_hist1MZ_of_Combine,(1/ZPeak_counter_combine));
    }

    void normalizeByContents(Histo1DPtr h) {
      normalize(h, h->bin(0).width());
    }

  private:
    Histo1DPtr _hist1MZ_of_MuMu;
    Histo1DPtr _hist1MZ_of_EleEle;
    Histo1DPtr _hist1MZ_of_Combine;
    Histo1DPtr _hist2YZ_of_MuMu_M20to30;
    Histo1DPtr _hist2YZ_of_MuMu_M30to45;
    Histo1DPtr _hist2YZ_of_MuMu_M45to60;
    Histo1DPtr _hist2YZ_of_MuMu_M60to120;
    Histo1DPtr _hist2YZ_of_MuMu_M120to200;
    Histo1DPtr _hist2YZ_of_MuMu_M200to1500;

    Histo1DPtr _hist2YZ_of_EleEle_M20to30;
    Histo1DPtr _hist2YZ_of_EleEle_M30to45;
    Histo1DPtr _hist2YZ_of_EleEle_M45to60;
    Histo1DPtr _hist2YZ_of_EleEle_M60to120;
    Histo1DPtr _hist2YZ_of_EleEle_M120to200;
    Histo1DPtr _hist2YZ_of_EleEle_M200to1500;



  };

  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(SMP_13_003);
}
