//
// g++ -I . swe/*.c *.cc -DNO_SWE_GLP -Wno-write-strings -o astrowrap
//
//   TODO :
//     * handle UTC shift properly,
//     * transit,
//     * synastry,
//     * speed (for retrograde),
//     * check consistency with weird locations and other charts.
//

#include <cstdio>
#include <cstdlib>

#include "astrowrap.h"

/* -------------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
  astrowrap::TimeData_t data;
  data.year   = 2021;
  data.month  = 3;
  data.day    = 28;
  data.hour   = 11;     // here compensating (UTC + 9)
  data.minute = 20;
  data.geoloc = astrowrap::GeoLocation_t(129.06, 35.17, +9);

  astrowrap::AstroChart_t astrochart(data);
  astrochart.display(false);

  return EXIT_SUCCESS;
}

/* -------------------------------------------------------------------------- */
