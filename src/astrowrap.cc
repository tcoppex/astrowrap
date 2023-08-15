#include "astrowrap.h"

#include <ctime>
#include <string>
#include "swe/swephexp.h"
#include "swe/swephlib.h"

/* -------------------------------------------------------------------------- */

namespace {

/* Enum binding to Swiss Ephemeris planetoid id. */
enum SWEPlanetEnum {
  Sun       = SE_SUN,
  Moon,
  Mercury,
  Venus,
  Mars,
  Jupiter,
  Saturn,
  Uranus,
  Neptune,
  Pluto,
  TrueNode  = SE_TRUE_NODE,
  Chiron    = SE_MEAN_APOG + 3,
  //WhiteMoon = SE_CUPIDO + 25,
  //BlackMoon = SE_WALDEMATH,
};

} // namespace

/* -------------------------------------------------------------------------- */

namespace astrowrap {

struct PlanetData_t {
  char const* symbol;
  char const* name;
  char const* desc;
  SWEPlanetEnum sweEnum;
};

const std::array<PlanetData_t, kNumCelestialPoints> kPlanetDatas{
  "☉",  "Sun",        "Ego",              SWEPlanetEnum::Sun,
  "☽",  "Moon",       "Emotion",          SWEPlanetEnum::Moon,
  "☿",  "Mercury",    "Communication",    SWEPlanetEnum::Mercury,
  "♀",  "Venus",      "Pleasure",         SWEPlanetEnum::Venus,
  "♂",  "Mars",       "Action",           SWEPlanetEnum::Mars,
  "♃",  "Jupiter",    "Expansion",        SWEPlanetEnum::Jupiter,
  "♄",  "Saturn",     "Restriction",      SWEPlanetEnum::Saturn,
  "⛢",  "Uranus",     "Rebellion",        SWEPlanetEnum::Uranus,
  "♆",  "Neptune",    "Mystery",          SWEPlanetEnum::Neptune,
  "♇",  "Pluto",      "Death & Rebirth",  SWEPlanetEnum::Pluto,
  "☊",  "True Node",  "Karmic Goal",      SWEPlanetEnum::TrueNode,
  "⚷",  "Chiron",     "Wounded Healer",   SWEPlanetEnum::Chiron,
};

char const* PlanetSymbol(CelestialPoint_t p)    { return kPlanetDatas[p].symbol;  }
char const* PlanetName(CelestialPoint_t p)      { return kPlanetDatas[p].name;    }
char const* PlanetDesc(CelestialPoint_t p)      { return kPlanetDatas[p].desc;    }
SWEPlanetEnum PlanetSweEnum(CelestialPoint_t p) { return kPlanetDatas[p].sweEnum; }

/* -------------------------------------------------------------------------- */

struct ZodiacData_t {
  char const* symbol;
  char const* name;
  CelestialPoint_t ruler;
};

const std::array<ZodiacData_t, kNumZodiacs> kZodiacDatas{
   "♈",   "Aries",       Mars,
   "♉",   "Taurus",      Venus,
   "♊",   "Gemini",      Mercury,
   "♋",   "Cancer",      Moon,
   "♌",   "Leo",         Sun,
   "♍",   "Virgo",       Mercury,
   "♎",   "Libra",       Venus,
   "♏",   "Scorpio",     Pluto,
   "♐",   "Sagittarius", Jupiter,
   "♑",   "Capricorn",   Saturn,
   "♒",   "Aquarius",    Uranus,
   "♓",   "Pisces",      Neptune,
};


char const* ZodiacSymbol(Zodiac_t z)     { return kZodiacDatas[z].symbol; }
char const* ZodiacName(Zodiac_t z)       { return kZodiacDatas[z].name;   }
CelestialPoint_t ZodiacRuler(Zodiac_t z) { return kZodiacDatas[z].ruler;  }

/* -------------------------------------------------------------------------- */

struct PlacidusData_t {
  char const* name;
  char const* desc;
};

const std::array<PlacidusData_t, kNumPlacidusElements> kPlacidusDatas{
  // Self
  "1st",    "Self",
  "2nd",    "Values",
  "3rd",    "Bubble",
  // Environment
  "4th",    "Home",
  "5th",    "Life",
  "6th",    "Dailies",
  // Others
  "7th",    "Relations",
  "8th",    "Externals",
  "9th",    "Journeys",
  // Society
  "10th",   "Achievements",
  "11th",   "Networks",
  "12th",   "Retreat",
  
  "ASC",    "Projection", 
  "MC",     "Perception"
};

char const* PlacidusName(Placidus_t p) { return kPlacidusDatas[p].name; }
char const* PlacidusDesc(Placidus_t p) { return kPlacidusDatas[p].desc; }

/* -------------------------------------------------------------------------- */

struct AspectData_t {
  char const* symbol;
  char const* name;
  int degree;
};

const int kAspectMaxDegreeDiff{ 6 };

const std::array<AspectData_t, kNumAspectTypes> kAspectDatas{
  "☌",  "Conjunction",    0,
  "⚹",  "Sextile",        60,
  "□",  "Square",         90,
  "△",  "Trine",          120,
  "☍",  "Opposition",     180,   
};

char const* AspectSymbol(AspectType_t a) { return kAspectDatas[a].symbol; }
char const* AspectName(AspectType_t a)   { return kAspectDatas[a].name;   }
int AspectDegree(AspectType_t a)         { return kAspectDatas[a].degree; }

/* -------------------------------------------------------------------------- */

// French Youtube videos

// Zodiacs on Ascendant, Moon, Mecury, Venus, Mars.
const std::array<std::array<std::string, 5>, kNumZodiacs> kZodiacPlanetVideoId{
  "bdvnS_v7GIs", "6fpRIxVHT6U", "Ar2Y2SqXnoc", "Y6Oj6vwuRv0", "YUsOzvm3Ki4", 
  "bqGDVhHPoVg", "aCiiWsc6Rug", "v55HgutWulo", "KFqn8QcmYH0", "t4uIK01LAqQ",
  "Au_wrR1MI7s", "7TJK7Uvquvc", "uvOdIW-honQ", "0C32CZ7lnOY", "bCYZmYaDjJk",
  "PF8gJCToIwM", "SGVMcwxMe_o", "87Hh-2JJ0Gc", "V5kG8aHNC7Q", "MeTdx5LJiFQ", 
  "n2lXnTSBP_c", "LJQK1Qt43dE", "cdgiblOjC8o", "-b6Ls_ekaoc", "z-bQz0XwuM4",  
  "BSTBXWKDOo4", "2jkM9N_7dV0", "xMaIffcsSl4", "hoa0km94Ol4", "CQXzh25-wPc", 
  "wsUsni6FceY", "Jlx1HSbYtWY", "uLlHxHXB8vo", "gvlVRg2KVzM", "h7LjOoU5Ywk",
  "OtQ16qJ3C9U", "N8X68p37JNE", "MqOsxxXPquk", "Gywim2cQj5A", "9lXIc9qhEDM", 
  "u-V4aDUF92g", "1YFR_mkqgE0", "MpZM2E_Ncw0", "1ffMLalnQYA", "l8MyafU4nRk", 
  "fGb4sX_Lk9M", "0kLLTqhFFO8", "IpY7AS82guc", "gJ_0V72tX5s", "eAGi9_YlVdg", 
  "Y45z9FDqpKI", "eHnUj6mn6kg", "VkuVmLrkDlc", "5WDgpEQnue4", "eTE_qI3hoLo", 
  "37LKdVMWxW8", "Uv7VcJUCjWM", "crrBfgsSErQ", "DKvLkmckNPQ", "LZjxTqBuH3Q",
};

// Planet in houses.
const std::array<std::array<std::string, kNumRulerPlanets>, kNumPlacidusHouses> kPlanetsInHouseVideoId{
  "jj_LM6k7PBc", "cYC7ALvp5TI", "i1GZFf8S7GY", "rHpaGN2Qywo", "vJD8FscXLu8", "TGobXkRvwlk", "b9PqaUEMBYo", "BPKAmcLQS8U", "WxJux4wYrXo", "TXeQY8DKUiQ",
  "Y1cLTAUosLc", "mZwH_ehgSyk", "ZW9XvnuPE0g", "OhSfNOas9CE", "k7usQvqCqTM", "rSRxwE_jkmM", "vFCnDKX7vN8", "dwSTQU8Rz6w", "EzMDVkgrPX8", "BgwUqlSkpx0",
  "Fq1e3bnKqTE", "RS9D85tSWHI", "P48CHBe3hyw", "yRMuuiJu5Cw", "GSF7Wb27R4o", "gMHoYJJ3GmE", "GIvm1BSe9Ag", "YTxj1d36rYw", "Lrhq-49H2S0", "_F_2Phf2PQY",
  "YuhqjmllRvk", "OA3ahcCWOYw", "oJOu4elQre8", "4NJ_lm4fQHM", "sG4YXIwWfmI", "mIi8x6Csses", "dPzzCDRtP4o", "1Sp-1bTd2dc", "Dnld0EXZVKY", "TnuAXj1YQ5g",
  "raYbNm-koAo", "KAqf8och96U", "pjPW0mHIf4U", "Q2LcXIosix0", "jnS0TPWVAxs", "DnFV-286tiM", "FCfeR9KOMJA", "Q4wqo0DKHwg", "9-UEbB4LWGQ", "qDCQwNYSme0",
  "WiWFqQ8c-Q4", "5lXGQvWB8uQ", "7TJS3Tbp6e8", "_H1p4_HQPG8", "EaWSeG4NM-c", "0ArhoeiiKbg", "MGgMrwDR5ew", "DQkhqjyDEgQ", "a3jYKlhczcw", "5A9DXZjUnu8",
  "xaEk2QKdNos", "Xnb72BTYgGg", "WhvuOBfYxeE", "kCAlHGn2pLM", "HcxhNhiNFbw", "llOokrJzCwI", "detKIp4HqmY", "DR-KjngUjtA", "K0Ycr3biqkw", "HujOR8fRBsI",
  "fT30L0Q1bwA", "PrfebiZOQMQ", "bYGSZpHQjtw", "AgNq2tIIF-U", "PsVr4buUNvQ", "aRx7KSrFNnI", "Q4-LqX21rYU", "cg3KEGKvVP0", "yXsPNwJ7Y2Y", "bfbn3bjTiUU",
  "keByH8UhAC4", "8yaISZURw5s", "BcCRRD4pncg", "PKyHv3bEe9g", "GElrYspQU5I", "iOluqy0pvXE", "TZHM8ZmX0XE", "bZ914XDE0ns", "Wgton9QhIOg", "7jKhBYkvst4",
  "veaK_p3ktMw", "CE6WpmLxPJ8", "Gzatl3vRxEg", "vQ5vZ9GYSzU", "RxT0kQd8sZo", "LJ-Ah8zATjM", "_MPqfW00xkE", "r3Dww1w078w", "NafIp50G6p8", "tSnuyOU-ekU",
  "kXf9mE3jRZg", "oeaxCSv8iig", "Q6_EmRZ8xVg", "ahKpRpkJVYY", "Q8et9kplGrM", "sZqsMUVXAkc", "nfnnba4euBU", "jGQL6v2G5ik", "dE__RAjHkwo", "hCTQcc5_aAM",
  "blElgVGt3Wc", "P0p9cyBP91w", "LF4S2BmF8Us", "JIXVtXOF8pg", "Wqzzp8aapzQ", "4bvpKedefbM", "dQAas7206FU", "pCxU8gBev80", "5Y4o9f7CyTQ", "GKlIeHPuyKQ",
};

// North Node in houses.
const std::array<std::string, kNumPlacidusHouses> kNorthNodeInHouseVideoId{
  "3sykuFvkoXQ", "ZQnnQsYzNd4", "Hq1SXOrZhjs", "_1E0UFG566o", "lx0Io9aavgY", "Gl_If7vxHp4", "O5HavG74ZB8", "ChVh0rGG1rE", "K96BA2xRPhE", "uy83erTBSU4", "9WViJjbABBk", "0ZM7_BTnRKM",
};

// Aspects on Sun, Moon, Mercury, Venus, Mars.
const std::array<std::string, 50> kAspectVideoId{
  // Sun.
  "x4TASn7ZnJ4", "SoQuWxLD0pA", "D_5eUVWYinw", "ZZUFhVQciOU", "aizl9qnrvQs", "kcQcdyxKDOU", "8fryO1v3MnM", "Zf3C-Yx3MxU", "KFfHHLRHteQ", "HlZg9mGMOkU",
                 // Moon.
   "",           "iHD89j2Mcu4", "cFyMVJe1IOg", "nDwRXypO9gs", "Mo04aIwPS-8", "AgTlwHW8Pp0", "VlyWXIhUlUA", "mCdy9v0HJF8", "EkiWb9aTqO0", "GH2R19_9hKs",
                                // Mercury.
   "",           "",            "TDxPTDkYPaA", "oSCLQumLNSo", "n44w3SVSPho", "0c1bnTEuk_I", "fTxQ_Euj09Q", "Lk-wl6OXPWA", "uZvv9QsXoT8", "GIOMj90BA0I",
                                               //Venus.
   "",           "",            "",            "YA1ZVhRDXh8", "yoz5dh-lc6c", "NqX2wqy6bOM", "ABLw_30ykJk", "l00Y-_hl3Is", "3HC6_qxSn-I", "tYUvSe_otqQ",
                                                              // Mars.
   "",           "",            "",            "",            "t2OKa57u-MQ", "uaJUDyTkVFQ", "vcP-KV6EzIo", "-PeDmB8MCkQ", "GlSdwf5R9ZE", "cp3I-9Cjc0M"

  // ascendant
  //"lfvfbPsMG98", "c4Ghny3VcoE", "ujq1yhqrVsM", "lO-OPF_xZKE"
};

/* -------------------------------------------------------------------------- */

TimeData_t::TimeData_t(GeoLocation_t _geoloc) {
  std::time_t t = std::time(0);
  std::tm* localtime = std::localtime(&t);
  //tm.tm_isdst = 0;
  
  year   = localtime->tm_year + 1900;
  month  = localtime->tm_mon + 1;
  day    = localtime->tm_mday;
  hour   = localtime->tm_hour - _geoloc.timezone; // [will bug on edge cases]
  minute = localtime->tm_min;
  geoloc = _geoloc;
}

/* -------------------------------------------------------------------------- */

void ConvertCoordsToAngle(const std::array<double, 6> &coords, PreciseAngle_t &angle)
{
  const double deg{ swe_degnorm(coords[0] + 0.5 / 3600) };
  angle.degree = static_cast<int>(deg);

  const double minute{ (deg - angle.degree) * 60.0 };
  angle.minute = static_cast<int>(minute);

  angle.second = (minute - angle.minute) * 60.0;
}

/* -------------------------------------------------------------------------- */

AstroChart_t::AstroChart_t(TimeData_t _timeData)
  : timeData(_timeData)
{
  // Initialize the Swiss Ephemeris API and set path to the ephemerides files.
  const int32_t whicheph{ SEFLG_SWIEPH };
  swe_set_ephe_path("swe/ephe/");  
  
  // Transform the UTC date from Gregorian to Julian days.
  // (todo : manage timezone shift automatically)
  double dret[2]{};
  swe_utc_to_jd(
    timeData.year, 
    timeData.month, 
    timeData.day,
    timeData.hour, 
    timeData.minute, 
    0.0, // seconds, unused.
    SE_GREG_CAL, 
    dret, 
    nullptr
  );
  
  // Compensate UTC time with delta.
  const double delta{ swe_deltat_ex(dret[1], whicheph, nullptr) };
  const double t{ dret[1] + delta };

  // Set geographical location.
  const double top_long{ timeData.geoloc.longitude };
  const double top_lat{ timeData.geoloc.latitude };
  swe_set_topo(timeData.geoloc.longitude, timeData.geoloc.latitude, 0.0);

  std::array<double, 6> coords{};

  // Retrieve each planet longitudinal coordinate.
  for (int i = 0; i < kNumCelestialPoints; ++i) {
    auto &p = planets[i];
    p.id = CelestialPoint_t(i);

    swe_calc(t, PlanetSweEnum(p.id), whicheph, coords.data(), nullptr);
    ConvertCoordsToAngle(coords, p.angle);

    p.pname      = PlanetName(p.id);
    p.pname_sign = ZodiacName(p.angle.zodiac()); 
  }

  // Retrieve each house longitudinal coordinate.
  double cusp[37];
  double cusp_speed[37];
  double ascmc[10];
  double ascmc_speed[10];
  swe_houses_ex2(t, whicheph, top_lat, top_long, 'P', cusp, ascmc, cusp_speed, ascmc_speed, nullptr);
  for (int i = 0; i < kNumPlacidusElements; ++i) {
    if (i <= Placidus_t::TwelfthHouse) {
      int id = i + 1;
      coords[0] = cusp[id];
      coords[3] = cusp_speed[id];
    } else {
      int id = i - Placidus_t::TwelfthHouse-1;
      coords[0] = ascmc[id];
      coords[3] = ascmc_speed[id];
    }
    coords[1] = 0.0;
    coords[2] = 1.0;

    auto &p = placidus[i];
    p.id = Placidus_t(i);
    ConvertCoordsToAngle(coords, p.angle);
    p.pname      = PlacidusName(p.id);
    p.pname_sign = ZodiacName(p.angle.zodiac()); 
  }

  // Compare two precise angles.
  auto geqAngle = [](const PreciseAngle_t &a, const PreciseAngle_t &b) {
    return (a.degree >= b.degree)
        || ((a.degree == b.degree) && (a.minute >= b.minute))
        || ((a.degree == b.degree) && (a.minute == b.minute) && (a.second >= b.second));
  };

  // Return true if x is between a and b.
  auto angleIsBetween = [&geqAngle](const PreciseAngle_t &x, const PreciseAngle_t &a, const PreciseAngle_t &b) {
    PreciseAngle_t dAB(a, b);
    PreciseAngle_t dXB(x, b);

    return geqAngle(dAB, dXB);
  };

  // Planet in houses.
  for (const auto &p : planets) {
    int house_id;
    for (house_id = 0; house_id < kNumPlacidusHouses; ++house_id) {
      const auto& h0(placidus[house_id]);
      const auto& h1(placidus[(house_id+1) % kNumPlacidusHouses]);
      
      if (angleIsBetween(p.angle, h0.angle, h1.angle)) {
        break;
      }  
    }

    planetInHouse[p.id] = Placidus_t((kNumPlacidusHouses + house_id)%kNumPlacidusHouses);
  }

  // ... Aspects ...
  for (const auto& src : planets) {
    for (auto dst_id = src.id+1; dst_id < kNumCelestialPoints; ++dst_id) {
      int diff = abs(src.angle.degree - planets[dst_id].angle.degree);
          diff = (180 < diff) ? 360 - diff : diff;
      Aspect_t asp;
      for (int i = 0; i < kNumAspectTypes; ++i) {
        const AspectType_t atype = AspectType_t(i);
        const int orb = diff - AspectDegree(atype);
        if (abs(orb) <= kAspectMaxDegreeDiff) {
          asp.type = atype;
          asp.orb  = orb;
          break;
        }
      }
      aspects[src.id][dst_id] = aspects[dst_id][src.id] = asp;
    }
  }

  // Binary / Ternary / Quaternary scores
  for (auto p : planets) {
    // (Use only the 10 main ruler planetoids)
    if (p.id >= kNumRulerPlanets) break;

    const auto z(p.angle.zodiac());

    const int z2{z % 2};
    polarity.nyang += (z2 == 0);
    polarity.nyin  += (z2 == 1);

    const int z3{z % 3};
    quality.ncardinal += (z3 == 0);
    quality.nfixed    += (z3 == 1);
    quality.nmutable  += (z3 == 2);

    const int z4{z % 4};
    elements.fire  += (z4 == 0);
    elements.earth += (z4 == 1);
    elements.air   += (z4 == 2);
    elements.water += (z4 == 3);
  }
}

/* -------------------------------------------------------------------------- */

static constexpr const char* GetVideoFormat(bool bOutputHTML)
{
  return bOutputHTML ? "<a href=\"https://youtu.be/%s\">%s</a>"
                     : "\e]8;;https://youtu.be/%s\a%s\e]8;;\a"
                     ;
}

void getAspectVideoURL(int src_id, int dst_id, bool bOutputHTML, char aspect_video_url[128]) {
  if ((src_id >= CelestialPoint_t::Sun) && (src_id <= CelestialPoint_t::Mars)
   && (dst_id > CelestialPoint_t::Sun) && (dst_id <= CelestialPoint_t::TrueNode))
  {
    const char* kVideoFormat = GetVideoFormat(bOutputHTML);

    // const int url_id = (dst_id - 1 - src.id) 
    //                  + src.id * (kNumRulerPlanets-1) 
    //                  + (src.id * (1 - src.id)) / 2;
    const int url_id = src_id * int(CelestialPoint_t::TrueNode - CelestialPoint_t::Sun)
                     + dst_id -1;
    const auto videoId{ kAspectVideoId[url_id] };
    sprintf(aspect_video_url, kVideoFormat, videoId.c_str(), "aspect");
  }
}

/* -------------------------------------------------------------------------- */

void AstroChart_t::display(bool bOutputHTML, bool bCondenseDisplay) const
{
  FILE *fd = stderr;

  if (bOutputHTML) {
    char filename[128]{0};
    sprintf( filename, "placidus_chart_%4d-%02d-%02d-%2d-%02d-%d-%d.html",
      timeData.year, timeData.month, timeData.day,
      timeData.hour, timeData.minute,
      int(timeData.geoloc.longitude), int(timeData.geoloc.latitude)
    );

    fd = fopen( filename, "w");
    fprintf( fd, "<pre>");
  }

  fprintf( fd, "~:: Tropical Placidus Chart ::~\n");
  fprintf( fd, " %4d-%02d-%02d\n", timeData.year, timeData.month, timeData.day);
  fprintf( fd, " %2d:%02d UT\n", timeData.hour, timeData.minute);
  fprintf( fd, " %.2f E - %.2f N (GMT %+d)\n", timeData.geoloc.longitude, timeData.geoloc.latitude, timeData.geoloc.timezone);
  fprintf( fd, "\n");

  // Binary / Ternary / Quaternary scores.
  const float percent{ 100.0f / static_cast<float>(kNumRulerPlanets) };
  fprintf( fd, "Polarity \t♀ %3.2f%% \t| \t♂ %3.2f%%\n",
    polarity.nyin*percent, polarity.nyang*percent
  );
  fprintf( fd, "Quality \tC %3.2f%% \t| \tF %3.2f%% \t| \tM %3.2f%%\n",
    quality.ncardinal*percent, quality.nfixed*percent, quality.nmutable*percent
  );
  fprintf( fd, "Elements \tᐃ %3.2f%% \t| \tᗄ %3.2f%% \t| \tᗋ %3.2f%% \t| \tᐁ %3.2f%%\n",
    elements.fire*percent, elements.earth*percent, elements.air*percent, elements.water*percent
  );

  fprintf( fd, "\n");
  
  const char* kVideoFormat = GetVideoFormat(bOutputHTML);

  // Planets in Signs & House.
  for (auto &p : planets) {
    const auto planetSymbol{ PlanetSymbol(p.id) };
    const auto houseId{ planetInHouse[p.id] };

    char str_planetInSign[64]{0};
    if (p.id >= Moon && p.id <= Mars) {
      const auto videoId{ kZodiacPlanetVideoId[p.angle.zodiac()][p.id] };
      sprintf(str_planetInSign, kVideoFormat, videoId.c_str(), "zodiac");
    } else if (p.id == TrueNode) {
      sprintf(str_planetInSign, kVideoFormat, kNorthNodeInHouseVideoId[p.angle.zodiac()].c_str(), "zodiac");
    }

    char str_planetInHouse[64]{0};
    if (p.id < kNumRulerPlanets) {
      const auto videoId{ kPlanetsInHouseVideoId[houseId][p.id] };
      sprintf(str_planetInHouse, kVideoFormat, videoId.c_str(), "house");
    } else if (p.id == TrueNode) {
      sprintf(str_planetInHouse, kVideoFormat, kNorthNodeInHouseVideoId[p.id].c_str(), "house");
    }

    char condensedInfo[16];
    sprintf( condensedInfo, "%s %s - %4s", 
      planetSymbol, 
      ZodiacSymbol(p.angle.zodiac()), 
      placidus[houseId].pname
    );

    if (bCondenseDisplay) {
      fprintf( fd, "%s\n", condensedInfo);
    } else {
      fprintf( fd, "%9s %s \t%12s \t%s \t%3d° \t%3d° %2d'%2.0f \t%16s \t[ %s ] \t%6s \t%6s\n",
        p.pname, planetSymbol, p.pname_sign, 
        ZodiacSymbol(p.angle.zodiac()),
        p.angle.degree % 30, p.angle.degree, p.angle.minute, p.angle.second,
        PlanetDesc(p.id),
        condensedInfo,
        str_planetInSign,
        str_planetInHouse
      );
    }
  }

  fprintf( fd, "\n");

  // Placidus houses.
  for (auto &p : placidus) {
    char ruler_str[128]{0};
    char condensed_ruler_str[32]{0};

    if (p.id < kNumPlacidusHouses) {
      const auto ruling_planet_id{ ZodiacRuler(p.angle.zodiac()) };
      const auto ruler_house{ planetInHouse[ruling_planet_id] };
      const auto& ruler{ planets[ruling_planet_id] };

      char s2[64]{0};
      int indent(12 - strlen(ruler.pname_sign));
      sprintf(s2, "%7s / %s%*s", ruler.pname, ruler.pname_sign, indent, "");

      sprintf(ruler_str, "[ %4s Ruler in %4s | %s| %s %s ]", 
        p.pname,
        placidus[ruler_house].pname,
        s2,
        PlanetSymbol(ruling_planet_id),
        ZodiacSymbol(ruler.angle.zodiac())
      );

      sprintf(condensed_ruler_str, "%4s %s %s",
        placidus[ruler_house].pname, 
        PlanetSymbol(ruling_planet_id),
        ZodiacSymbol(ruler.angle.zodiac())
      );
    }

    // Separates houses and others placidus elements.
    if (p.id == kNumPlacidusHouses) {
      if (bCondenseDisplay) {
        break;
      }
      fprintf( fd, "\n");
    }

    if (p.id == Ascendant) {
      const auto videoId{ kZodiacPlanetVideoId[p.angle.zodiac()][0] };
      sprintf(ruler_str, kVideoFormat, videoId.c_str(), "ascendant");
    }

    if (bCondenseDisplay) {
      fprintf( fd, "%5s %s [%s]\n",
        p.pname,
        ZodiacSymbol(p.angle.zodiac()),
        condensed_ruler_str
      );
    } else {
      fprintf( fd, "%8s \t%12s \t%s\t%3d° \t%3d° %2d'%2.0f \t%16s \t%s\n",
        p.pname, p.pname_sign,
        ZodiacSymbol(p.angle.zodiac()),
        p.angle.degree % 30, p.angle.degree, p.angle.minute, p.angle.second,
        PlacidusDesc(p.id),
        ruler_str
      );
    }
  }

  fprintf( fd, "\n");

  // Planets aspects.
  for (const auto& src : planets) {
    for (auto dst_id = size_t(src.id+1); dst_id < aspects.size(); ++dst_id) {
      const auto& A = aspects[src.id][dst_id];
      if (A.type != AspectType_t::None)
      {
        char aspect_video_url[128]{0};
        getAspectVideoURL(src.id, dst_id, bOutputHTML, aspect_video_url);

        const auto &dst{ planets[dst_id] };

        char condensedInfo[64]{0};
        sprintf(condensedInfo, "(%s) %s %s %s (%s)", 
          ZodiacSymbol(src.angle.zodiac()), PlanetSymbol(src.id),
          AspectSymbol(A.type),
          PlanetSymbol(dst.id), ZodiacSymbol(dst.angle.zodiac())
        );

        if (bCondenseDisplay) {
          fprintf( fd, "%s %+d°\n", condensedInfo, A.orb);
        } else {
          fprintf( fd, "%8s \t%10s \t%10s\t %+d° \t| \t%s \t%6s\n", 
            src.pname, AspectName(A.type), dst.pname, A.orb,
            condensedInfo,
            aspect_video_url
          );
        }
      }
    }
  }
  //fprintf( fd, "\n");

  if (bOutputHTML) {
    fprintf( fd, "</pre>");
    fclose(fd);
  }
}

/* -------------------------------------------------------------------------- */

void AstroChart_t::displayTransit(AstroChart_t const& chart, bool bOutputHTML) const {
  constexpr int kTransitAspectMaxDegreeDiff{ 3 };
  AspectMatrix_t transitAspects;

  for (const auto& src : planets) {
    for (auto dst_id = src.id+0; dst_id < kNumCelestialPoints; ++dst_id) {
      int diff = abs(src.angle.degree - chart.planets[dst_id].angle.degree);
          diff = (180 < diff) ? 360-diff : diff;

      for (int i = 0; i < kNumAspectTypes; ++i) {
        const AspectType_t atype = AspectType_t(i);
        const int orb = diff - AspectDegree(atype);
        if (abs(orb) <= kTransitAspectMaxDegreeDiff) {
          transitAspects[src.id][dst_id] = transitAspects[dst_id][src.id] = { atype, orb };
          break;
        }
      }
    }
  }

  fprintf(stderr, "Current Transit.\n" );
  fprintf(stderr, " %4d-%02d-%02d\n", timeData.year, timeData.month, timeData.day);
  fprintf(stderr, " %02d:%02d UT\n", timeData.hour, timeData.minute);
  fprintf(stderr, " %.2f E - %.2f N (GMT %+d)\n", timeData.geoloc.longitude, timeData.geoloc.latitude, timeData.geoloc.timezone);
  fprintf(stderr, "\n" );


  // Planets aspects.
  for (const auto& src : planets) {
    for (auto dst_id = size_t(src.id+0); dst_id < transitAspects.size(); ++dst_id) {
      const auto& A = transitAspects[src.id][dst_id];
      if (A.type != AspectType_t::None)
      {

        char aspect_video_url[128]{0};
        getAspectVideoURL(src.id, dst_id, bOutputHTML, aspect_video_url);        

        const auto &dst{ chart.planets[dst_id] };

        fprintf(stderr, "%8s \t%10s \t%10s \t%+d° \t| \t(%s) %s %s %s (%s) \t%6s\n", 
          src.pname, AspectName(A.type), dst.pname, A.orb,
          ZodiacSymbol(src.angle.zodiac()), PlanetSymbol(src.id),
          AspectSymbol(A.type),
          PlanetSymbol(dst.id), ZodiacSymbol(dst.angle.zodiac()),
          aspect_video_url
        );
      }
    }
  }
}

} // namespace "astrowrap"


/* -------------------------------------------------------------------------- */
