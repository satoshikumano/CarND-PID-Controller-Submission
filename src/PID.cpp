#include "PID.h"
#include <math.h>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double taup, double taud, double taui) {
    this->cte_sum = 0.;
    this->cte_ave = 0.;
    this->cte_best = 100000.;
    this->count = 0;
    this->has_prev = false;
    this->dp = 0.01;
    this->dd = 0.01;
    this->di = 0.0001;
    this->step = 0.05;
    this->taup = taup;
    this->taud = taud;
    this->taui = taui;
}

void PID::UpdateParams(double cte) {
    double sum = dp + dd + di;
    cout << "dsum: " << sum << endl;
    if (sum < 0.0001) {
        return;
    }
    int index = count % 9;
    if (index == 0) {
        taup += dp;
    }
    else if (index == 1) {
        if (fabs(cte) < fabs(cte_best)) {
            dp *= (1. + step);
            cte_best = cte;
        } else {
            taup -= 2. * dp;
        }
    }
    else if (index == 2) {
        if (fabs(cte) < fabs(cte_best)) {
            dp *= (1. + step);
            cte_best = cte;
        } else {
            taup += dp;
            dp *= (1. - step);
        }
    }
    else if (index == 3) {
        taud += dd;
    }
    else if (index == 4) {
        if (fabs(cte) < fabs(cte_best)) {
            dd *= (1. + step);
            cte_best = cte;
        } else {
            taud -= 2. * dd;
        }
    }
    else if (index == 5) {
        if (fabs(cte) < fabs(cte_best)) {
            dd *= (1. + step);
            cte_best = cte;
        } else {
            taud += dd;
            dd *= (1. - step);
        }
    }
    else if (index == 6) {
        taui += di;
    }
    else if (index == 7) {
        if (fabs(cte) < fabs(cte_best)) {
            di *= (1. + step);
            cte_best = cte;
        } else {
            taui -= 2. * di;
        }
    }
    else if (index == 8) {
        if (fabs(cte) < fabs(cte_best)) {
            di *= (1. + step);
            cte_best = cte;
        } else {
            taui += di;
            di *= (1. - step);
        }
    }
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
    cte_ave = cte_sum / (double)count;
    if (twiddle_optimization) {
        UpdateParams(cte);
    }

    p_error = cte * taup;
    d_error = diff * taud;
    i_error = cte_sum * taui;
}

double PID::TotalError() {
    return p_error + d_error + i_error;
}