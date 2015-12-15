import ROOT
import os
import sys
ROOT.gROOT.SetBatch(True)

if len(sys.argv) < 2 :
    print "insufficient options provided "
    print "please provide directory in which all textfiles for optimization are kept"
    print "this script will create Datacard directory for each of these text files."

if len(sys.argv) == 2 :
    print ('Now taking text files from directory '+sys.argv[1])

indirname=sys.argv[1]
outdir='Datacards_'+indirname
os.system('mkdir '+outdir)

os.system('ls -1 '+indirname+' | grep .txt >& tmpfiles.txt')

filein = open('tmpfiles.txt','r')
for line in filein :
    filename =  line.rstrip()
    dirname = filename.split('.txt')[0]
    fullfilename=indirname+'/'+filename
    print('python MakeDataCards.py '+fullfilename+' '+dirname)
    ##print (filename, dirname)
    os.system('python MakeDataCards.py '+fullfilename+' '+dirname)
    if os.path.isdir(outdir+'/'+dirname):
        os.system('rm -rf '+outdir+'/'+dirname)
    os.system('mv '+dirname+' '+outdir)
os.system('rm tmpfiles.txt')
