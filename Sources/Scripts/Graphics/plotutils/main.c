#include <stdio.h>
#include <plot.h>
#define MAXORDER 12
void draw c curve (plPlotter *plotter, double dx, double dy, int order)
{
	if (order >= MAXORDER)
		/* continue path along (dx, dy) */
		pl fcontrel r (plotter, dx, dy);
	else {
		draw c curve (plotter,
		              0.5 * (dx - dy), 0.5 * (dx + dy), order + 1);
		draw c curve (plotter,
		              0.5 * (dx + dy), 0.5 * (dy - dx), order + 1);
	}
}
int main ()
{
	plPlotter *plotter;
	plPlotterParams *plotter params;
	/* set a Plotter parameter */
	plotter params = pl newplparams ();
	pl setplparam (plotter params, "PAGESIZE", "letter");
	/* create a Postscript Plotter that writes to standard output */
	if ((plotter = pl newpl r ("ps", stdin, stdout, stderr,
	                           plotter params)) == NULL) {
		fprintf (stderr, "Couldn’t create Plotter\n");
		return 1;
	}
	if (pl openpl r (plotter) < 0) { /* open Plotter */
		fprintf (stderr, "Couldn’t open Plotter\n");
		return 1;
	}
	pl fspace r (plotter, 0.0, 0.0, 1000.0, 1000.0); /* set coor system */
	pl flinewidth r (plotter, 0.25); /* set line thickness */
	pl pencolorname r (plotter, "red"); /* use red pen */
	pl erase r (plotter); /* erase graphics display */
	pl fmove r (plotter, 600.0, 300.0); /* position the graphics cursor */
	draw c curve (plotter, 0.0, 400.0, 0);
	if (pl closepl r (plotter) < 0) { /* close Plotter */
		fprintf (stderr, "Couldn’t close Plotter\n");
		return 1;
	}
	if (pl deletepl r (plotter) < 0) { /* delete Plotter */
		fprintf (stderr, "Couldn’t delete Plotter\n");
		return 1;
	}
	return 0;
}