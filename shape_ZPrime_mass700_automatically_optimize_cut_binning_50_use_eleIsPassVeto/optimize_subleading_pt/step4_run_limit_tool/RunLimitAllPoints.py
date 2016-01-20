import os
import sys
if len(sys.argv) < 2 :
    print "insufficient options provided see help function "
    exit (1)

if len(sys.argv) == 2 :
    print ('You are running limits for '+sys.argv[1]+' case')

inputdir=sys.argv[1]

masspoints=['800',
            '1000',
            '1200',
            '1400',
            '1600',
	    '1800',
            '2000',
            '2500',
            '3000',
            '3500',
            '4000' ]


for imass in range(len(masspoints)):
    datacardname= inputdir+'/DataCard_M'+str(masspoints[imass])+'GeV_ZPTOZHEE_13TeV.txt'
    print "================="
    print "estimating limit for ",datacardname
    print "================="
    os.system('combine -M Asymptotic '+datacardname+ ' -m '+str(masspoints[imass]))
    print "================="
    print "========moving rootfile to =========",sys.argv[1]
    os.system('mv higgsCombineTest.Asymptotic.mH'+str(masspoints[imass])+'.root '+sys.argv[1])
    print "================="
