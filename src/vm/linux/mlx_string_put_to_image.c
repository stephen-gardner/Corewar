//@asarandi
#include "mlx_int.h"

int        mlx_string_put_to_image(t_xvar *xvar,t_win_list *win, t_img *img, int x, int y, int color, char *string)
{
	XGCValues    xgcv;

	xgcv.foreground = mlx_int_get_good_color(xvar,color);
	XChangeGC(xvar->display,win->gc,GCForeground,&xgcv);
	XDrawImageString(xvar->display,img->pix,win->gc,x,y,string,strlen(string));
	if (xvar->do_flush)
		XFlush(xvar->display);
	return (0);
}
