#ifndef JetReco_GenJet_h
#define JetReco_GenJet_h

/** \class reco::GenJet
 *
 * \short Jets made from MC generator particles
 *
 * GenJet represents Jets made from MC candidates
 * Provide energy contributions from different particle types
 * in addition to generic Jet parameters
 *
 * \author Fedor Ratnikov, UMd
 *
 * \version   Original March 31, 2006 by F.R.
 ************************************************************/


#include "DataFormats/JetReco/interface/Jet.h"


namespace reco {
  class GenParticle;

class GenJet : public Jet {
public:
  struct Specific {
    Specific () :

      m_ChEmEnergy (0),
      m_NeEmEnergy (0),
      m_EmEnergy (0),

      m_ChHadEnergy (0),
      m_NeHadEnergy (0),
      m_HadEnergy (0),

      m_MuEnergy (0),
      m_InvisibleEnergy (0),

      m_AuxiliaryEnergy (0) {}

    /* Energy of charged EM particles */
    float m_ChEmEnergy;
    /* Energy of neutral EM particles */
    float m_NeEmEnergy;
    /* Energy of EM particles */
    float m_EmEnergy;

    /* Energy of charged Hadrons */
    float m_ChHadEnergy;
    /* Energy of neutral Hadrons */
    float m_NeHadEnergy;
    /* Energy of Hadrons */
    float m_HadEnergy;

    /* Energy of Muons */
    float m_MuEnergy;
    /* Invisible energy (three kinds of neutrinos) */
    float m_InvisibleEnergy;

    /* Anything else (Other things not listed in above) */
    float m_AuxiliaryEnergy;
  };

  /** Default constructor*/
  GenJet() {}

  /** Constructor from values*/
  GenJet(const LorentzVector& fP4, const Point& fVertex, const Specific& fSpecific, 
	 const Jet::Constituents& fConstituents);
  GenJet(const LorentzVector& fP4, const Point& fVertex, const Specific& fSpecific);

  /** backward compatible, vertex=(0,0,0) */
  GenJet(const LorentzVector& fP4, const Specific& fSpecific, 
	 const Jet::Constituents& fConstituents);

  virtual ~GenJet() {};

  /** Returns energy of charged electromagnetic particles*/
  float chEmEnergy() const {return m_specific.m_ChEmEnergy;};

  /** Returns energy of neutral electromagnetic particles*/
  float neEmEnergy() const {return m_specific.m_NeEmEnergy;};
  /** Returns energy of electromagnetic particles*/
  float emEnergy() const {return m_specific.m_EmEnergy;};


  /** Returns energy of charged hadronic particles*/
  float chHadEnergy() const {return m_specific.m_ChHadEnergy;};
  /** Returns energy of neutral hadronic particles*/
  float neHadEnergy() const {return m_specific.m_NeHadEnergy;};
  /** Returns energy of hadronic particles*/
  float hadEnergy() const {return m_specific.m_HadEnergy;};

  /** Returns energy of Muon*/
  float muEnergy() const {return m_specific.m_MuEnergy;};
  /** Returns invisible energy*/
  float invisibleEnergy() const {return m_specific.m_InvisibleEnergy;};

  /** Returns other energy*/
  float auxiliaryEnergy() const {return m_specific.m_AuxiliaryEnergy;};

  /// Detector Eta (use reference Z and jet kinematics only)
  float detectorEta (float fZVertex) const;

  /// convert generic constituent to specific type
  static const GenParticle* genParticle (const reco::Candidate* fConstituent);
  /// get specific constituent
  virtual const GenParticle* getGenConstituent (unsigned fIndex) const;
  /// get all constituents
  virtual std::vector <const GenParticle*> getGenConstituents () const;
  
  // block accessors

  const Specific& getSpecific () const {return m_specific;}

  /// set the specific (note: responsibility of keeping it consistent with the jet daughers belongs to the caller)
  void setSpecific (const Specific &spec ) {m_specific = spec;}
  
  /// Polymorphic clone
  virtual GenJet* clone () const;

  /// Print object
  virtual std::string print () const;
  
private:
  /// Polymorphic overlap
  virtual bool overlap( const Candidate & ) const;
  
  // Data members
  //Variables specific to to the GenJet class
  Specific m_specific;
};
}
// temporary fix before include_checcker runs globally
#include "DataFormats/JetReco/interface/GenJetCollection.h" //INCLUDECHECKER:SKIP
#endif
