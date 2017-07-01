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
#include "TH2.h"

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

      TH1D *h_jet_leading_pt;
      TH1D *h_jet_leading_eta;
      TH1D *h_jet_leading_phi;
      TH1D *h_jet_leading_energy;
      TH1D *h_leading_chEm;
      TH1D *h_leading_neEm;
      TH1D *h_leading_Em;
      TH1D *h_leading_chHad;
      TH1D *h_leading_neHad;
      TH1D *h_leading_Had;
      TH1D *h_leading_Mu;
      TH1D *h_leading_Invisible;
      TH1D *h_leading_Other;

      TH1D *h_leading_sum_EM;
      TH1D *h_leading_sum_Had;
      TH1D *h_leading_sum_All;

      TH2D *h_leading_chEm_RECOvsGen;
      TH2D *h_leading_neEm_RECOvsGen;

      TH2D *h_leading_chHad_RECOvsGen;
      TH2D *h_leading_neHad_RECOvsGen;


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

   h_jet_leading_pt     = fs->make<TH1D>("jet_leading_pt"      , "leading jet pt"         , 50 , 0 , 500 );
   h_jet_leading_eta    = fs->make<TH1D>("jet_leading_eta"     , "leading jet eta"        , 100 , -5 , 5 );
   h_jet_leading_phi    = fs->make<TH1D>("jet_leading_phi"     , "leading jet phi"        , 140 , -7 , 7 );
   h_jet_leading_energy = fs->make<TH1D>("jet_leading_energy"  , "leading jet energy"     , 50 , 0 , 500 );

   h_leading_chEm      = fs->make<TH1D>("h_leading_chEm"      , ""     , 50 , 0 , 500 );
   h_leading_neEm      = fs->make<TH1D>("h_leading_neEm"      , ""     , 50 , 0 , 500 );
   h_leading_Em        = fs->make<TH1D>("h_leading_Em"        , ""     , 50 , 0 , 500 );
   h_leading_chHad     = fs->make<TH1D>("h_leading_chHad"     , ""     , 50 , 0 , 500 );
   h_leading_neHad     = fs->make<TH1D>("h_leading_neHad"     , ""     , 50 , 0 , 500 );
   h_leading_Had       = fs->make<TH1D>("h_leading_Had"       , ""     , 50 , 0 , 500 );
   h_leading_Mu        = fs->make<TH1D>("h_leading_Mu"        , ""     , 50 , 0 , 500 );
   h_leading_Invisible = fs->make<TH1D>("h_leading_Invisible" , ""     , 50 , 0 , 500 );
   h_leading_Other     = fs->make<TH1D>("h_leading_Other"     , ""     , 50 , 0 , 500 );

   h_leading_sum_EM    = fs->make<TH1D>("h_leading_sum_EM"    , ""     , 50 , 0 , 500 );
   h_leading_sum_Had   = fs->make<TH1D>("h_leading_sum_Had"   , ""     , 50 , 0 , 500 );
   h_leading_sum_All   = fs->make<TH1D>("h_leading_sum_All"   , ""     , 50 , 0 , 500 );

   h_leading_chEm_RECOvsGen = fs->make<TH2D>("h_leading_chEm_RECOvsGen", "", 50 , 0 , 500, 50 , 0 , 500 );
   h_leading_neEm_RECOvsGen = fs->make<TH2D>("h_leading_neEm_RECOvsGen", "", 50 , 0 , 500, 50 , 0 , 500 );

   h_leading_chHad_RECOvsGen = fs->make<TH2D>("h_leading_chHad_RECOvsGen", "", 50 , 0 , 500, 50 , 0 , 500 );
   h_leading_neHad_RECOvsGen = fs->make<TH2D>("h_leading_neHad_RECOvsGen", "", 50 , 0 , 500, 50 , 0 , 500 );



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


/*
    edm::Handle<pat::MuonCollection> muons;
    iEvent.getByToken(muonToken_, muons);
    for (const pat::Muon &mu : *muons) {
        if (mu.pt() < 5 || !mu.isLooseMuon()) continue;
        std::cout<<"mu.pt()"<< mu.pt() << std::endl;


//        printf("muon with pt %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d\n",
//                mu.pt(), mu.muonBestTrack()->dz(PV.position()), mu.isLooseMuon(), mu.isTightMuon(PV));
    }
*/


    edm::Handle<pat::JetCollection> jets;
