#include "geometry.h"

double range_2D(point_2D A, point_2D B)
{
	return sqrt((B.x - A.x)*(B.x - A.x) + (B.y - A.y)*(B.y - A.y));
}

double range_line_2D(point_2D M, double A, double B, double C)
{
	return (A*M.x + B*M.y + C)/sqrt(A*A + B*B);
}

point_2D cross_line_2D(double A1, double B1, double C1, double A2, double B2, double C2)
{
	point_2D M;
	if((A1*B2 - A2*B1) == 0) return inf_pos_2D;
	else {
			M.x = -(C1*B2 - C2*B1)/(A1*B2 - A2*B1);
			M.y = -(A1*C2 - A2*C1)/(A1*B2 - A2*B1);
		}
	return M;
}

double range_3D(point_3D A, point_3D B)
{
	return sqrt((B.x - A.x)*(B.x - A.x) + (B.y - A.y)*(B.y - A.y) + (B.z - A.z)*(B.z - A.z));
}