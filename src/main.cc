//
// g++ -I . swe/*.c *.cc -DNO_SWE_GLP -Wno-write-strings -o astrowrap
//
//   TODO :
//     * transit,
//     * synastry,
//     * speed (for retrograde),
//     * check consistency with weird locations and other charts.
//

#include <cstdlib>

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "astrowrap.h"

/* -------------------------------------------------------------------------- */

std::map<std::string, std::string> parse_args(int argc, char* argv[])
{
  std::map<std::string, std::string> args;

  for (int i = 1; i < argc - 1; ++i) {
    std::string key = argv[i];
    if (key.rfind("--", 0) == 0) {
      std::string value = argv[i + 1];
      if (value.rfind("--", 0) != 0) {
        args[key] = value;
        ++i;
      } else {
        args[key] = "";
      }
    }
  }
  return args;
}

std::vector<std::string> split(const std::string &s, char delimiter)
{
  std::vector<std::string> tokens;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delimiter)) {
    tokens.push_back(item);
  }
  return tokens;
}

/* -------------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
  auto args = parse_args(argc, argv);

  auto const bOutputHTML{ args.find("--output-html") != args.end() };
  auto const bCompact{ args.find("--compact") != args.end() };

  if (args.find("--date") == args.end() ||
      args.find("--time") == args.end() ||
      args.find("--gps")  == args.end()) {
    std::cerr << "Usage: " << argv[0]
              << " --gps LAT,LON --date YYYY/MM/DD --time HH:MM"
              << std::endl
              ;
    return EXIT_FAILURE;
  }

  float latitude = 0.0f, longitude = 0.0f;
  {
    std::vector<std::string> gps{ split(args["--gps"], ',') };
    if (gps.size() == 2) {
      latitude = std::stof(gps[0]);
      longitude = std::stof(gps[1]);
    }
  }

  unsigned int year = 0, month = 0, day = 0;
  {
    std::vector<std::string> date{ split(args["--date"], '/') };
    if (date.size() == 3) {
      year = std::stoul(date[0]);
      month = std::stoul(date[1]);
      day = std::stoul(date[2]);
    }
  }

  unsigned int hour = 0, minute = 0;
  {
    std::vector<std::string> time{ split(args["--time"], ':') };
    if (time.size() == 2) {
      hour = std::stoul(time[0]);
      minute = std::stoul(time[1]);
    }
  }

  // ----------------

  // Native.
  auto const nativeLocation = astrowrap::GeoLocation_t(longitude, latitude, 0);
  astrowrap::TimeData_t native(year, month, day, hour, minute, nativeLocation); //
  astrowrap::AstroChart_t nativeChart(native);

  // Charts.
  nativeChart.display(bOutputHTML, bCompact);

  // Transit.
  // astrowrap::TimeData_t hereAndNow(astrowrap::GeoLocation_t(2.45, 48.52, +1));
  // astrowrap::AstroChart_t currentChart(hereAndNow);
  // if (!bOutputHTML) {
  //   fprintf(stderr, "\n\n");
  // }
  // currentChart.displayTransit(nativeChart, bOutputHTML);
  // nativeChart.displayTransit(currentChart, bOutputHTML);

  return EXIT_SUCCESS;
}

/* -------------------------------------------------------------------------- */
