import os
import sys
if len(sys.argv) < 2 :
    print "insufficient options provided see help function "
    exit (1)

if len(sys.argv) == 2 :
    print ('You are running limits for '+sys.argv[1]+' case')

inputdir=sys.argv[1]

os.system('ls -1 '+inputdir+'  >& tmpfiles.txt')
filein = open('tmpfiles.txt','r')
for line in filein :
    filename =  line.rstrip()
    fullpath=inputdir+'/'+filename
    os.system('python RunLimitAllPoints.py '+fullpath)
    
os.system('rm tmpfiles.txt')
