Cache Simulator
===============
This project implements a simulator to test cache configurations and their performance w.r.t. different access patterns.
I have implementd a LRU with WriteBack/WriteAllocate cache with victim block.
Multiple cache levels can be chained.
Main.cpp demonstrates the use of 2 levels of cache with user provided input configurations.

How to build
-------------
```bash
$> cd CacheSimulator
$> make
```

How to run unit tests
----------------
```bash
$>./verifyB.sh
```

How to run simulator
--------------------
* Make  generates the project binary sim_cache
```bash 
./sim_cache
```
* Application will prompt with list of expected arguments
* Specify the arguments in correct order and run the applicatio again
* Results are printed to console hence you can redirect it to a file for future use
* Have a look at verifyB.sh for sample inputs
```bash
$> ./sim_cache <arguments> > Result.txt
```

