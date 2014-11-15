// ----------------------------------------------------------------------------
//
// VDream Component Suite version 7.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __MEMORY_LEAK_H__
#define __MEMORY_LEAK_H__

#include <stdlib.h>
#include <stdio.h> // for size_t

// ----------------------------------------------------------------------------
// MemoryLeakInfo
// ----------------------------------------------------------------------------
typedef struct _MemoryLeakInfo
{
  void*  p;
  size_t size;
  char*  file;
  int    line;
} MemoryLeakInfo;

// ----------------------------------------------------------------------------
// MemoryLeak
// ----------------------------------------------------------------------------
class MemoryLeak
{
  friend void* debug_malloc(size_t size, const char* file, const int line);
  friend void  debug_free  (void* p,     const char* file, const int line);

protected:
  MemoryLeakInfo* m_info;
  bool            m_del_check;
  int             m_cnt;
  int             m_cur_max_cnt;

public:
  static const int MEMORY_LEAK_CNT = 65536;

public:
  MemoryLeak();
  virtual ~MemoryLeak();

protected:
  void _start(bool del_check, int cnt);
  int  _stop(bool auto_free);

protected:
  MemoryLeakInfo* find(void* p);
  MemoryLeakInfo* add (void* p, size_t size, char* file, int line);
  MemoryLeakInfo* del (void* p);

public:
  static void start(bool del_check = true, int cnt = MEMORY_LEAK_CNT);
  static int  stop(bool auto_free = true);
};

#endif // __MEMORY_LEAK_H__
