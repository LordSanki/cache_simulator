#ifndef __TRACE_READER_H__
#define __TARCE_READER_H__
#include <CustomTypes.h>
#include <cstdio>
#include <exception>
#include <cstdlib>
#include <Memory.h>

namespace CacheSimulator
{
  class TraceReader
  {
    enum InstructionType
    {
      e_Read  =0,
      e_Write =1,
      e_Null  =2
    };
    private:
      FILE *_fp;
      InstructionType _nextInst;
      ui32 _nextAddr;
      void parse()
      {
        c8 ins;
        c8 buff[100] = {0};
        _nextInst = e_Null;
        _nextAddr = 0U;
        fscanf(_fp, "%c", &ins);
        switch(ins)
        {
          case 'r':
          case 'R':
            _nextInst = e_Read;
            break;
          case 'w':
          case 'W':
            _nextInst = e_Write;
            break;
          default:
            _nextInst = e_Null;
            break;
        }
        fgets((c8*)buff, 99, _fp);
        _nextAddr = (ui32)atoi((c8*)buff);
      }
    public:
      TraceReader(c8 *filename)
        :_fp(NULL)
      {
        _fp = fopen(filename, "rb");
        if(_fp == NULL) throw "Unable to open trace file";
        parse();
      }
      ~TraceReader()
      {
        if(_fp)
          fclose(_fp);
        _fp = NULL;
      }
      operator bool() const
      {
        return (_nextInst != e_Null);
      }
      void operator ++(i32)
      {
        parse();
      }
      void operator>>(Memory* m)
      {
        switch(_nextInst)
        {
          case e_Read:
            (void)m->read(_nextAddr);
            break;
          case e_Write:
            m->write(_nextAddr);
            break;
          default:
            break;
        }
      }
  };
};
#endif //__TARCE_READER_H__
