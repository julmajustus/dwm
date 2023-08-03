/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 2;   /* border pixel of windows */
static const unsigned int snap           = 10;  /* snap pixel */
static const int swallowfloating         = 1;   /* 1 means swallow floating windows by default */
static const int scalepreview            = 4;        /* Tag preview scaling */
static const unsigned int gappih         = 15;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;  /* vert inner gap between windows */
static const unsigned int gappoh         = 10;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 20;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const char autostartblocksh[]     = "autostart_blocking.sh";
static const char autostartsh[]          = "autostart.sh";
static const char dwmdir[]               = "dwm";
static const char localshare[]           = ".local/share";
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int bar_height              = 35;   /* 0 means derive from font, >= 1 explicit height */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */



/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_NONE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_NONE;
static const char *fonts[]               = { "monospace:size=18", "iosevka:size=22" };
static const char dmenufont[]            = "monospace:size=10";

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#bbbbbb";
static char normbgcolor[]                = "#222222";
static char normbordercolor[]            = "#343A40";
static char normfloatcolor[]             = "#343A40";

static char selfgcolor[]                 = "#9EE9EA";
static char selbgcolor[]                 = "#a3dfaf";
static char selbordercolor[]             = "#9EE9EA";
static char selfloatcolor[]              = "#9EE9EA";

static char titlenormfgcolor[]           = "#bbbbbb";
static char titlenormbgcolor[]           = "#222222";
static char titlenormbordercolor[]       = "#9EE9EA";
static char titlenormfloatcolor[]        = "#343A40"; //Floatborder unfocused

static char titleselfgcolor[]            = "#444444"; //Titlebar color
static char titleselbgcolor[]            = "#222222"; //Titlebar background color
static char titleselbordercolor[]        = "#005577";
static char titleselfloatcolor[]         = "#a3dfaf"; //Floatborder selected

static char tagsnormfgcolor[]            = "#bbbbbb";
static char tagsnormbgcolor[]            = "#222222";
static char tagsnormbordercolor[]        = "#a3dfaf";
static char tagsnormfloatcolor[]         = "#DF8293";

static char tagsselfgcolor[]             = "#9EE9EA"; //Tag icon highlight
static char tagsselbgcolor[]             = "#343A40"; //Tag icon background
static char tagsselbordercolor[]         = "#9EE9EA";
static char tagsselfloatcolor[]          = "#9EE9EA";

static char hidnormfgcolor[]             = "#a3dfaf";
static char hidselfgcolor[]              = "#227799";
static char hidnormbgcolor[]             = "#222222";
static char hidselbgcolor[]              = "#222222";

static char urgfgcolor[]                 = "#bbbbbb";
static char urgbgcolor[]                 = "#222222";
static char urgbordercolor[]             = "#a3dfaf";
static char urgfloatcolor[]              = "#db8fd9";





static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};




const char *spcmd1[] = {"st", "-n", "spterm", "-g", "1050x800", NULL };
static Sp scratchpads[] = {
   /* name          cmd  */
   {"spterm",      spcmd1},
};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][1] = {
          [DEFAULT_TAGS] = { "" },
      };

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.title = "Qalculate!", .isfloating = 1)
	RULE(.class = "file-roller", .isfloating = 1)
	RULE(.class = "gthumb", .isfloating = 1)
	RULE(.class = "obs", .isfloating = 1)
	RULE(.class = "steam", .isfloating = 1)
	RULE(.title = "Zenmonitor3", .isfloating = 1)
	RULE(.title = "File Operation Progress", .isfloating = 1)
	RULE(.instance = "spterm", .tags = SPTAG(0), .isfloating = 1)
};



/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,              click_tags,              hover_tags,              "tags" },
	{ -1,        0,     BAR_ALIGN_RIGHT,  width_systray,            draw_systray,           click_systray,           NULL,                    "systray" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
	{ 'A',       0,     BAR_ALIGN_RIGHT,  width_status2d,           draw_status2d,          click_statuscmd,         NULL,                    "status" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,           draw_wintitle,          click_wintitle,          NULL,                    "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 4;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */



static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "|||",      col },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ NULL,       NULL },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },



/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL
};
/* Custom program scripts */
static const char *termcmd[]  = { "st", NULL };

