/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2;        /* border pixel of windows */
static const unsigned int gappx    = 10;       /* gap between windows */
static const unsigned int snap     = 32;       /* snap pixel */
static const int showbar           = 1;        /* 0 means no bar */
static const int topbar            = 1;        /* 0 means bottom bar */

/* colors */
static const char col_jellybean0[]  = "#181818";
static const char col_jellybean1[]  = "#3b3b3b";
static const char col_jellybean2[]  = "#6c6c6c";
static const char col_jellybean3[]  = "#e8e8d3";
static const char col_jellybean4[]  = "#cf6a4c";
static const char col_jellybean5[]  = "#db8f78";
static const char col_jellybean6[]  = "#99ad6a";
static const char col_jellybean7[]  = "#b2c18f";
static const char col_jellybean8[]  = "#d8ad4c";
static const char col_jellybean9[]  = "#e1c178";
static const char col_jellybean10[] = "#597bc5";
static const char col_jellybean11[] = "#829cd3";
static const char col_jellybean12[] = "#a037b0";
static const char col_jellybean13[] = "#b769c3";
static const char col_jellybean14[] = "#71b9f8";
static const char col_jellybean15[] = "#94caf9";
static const char col_jellybean16[] = "#adadad";
static const char col_jellybean17[] = "#c1c1c1";
static const char *colors[][3]      = {
	/*               fg               bg              border          */
	[SchemeNorm] = { col_jellybean2,  col_jellybean0, col_jellybean1  },
	[SchemeSel]  = { col_jellybean17, col_jellybean0, col_jellybean4  },
	[SchemeUrg]  = { col_jellybean3,  col_jellybean4, col_jellybean11 },
};

/* tagging */
static const char *tags[] = {
	"WEB",
	"SYS",
	"DEV",
	"DOC",
	"COM",
	"MISC",
	"DOTS",
	"VID",
	"9"
};

/* fonts */
static const char *fonts[] = {
	"Tamzen:size=10",
	"Siji:size=10"
};
static const char dmenufont[] = "monospace:size=10";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance    title       tags mask     isfloating   monitor */
	{ "Gimp",          NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",       NULL,       NULL,       1 << 0,       0,           -1 },
	{ "konsole",       NULL,       NULL,       1 << 1,       0,           -1 },
	{ "st-256color",   NULL,       NULL,       1 << 1,       0,           -1 },
	{ "PacketTracer7", NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Zim",           NULL,       NULL,       1 << 3,       0,           -1 },
	{ "keepassxc",     NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Slack",         NULL,       NULL,       1 << 4,       0,           -1 },
	{ "mpv",           NULL,       NULL,       1 << 7,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[  ] ",      tile },    /* first entry is default */
	{ "[  ] ",      NULL },    /* no layout function means floating behavior */
	{ "[  ] ",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]  = { "rofi", "-show", "run", NULL };
static const char *termcmd[]   = { "konsole", NULL };
static const char *lockcmd[]   = { "i3lock", "-i", "/home/jj/Obrazy/tapety/pluto-blurred.png", NULL };
static const char *mpctoggle[] = { "mpc", "toggle", NULL };
static const char *mpcprev[]   = { "mpc", "prev", NULL };
static const char *mpcnext[]   = { "mpc", "next", NULL };
static const char *raise_vol[] = { "amixer", "set", "Master", "5000+", NULL };
static const char *lower_vol[] = { "amixer", "set", "Master", "5000-", NULL };
static const char *mute_vol[]  = { "amixer", "set", "Master", "toggle", NULL };
static const char *raise_br[]  = { "xbacklight", "+10", "-fps", "100", NULL };
static const char *lower_br[]  = { "xbacklight", "-10", "-fps", "100", NULL };
static const char *touchpad[]  = { "/home/jj/Skrypty/touchpadtoggle.sh", NULL };

#include <X11/XF86keysym.h>
#include "movestack.c"

static Key keys[] = {
	/* modifier                     key                        function        argument */
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = raise_vol} },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = lower_vol} },
	{ 0,                            XF86XK_AudioMute,          spawn,          {.v = mute_vol} },
	{ 0,                            XF86XK_AudioPlay,          spawn,          {.v = mpctoggle} },
	{ 0,                            XF86XK_AudioPrev,          spawn,          {.v = mpcprev} },
	{ 0,                            XF86XK_AudioNext,          spawn,          {.v = mpcnext} },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,          {.v = raise_br} },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,          {.v = lower_br} },
	{ 0,                            XF86XK_TouchpadToggle,     spawn,          {.v = touchpad} },
	{ MODKEY,                       XK_y,                      spawn,          {.v = lockcmd} },
	{ MODKEY,                       XK_r,                      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                      togglebar,      {0} },
	{ MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,                      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,                      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,                      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_j,                      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return,                 zoom,           {0} },
	{ MODKEY,                       XK_Tab,                    view,           {0} },
	{ MODKEY,                       XK_q,                      killclient,     {0} },
	{ MODKEY,                       XK_t,                      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                  togglefloating, {0} },
	{ MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                                      0)
	TAGKEYS(                        XK_2,                                      1)
	TAGKEYS(                        XK_3,                                      2)
	TAGKEYS(                        XK_4,                                      3)
	TAGKEYS(                        XK_5,                                      4)
	TAGKEYS(                        XK_6,                                      5)
	TAGKEYS(                        XK_7,                                      6)
	TAGKEYS(                        XK_8,                                      7)
	TAGKEYS(                        XK_9,                                      8)
	{ MODKEY|ShiftMask,             XK_q,                      quit,           {-1} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

