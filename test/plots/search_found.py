#!/usr/bin/env python2.7

from numpy import *
from pylab import *
from matplotlib import rc, rcParams


trie = genfromtxt('../data/trie_search_found.output')
tst = genfromtxt('../data/tst_search_found.output')
radix = genfromtxt('../data/radix_search_found.output')
_map = genfromtxt('../data/map_search_found.output')
umap  = genfromtxt('../data/umap_search_found.output')

######## TIME ########
plot(trie[:,0], trie[:,1], '-o', label='Trie')
hold(True)
plot(tst[:,0], tst[:,1], '-o', label='Ternary Search Tree')
plot(radix[:,0], radix[:,1], '-o', label='Radix Tree')
plot(_map[:,0], _map[:,1], '-o', label='STL ordered Map')
plot(umap[:,0], umap[:,1], '-o', label='STL unordered Map')

xlabel('Max length of the string')
ylabel('Time(ms)')
title('Search test (found)')
legend(loc='best')
grid(True)
savefig('../images/search_found/random/search_found_time_ALL.eps')

hold(False)
plot(tst[:,0], tst[:,1], '-o', label='Ternary Search Tree')
hold(True)
plot(radix[:,0], radix[:,1], '-o', label='Radix Tree')
plot(_map[:,0], _map[:,1], '-o', label='STL ordered Map')
plot(umap[:,0], umap[:,1], '-o', label='STL unordered Map')

xlabel('Max length of the string')
ylabel('Time(ms)')
title('Search test (found)')
legend(loc='best')
grid(True)
savefig('../images/search_found/random/search_found_time_TRMU.eps')

hold(False)
plot(radix[:,0], radix[:,1], '-o', label='Radix Tree')
hold(True)
plot(_map[:,0], _map[:,1], '-o', label='STL ordered Map')
plot(umap[:,0], umap[:,1], '-o', label='STL unordered Map')

xlabel('Max length of the string')
ylabel('Time(ms)')
title('Search test (found)')
legend(loc='best')
grid(True)
savefig('../images/search_found/random/search_found_time_RMU.eps')

hold(False)
plot(trie[:,0], trie[:,1], '-o', label='Trie')
hold(True)
plot(tst[:,0], tst[:,1], '-o', label='Ternary Search Tree')
plot(radix[:,0], radix[:,1], '-o', label='Radix Tree')

xlabel('Max length of the string')
ylabel('Time(ms)')
title('Search test (found)')
legend(loc='best')
grid(True)
savefig('../images/search_found/random/search_found_time_TTR.eps')
