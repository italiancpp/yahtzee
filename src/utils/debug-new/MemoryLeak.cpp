#include "MemoryLeak.h"

#include <malloc.h>

// ----------------------------------------------------------------------------
// MemoryLea
// ----------------------------------------------------------------------------
MemoryLeak g_memoryLeak;

MemoryLeak::MemoryLeak()
{
  start(MEMORY_LEAK_CNT); // initialize memory
  m_del_check = false;
}

MemoryLeak::~MemoryLeak()
{
  stop(false);     // check last memory leak
  start(false, 0); // clear memory
}

void MemoryLeak::_start(bool del_check, int cnt)
{
  if (m_info != NULL)
  {
    ::free(m_info);
    m_info = NULL;
  }
  m_del_check = del_check;
  if (cnt != 0)
  {
    m_info = (MemoryLeakInfo*) ::malloc(sizeof(MemoryLeakInfo) * cnt);
    for (int i = 0; i < cnt; i++)
    {
      MemoryLeakInfo* info = &m_info[i];
      info->p    = NULL;
      info->size = 0;
      info->file = NULL;
      info->line = 0;
    }
  }
  m_cnt          = cnt;
  m_cur_max_cnt  = 0;
}

int MemoryLeak::_stop(bool auto_free)
{
  m_del_check = false;

  int res = 0;
  for (int i = 0; i < m_cur_max_cnt; i++)
  {
    MemoryLeakInfo* info = &m_info[i];
    if (info->p != NULL)
    {
      printf("memory leak %p(%u) %s:%d\n", info->p, info->size, info->file, info->line);
      res++;
      if (auto_free)
      {
        ::free(info->p);
        info->p    = NULL;
        info->size = 0;
        info->file = NULL;
        info->line = 0;
      }
    }
  }
  return res;
}

MemoryLeakInfo* MemoryLeak::find(void* p)
{
  for (int i = 0; i < m_cur_max_cnt; i++)
  {
    MemoryLeakInfo* info = &m_info[i];
    if (info->p == p)
    {
      return info;
    }
  }
  return NULL;
}

MemoryLeakInfo* MemoryLeak::add(void* p, size_t size, char* file, int line)
{
  for (int i = 0; i < m_cnt; i++)
  {
    MemoryLeakInfo* info = &m_info[i];
    if (info->p == NULL)
    {
      info->p    = p;
      info->size = size;
      info->file = file;
      info->line = line;
      if (i + 1 > m_cur_max_cnt) m_cur_max_cnt = i + 1;
      return info;
    }
  }
  return NULL;
}

MemoryLeakInfo* MemoryLeak::del(void* p)
{
  for (int i = 0; i < m_cur_max_cnt; i++)
  {
    MemoryLeakInfo* info = &m_info[i];
    if (info->p == p)
    {
      info->p    = NULL;
      info->size = 0;
      info->file = NULL;
      info->line = 0;

      bool m_cur_max_cnt_move = true;
      MemoryLeakInfo* temp = info + 1;
      for (int j = i + 1; j < m_cur_max_cnt; j++)
      {
        if (temp->p != NULL)
        {
          m_cur_max_cnt_move = false;
          break;
        }
        temp++;
      }

      if (m_cur_max_cnt_move) m_cur_max_cnt = i + 1;

      return info;
    }
  }
  return NULL;
}

void MemoryLeak::start(bool del_check, int cnt)
{
  g_memoryLeak._start(del_check, cnt);
}

int MemoryLeak::stop(bool auto_free)
{
  return g_memoryLeak._stop(auto_free);
}
