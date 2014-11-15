// ----------------------------------------------------------------------------
//
// VDream Component Suite version 7.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __DEBUG_NEW_H__
#define __DEBUG_NEW_H__

#include <stdlib.h>
#include <stdio.h> // for size_t
#include "MemoryLeak.h"

// ----------------------------------------------------------------------------
// Overload functions
// ----------------------------------------------------------------------------
void* debug_malloc      (size_t size, const char* file, const int line);
void  debug_free        (void* p,     const char* file, const int line);
void* operator new      (size_t size, const char* file, const int line);
void  operator delete   (void* p,     const char* file, const int line);
void  operator delete   (void* p);
void* operator new[]    (size_t size, const char* file, const int line);
void  operator delete[] (void* p,     const char* file, const int line);
void  operator delete[] (void* p);

// ----------------------------------------------------------------------------
// Macros
// ----------------------------------------------------------------------------
#define debug_new new(__FILE__, __LINE__)
#define new       debug_new
//#define malloc(A) debug_malloc((A), __FILE__, __LINE__)
//#define free(A)   debug_free((A), __FILE__, __LINE__)
#define delete(A) operator delete((A), __FILE__, __LINE__) // deprecated /// gilgil temp 2011.09.14

#endif // __DEBUG_NEW_H__
