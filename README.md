Cache Simulator
===============

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
* After make is run a sim_cache binary would have been generated
```bash 
./sim_cache
```
* Application will prompt with list of expected arguments
* Specify the arguments in correct order and run the applicatio again
* Results are printed to console hence you can redirect it to a file for future use
```bash
$> ./sim_cache <arguments> > Result.txt
```

