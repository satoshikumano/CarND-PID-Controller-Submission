#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  double cte_prev;
  bool has_prev;
  double cte_sum;
  long long count;
  double cte_ave;
  
  /*
  * Coefficients
  */ 
  double taup;
  double taui;
  double taud;

  /*
  * Twiddle params
  */
  double dp;
  double di;
  double dd;
  double step;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  void UpdateParams(double cte);

};

#endif /* PID_H */
