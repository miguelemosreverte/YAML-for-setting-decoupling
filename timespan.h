#ifndef TIMESPAN_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TIMESPAN_H

#include <sys/timeb.h>

int getMilliCount();
int getMilliSpan(int a);

#endif
