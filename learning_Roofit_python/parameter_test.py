#!/usr/bin/env python

from datetime import datetime
import optparse

usage = "usage: %prog [options]"
parser = optparse.OptionParser(usage)

parser.add_option('-v', '--verbose', action='store_true', dest='verbose', # 3
                      default=False,
                      help='Print current time as well.')

parser.add_option('-Y', '--Yuhsiang', action='store_true', dest='Yuhsiang', 
                      default=False,
                      help='name 1')

parser.add_option('-e', '--eiko', action='store_true', dest='eiko',
                      default=False,
                      help='name 2')

parser.add_option('-r', '--raman', action='store_true', dest='raman',
                      default=False,
                      help='name 3')

parser.add_option("-n", "--name", action="store", type="string", dest="name", default="")

parser.add_option("-c", "--channel", action="store", type="string", dest="channel", default="")


(options, args) = parser.parse_args()


if options.verbose:
        print datetime.now().strftime('%I:%M:%S %p')

if options.Yuhsiang:
        print "Yu-hsinag is a PhD student of NCU HEP lab"

if options.eiko:
        print "Eiko is a professor of NCU HEP lab"

if options.raman:
        print "Raman is a postdoc of NCU HEP lab"

if options.name:
        print "the name you type is: ", options.name 

if options.channel:
	print "the channel is: ", options.channel # print the string saved in channel
	Channel = options.channel
	print "Channel is: ", Channel






