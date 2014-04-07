#include <math.h>
#include <float.h>

typedef struct {
				double x,y;
		} point_2D;
		
typedef struct {
				double x,y,z;
		} point_3D;
		
const point_2D inf_pos_2D = {DBL_MAX,DBL_MAX};
const point_3D inf_pos_3D = {DBL_MAX,DBL_MAX,DBL_MAX};
const point_2D inf_neg_2D = {DBL_MIN,DBL_MIN};
const point_3D inf_neg_3D = {DBL_MIN,DBL_MIN,DBL_MIN};
		
double range_2D(point_2D, point_2D);
double range_line_2D(point_2D, double, double, double);
point_2D cross_line_2D(double, double, double, double, double, double);

double range_3D(point_3D, point_3D);