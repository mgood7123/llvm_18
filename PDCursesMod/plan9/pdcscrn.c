#include <pdcurses_curspriv.h>
#include <stdlib.h>
#include "pdcplan9.h"

bool PDC_can_change_color(void)
{
	PDC_LOG(("PDC_can_change_color() - called.\n"));

	return FALSE;
}


int PDC_color_content(int color, int *red, int *green, int *blue)
{
	PDC_LOG(("PDC_color_content() - called.\n"));

	return ERR;
}


int PDC_init_color(int color, int red, int green, int blue)
{
	PDC_LOG(("PDC_init_color() - called. Lines: %d Cols: %d\n", color,
		 red, green, blue));

	return OK;
}


int PDC_scr_open(void)
{
	PDC_LOG(("PDC_scr_open() - called\n"));

	SP = calloc(1, sizeof(SCREEN));
	if (!SP)
		return ERR;

	p9init();
	SP->cols = PDC_get_columns();
	SP->lines = PDC_get_rows();
	SP->cursrow = SP->curscol = 0;
	SP->orig_attr = FALSE;
	SP->orig_cursor = 0;

	return OK;
}


void PDC_scr_close(void)
{
	PDC_LOG(("PDC_scr_close() - called\n"));
}


void PDC_reset_shell_mode(void)
{
	PDC_LOG(("PDC_reset_shell_mode() - called\n"));
}


int PDC_resize_screen(int nlines, int ncols)
{
	PDC_LOG(("PDC_resize_screen() - called. Lines: %d Cols: %d\n",
		 nlines, ncols));

	if( !stdscr)     /* We're trying to specify an initial screen size */
	{                /* before calling initscr().  This works on some  */
		return OK;   /* some platforms,  but not this one.             */
	}

	if (nlines == 0 && ncols == 0)
		return OK;

	p9resize(nlines, ncols);
	SP->resized = FALSE;
	SP->cursrow = SP->curscol = 0;

	return OK;
}


void PDC_reset_prog_mode(void)
{
	PDC_LOG(("PDC_reset_prog_mode() - called.\n"));
}


void PDC_restore_screen_mode(int)
{
	PDC_LOG(("PDC_restore_screen_mode() - called.\n"));
}


void PDC_save_screen_mode(int)
{
	PDC_LOG(("PDC_save_screen_mode() - called.\n"));
}


void PDC_scr_free(void)
{
	free(SP);
}
