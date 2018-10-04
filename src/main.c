#include <stdbool.h>
#include <stdlib.h>
#include <gem.h>
#include <windom.h>
#include "protocol.h"
#include "screen.h"
#include "io.h"
#include "terminal.h"
#include "keyboard.h"

unsigned char already_started=false;

extern padByte splash[];
extern short appl_init_successful;

int main(void)
{
  config_init();
  io_init();
  screen_init();
  applinit();
  graf_mouse(M_OFF,NULL);
  terminal_show_greeting();
  graf_mouse(M_ON,NULL);
  terminal_init();
  already_started=true;
  appl_show_menu();
  
  if (appl_init_successful==true)
    {
      applmain();
      terminal_done();
      appldone();
      return 0;
    }
  else
    {
      terminal_done();
      appldone();
      return -1;
    }
}
