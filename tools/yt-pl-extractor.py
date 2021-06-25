#!/usr/bin/env python
#
# This script extracts video ids from youtube playlists and display
# them as a C array of strings.
#
# Alternative :
#  youtube-dl --get-id [playlist_url] -i


def extractPlaylist(pl_id: str) -> [str]:
  """ Extract and return the ordered list of videos ID for a given youtube playlist """

  from urllib.request import urlopen

  # Retrieve all potential video ids in playlist URL.
  html = urlopen( "https://www.youtube.com/playlist?list=PLIU_87maEvm%s" % pl_id )
  src = str(html.read())
  raw_videoIds = src.split("https://i.ytimg.com/vi/")
  raw_videoIds = [x[:11] for x in raw_videoIds]

  # Remove the first one, unused.
  raw_videoIds = raw_videoIds[1:]

  # Create an ordered and trimmed video list.
  ordered = list()
  processed = set()
  for vid in raw_videoIds:
    if vid not in processed:
      processed.add(vid)
      ordered.append(vid)
  
  return ordered


if __name__ == '__main__':
  # Planet in House playlist (for each house)
  kPlaylists = (
    "maC7ss0PHuPqTpVYtRV9iM",
    "kH3diTI4IHkR5oS0w2pvDA",
    "nCTke7des7RCGnfytt_lOw",
    "lmBO1jOma1qQbNaw_uJEVp",
    "m0fEmp7aIEkt69jouinGP-",
    "m0PXDKfmK6YVNiHjvfZWDd",
    "lbp_5L9cmmUEqo7wvyKwpJ",
    "liJGT8vSnSL2wACxn_M8-_",
    "luX0ufuGItS3PZQ-rT3Cny",
    "kR-sYrYGsFc_cvYOGwyOKp",
    "nnpx-kBjGFL6K-onrdHI4Q",
    "nkVFLLJt_WBZkuP5GJ9Ee7",
  )

  # Sun in house playlist.
  kSunInHousePlaylist = "nnlFxhcrvJvKI5rCvHm11n"

  # LUT to reorder planets video ids to match astrowrap's.
  kLUT = (0, 3, 2, 1, 4, 5, 6, 8, 7)

  # Reorder and display the list ids as a C array of strings.
  videoId_perHouse = [extractPlaylist(x) for x in kPlaylists]
  videoId_sun = extractPlaylist(kSunInHousePlaylist)
  for i in range(len(videoId_perHouse)):
    # retrieve planet in house.
    planetsInHouse = videoId_perHouse[i]
    # add the sun in house videoId.
    l = [videoId_sun[i]] + [planetsInHouse[j] for j in kLUT]
    # add C quotes.
    l = ("\"%s\"" % x for x in l)
    # output as a C array.
    print("\t%s," % ", ".join(l))
