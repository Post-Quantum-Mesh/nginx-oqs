#include <stdint.h>
#include "params.h"
#include "consts.h"

#define QINV 58728449 // q^(-1) mod 2^32
#define MONT -4186625 // 2^32 mod q
#define DIV 41978 // mont^2/256
#define DIV_QINV -8395782

const qdata_t qdata = {{
#define _8XQ 0
  Q, Q, Q, Q, Q, Q, Q, Q,

#define _8XQINV 8
  QINV, QINV, QINV, QINV, QINV, QINV, QINV, QINV,

#define _8XDIV_QINV 16
  DIV_QINV, DIV_QINV, DIV_QINV, DIV_QINV, DIV_QINV, DIV_QINV, DIV_QINV, DIV_QINV,

#define _8XDIV 24
  DIV, DIV, DIV, DIV, DIV, DIV, DIV, DIV,

#define _ZETAS_QINV 32
   -151046689,  1830765815, -1929875198, -1927777021,  1640767044,  1477910808,  1612161320,  1640734244,
    308362795,   308362795,   308362795,   308362795, -1815525077, -1815525077, -1815525077, -1815525077,
  -1374673747, -1374673747, -1374673747, -1374673747, -1091570561, -1091570561, -1091570561, -1091570561,
  -1929495947, -1929495947, -1929495947, -1929495947,   515185417,   515185417,   515185417,   515185417,
   -285697463,  -285697463,  -285697463,  -285697463,   625853735,   625853735,   625853735,   625853735,
   1727305304,  1727305304,  2082316400,  2082316400, -1364982364, -1364982364,   858240904,   858240904,
   1806278032,  1806278032,   222489248,   222489248,  -346752664,  -346752664,   684667771,   684667771,
   1654287830,  1654287830,  -878576921,  -878576921, -1257667337, -1257667337,  -748618600,  -748618600,
    329347125,   329347125,  1837364258,  1837364258, -1443016191, -1443016191, -1170414139, -1170414139,
  -1846138265, -1631226336, -1404529459,  1838055109,  1594295555, -1076973524, -1898723372,  -594436433,
   -202001019,  -475984260,  -561427818,  1797021249, -1061813248,  2059733581, -1661512036, -1104976547,
  -1750224323,  -901666090,   418987550,  1831915353, -1925356481,   992097815,   879957084,  2024403852,
   1484874664, -1636082790,  -285388938, -1983539117, -1495136972,  -950076368, -1714807468,  -952438995,
  -1574918427,  1350681039, -2143979939,  1599739335, -1285853323,  -993005454, -1440787840,   568627424,
   -783134478,  -588790216,   289871779, -1262003603,  2135294594, -1018755525,  -889861155,  1665705315,
   1321868265,  1225434135, -1784632064,   666258756,   675310538, -1555941048, -1999506068, -1499481951,
   -695180180, -1375177022,  1777179795,   334803717,  -178766299,  -518252220,  1957047970,  1146323031,
   -654783359, -1974159335,  1651689966,   140455867, -1039411342,  1955560694,  1529189038, -2131021878,
   -247357819,  1518161567,   -86965173,  1708872713,  1787797779,  1638590967,  -120646188, -1669960606,
   -916321552,  1155548552,  2143745726,  1210558298, -1261461890,  -318346816,   628664287, -1729304568,
   1422575624,  1424130038, -1185330464,   235321234,   168022240,  1206536194,   985155484,  -894060583,
      -898413, -1363460238,  -605900043,  2027833504,    14253662,  1014493059,   863641633,  1819892093,
   2124962073, -1223601433, -1920467227, -1637785316, -1536588520,   694382729,   235104446, -1045062172,
    831969619,  -300448763,   756955444,  -260312805,  1554794072,  1339088280, -2040058690,  -853476187,
  -2047270596, -1723816713, -1591599803,  -440824168,  1119856484,  1544891539,   155290192,  -973777462,
    991903578,   912367099,   -44694137,  1176904444,  -421552614,  -818371958,  1747917558,  -325927722,
    908452108,  1851023419, -1176751719, -1354528380,   -72690498,  -314284737,   985022747,   963438279,
  -1078959975,   604552167, -1021949428,   608791570,   173440395, -2126092136, -1316619236, -1039370342,
      6087993,  -110126092,   565464272, -1758099917, -1600929361,   879867909, -1809756372,   400711272,
   1363007700,    30313375,  -326425360,  1683520342,  -517299994,  2027935492, -1372618620,   128353682,
  -1123881663,   137583815,  -635454918,  -642772911,    45766801,   671509323, -2070602178,   419615363,
   1216882040,  -270590488, -1276805128,   371462360, -1357098057,  -384158533,   827959816,  -596344473,
    702390549,  -279505433,  -260424530,   -71875110, -1208667171, -1499603926,  2036925262,  -540420426,
    746144248, -1420958686,  2032221021,  1904936414,  1257750362,  1926727420,  1931587462,  1258381762,
    885133339,  1629985060,  1967222129,     6363718, -1287922800,  1136965286,  1779436847,  1116720494,
   1042326957,  1405999311,   713994583,   940195359, -1542497137,  2061661095,  -883155599,  1726753853,
  -1547952704,   394851342,   283780712,   776003547,  1123958025,   201262505,  1934038751,   374860238,

#define _ZETAS 328
  -3975713,    25847, -2608894,  -518909,   237124,  -777960,  -876248,   466468,
   1826347,  1826347,  1826347,  1826347,  2353451,  2353451,  2353451,  2353451,
   -359251,  -359251,  -359251,  -359251, -2091905, -2091905, -2091905, -2091905,
   3119733,  3119733,  3119733,  3119733, -2884855, -2884855, -2884855, -2884855,
   3111497,  3111497,  3111497,  3111497,  2680103,  2680103,  2680103,  2680103,
   2725464,  2725464,  1024112,  1024112, -1079900, -1079900,  3585928,  3585928,
   -549488,  -549488, -1119584, -1119584,  2619752,  2619752, -2108549, -2108549,
  -2118186, -2118186, -3859737, -3859737, -1399561, -1399561, -3277672, -3277672,
   1757237,  1757237,   -19422,   -19422,  4010497,  4010497,   280005,   280005,
   2706023,    95776,  3077325,  3530437, -1661693, -3592148, -2537516,  3915439,
  -3861115, -3043716,  3574422, -2867647,  3539968,  -300467,  2348700,  -539299,
  -1699267, -1643818,  3505694, -3821735,  3507263, -2140649, -1600420,  3699596,
    811944,   531354,   954230,  3881043,  3900724, -2556880,  2071892, -2797779,
  -3930395, -3677745, -1452451,  2176455, -1257611, -4083598, -3190144, -3632928,
   3412210,  2147896, -2967645,  -411027,  -671102,   -22981,  -381987,  1852771,
  -3343383,   508951,    44288,   904516, -3724342,  1653064,  2389356,   759969,
    189548,  3159746, -2409325,  1315589,  1285669,  -812732, -3019102, -3628969,
  -1528703, -3041255,  3475950, -1585221,  1939314, -1000202, -3157330,   126922,
   -983419,  2715295, -3693493, -2477047, -1228525, -1308169,  1349076, -1430430,
    264944,  3097992, -1100098,  3958618,    -8578, -3249728,  -210977, -1316856,
  -3553272, -1851402,  -177440,  1341330, -1584928, -1439742, -3881060,  3839961,
   2091667, -3342478,   266997, -3520352,   900702,   495491,  -655327, -3556995,
    342297,  3437287,  2842341,  4055324, -3767016, -2994039, -1333058,  -451100,
  -1279661,  1500165,  -542412, -2584293, -2013608,  1957272, -3183426,   810149,
  -3038916,  2213111,  -426683, -1667432, -2939036,   183443,  -554416,  3937738,
   3407706,  2244091,  2434439, -3759364,  1859098, -1613174, -3122442,  -525098,
    286988, -3342277,  2691481,  1247620,  1250494,  1869119,  1237275,  1312455,
   1917081,   777191, -2831860, -3724270,  2432395,  3369112,   162844,  1652634,
   3523897,  -975884,  1723600, -1104333, -2235985,  -976891,  3919660,  1400424,
   2316500, -2446433, -1235728, -1197226,   909542,   -43260,  2031748,  -768622,
  -2437823,  1735879, -2590150,  2486353,  2635921,  1903435, -3318210,  3306115,
  -2546312,  2235880, -1671176,   594136,  2454455,   185531,  1616392, -3694233,
   3866901,  1717735, -1803090,  -260646,  -420899,  1612842,   -48306,  -846154,
   3817976, -3562462,  3513181, -3193378,   819034,  -522500,  3207046, -3595838,
   4108315,   203044,  1265009,  1595974, -3548272, -1050970, -1430225, -1962642,
  -1374803,  3406031, -1846953, -3776993,  -164721, -1207385,  3014001, -1799107,
    269760,   472078,  1910376, -3833893, -2286327, -3545687, -1362209,  1976782,
}};
