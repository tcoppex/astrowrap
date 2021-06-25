
# AstroWrap

_**AstroWrap**_ helps you visualize formatted tropical placidus astral chart, either on the command line or as an HTML file.

It uses the *Astrodienst Swiss Ephemeris* in accordance to its license.

### Sample output

<pre>~:: Tropical Placidus Chart ::~
 2021-03-28
 11:20 UT
 129.06 E - 35.17 N (GMT +9)

Polarity    ♀ 40.00%    |   ♂ 60.00%
Quality     C 40.00%    |   F 30.00%    |   M 30.00%
Elements    ᐃ 20.00%    |   ᗄ 20.00%    |   ᗋ 40.00%    |   ᐁ 20.00%

      Sun ☉        Aries    ♈     7°      7° 59'60               Ego    [ ☉ ♈ -  6th ]          <a href="https://youtu.be/WiWFqQ8c-Q4">house</a>
     Moon ☽        Libra    ♎     3°    183° 40'45           Emotion    [ ☽ ♎ - 11th ]  <a href="https://youtu.be/Jlx1HSbYtWY">zodiac</a>   <a href="https://youtu.be/oeaxCSv8iig">house</a>
  Mercury ☿       Pisces    ♓    18°    348° 35'52     Communication    [ ☿ ♓ -  5th ]  <a href="https://youtu.be/crrBfgsSErQ">zodiac</a>   <a href="https://youtu.be/pjPW0mHIf4U">house</a>
    Venus ♀        Aries    ♈     8°      8° 33'12          Pleasure    [ ♀ ♈ -  6th ]  <a href="https://youtu.be/Y6Oj6vwuRv0">zodiac</a>   <a href="https://youtu.be/_H1p4_HQPG8">house</a>
     Mars ♂       Gemini    ♊    14°     74° 20'11            Action    [ ♂ ♊ -  8th ]  <a href="https://youtu.be/bCYZmYaDjJk">zodiac</a>   <a href="https://youtu.be/PsVr4buUNvQ">house</a>
  Jupiter ♃     Aquarius    ♒    22°    322° 31'48         Expansion    [ ♃ ♒ -  4th ]          <a href="https://youtu.be/mIi8x6Csses">house</a>
   Saturn ♄     Aquarius    ♒    11°    311°  5'30       Restriction    [ ♄ ♒ -  4th ]          <a href="https://youtu.be/dPzzCDRtP4o">house</a>
   Uranus ⛢       Taurus    ♉     8°     38° 49'43         Rebellion    [ ⛢ ♉ -  7th ]          <a href="https://youtu.be/DR-KjngUjtA">house</a>
  Neptune ♆       Pisces    ♓    21°    351° 17'19           Mystery    [ ♆ ♓ -  5th ]          <a href="https://youtu.be/9-UEbB4LWGQ">house</a>
    Pluto ♇    Capricorn    ♑    26°    296° 35' 9   Death & Rebirth    [ ♇ ♑ -  3rd ]          <a href="https://youtu.be/_F_2Phf2PQY">house</a>
