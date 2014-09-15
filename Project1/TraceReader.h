#ifndef __TRACE_READER_H__
#define __TARCE_READER_H__
#include <CustomTypes.h>
#include <cstdio>
#include <exception>
#include <cstdlib>
#include <Memory.h>
#include <iostream>
#include <iomanip>
namespace CacheSimulator
{
#define INVALID_CHAR 255U
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
      ui16 _hexMap[256];
      ui32 Ascii2Hex(ui8 buff [])
      {
        ui32 num=0U;
        i32 k=0;
        while(buff[k])
        {
          if(_hexMap[(i32)buff[k]] != INVALID_CHAR)
          {
            num = (num<<4U) + _hexMap[(i32)buff[k]];
          }
          k++;
        }
        return num;
      }
      void parse()
      {
        c8 ins=0U;
        ui8 buff[20] = {0};
        _nextInst = e_Null;
        _nextAddr = 0U;
        if(!feof(_fp))
        {
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
          fgets((c8*)buff, 20, _fp);
          _nextAddr = Ascii2Hex(buff);
        }
      }
    public:
      TraceReader(c8 *filename)
        :_fp(NULL)
      {
        for(ui16 i=1; i<256;i++)
          _hexMap[i] = INVALID_CHAR;
        _hexMap[0] = 0;
        ui8 val=0;
        for (ui8 i='0'; i<='9'; i++)
          _hexMap[i] = val++;
        val=0xa;
        for(ui8 i='a'; i<='f'; i++)
          _hexMap[i] = val++;
        val=0xa;
        for(ui8 i='A'; i<='F'; i++)
          _hexMap[i] = val++;

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
