#include <gem.h>
#include <windom.h>
#include <stdint.h>
#include <stdlib.h>
#include "appl.h"
#include "protocol.h"
#include "screen.h"
#include "screen_queue.h"
#include <osbind.h>

extern unsigned char splash[];
extern short splash_size;
extern DrawElement* screen_queue;

int16_t magic_os=FALSE;                // Are we running under MagiC?
int16_t mint_os=FALSE;                 // Are we running under MINT?
int16_t full_screen=FALSE;             // Are we running full screen? 
int16_t appl_atari_hi_res=FALSE;       // Are we in Atari Hi Res (640x400?)
int16_t appl_atari_med_res=FALSE;      // Are we in Atari Med Res (640x200?)
int16_t appl_atari_low_res=FALSE;      // Are we in Atari Low Res (640x200?)
WINDOW* win;
int16_t window_x, window_y;            // Window coordinates

static void appl_redraw(WINDOW* win,short wbuff[8])
{
  short xw, yw, ww, hw; // Window dimensions
  short xy[8];

  wind_get(app.aeshdl,WF_WORKXYWH,&xw,&yw,&ww,&hw);
  window_x=xw;
  window_y=yw;

  wind_update(BEG_UPDATE);
  appl_clear_screen();
  v_show_c(app.aeshdl,1);
  screen_redraw();
  wind_update(END_UPDATE);

}

/**
 * Initialize the application context
 */
void applinit(void)
{
  short xw,yw,ww,hw;
  ApplInit();

  // Detect if we are under MagiC or MINT
  magic_os = vq_magx();
  mint_os = vq_mint();

  // Determine if we need to go full screen
  full_screen=appl_get_fullscreen();
    
  // Create the window.
  if (full_screen==TRUE)
    win=WindCreate(WAT_ALL,app.x,app.y,app.w,app.h);
  else
    win = WindCreate( NAME|MOVER|CLOSER, app.x, app.y, app.w, app.h);
  
  if (full_screen==TRUE)
    WindOpen( win, app.x, app.y, app.x+app.w, app.y+app.h);
  else
    WindOpen( win, app.x, app.y, 512, 512);
  WindSetStr( win, WF_NAME, "PLATOTerm ST");

  wind_get(app.aeshdl,WF_WORKXYWH,&xw,&yw,&ww,&hw);
  window_x=xw;
  window_y=yw;

  FormAlert(1, "[x: %d y: %d w: %d h: %d][OK]",xw,yw,ww,hw);
  
  EvntAttach(win,WM_REDRAW,appl_redraw);
  
}

/**
 * Application main loop
 */
void applmain(void)
{
  appl_clear_screen();
  ShowPLATO((padByte *)splash,splash_size);
  
  for (;;)
    EvntWindom( MU_MESAG|MU_TIMER|MU_KEYBD|MU_BUTTON);
}

/**
 * Restore from full screen
 */
void appl_restore_screen( void)
{
  form_dial( FMD_FINISH, 0, 0, 1 + app.work_out[0], 1 + app.work_out[1], 0, 0, 1 + app.work_out[0], 1 + app.work_out[1]);
  v_show_c( app.aeshdl, 0);
}

/**
 * Clear screen
 */
void appl_clear_screen(void)
{
  short xy[8];
  short xw,yw,ww,hw;

  if (full_screen==true)
    {
      vswr_mode( app.aeshdl, MD_REPLACE);
      form_dial( FMD_START, 0, 0, 1 + app.work_out[0], 1 + app.work_out[1], 0, 0, 1 + app.work_out[0], 1 + app.work_out[1]);
      vsf_perimeter( app.aeshdl, 0);
      vsf_interior( app.aeshdl, FIS_SOLID);
      xy[0] = xy[1] = 0;
      xy[2] = app.work_out[0];
      xy[3] = app.work_out[1];
    }
  else // Windowed.
    {
      WindClear(win);
    }
}

/**
 * Set the PLATO display as fullscreen
 */
void appl_fullscreen(void)
{
  short	screenw = app.work_out[0] + 1;	// bottom-right X
  short	screenh = app.work_out[1] + 1;	// bottom-right Y
  MFDB 	*out, resized_out = { NULL, screenw, screenh, 0, 0, 0, 0, 0, 0}, screen = {0};
  short	posx, posy, xy[8];
  short pxy[4];

  appl_clear_screen();
  
}

/**
 * Return whether full screen is needed.
 */
short appl_get_fullscreen(void)
{
  // Set full screen if screen is small enough.
  if (app.work_out[0]==639 && app.work_out[1]==399)
    appl_atari_hi_res=TRUE;
  else if (app.work_out[0]==639 && app.work_out[1]==199)
    appl_atari_med_res=TRUE;
  else if (app.work_out[0]==319 && app.work_out[1]==199)
    appl_atari_low_res=TRUE;

  if (appl_atari_hi_res==TRUE || appl_atari_med_res==TRUE || appl_atari_low_res==TRUE)
    {
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

/**
 * Initialize the off-screen bitmap for terminal.
 */
void appl_terminal_bitmap_init(void)
{
  
}
