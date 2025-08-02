#ifndef ASTROWRAP_H_
#define ASTROWRAP_H_

#include <array>

namespace astrowrap {

/* -------------------------------------------------------------------------- */

/* Celestial objects (luminaries, planets, comets, celestial points). */
enum CelestialPoint_t {
  Sun,
  Moon,
  Mercury,
  Venus,
  Mars,
  Jupiter,
  Saturn,
  Uranus,
  Neptune,
  Pluto,
  kNumRulerPlanets,

  TrueNode = kNumRulerPlanets,
  // Chiron,

  kNumCelestialPoints
};

/* Western Zodiac Signs. */
enum Zodiac_t {
  Aries,
  Taurus,
  Gemini,
  Cancer,
  Leo,
  Virgo,
  Libra,
  Scorpio,
  Sagittarius,
  Capricorn,
  Aquarius,
  Pisces,

  kNumZodiacs
};

/* Placidus houses and elements. */
enum Placidus_t {
  FirstHouse,
  SecondHouse,
  ThirdHouse,
  FourthHouse,
  FifthHouse,
  SixthHouse,
  SeventhHouse,
  EightHouse,
  NinethHouse,
  TenthHouse,
  EleventhHouse,
  TwelfthHouse,
  kNumPlacidusHouses,

  Ascendant = kNumPlacidusHouses,
  MediumCoeli,

  kNumPlacidusElements
};

/* -------------------------------------------------------------------------- */

enum AspectType_t {
  None = -1,

  Conjunction = 0,
  Sextile,
  Square,
  Trine,
  Opposition,

  kNumAspectTypes
};

struct Aspect_t {
  AspectType_t type = None;
  int orb = 0;
};

using AspectMatrix_t = std::array<std::array<Aspect_t, kNumCelestialPoints>, kNumCelestialPoints>;

/* -------------------------------------------------------------------------- */

struct PreciseAngle_t {
  PreciseAngle_t(int _degree, int _minute, double _second)
    : degree(_degree)
    , minute(_minute)
    , second(_second)
  {}

  PreciseAngle_t()
   : PreciseAngle_t(0, 0, 0.0)
  {} 
  
  PreciseAngle_t(const PreciseAngle_t &a, const PreciseAngle_t &b)
    : degree(b.degree - a.degree)
    , minute(b.minute - a.minute)
    , second(b.second - a.second)
  {
    if (second < 0.0) {
      minute -= 1;
      second += 60.0;
    }
    if (minute < 0) {
      degree -= 1;
      minute += 60;
    }
    degree = (360 + degree) % 360;
  }

  int degree;
  int minute;
  double second;

  Zodiac_t zodiac() const { return static_cast<Zodiac_t>(degree / 30); }
};

template<typename T>
struct ChartData_t {
  T                 id;  
  PreciseAngle_t    angle;
  char const*       pname; //
  char const*       pname_sign; //
};

using CelestialChartData_t = ChartData_t<CelestialPoint_t>;
using PlacidusChartData_t  = ChartData_t<Placidus_t>;

/* -------------------------------------------------------------------------- */

using LongLat_t = double;

struct GeoLocation_t {
  GeoLocation_t() = default;

  GeoLocation_t(double _longitude, double _latitude, int _timezone)
   : longitude(_longitude)
   , latitude(_latitude)
   , timezone(_timezone)
  {}

  LongLat_t longitude;
  LongLat_t latitude; 
  int timezone;
};

struct TimeData_t {
  TimeData_t() = default;
  
  TimeData_t(int _year, int _month, int _day, int _hour, int _minute, GeoLocation_t _geoloc)
    : year(_year)
    , month(_month)
    , day(_day)
    , hour(_hour)
    , minute(_minute)
    , geoloc(_geoloc)
  {}

  explicit 
  TimeData_t(GeoLocation_t _geoloc);

  int year;
  int month;
  int day;
  int hour;
  int minute;
  GeoLocation_t geoloc;
};

/* -------------------------------------------------------------------------- */

struct AstroChart_t {
  TimeData_t timeData;

  std::array<CelestialChartData_t, kNumCelestialPoints> planets;
  std::array<PlacidusChartData_t, kNumPlacidusElements> placidus;
  std::array<Placidus_t, kNumCelestialPoints> planetInHouse;
  AspectMatrix_t aspects;

  struct {
    int nyin  = 0;
    int nyang = 0;
  } polarity;

  struct {
    int ncardinal = 0;    // sulfur-soul
    int nfixed    = 0;    // salt-body
    int nmutable  = 0;    // mercury-mind
  } quality;

  struct {
    int fire  = 0;
    int earth = 0;
    int air   = 0;
    int water = 0;
  } elements;

  explicit 
  AstroChart_t(TimeData_t timeData);
  
  void display(bool bOutputHTML, bool bCondenseDisplay = false) const;

  void displayTransit(AstroChart_t const& chart, bool bOutputHTML) const;
};

/* -------------------------------------------------------------------------- */

} // namespace "astrowrap"

#endif // ASTROWRAP_H_