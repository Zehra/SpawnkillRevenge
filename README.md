# Spawnkill Revenge

Spawnkilling is dubious at the best of times, and _no one_ likes to be on the receiving end.  On
some maps, frequent spawnkilling leads to an entire team dying over and over.

Not only does this ruin the game for those players, they will often leave in disgust, thus making
that team weaker (facilitating more spawnkills), decreasing the number of targets (increasing
spawnkill frequency by increasing competition among attacking players), and unbalancing the teams
(breaking CTF).

This plugin attempts to address such problems by automatically killing players if they spawnkill.



## Spawnkill Detection

As-defined by this plugin, a player is a valid target if it has been a (configurable) length of time
since they spawned.  Optionally, also if they have fired at least once.  Otherwise, killing them is
counted as a spawnkill.

This is somewhat-imperfect.  In-particular, sometimes players spawn into fire (or could conceivably
drive into it deliberately).  It would also be nice to allow a jump or two without decrementing the
timeout while in the air, tying it to position somehow, or optionally allowing spawnkills that are
so rapid they could only have happened by accident.

Generally, though, I think this should work as-intended.  At the very least, the fact of the
plugin's existence deters players from attempting to spawnkill, which is most of the point.



## Some Thoughts About Gameplay Impact

The main effect, besides reducing spawnkill frequency, is that some players have to change their
strategies.  E.g., camping in places which were otherwise invulnerable (because a spawnkiller could
usually kill everyone who spawns nearby) is no longer viable.

While some players might complain, I frankly don't see a problem with this.  On many maps, these
spawncamped places end up being places like "your base" or "a whole quadrant of the map".  Such is
the case e.g. on "Missile War 2.3" (where ST and WG make spawnkilling the base easy) and "Fog of
War" (where the two base towers encourage spawnkilling half the map—and every spawn point—with GM).

With the plugin, would-be spawncampers are forced to instead actually _play_.

On free-for-all maps, the greater variety in spawn points makes for more genuine accidents and false
positives.  Maps with lots of accidental reflection (which is its own issue), especially of laser,
also cause this.  Although this plugin has been tested and works acceptably on such maps, it is not
really suited to them.  The spawnkill frequency is just unavoidably higher on these maps, and so it
makes (less) sense to punish it.



## Building (Linux Ubuntu)

You will probably need to install some development packages.  Besides the more-usual C++ packages
already in my build environment, I needed:

    sudo apt-get install libc-ares-dev libcurl4-gnutls-dev

Setup and build:

    git clone -b 2.4 https://github.com/BZFlag-Dev/bzflag.git bzflag
    cd bzflag/plugins/
    git clone https://github.com/agatha2/SpawnkillRevenge.git
    cd ../

    ./autogen.sh
    ./configure --enable-custom-plugins=SpawnkillRevenge

    make

    sudo make install



## Configuring and Running

Load the plugin by passing the following to your server:

    -loadplugin SpawnkillRevenge

You can unload/load the plugin in-game with:

    /unloadplugin SpawnkillRevenge
    /loadplugin SpawnkillRevenge

The period of time during which a player is considered to be spawnkilled is given by the
floating-point BZDB variable `spawnkillTime` (the default is "5.0" seconds; you should experiment
to find a fitting value for your map and server conbination).  By default, shooting will invalidate
a player's spawnkill grace period.  This is controlled by `spawnkillFireInvalidates`.  You can set
these at load time by passing:

    -set spawnkillTime <seconds>
    -set spawnkillFireInvalidates <truthy value>

You can set it in-game with:

    /set spawnkillTime <seconds>
    /set spawnkillFireInvalidates <truthy value>
