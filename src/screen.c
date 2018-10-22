
#include "protocol.h"
#include "screen.h"
#include "terminal.h"

unsigned char CharWide=8;
unsigned char CharHigh=16;
padPt TTYLoc;
extern padBool FastText; /* protocol.c */

/**
 * screen_init() - Set up the screen
 */
void screen_init(void)
{
}

/**
 * screen_load_driver()
 * Load the TGI driver
 */
void screen_load_driver(void)
{
}

/**
 * screen_init_hook()
 * Called after tgi_init to set any special features, e.g. nmi trampolines.
 */
void screen_init_hook(void)
{
}

/**
 * screen_wait(void) - Sleep for approx 16.67ms
 */
void screen_wait(void)
{
}

/**
 * screen_beep(void) - Beep the terminal
 */
void screen_beep(void)
{
}

/**
 * screen_remap_palette(void)
 * Remap the screen palette
 */
void screen_remap_palette(void)
{
}

/**
 * screen_clear - Clear the screen
 */
void screen_clear(void)
{
}

/**
 * screen_block_draw(Coord1, Coord2) - Perform a block fill from Coord1 to Coord2
 */
void screen_block_draw(padPt* Coord1, padPt* Coord2)
{

  if (CurMode==ModeErase || CurMode==ModeInverse)
    {
      /* vsf_color(app.aeshdl,background_color_index); */
    }
  else
    {
      /* vsf_color(app.aeshdl,foreground_color_index); */
    }
  
  /* v_bar(app.aeshdl,pxyarray); */
}

/**
 * screen_dot_draw(Coord) - Plot a mode 0 pixel
 */
void screen_dot_draw(padPt* Coord)
{
    switch(CurMode)
    {
    case ModeWrite:
      /* vswr_mode(app.aeshdl,1); */
      break;
    case ModeErase:
      /* vswr_mode(app.aeshdl,3); */
      break;
    }
  
  /* vsl_type(app.aeshdl,1); */
  /* v_pline(app.aeshdl,2,pxyarray); */
}

/**
 * screen_line_draw(Coord1, Coord2) - Draw a mode 1 line
 */
void screen_line_draw(padPt* Coord1, padPt* Coord2)
{
  switch(CurMode)
    {
    case ModeWrite:
      /* vsl_color(app.aeshdl,foreground_color_index); */
      break;
    case ModeErase:
      /* vsl_color(app.aeshdl,background_color_index); */
      break;
    }

  /* vsl_type(app.aeshdl,1); */
  /* v_pline(app.aeshdl,2,pxyarray); */
}

/**
 * screen_char_draw(Coord, ch, count) - Output buffer from ch* of length count as PLATO characters
 */
void screen_char_draw(padPt* Coord, unsigned char* ch, unsigned char count)
{
}

/**
 * screen_tty_char - Called to plot chars when in tty mode
 */
void screen_tty_char(padByte theChar)
{
  if ((theChar >= 0x20) && (theChar < 0x7F)) {
    screen_char_draw(&TTYLoc, &theChar, 1);
    TTYLoc.x += CharWide;
  }
  else if ((theChar == 0x0b)) /* Vertical Tab */
    {
      TTYLoc.y += CharHigh;
    }
  else if ((theChar == 0x08) && (TTYLoc.x > 7))	/* backspace */
    {
      TTYLoc.x -= CharWide;
      /* vsf_color(app.aeshdl,0); */
      /* vsf_interior(app.aeshdl,1); */
      /* v_bar(app.aeshdl,pxyarray); */
      /* vsf_color(app.aeshdl,1); */
    }
  else if (theChar == 0x0A)			/* line feed */
    TTYLoc.y -= CharHigh;
  else if (theChar == 0x0D)			/* carriage return */
    TTYLoc.x = 0;
  
  if (TTYLoc.x + CharWide > 511) {	/* wrap at right side */
    TTYLoc.x = 0;
    TTYLoc.y -= CharHigh;
  }
  
  if (TTYLoc.y < 0) {
    screen_clear();
    TTYLoc.y=495;
  }

}

/**
 * screen_done()
 * Close down TGI
 */
void screen_done(void)
{
}

/**
 * Set foreground color
 */
void screen_foreground(padRGB* theColor)
{
}

/**
 * Set background color
 */
void screen_background(padRGB* theColor)
{
}

/**
 * paint
 */
void screen_paint(padPt* Coord)
{
}

