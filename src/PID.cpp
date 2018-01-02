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
    this->count = 0;
    this->has_prev = false;
    this->dp = 0.01;
    this->dd = 0.;
    this->di = 0.;
    this->step = 0.05;
    this->taup = taup;
    this->taud = taud;
    this->taui = taui;
}

void PID::UpdateParams(double cte) {
    cout << "dp: " << dp << endl;
    if (dp + dd + di < 0.0001) {
        return;
    }
    int index = count % 9;
    if (index == 0) {
        taup += dp;
    }
    else if (index == 1) {
        if (cte < cte_ave) {
            dp *= (1. + step);
        } else {
            taup -= 2. * dp;
        }
    }
    else if (index == 2) {
        if (cte < cte_ave) {
            dp *= (1. + step);
        } else {
            taup += dp;
            dp *= (1. - step);
        }
    }
    else if (index == 3) {
        taud += dd;
    }
    else if (index == 4) {
        if (cte < cte_ave) {
            dd *= (1. + step);
        } else {
            taud -= 2. * dd;
        }
    }
    else if (index == 5) {
        if (cte < cte_ave) {
            dd *= (1. + step);
        } else {
            taud += dd;
            dd *= (1. - step);
        }
    }
    else if (index == 6) {
        taui += di;
    }
    else if (index == 7) {
        if (cte < cte_ave) {
            di *= (1. + step);
        } else {
            taui -= 2. * di;
        }
    }
    else if (index == 8) {
        if (cte < cte_ave) {
            di *= (1. + step);
        } else {
            taui += di;
            di *= (1. - step);
        }
    }
}

void PID::UpdateError(double cte) {
    ++count;
    cte_ave = (cte + cte_ave) / (double)count;
    if (!has_prev) {
        cte_prev = cte;
    }
    double diff = cte - cte_prev;
    cte_prev = cte;
    has_prev = true;

    cte_sum += cte;
    UpdateParams(cte);

    p_error = cte * taup;
    d_error = diff * taud;
    i_error = cte_sum * taui;
}

double PID::TotalError() {
    return p_error + d_error + i_error;
}