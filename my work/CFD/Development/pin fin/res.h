#ifndef res
#define res

struct grid{
  double data;
  double del_x;
  double x_e;
  double x_w;
  double ap;
  double ae;
  double aw;
  double lhs;
};
extern double T_inf;
void iterations(void);
#endif