/* This defines the name of the executable that handles the bar (used for signalling purposes) */
#define STATUSBAR "dwmblocks"
#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key            function                argument */
	/* Basic DWM-commands */
	{ MODKEY,                       XK_t,          spawn,                  {.v = termcmd } },
	{ MODKEY,                       XK_c,          killclient,             {0} },
	{ ControlMask|Mod1Mask,         XK_Delete,     quit,                   {0} },
	/* Master stack count control*/
	{ MODKEY|Mod1Mask,              XK_i,          incnmaster,             {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_d,          incnmaster,             {.i = -1 } },
	/* Client focus */
	{ MODKEY,                       XK_l,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_h,          focusstack,             {.i = -1 } },
	/* <> */
	{ MODKEY,                       XK_Right,      focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_Left,       focusstack,             {.i = -1 } },
	/* Client move controls */
	{ MODKEY|ShiftMask,             XK_j,          pushdown,               {0} },
	{ MODKEY|ShiftMask,             XK_k,          pushup,                 {0} },
	{ MODKEY|ShiftMask,             XK_l,          movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,          movestack,              {.i = -1 } },
	/* <> */
	{ MODKEY|ShiftMask,             XK_Right,      movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,       movestack,              {.i = -1 } },
	/* Client size controls */
	{ MODKEY|ControlMask,           XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,          setmfact,               {.f = +0.05} },
	/* <> */
	{ MODKEY|ControlMask,           XK_Left,       setmfact,               {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_Right,      setmfact,               {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_k,          setcfact,               {.f = +0.25} },
	{ MODKEY|ControlMask,           XK_j,          setcfact,               {.f = -0.25} },
	/* <> */
	{ MODKEY|ControlMask,           XK_Up,         setcfact,               {.f = +0.25} },
	{ MODKEY|ControlMask,           XK_Down,       setcfact,               {.f = -0.25} },
	{ MODKEY|ControlMask,           XK_o,          setcfact,               {0} },
	/* Tag controls */
	{ MODKEY,                       XK_Tab,        view,                   {0} },
	{ ControlMask|Mod1Mask,         XK_Left,       shiftview,              { .i = -1 } },
	{ ControlMask|Mod1Mask,         XK_Right,      shiftview,              { .i = +1 } },
	{ Mod1Mask|ShiftMask,           XK_Left,       shiftboth,              { .i = -1 } }, // note keybinding conflict with focusadjacenttag tagandviewtoleft
	{ Mod1Mask|ShiftMask,           XK_Right,      shiftboth,              { .i = +1 } }, // note keybinding conflict with focusadjacenttag tagandviewtoright
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
	{ MODKEY,                       XK_Return,     togglefullscreen,       {0} },
	{ MODKEY|ShiftMask,             XK_f,          fullscreen,             {0} },
	/* Layout controls */
	{ MODKEY|Mod1Mask,              XK_1,          setlayout,              {.v = &layouts[0]} }, /* Column layout */
	{ MODKEY|Mod1Mask,              XK_2,          setlayout,              {.v = &layouts[1]} }, /* Floating layout */
	{ MODKEY|Mod1Mask,              XK_3,          setlayout,              {.v = &layouts[3]} }, /* Centered master layout */
	{ MODKEY,                       XK_space,      setlayout,              {0} },
	{ MODKEY,                       XK_q,          cyclelayout,            {.i = +1 } },
	/* Scratchpads */
	{ MODKEY|Mod1Mask,              XK_g,          togglescratch,          {.ui = 0 } },
	{ MODKEY|ShiftMask,             XK_g,          setscratch,             {.ui = 0 } },
	{ MODKEY|ControlMask,           XK_g,          removescratch,          {.ui = 0 } },
	/* ---- */
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[1]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button1,        sigstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,                   Button2,        sigstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,                   Button3,        sigstatusbar,   {.i = 3 } },
	{ ClkStatusText,        0,                   Button4,        sigstatusbar,   {.i = 4 } },
	{ ClkStatusText,        0,                   Button5,        sigstatusbar,   {.i = 5 } },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,              Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ControlMask,  Button3,        dragcfact,      {0} },
	{ ClkClientWin,         MODKEY|ControlMask,  Button1,        dragmfact,      {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};


