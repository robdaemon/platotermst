#include <tos.h>
#include "io.h"
#include "protocol.h"

static unsigned char io_buffer[4096];
static unsigned short io_buffer_size;

void io_init(void)
{
  io_configure();
}

void io_configure(void)
{
  Rsconf(7,2,-1,-1,-1,-1);
  Ongibit(0x10);
} 

/**
 * Not needed for now, remove.
 */
void io_init_funcptrs(void)
{
}

void io_open(void)
{  
}

void io_send_byte(unsigned char b)
{
  Bconout(1,b);
}

void io_main(void)
{
  while (Bconstat(1)==-1)
    {
      io_buffer[io_buffer_size++]=(unsigned char)Bconin(1)&0xFF;
    }

  if (io_buffer_size>0)
    {
      ShowPLATO((padByte *)io_buffer,io_buffer_size);
      io_buffer_size=0;
    }

  /* if (Bconstat(1)==-1) */
  /*   { */
  /*     ch=(unsigned char)Bconin(1)&0xFF; */
  /*     ShowPLATO(&ch,1); */
  /*   } */
}

void io_recv_serial(void)
{  
}

/**
 * Hang up
 */
void io_hang_up(void)
{
  /* Bconout(2,0x07); */
  /* Offgibit(0x10);  */
  /* io_send_byte(0x2B); */
  /* io_send_byte(0x2B); */
  /* io_send_byte(0x2B); */
  /* usleep(3000000);   */
  /* io_send_byte('A'); */
  /* io_send_byte('T'); */
  /* io_send_byte('H'); */
  /* io_send_byte(0x0D); */
  /* io_send_byte(0x0A); */
  /* Ongibit(0x10); */
}


void io_done()
{
  Offgibit(0x10);
}
