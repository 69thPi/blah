#ifndef res
#define res


struct grid{
  double data;
  double del_x;
  double del_y;
  double x_e;
  double x_w;
  double y_n;
  double y_s;
  double ap;
  double an;
  double as;
  double ae;
  double aw;
  int eqn;
};

void dir_solve_cell(int,int,int);

#endif
