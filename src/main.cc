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
#include <cstdio>
#include "astrowrap.h"

/* -------------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
  // Native.
  auto const nativeLocation = astrowrap::GeoLocation_t(2.31, 48.49, +1);
  astrowrap::TimeData_t native(1988, 1, 28, 12 - nativeLocation.timezone, 20, nativeLocation); //
  astrowrap::AstroChart_t nativeChart(native);

  // Transit.
  astrowrap::TimeData_t hereAndNow(astrowrap::GeoLocation_t(2.45, 48.52, +1));
  astrowrap::AstroChart_t currentChart(hereAndNow);

  // Charts.
  const bool bOutputHTML = false;
  nativeChart.display(bOutputHTML, false);

  // Transits.
  if (!bOutputHTML) {
    fprintf(stderr, "\n\n");
  }
  currentChart.displayTransit(nativeChart, bOutputHTML);
  // nativeChart.displayTransit(currentChart, bOutputHTML);

  return EXIT_SUCCESS;
}

/* -------------------------------------------------------------------------- */
