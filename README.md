# dwm - dynamic window manager


### dwm is an extremely fast, small, and dynamic window manager for X.

---

### Requirements
In order to build dwm you need the Xlib header files.

---

### Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

```sh
make clean install
```

If you are going to use the default bluegray color scheme it is highly
recommended to also install the bluegray files shipped in the dextra package.

---

### Running dwm
Add the following line to your .xinitrc to start dwm using startx:

```sh
exec dwm
```

In order to connect dwm to a specific display, make sure that
the **DISPLAY** environment variable is set correctly, e.g.:

```sh
DISPLAY=foo.bar:1 exec dwm
```

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

```sh
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
	sleep 1
done &
exec dwm
```

or using i3status:

```sh
i3status | while read -r line ; do
	xsetroot -name " $line "
done &
```

### Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

---

### Applied patches
1. attachaside
1. gaps
1. cfacts
1. movestack
1. combotag
1. colorstatus
1. warp
1. hide vacant tags

---

### Screnshots

[dwm screenshot](./screenshot.png)
