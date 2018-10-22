#include	<GODLIB\GEMDOS\GEMDOS.H>
#include	<GODLIB\GRAPHIC\GRAPHIC.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\MEMORY\MEMORY.H>
#include	<GODLIB\SYSTEM\SYSTEM.H>
#include	<GODLIB\VBL\VBL.H>
#include	<GODLIB\VIDEO\VIDEO.H>
#include "protocol.h"
#include "screen.h"
#include "io.h"
#include "terminal.h"
#include "keyboard.h"

unsigned char already_started=false;

extern padByte splash[];

short GodLib_Game_Main( short aArgCount, short * apArgs[] )
{
  (void)aArgCount;
  (void)apArgs;
  
  GemDos_Super( 0 );
  
  return 0;
}
