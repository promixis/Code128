Code128
=======

Copyright (c) 2013 Promixis, LLC

Code128 Implementation for Qt. If you just need Code128 this code handles all ASCII characters in 
Mode B and is able to switch mid encoding to Mode C to save space if numbers are present.

The Rendering code uses Qt heavily. The Code128 encoding code in files Code128.h and Code128.cpp 
do not. The Code128 class can be re-written trivially to remove Qt dependency.

Demo application included.

Details on Code128 barcode can be found here: https://en.wikipedia.org/wiki/Code_128