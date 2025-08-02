#!/usr/bin/python3

# -----------------------------------------------------------------------------

import argparse
import pgeocode
import pytz
from timezonefinder import TimezoneFinder
from datetime import datetime

# -----------------------------------------------------------------------------

def parse_native_location(place_name, country_code, local_dt):
  args = {}

  nomi = pgeocode.Nominatim(country_code)
  location_data = nomi.query_location(place_name)

  if not location_data.empty:
    lat = location_data.iloc[0]['latitude']
    lon = location_data.iloc[0]['longitude']

    if lat is not None and lon is not None:
      tf = TimezoneFinder()
      timezone_name = tf.timezone_at(lng=lon, lat=lat)

      if timezone_name:
        args['lat'] = lat
        args['long'] = lon

        try:
          from zoneinfo import ZoneInfo
          tz = ZoneInfo(timezone_name)

          standard_local_time = local_dt.replace(tzinfo=tz)

          utc_dt = standard_local_time.astimezone(ZoneInfo("UTC"))
          args['date'] = utc_dt.strftime('%Y/%m/%d')
          args['time'] = utc_dt.strftime('%H:%M')

        except Exception as e:
          print(f"Could not load timezone object for {timezone_name}: {e}")
      else:
        print(f"Could not determine timezone for coordinates: ({lat}, {lon})")
    else:
      print(f"Could not retrieve coordinates for: {place_name}")
  else:
    print(f"Could not find location data for: {place_name} in {country_code}")

  return args

# -----------------------------------------------------------------------------

if __name__ == '__main__':
  parser = argparse.ArgumentParser(description='Standardize geographical and time parameters for astrowrap.')
  subs = parser.add_subparsers(dest='command')
  subs.required = True

  s_parser = subs.add_parser('native', description='Display the birth chart of a native');
  s_parser.add_argument('city',
                        type=str,
                        help=f"City name of the place of birth (eg. 'Paris').")
  s_parser.add_argument('country',
                        type=str,
                        help=f"Country code of the place of birth (eg. 'fr' for France).")
  s_parser.add_argument('date',
                        type=str,
                        help=f"Date of birth as YYYY/MM/DD")
  s_parser.add_argument('--time',
                        type=str,
                        help=f"Time of birth as HH:MM",
                        default='')

  args = parser.parse_args()

  if args.command == 'native':
    if not args.city.strip() or not args.country.strip() or not args.date.strip():
      print('Error:')
      sys.exit(1)

    local_dt = None
    if args.time:
      local_dt = datetime.strptime(f"{args.date} {args.time}", "%Y/%m/%d %H:%M")
    else:
      local_dt = datetime.strptime(args.date, "%Y/%m/%d")

    r = parse_native_location(args.city, args.country, local_dt)

    standard_parameters = f"--gps {r['lat']},{r['long']} --date {r['date']} --time {r['time']}"
    print(standard_parameters)