//    edm::Handle<reco::GenJetCollection> jets;

    iEvent.getByToken(jetToken_, jets);
    int ijet = 0;

//    std::cout<<"jets->size(): "<< jets->size() << std::endl;

    h_nJet->Fill ( jets->size() );  


    for (const pat::Jet &j : *jets) {
//    for (const reco::GenJet &j : *jets) {

//        if (j.pt() < 30 || fabs(j.eta())>2.5 ) continue;

        if (j.genJet() == false ) continue;
        if (j.genJet()->pt() < 30 || fabs(j.genJet()->eta())>2.5 ) continue;

        if ( ijet == 0 ){// leading jet

          h_jet_leading_pt    ->Fill( j.genJet()->pt()     );
          h_jet_leading_eta   ->Fill( j.genJet()->eta()    );
          h_jet_leading_phi   ->Fill( j.genJet()->phi()    );
          h_jet_leading_energy->Fill( j.genJet()->energy() );

          h_leading_chEm      ->Fill( j.genJet()->chEmEnergy()  );
          h_leading_neEm      ->Fill( j.genJet()->neEmEnergy()  );
          h_leading_Em        ->Fill( j.genJet()->emEnergy()    );
          h_leading_chHad     ->Fill( j.genJet()->chHadEnergy() );
          h_leading_neHad     ->Fill( j.genJet()->neHadEnergy() );
          h_leading_Had       ->Fill( j.genJet()->hadEnergy()   );
          h_leading_Mu        ->Fill( j.genJet()->muEnergy()    );
          h_leading_Invisible ->Fill( j.genJet()->invisibleEnergy()  );
          h_leading_Other     ->Fill( j.genJet()->auxiliaryEnergy()  );


	  h_leading_sum_EM   ->Fill( j.genJet()->chEmEnergy() + j.genJet()->neEmEnergy() ) ;
	  h_leading_sum_Had  ->Fill( j.genJet()->chHadEnergy() + j.genJet()->neHadEnergy() ) ;
	  h_leading_sum_All  ->Fill( j.genJet()->chEmEnergy()  + j.genJet()->neEmEnergy()  +
				     j.genJet()->chHadEnergy() + j.genJet()->neHadEnergy() +
				     j.genJet()->muEnergy() + j.genJet()->invisibleEnergy() + j.genJet()->auxiliaryEnergy() );


          h_leading_chEm_RECOvsGen ->Fill ( j.genJet()->chEmEnergy() , j.electronEnergy ()      );
          h_leading_neEm_RECOvsGen ->Fill ( j.genJet()->neEmEnergy() , j.photonEnergy ()        );
          h_leading_chHad_RECOvsGen->Fill ( j.genJet()->chHadEnergy(), j.chargedHadronEnergy () );
          h_leading_neHad_RECOvsGen->Fill ( j.genJet()->neHadEnergy(), j.neutralHadronEnergy () );

/*
          std::cout<<"reco jet electron: " << j.electronEnergy () 
		   <<" gen jet chEM: " << j.genJet()->chEmEnergy() << std::endl;

          std::cout<<"reco jet photon: " << j.photonEnergy () 
		   <<" gen jet neEM: " << j.genJet()->neEmEnergy() << std::endl;


          std::cout<<"reco jet chHad: " << j.chargedHadronEnergy()  
                   <<" gen jet chHad: " << j.genJet()->chHadEnergy() << std::endl;
*/
          std::cout<<"reco jet neHad: " << j.neutralHadronEnergy() 
                   <<" gen jet neHad: " << j.genJet()->neHadEnergy() << std::endl;


/*
          std::cout<<"energy: " <<j.genJet()->energy()
                   <<" chEM: "  <<j.genJet()->chEmEnergy()
                   <<" neEM: "  <<j.genJet()->neEmEnergy()
                   <<" chHad: " <<j.genJet()->chHadEnergy()
                   <<" neHad: " <<j.genJet()->neHadEnergy()
                   <<" Mu: "    <<j.genJet()->muEnergy()
                   <<" invisible: "  <<j.genJet()->invisibleEnergy()
                   <<" other: " <<j.genJet()->auxiliaryEnergy()
                   <<std::endl;
*/
        }

        ijet++;   
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
