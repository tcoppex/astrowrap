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

#include <cstdlib>
#include "astrowrap.h"

/* -------------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
  // Native.
  astrowrap::TimeData_t native;
  {
    int constexpr utc = +1;
    native.year   = 1988;
    native.month  = 1;
    native.day    = 28;
    native.hour   = 12 - utc;
    native.minute = 20;
    native.geoloc = astrowrap::GeoLocation_t(2.31, 48.49, utc);
  }
  astrowrap::AstroChart_t nativeChart(native);

  // Transit.
  astrowrap::TimeData_t hereAndNow(astrowrap::GeoLocation_t(2.45, 48.52, +1));
  astrowrap::AstroChart_t currentChart(hereAndNow);

  // Charts.
  nativeChart.display(false);
  currentChart.displayTransit(nativeChart);

  return EXIT_SUCCESS;
}

/* -------------------------------------------------------------------------- */
