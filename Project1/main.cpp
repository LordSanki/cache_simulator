#include <iostream>
#include <cstdlib>
#include <Cache.h>
#include <MainMemory.h>
#include <ResultGenerator.h>
#include <TraceReader.h>

using namespace std;
using namespace CacheSimulator;

int main(int argc, char **argv)
{
  if(argc != 7)
  {
    cout<<"invalid number of arguments"<<endl;
    cout<<"sim_cache <L1_BLOCKSIZE> <L1_SIZE> <L1_ASSOC> <L1_REPACEMENT_POLICY> <L1_WRITE_POLICY> <TRACE_FILE>"<<endl;
    return -1;
  }
  ui16 block_size = atoi(argv[1]);
  ui16 size       = atoi(argv[2]);
  ui16 assoc      = atoi(argv[3]);

  ReplacementPolicy::Types rP  = (ReplacementPolicy::Types)atoi(argv[4]);
  WritePolicy wP        = (WritePolicy)atoi(argv[5]);

  //MainMemory *mm  = new MainMemory();

  Cache *l1 = new Cache( block_size, size, assoc, rP, wP, (Memory*)new MainMemory());
  l1->init(); 
  l1->name("L1");

  ResultGenerator rGen(argc, argv);

  for(TraceReader tReader(argv[6]); tReader; tReader++)
  {
    tReader>>l1;
  }
  rGen<<l1;

  delete l1;

  return 0;
}

