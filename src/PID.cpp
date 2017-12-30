#include "PID.h"
#include <math.h>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double taup, double taud, double taui) {
    this->cte_sum = 0.;
    this->count = 0;
    this->has_prev = false;
    this->taup = taup;
    this->taud = taud;
    this->taui = taui;
}

void PID::UpdateError(double cte) {
    ++count;
    if (!has_prev) {
        cte_prev = cte;
    }
    double diff = cte - cte_prev;
    cte_prev = cte;
    has_prev = true;

    cte_sum += cte;

    p_error = cte * taup;
    d_error = diff * taud;
    i_error = cte_sum * taui;
}

double PID::TotalError() {
    return p_error + d_error + i_error;
}