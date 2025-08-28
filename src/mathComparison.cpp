#include "mathComparison.h"
#include "solver.h"

#include <math.h>
int mathComparison( double firstNumber, double secondNumber ) {
    if (  fabs( firstNumber - secondNumber ) <= delta ) {
        return 1;
    }
    else {
        return 0;
    }
}