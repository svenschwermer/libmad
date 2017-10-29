/***********************************************************************/
/*  This file is part of the uVision/ARM development tools             */
/*  Copyright KEIL ELEKTRONIK GmbH 2002-2004                           */
/***********************************************************************/
/*                                                                     */
/*  SYSCALLS.C:  System Calls Remapping                                */
/*                                                                     */
/***********************************************************************/

#include <stdlib.h>


void _exit (int n) {
label:  goto label; /* endless loop */
}


#define HEAP_LIMIT 0x80200000

caddr_t sbrk (int incr) {
  extern char   end asm ("end");	/* Defined by the linker */
  static char * heap_end;
         char * prev_heap_end;

  if (heap_end == NULL) 
     heap_end = &end;

  prev_heap_end = heap_end;
  
  if (heap_end + incr >= (char *)HEAP_LIMIT) {
    abort ();	   /* Out of Memory */ 
  }  
  heap_end += incr;

  return (caddr_t) prev_heap_end;
}
