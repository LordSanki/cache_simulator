#ifndef __RESULT_GENERATOR_H__
#define __RESULT_GENERATOR_H__

#include <Memory.h>
#include <Cache.h>
#include <iostream>
#include <iomanip>
#include <cmath>
namespace CacheSimulator
{
  class ResultGenerator
  {
    public:
      ResultGenerator(i32 argc, c8** argv)
      {
        _argc = argc;
        _argv = argv;
      }
      void operator<<(Cache* mem)
      {

        // Printing the simulator configuration
        std::cout<<"===== Simulator configuration ====="<<std::endl;
#ifdef PROJ1A
        std::cout<<"L1_BLOCKSIZE:          "<<_argv[1]<<std::endl;
        std::cout<<"L1_SIZE:               "<<_argv[2]<<std::endl;
        std::cout<<"L1_ASSOC:              "<<_argv[3]<<std::endl;
        std::cout<<"L1_REPLACEMENT_POLICY: "<<_argv[4]<<std::endl;
        std::cout<<"L1_WRITE_POLICY:       "<<_argv[5]<<std::endl;
        std::cout<<"trace_file:            "<<_argv[6]<<std::endl;
        std::cout<<"==================================="<<std::endl;
        std::cout<<std::endl;
#else
        std::cout<<"BLOCKSIZE:          "<<_argv[1]<<std::endl;
        std::cout<<"L1_SIZE:            "<<_argv[2]<<std::endl;
        std::cout<<"L1_ASSOC:           "<<_argv[3]<<std::endl;
        std::cout<<"Victim_Cache_SIZE:  "<<_argv[4]<<std::endl;
        std::cout<<"L2_SIZE:            "<<_argv[5]<<std::endl;
        std::cout<<"L2_ASSOC:           "<<_argv[6]<<std::endl;
        std::cout<<"trace_file:         "<<_argv[7]<<std::endl;
        std::cout<<"==================================="<<std::endl;
#endif

#ifdef PROJ1A
        printCacheContents((Cache*) mem);
        std::cout<<std::endl;
#else
        Memory *t = mem;
        while(t->isCache())
        {
          printCacheContents((Cache*) t);
          t = t->next();
        }
#endif
        printSimulationResultsRaw(mem);
#ifdef PROJ1A
        std::cout<<std::endl;
#endif
        printSimulationResultsPerformance(mem);

      }
    private:
      c8 **_argv;
      i32 _argc;

      void printCacheContents(Cache * cache)
      {
        std::cout<<"===== "<<cache->name()<<" contents ====="<<std::endl;

        for(ui32 i=0; i<cache->set(); i++)
        {
          TagSet &set = cache->_tags[i];
#ifdef PROJ1A
          std::cout<<"set  "<<i<<":";
#else
          std::cout<<"set "<<i<<": ";
#endif

#ifdef PROJ1A
          for (ui32 j=0; j<set.size(); j++)
          {
            std::cout<<"   "<<std::hex<<set[j].tag()<<std::dec;
            if(set[j].dirty())
              std::cout<<" D";
          }
#else
          set.sort();
          for (ui32 j=0; j<set.size(); j++)
          {
            std::cout<<std::hex<<set[j].tag()<<std::dec;
            if(set[j].dirty())
              std::cout<<" D  ";
            else
              std::cout<<"    ";
          }
#endif

          std::cout<<std::endl;
        }
      }

      void printSimulationResultsRaw(Memory *mem)
      {
        ui32 a,b,c,d, f, g;
        f32 e;

        std::cout<<"====== Simulation results (raw) ======"<<std::endl;
        c8 srNo = 'a';

        Memory *t = mem;
        while(t->isCache())
        {
          Cache *ch = (Cache*)t;
          a = ch->reads();
          b = ch->reads() - ch->rhits();
          c = ch->writes();
          d = ch->writes() - ch->whits();
          if(t->name() == "L1")
            e = ((f64)b+d)/(a+c);
          else
            e =  ((f64)b)/(a);
          f = ch->wbacks();

          std::cout<<srNo++<<". number of "<<t->name()<<" reads:              "<< a <<std::endl;
          std::cout<<srNo++<<". number of "<<t->name()<<" read misses:        "<< b <<std::endl;
          std::cout<<srNo++<<". number of "<<t->name()<<" writes:             "<< c <<std::endl;
          std::cout<<srNo++<<". number of "<<t->name()<<" write misses:       "<< d <<std::endl;
          std::cout<<srNo++<<". "<<t->name()<<" miss rate:                    "<<std::fixed<<std::setprecision(4)<< e <<std::endl;
#ifdef PROJ1A
          std::cout<<srNo++<<". number of writebacks from "<<t->name()<<":    "<< f <<std::endl;
#else
          if(t->name() == "L1")
          {
            std::cout<<srNo++<<". number of swaps:                  "<< 0 <<std::endl;
            std::cout<<srNo++<<". number of victim cache writeback: "<< 0 <<std::endl;
          }
          else
          {
            std::cout<<srNo++<<". number of "<<t->name()<<" writebacks:         "<< f <<std::endl;
          }
#endif
          t = t->next();
        }

        g = t->writes() + t->reads();
        std::cout<<srNo++<<". total memory traffic:            "<< g <<std::endl;
      }

      void printSimulationResultsPerformance(Memory *mem)
      {

        Cache *l1 = (Cache*)mem;

        f64 l1_hit_time = 0.25 + 2.5 * (l1->size() / (512.0*1024))
            + 0.025 * (l1->blocksize()/16.0) + 0.025 * l1->assoc();

        f64 l1_miss_rate = ((l1->reads() - l1->rhits()) + (l1->writes() - l1->whits()))
                            /((f64)(l1->reads() + l1->writes()));

        f64 l1_miss_penalty = (20.0 + 0.5*(l1->blocksize() / 16.0 ));

#ifdef PROJ1A
        f64 avg_access_time = l1_hit_time + (l1_miss_rate * l1_miss_penalty);
#else
        Cache *l2 = (Cache*)l1->next();

        f64 l2_hit_time = 2.5 + 2.5 * (l2->size() / (512.0*1024)) 
            + 0.025 * (l2->blocksize() / 16) + 0.025 * l2->assoc();

        f64 l2_miss_penalty = 20  + 0.5*(l2->blocksize() / 16.0 );

        f64 l2_miss_rate = (l2->reads() - l2->rhits())/((f64)l2->reads());

        f64 avg_access_time = l1_hit_time + (l1_miss_rate *(l2_hit_time + l2_miss_rate*l2_miss_penalty));
#endif
        std::cout<<"==== Simulation results (performance) ===="<<std::endl;
        std::cout<<"1. average access time:         ";
        std::cout<<std::fixed<<std::setprecision(4)<<avg_access_time;
        std::cout <<" ns"<<std::endl;
      }
  };
};

#endif //__RESULT_GENERATOR_H__

