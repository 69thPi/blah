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

// void dir_solve_cell(int,int,int);
// double ret_bound_val(int);
// void solve_setup(void);
// void grid_read(void);
// void dsplay(void);
void iterations(void);

#endif
