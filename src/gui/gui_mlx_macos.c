#include "mlx.h"

int      mlx_string_put_to_image(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y, int color, char *string)   //@asarandi
{
    (void)img_ptr;
    return (mlx_string_put(mlx_ptr, win_ptr, x, y, color, string));
}
