/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "RobotoMono:pixelsize=14:antialias=true:autohint=true" };
static const char norm_fg[]         = "#d6a6c4";
static const char norm_bg[]         = "#0e1d26";
static const char norm_border[]     = "#0e1d26";
static const char sel_fg[]          = "#d6a6c4";
static const char sel_bg[]          = "#ac414b";
static const char sel_border[]      = "#ac414b";
static const char *colors[][3]      = {
  /*               fg           bg         border      */
  [SchemeNorm] = { norm_fg,     norm_bg,   norm_border },
  [SchemeSel]  = { sel_fg,      sel_bg,    sel_border  },
};

/* tagging */
static const char *tags[] = { " ☰ ", " ☲ ", " ☱ ", " ☴ ", " ☵ ", " ☶ ", " ☳ ", " ☷ ", " ☰ " };

static const Rule rules[] = {
	/* xprop(1):
	 *   WM_CLASS(STRING) = instance, class
	 *   WM_NAME(STRING) = title
	 */
	/* class                       instance          title    tags mask   mtags mask    isfloating   monitor */
	{ "dialog",                    NULL,             NULL,    0,          0,            1,           -1 },
	{ "pop-up",                    NULL,             NULL,    0,          0,            1,           -1 },
	{ "task-dialog",               NULL,             NULL,    0,          0,            1,           -1 },

	{ "firefoxdeveloperedition",   NULL,             NULL,    1 << 0,     1 << 0,       0,           1  },
	{ "sun-awt-X11-XDialogPeer",   NULL,             NULL,    1 << 2,     1 << 1,       0,           1  },
	{ "jetbrains-idea",            NULL,             NULL,    1 << 2,     1 << 1,       0,           1  },
	{ "st-256color",               "nnnterm",        NULL,    1 << 1,     1 << 1,       0,           0  },
	{ "st-256color",               "tmuxterm",       NULL,    1 << 1,     1 << 1,       0,           0  },
	{ "Slack",                     NULL,             NULL,    1 << 3,     1 << 2,       0,           0  },
	{ "Chromium",                  NULL,             NULL,    1 << 5,     1 << 3,       0,           1  },
	{ "Postman",                   NULL,             NULL,    1 << 5,     1 << 3,       0,           1  },
	{ "st-256color",               "rtorrentterm",   NULL,    1 << 4,     1 << 3,       0,           0  },
	{ "st-256color",               "sptterm",        NULL,    1 << 4,     1 << 3,       0,           0  },
  { "qBittorrent",               "qbittorrent",    NULL,    1 << 3,     1 << 3,       0,           0  },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
  /* symbol   arrange function */
  { "≦",      tile },    /* first entry is default */
  { "⋇",      NULL },    /* no layout function means floating behavior */
  { "⋈",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]      = { "dma", "-c", "-l", "10", NULL };
static const char *termcmd[]       = { "tabbed", "-c", "st", "-w", NULL };
static const char *termtmuxcmd[]   = { "st", "-e", "tmux", "-2", NULL };

static Key keys[] = {
	/* modifier                     key              function        argument */
	{ MODKEY,                       XK_p,            spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_o,            spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_o,            spawn,          {.v = termtmuxcmd } },
	{ MODKEY,                       XK_b,            togglebar,      {0} },
	{ MODKEY,                       XK_j,            focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,            focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,            incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,            incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_r,            setmfact,       {.f =  0.00} },
	{ MODKEY,                       XK_backslash,    zoom,           {0} },
	{ MODKEY,                       XK_BackSpace,    view,           {0} },
	{ MODKEY,                       XK_q,            killclient,     {0} },
	{ MODKEY,                       XK_bracketleft,  killclient,     {0} },
	{ MODKEY,                       XK_t,            setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,            setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,            setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,        togglefloating, {0} },
	{ MODKEY,                       XK_3,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_3,            tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_semicolon,    focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_apostrophe,   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_bracketright, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_equal,                        0)
	TAGKEYS(                        XK_minus,                        1)
	TAGKEYS(                        XK_0,                            2)
	TAGKEYS(                        XK_9,                            3)
	TAGKEYS(                        XK_8,                            4)
	TAGKEYS(                        XK_7,                            5)
	TAGKEYS(                        XK_6,                            6)
	TAGKEYS(                        XK_5,                            7)
	TAGKEYS(                        XK_4,                            8)
	{ MODKEY|ShiftMask,             XK_q,            quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

