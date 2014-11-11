#include "MemoryLeak.h"

#include <malloc.h>

extern MemoryLeak g_memoryLeak;

#define debug_new_log // printf

// ----------------------------------------------------------------------------
// Overload functions
// ----------------------------------------------------------------------------
void* debug_malloc(size_t size, const char* file, const int line)
{
  void* p = ::malloc(size);
  debug_new_log("debug_malloc(%u, %s, %d) %p\n", size, file, line, p);

  MemoryLeakInfo* info = g_memoryLeak.find(p);
  if (info != NULL)
  {
    printf("already exist %p %s %d\n", p, file, line);
    printf("existing info : %p(%u) %s:%d\n", info->p, info->size, info->file, info->line);
    ::free(p);
    return NULL;
  }
  info = g_memoryLeak.add(p, size, (char*)file, (int)line);
  if (info == NULL)
  {
    printf("can not add %p(%u) %s:%d\n", p, size, file, line);
    ::free(p);
    return NULL;
  }
  return p;
}

void debug_free(void* p, const char* file, const int line)
{
  debug_new_log("debug_free(%p, %s, %d)\n", p, file, line);
  MemoryLeakInfo* info = g_memoryLeak.del(p);
  if (g_memoryLeak.m_del_check && info == NULL)
  {
    printf("can not del %p %s:%d\n", p, file, line);
  }
  ::free(p);
}

void* operator new (size_t size, const char* file, const int line)
{
  void* p = debug_malloc(size, file, line);
  debug_new_log("new(%u, %s, %d) %p\n", size, file, line, p);
  return p;
}

void operator delete (void* p, const char* file, const int line)
{
  debug_new_log("delete(%p, %s, %d)\n", p, file, line);
  operator delete(p);
  debug_free(p, file, line);
}

void operator delete (void* p)
{
  debug_new_log("delete(%p)\n", p);
  return debug_free(p, "unknown", 0);
}

void* operator new[] (size_t size, const char* file, const int line)
{
  void* p = debug_malloc(size, file, line);
  debug_new_log("new[](%u, %s, %d) %p\n", size, file, line, p);
  return p;
}

void operator delete[] (void* p, const char* file, const int line)
{
  debug_new_log("delete[](%p, %s, %d)\n", p, file, line);
  delete[] p;
  return debug_free(p, file, line);
}

void  operator delete[] (void* p)
{
  debug_new_log("delete[](%p)\n", p);
  return debug_free(p, "unknown", 0);
}
