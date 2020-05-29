/*  ______        ____  __
 * |  _ \ \      / /  \/  |
 * | | | \ \ /\ / /| |\/| |
 * | |_| |\ V  V / | |  | |
 * |____/  \_/\_/  |_|  |_| */
                        
/* => Appearance {{{1 */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int viewontag          = 1;        /* 0 means don't follow */
static const char *fonts[]          = {
  /* "Hermit-Regular:size=12:antialias=true:autohint=true", */
  "Ubuntu Mono:size=14:antialias=true:autohint=true",
  "Symbols Nerd Font:size=12:antialias=true:autohint=true"
};

#include "../colors.h"
static const char *colors[][3]      = {
	/*               fg        bg        border     */
	[SchemeNorm]          = { col_fg,   col_bg,   col_bdnorm },
	[SchemeSel]           = { col_bg,   col_cyan, col_cyan   },
};

/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const char *alttags[] = { " HOME", " WEB", " MUSIC", " CODE", " EDIT", " GAME", " OFFICE", " HMM", " MISC" };
// }}}1

// => Window rules {{{1
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
  { "firefox",            NULL,           NULL,   1 << 1,       0,           -1 },
  { "Brave-browser",      NULL,           NULL,   1 << 1,       0,           -1 },
  { "Spotify",            NULL,           NULL,   1 << 2,       0,           -1 },
  { "code-oss",           NULL,           NULL,   1 << 3,       0,           -1 },
  { "Gimp",               NULL,           NULL,   1 << 4,       0,           -1 },
  { "discord",            NULL,           NULL,   1 << 5,       0,           -1 },
  { "Steam",              NULL,           NULL,   1 << 5,       0,           -1 },
  { NULL,                 "libreoffice",  NULL,   1 << 6,       0,           -1 },
  { "Tor Browser",        NULL,           NULL,   1 << 8,       0,           -1 },
}; // }}}1

/* => Layout(s) {{{1 */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
  { "",      tile },
  { "",      NULL },
  { "",    monocle },
}; // }}}1

/* => Key definitions {{{1 */
#define MODKEY Mod1Mask
#define MODSUP Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
// }}}1

/* => Commands {{{1 */
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-l", "5", "-m", dmenumon, NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
// }}}1

// => Key bindings {{{1
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
  // > Apps {{{2
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
  { MODSUP,                       XK_Return, spawn,          SHCMD("st") },
  { MODSUP,                       XK_f,      spawn,          SHCMD("brave") },
  { MODSUP,                       XK_w,      spawn,          SHCMD("st -e ranger") },
  { MODSUP,                       XK_i,      spawn,          SHCMD("st -e htop") },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
  // }}}2

  // > Tag and win ctl {{{2
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },

	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY|ShiftMask,             XK_l,      quit,           {0} },
  // }}}2

  /* > Other ctl {{{2 */
  { 0,              XF86XK_MonBrightnessDown,spawn,          SHCMD("xbacklight -dec 5") },
	{ 0,              XF86XK_MonBrightnessUp,  spawn,          SHCMD("xbacklight -inc 5") },

  { 0,              XF86XK_AudioLowerVolume, spawn,          SHCMD("amixer -q -D pulse sset Master 5%-; notify-send -u low -a volume 5 down") },
  { MODSUP,         XK_j,                    spawn,          SHCMD("amixer -q -D pulse sset Master 5%-; notify-send -u low -a volume 5 down") },
  { 0,              XF86XK_AudioMute,        spawn,          SHCMD("amixer -q sset Master toggle; notify-send -u low -a volume toggled") },
  { 0,              XF86XK_AudioRaiseVolume, spawn,          SHCMD("amixer -q -D pulse sset Master 5%+; notify-send -u low -a volume 5 up") },
  { MODSUP,         XK_k,                    spawn,          SHCMD("amixer -q -D pulse sset Master 5%+; notify-send -u low -a volume 5 up") },
  { 0,              XF86XK_AudioPlay,        spawn,          SHCMD("playerctl play-pause") },
  { MODSUP,         XK_p,                    spawn,          SHCMD("playerctl play-pause") },
  { 0,              XF86XK_AudioNext,        spawn,          SHCMD("playerctl next") },
  { MODSUP,         XK_l,                    spawn,          SHCMD("playerctl next") },
  { 0,              XF86XK_AudioPrev,        spawn,          SHCMD("playerctl previous") },
  { MODSUP,         XK_h,                    spawn,          SHCMD("playerctl previous") },

  { MODKEY|ControlMask,           XK_p,      spawn,          SHCMD("~/.dotfiles/scripts/powermenu.sh") },
  { MODKEY|ControlMask,           XK_m,      spawn,          SHCMD("~/.dotfiles/scripts/displaymenu.sh") },

  { 0,                            XK_Print,  spawn,          SHCMD("maim ~/Pictures/Screenshots/$(date +\%s).png") },
  { ControlMask,                  XK_Print,  spawn,          SHCMD("maim -s ~/Pictures/Screenshots/$(date +\%s).png") },
  // }}}2
}; // }}}1

/* => Mouse bindings {{{1*/
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkStatusText,        ControlMask,    Button1,        spawn,          SHCMD("~/.dotfiles/scripts/wallpaper.sh ~/Pictures/Wallpapers/dwmwalls") },
}; // }}}1

