import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('Demo')


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )
#process.MessageLogger.cerr.INFO = cms.untracked.PSet(
#    limit = cms.untracked.int32(-1)
#)

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )




process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#        'file:myfile.root'
            'file:/afs/cern.ch/cms/Tutorials/TWIKI_DATA/TTJets_8TeV_53X.root'
    )
)

#process.demo = cms.EDAnalyzer('DemoAnalyzer'
#)

#process.demo = cms.EDAnalyzer('DemoAnalyzer',
#           minTracks = cms.untracked.uint32(1000)
#         )

process.load("Demo.DemoAnalyzer.CfiFile_cfi")
process.demo.minTracks=800

#process.dump=cms.EDAnalyzer('EventContentAnalyzer')

#process.Tracer = cms.Service("Tracer")

process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('histodemo.root')
                                   )

process.p = cms.Path(process.demo)

#process.p = cms.Path(process.demo*process.dump)



