#!/usr/bin/env python2.7

from numpy import *
from pylab import *
from matplotlib import rc, rcParams

rc('font',**{'family':'serif','serif':['Computer Modern']})

trie = genfromtxt('../data/trie_get_keys.output')
tst = genfromtxt('../data/tst_get_keys.output')
radix = genfromtxt('../data/radix_get_keys.output')
_map = genfromtxt('../data/map_get_keys.output')
umap  = genfromtxt('../data/umap_get_keys.output')

######## TIME ########
plot(trie[:,0], trie[:,1], '-o', label='Trie')
hold(True)
plot(tst[:,0], tst[:,1], '-o', label='Ternary Search Tree')
plot(radix[:,0], radix[:,1], '-o', label='Radix Tree')
plot(_map[:,0], _map[:,1], '-o', label='STL ordered Map')
plot(umap[:,0], umap[:,1], '-o', label='STL unordered Map')

xlabel('Max length of the string')
ylabel('Time(ms)')
title('Remove test (found)')
legend(loc='best')
grid(True)
savefig('get_keys_time_ALL.eps')

hold(False)
plot(tst[:,0], tst[:,1], '-o', label='Ternary Search Tree')
hold(True)
plot(radix[:,0], radix[:,1], '-o', label='Radix Tree')
plot(_map[:,0], _map[:,1], '-o', label='STL ordered Map')
plot(umap[:,0], umap[:,1], '-o', label='STL unordered Map')

xlabel('Max length of the string')
ylabel('Time(ms)')
title('Remove test (found)')
legend(loc='best')
grid(True)
savefig('get_keys_time_TRMU.eps')

hold(False)
plot(radix[:,0], radix[:,1], '-o', label='Radix Tree')
hold(True)
plot(_map[:,0], _map[:,1], '-o', label='STL ordered Map')
plot(umap[:,0], umap[:,1], '-o', label='STL unordered Map')

xlabel('Max length of the string')
ylabel('Time(ms)')
title('Remove test (found)')
legend(loc='best')
grid(True)
savefig('get_keys_time_RMU.eps')
