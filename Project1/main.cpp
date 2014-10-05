#include <iostream>
#include <cstdlib>
#include <Cache.h>
#include <MainMemory.h>
#include <ResultGenerator.h>
#include <TraceReader.h>
#include <exception>

using namespace std;
using namespace CacheSimulator;

#ifdef PROJ1A
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
#else
enum Argumetns
{
  e_BLOCKSIZE = 1,
  e_L1_SIZE = 2,
  e_L1_ASSOC = 3,
  e_VICTIM_CACHE_SIZE = 4,
  e_L2_SIZE  = 5,
  e_L2_ASSOC = 6,
  e_TRACE_FILE = 7
};

int main(int argc, char **argv)
{
  if(argc != 8)
  {
    cout<<"invalid number of arguments"<<endl;
    cout<<"sim_cache <BLOCKSIZE> <L1_SIZE> <L1_ASSOC> <Victim_Cache_SIZE> <L2_SIZE> <L2_ASSOC> <TRACE_FILE>"<<endl;
    return -1;
  }
  ui16 block_size = atoi(argv[e_BLOCKSIZE]);
  ui16 l1_size       = atoi(argv[e_L1_SIZE]);
  ui16 l1_assoc      = atoi(argv[e_L1_ASSOC]);
  ui16 l2_size      = atoi(argv[e_L2_SIZE]);
  ui16 l2_assoc      = atoi(argv[e_L2_ASSOC]);
  ui16 victim_size      = atoi(argv[e_VICTIM_CACHE_SIZE]);

  ReplacementPolicy::Types rP  = ReplacementPolicy::e_LRU;
  WritePolicy wP        = e_WBWA;

  //MainMemory *mm  = new MainMemory();

  try
  {
    Cache *l2 = new Cache( block_size, l2_size, l2_assoc, rP, wP, (Memory*)new MainMemory());
    Cache *l1 = new Cache( block_size, l1_size, l1_assoc, rP, wP, (Memory*)l2);

    l1->init(); 
    l1->name("L1");
    l2->name("L2");

    ResultGenerator rGen(argc, argv);
    for(TraceReader tReader(argv[e_TRACE_FILE]); tReader; tReader++)
    {
      tReader>>l1;
    }
    rGen<<l1;
    delete l1;

  }
  catch(const exception &e)
  {
    cout<<e.what()<<endl;
  }


  return 0;
}
#endif
