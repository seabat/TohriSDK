#ifndef _SBT_WEB_
#define _SBT_WEB_
/**
 * html$B%U%!%$%k$K4^$^$l$kJ8;zNs$r<hF@(B 
 *
 * [$B0z?t(B]
 *  outBuf[OUT] :perse$B8e$NJ8;zNs(B
 *  inBuf[IN]   :psrse$B$9$k(BHTML$B%U%!%$%k$N#19TJ,(B
 *
 * [$BLa$jCM(B]
 *  $B$J$7(B
 *
 * [$B@)8B;v9`(B]
 *  inBuf$B$O(BEvernote$B$G%(%/%9%]!<%H$7$?(BHTML$B%U%!%$%k$N#19TJ,$r;XDj$9$k!#(B
 *  $BK\4X?tFb$G(BoutBuf$B$K(Ballocate$B$5$l$k$N$G!"K\4X?t$r;HMQ$9$kB&$G$=$l$r3+J|$9$k$3$H!#(B
 */
void sbt_web_html_parse(char** outBuf,const char* inBuf);

void sbt_web_html_parse_test();

#endif