True Node ☊       Gemini    ♊    12°     72° 56'15       Karmic Goal    [ ☊ ♊ -  8th ]  <a href="https://youtu.be/Hq1SXOrZhjs">zodiac</a>   <a href="https://youtu.be/9WViJjbABBk">house</a>
   Chiron ⚷        Aries    ♈     0°      0°  0' 0    Wounded Healer    [ ⚷ ♈ -  5th ]                

     1st           Libra    ♎    29°    209° 26' 5              Self    [  1st Ruler in  6th |   Venus / Aries       | ♀ ♈ ]
     2nd         Scorpio    ♏    27°    237° 57'33            Values    [  2nd Ruler in  3rd |   Pluto / Capricorn   | ♇ ♑ ]
     3rd     Sagittarius    ♐    29°    269° 33'22            Bubble    [  3rd Ruler in  4th | Jupiter / Aquarius    | ♃ ♒ ]
     4th        Aquarius    ♒     3°    303°  8'56              Home    [  4th Ruler in  7th |  Uranus / Taurus      | ⛢ ♉ ]
     5th          Pisces    ♓     5°    335° 52'46              Life    [  5th Ruler in  5th | Neptune / Pisces      | ♆ ♓ ]
     6th           Aries    ♈     4°      4° 55'45           Dailies    [  6th Ruler in  8th |    Mars / Gemini      | ♂ ♊ ]
     7th           Aries    ♈    29°     29° 26' 5         Relations    [  7th Ruler in  8th |    Mars / Gemini      | ♂ ♊ ]
     8th          Taurus    ♉    27°     57° 57'33         Externals    [  8th Ruler in  6th |   Venus / Aries       | ♀ ♈ ]
     9th          Gemini    ♊    29°     89° 33'22          Journeys    [  9th Ruler in  5th | Mercury / Pisces      | ☿ ♓ ]
    10th             Leo    ♌     3°    123°  8'56      Achievements    [ 10th Ruler in  6th |     Sun / Aries       | ☉ ♈ ]
    11th           Virgo    ♍     5°    155° 52'46          Networks    [ 11th Ruler in  5th | Mercury / Pisces      | ☿ ♓ ]
    12th           Libra    ♎     4°    184° 55'45           Retreat    [ 12th Ruler in  6th |   Venus / Aries       | ♀ ♈ ]

     ASC           Libra    ♎    29°    209° 26' 5        Projection    <a href="https://youtu.be/wsUsni6FceY">ascendant</a>
      MC             Leo    ♌     3°    123°  8'56        Perception    

     Sun    Opposition        Moon   -4°    |   (♈) ☉ ☍ ☽ (♎)       <a href="https://youtu.be/x4TASn7ZnJ4">aspect</a>
     Sun    Conjunction      Venus   +1°    |   (♈) ☉ ☌ ♀ (♈)       <a href="https://youtu.be/D_5eUVWYinw">aspect</a>
     Sun       Sextile      Saturn   -4°    |   (♈) ☉ ⚹ ♄ (♒)       <a href="https://youtu.be/kcQcdyxKDOU">aspect</a>
     Sun       Sextile   True Node   +5°    |   (♈) ☉ ⚹ ☊ (♊)             
    Moon    Opposition       Venus   -5°    |   (♎) ☽ ☍ ♀ (♈)       <a href="https://youtu.be/cFyMVJe1IOg">aspect</a>
    Moon    Opposition      Chiron   -3°    |   (♎) ☽ ☍ ⚷ (♈)             
 Mercury        Square        Mars   -4°    |   (♓) ☿ □ ♂ (♊)       <a href="https://youtu.be/oSCLQumLNSo">aspect</a>
 Mercury    Conjunction    Neptune   +3°    |   (♓) ☿ ☌ ♆ (♓)       <a href="https://youtu.be/Lk-wl6OXPWA">aspect</a>
 Mercury        Square   True Node   -6°    |   (♓) ☿ □ ☊ (♊)             
   Venus       Sextile        Mars   +6°    |   (♈) ♀ ⚹ ♂ (♊)       <a href="https://youtu.be/YA1ZVhRDXh8">aspect</a>
   Venus       Sextile      Saturn   -3°    |   (♈) ♀ ⚹ ♄ (♒)       <a href="https://youtu.be/NqX2wqy6bOM">aspect</a>
   Venus       Sextile   True Node   +4°    |   (♈) ♀ ⚹ ☊ (♊)             
    Mars         Trine      Saturn   +3°    |   (♊) ♂ △ ♄ (♒)       <a href="https://youtu.be/uaJUDyTkVFQ">aspect</a>
    Mars    Conjunction  True Node   +2°    |   (♊) ♂ ☌ ☊ (♊)             
  Saturn        Square      Uranus   -3°    |   (♒) ♄ □ ⛢ (♉)             
  Saturn         Trine   True Node   +1°    |   (♒) ♄ △ ☊ (♊)             
 Neptune       Sextile       Pluto   -5°    |   (♓) ♆ ⚹ ♇ (♑)             
   Pluto       Sextile      Chiron   +4°    |   (♑) ♇ ⚹ ⚷ (♈)             
</pre>


## License

AstroWrap is released under the *GNU General Public License v3.0*.