// -*- C++ -*-
//
// Package:    my_EDanalzyer/MiniAnalyzer
// Class:      MiniAnalyzer
// 
/**\class MiniAnalyzer MiniAnalyzer.cc my_EDanalzyer/MiniAnalyzer/plugins/MiniAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yu-Hsiang Chang
//         Created:  Wed, 31 May 2017 13:15:23 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

#include "DataFormats/JetReco/interface/GenJet.h" 

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class MiniAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit MiniAnalyzer(const edm::ParameterSet&);
      ~MiniAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------

      edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
      edm::EDGetTokenT<pat::MuonCollection> muonToken_;
      edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
      edm::EDGetTokenT<pat::TauCollection> tauToken_;
      edm::EDGetTokenT<pat::PhotonCollection> photonToken_;

      edm::EDGetTokenT<pat::JetCollection> jetToken_;
//      edm::EDGetTokenT<reco::GenJetCollection> jetToken_;

      edm::EDGetTokenT<pat::JetCollection> fatjetToken_;
      edm::EDGetTokenT<pat::METCollection> metToken_;

//      TH1D *demohisto;

      TH1D *h_nJet;
      TH1D *h_jet_pt;
      TH1D *h_jet_eta;
      TH1D *h_jet_phi;
      TH1D *h_jet_energy;

      TH1D *h1;
      TH1D *h2;
      TH1D *h3;
      TH1D *h4;
      TH1D *h5;
      TH1D *h6;
      TH1D *h7;


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
MiniAnalyzer::MiniAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   usesResource("TFileService");



//   muonToken_  = consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muoLabel"));
   muonToken_  = consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"));

   jetToken_   = consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets")); 
//   jetToken_   = consumes<reco::GenJetCollection>(iConfig.getParameter<edm::InputTag>("jets"));

   edm::Service<TFileService> fs;
//   demohisto = fs->make<TH1D>("tracks" , "Tracks" , 100 , 0 , 5000 );

   h_nJet       = fs->make<TH1D>("nJet"        , "Number of Jets" , 20 , 0 , 20 );
   h_jet_pt     = fs->make<TH1D>("jet_pt"      , "jet pt"         , 50 , 0 , 500 );
   h_jet_eta    = fs->make<TH1D>("jet_eta"     , "jet eta"        , 100 , -5 , 5 );
   h_jet_phi    = fs->make<TH1D>("jet_phi"     , "jet phi"        , 70 , 0 , 7 );
   h_jet_energy = fs->make<TH1D>("jet_energy"  , "jet energy"     , 50 , 0 , 500 );

   h1 = fs->make<TH1D>("ChEmEnergy"      , "Charged EM Energy"     , 50 , 0 , 500 );
   h2 = fs->make<TH1D>("NeEmEnergy"      , "Neutral EM Energy"     , 50 , 0 , 500 );
   h3 = fs->make<TH1D>("ChHadEnergy"     , "Charged Hadron Energy" , 50 , 0 , 500 );
   h4 = fs->make<TH1D>("NeHadEnergy"     , "Neutral Hadron Energy" , 50 , 0 , 500 );
   h5 = fs->make<TH1D>("MuEnergy"        , "Muon energy"           , 50 , 0 , 500 );
   h6 = fs->make<TH1D>("InvisibleEnergy" , "Invisible Energy"      , 50 , 0 , 500 );
   h7 = fs->make<TH1D>("OtherEnergy"     , "Other Energy"          , 50 , 0 , 500 );


}


MiniAnalyzer::~MiniAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MiniAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;



    edm::Handle<pat::MuonCollection> muons;
    iEvent.getByToken(muonToken_, muons);
    for (const pat::Muon &mu : *muons) {
        if (mu.pt() < 5 || !mu.isLooseMuon()) continue;
        std::cout<<"mu.pt()"<< mu.pt() << std::endl;


//        printf("muon with pt %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d\n",
//                mu.pt(), mu.muonBestTrack()->dz(PV.position()), mu.isLooseMuon(), mu.isTightMuon(PV));
    }



    edm::Handle<pat::JetCollection> jets;
//    edm::Handle<reco::GenJetCollection> jets;

    iEvent.getByToken(jetToken_, jets);
    int ijet = 0;

//    std::cout<<"jets->size(): "<< jets->size() << std::endl;

    h_nJet->Fill ( jets->size() );  


    for (const pat::Jet &j : *jets) {
//    for (const reco::GenJet &j : *jets) {

        if (j.pt() < 30 || fabs(j.eta())>2.5 ) continue;
        
//        std::cout<<"jet index: "<< ijet       << std::endl; 
//        std::cout<<"pt: "       << j.pt()     << std::endl;
//        std::cout<<"energy: "   << j.energy() << std::endl;
//        std::cout<<"eta: "      << j.eta()    << std::endl;
//        std::cout<<"phi: "      << j.phi()    << std::endl;
//        std::cout<<"abs(eta): "<<  fabs( j.eta() )    << std::endl;

        h_jet_pt     ->Fill( j.pt()     );
        h_jet_eta    ->Fill( j.eta()    );
        h_jet_phi    ->Fill( j.phi()    );
        h_jet_energy ->Fill( j.energy() );
/*
        std::cout<<"charged EM energy: "  << j.emEnergy()	<< std::endl;
        std::cout<<"neutral EM energy: "  << j.neEmEnergy()	<< std::endl;
        std::cout<<"charged Had energy: " << j.chHadEnergy()	<< std::endl;
        std::cout<<"neutral Had energy: " << j.hadEnergy()	<< std::endl;
        std::cout<<"Muon energy: "	  << j.muEnergy()	<< std::endl;
        std::cout<<"Invisible energy: "   << j.invisibleEnergy()<< std::endl;
        std::cout<<"Other energy: "	  << j.auxiliaryEnergy()<< std::endl;
*/

//        std::cout<<"charged EM energy: "  << j.genJet()->emEnergy()       << std::endl;
//        std::cout<<"neutral EM energy: "  << j.genJet()->neEmEnergy()     << std::endl;

//        demohisto->Fill( j.genJet()->emEnergy() );
        h1->Fill( j.genJet()->emEnergy() );
        h2->Fill( j.genJet()->neEmEnergy() );
        h3->Fill( j.genJet()->chHadEnergy() );
        h4->Fill( j.genJet()->hadEnergy() );
        h5->Fill( j.genJet()->muEnergy() );
        h6->Fill( j.genJet()->invisibleEnergy() );
        h7->Fill( j.genJet()->auxiliaryEnergy() );

        ijet++;   std::cout<<std::endl;
    }





/*
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
*/


}


// ------------ method called once each job just before starting event loop  ------------
void 
MiniAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MiniAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MiniAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MiniAnalyzer);
