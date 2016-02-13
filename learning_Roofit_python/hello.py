#!/usr/bin/env python
from datetime import datetime
from optparse import OptionParser

def main():
    options = parse_args() # 6
    if options.verbose:
        print datetime.now().strftime('%I:%M:%S %p')
    print options.greeting % options.who

def parse_args():
    parser = OptionParser(usage='%prog [OPTIONS] [WHO]')    # 12
    parser.add_option('-g', '--greeting', dest='greeting',  # 13
                      default="Hello, %s!",
                      help='The template of the greeting message, which defaults to "%default".', # 2
                      metavar='MESSAGE')
    parser.add_option('-v', '--verbose', action='store_true', dest='verbose', # 3
                      default=False,
                      help='Print current time as well.')

    options, args = parser.parse_args()                     # 14

    if '%s' not in options.greeting:                        # 5
        parser.error('-g options requires a placeholder %s in it.')
    if len(args) > 1:
        parser.error('Too many arguments.')
    options.who = 'World' if len(args) == 0 else args[0]

    return options

if __name__ == '__main__':
    main()
