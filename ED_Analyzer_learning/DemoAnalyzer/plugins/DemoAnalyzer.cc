// -*- C++ -*-
//
// Package:    Demo/DemoAnalyzer
// Class:      DemoAnalyzer
// 
/**\class DemoAnalyzer DemoAnalyzer.cc Demo/DemoAnalyzer/plugins/DemoAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yu-Hsiang Chang
//         Created:  Wed, 05 Apr 2017 15:18:58 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include <TLorentzVector.h>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"


//
// class declaration
//

class DemoAnalyzer : public edm::EDAnalyzer {
   public:
      explicit DemoAnalyzer(const edm::ParameterSet&);
      ~DemoAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      unsigned int minTracks_;
      TH1D *demohisto;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
//DemoAnalyzer::DemoAnalyzer(const edm::ParameterSet& iConfig)

DemoAnalyzer::DemoAnalyzer(const edm::ParameterSet& iConfig) :
minTracks_(iConfig.getUntrackedParameter<unsigned int>("minTracks",0))
{
   //now do what ever initialization is needed

   edm::Service<TFileService> fs;
   demohisto = fs->make<TH1D>("tracks" , "Tracks" , 100 , 0 , 5000 );

}


DemoAnalyzer::~DemoAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DemoAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

// ---- generalTracks ------- //
Handle<reco::TrackCollection> tracks;
iEvent.getByLabel("generalTracks", tracks); 

//LogInfo("Demo") << "number of tracks "<<tracks->size();
   demohisto->Fill(tracks->size());

if( minTracks_ <= tracks->size() ) {
   LogInfo("Demo") << "number of tracks "<<tracks->size();
}

std::cout<<"my tracks: "<< tracks->size()<< std::endl;

/*
if(tracks->size() != 0 ){
//  std::cout<<"tracks->at(0)->outerPx(): "<<tracks->at(0)->outerPx() << std::endl;

 reco::Track first_TRK = tracks->at(0);   
// std::cout<<"test: "<< first_TRK.outerPx() << std::endl;
 std::cout<<"test: "<< first_TRK.found() << std::endl;
}
*/

for(unsigned int i=0 ; i<tracks->size() ;i++){
  if(i>=5) continue; // print out only first five tracks' info

  std::cout<<"track index:"<< i << std::endl;
//  reco::Track the_TRK = tracks->at(i);
//  std::cout<<"Number of valid hits on track: "<< the_TRK.found() << std::endl;
  std::cout<<"Number of valid hits on track: "<< tracks->at(i).found() << std::endl;
}



// ---- globalMuons ------- //
Handle<reco::TrackCollection> my_globalMuons;
iEvent.getByLabel("globalMuons", my_globalMuons);

std::cout<<"my globalMuons: "<< my_globalMuons->size()<< std::endl;




// ---- photons  ------- //
Handle<reco::PhotonCollection> my_photons;
iEvent.getByLabel("photons", my_photons);

std::cout<<"my photons: "<< my_photons->size()<< std::endl;

for(unsigned int i=0 ; i<my_photons->size() ;i++){
  if(i>=5) continue; // print out only first five photons' info
  
  std::cout<<"photon index:"<< i << std::endl;
  std::cout<<"e1x5(): "<< my_photons->at(i).e1x5() << std::endl;
  std::cout<<"sigmaIetaIeta(): "<< my_photons->at(i).sigmaIetaIeta() << std::endl;


/*
//    const TLorentzVector my_PhotonP4 = my_photons->at(i).getCandidateP4type();
  TLorentzVector my_PhotonP4;
  my_PhotonP4 =  my_photons->setCandidateP4type();

  std::cout<<"energy: "<< my_PhotonP4.E()   <<std::endl;
  std::cout<<"Pt: "    << my_PhotonP4.Pt()  <<std::endl;
  std::cout<<"Eta: "   << my_PhotonP4.Eta() <<std::endl;
  std::cout<<"Phi: "   << my_PhotonP4.Phi() <<std::endl;
*/
}






#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
DemoAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DemoAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
DemoAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
DemoAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
DemoAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
DemoAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DemoAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DemoAnalyzer);
