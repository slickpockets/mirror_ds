#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "io.h"
#include "../port/error.h"
#include "interp.h"

#include "sds.root.h"

ulong ndevs = 24;
extern Dev rootdevtab;
extern Dev consdevtab;
extern Dev envdevtab;
extern Dev mntdevtab;
extern Dev pipedevtab;
extern Dev progdevtab;
extern Dev rtcdevtab;
extern Dev srvdevtab;
extern Dev dupdevtab;
extern Dev drawdevtab;
extern Dev pointerdevtab;
extern Dev ipdevtab;
extern Dev etherdevtab;
extern Dev ndsdevtab;
extern Dev dldidevtab;
extern Dev audiodevtab;
Dev* devtab[24]={
	&rootdevtab,
	&consdevtab,
	&envdevtab,
	&mntdevtab,
	&pipedevtab,
	&progdevtab,
	&rtcdevtab,
	&srvdevtab,
	&dupdevtab,
	&drawdevtab,
	&pointerdevtab,
	&ipdevtab,
	&etherdevtab,
	&ndsdevtab,
	&dldidevtab,
	&audiodevtab,
	nil,
};

extern void fifolink(void);
extern void etherndslink(void);
extern void ethermediumlink(void);
extern void iompcflink(void);
extern void ior4tflink(void);
void links(void){
	fifolink();
	etherndslink();
	ethermediumlink();
	iompcflink();
	ior4tflink();
}

extern void mathmodinit(void);
extern void sysmodinit(void);
extern void drawmodinit(void);
extern void tkmodinit(void);
extern void keyringmodinit(void);
void modinit(void){
	mathmodinit();
	sysmodinit();
	drawmodinit();
	tkmodinit();
	keyringmodinit();
}

#include "../ip/ip.h"
extern void tcpinit(Fs*);
extern void udpinit(Fs*);
extern void ipifcinit(Fs*);
extern void icmpinit(Fs*);
extern void icmp6init(Fs*);
void (*ipprotoinit[])(Fs*) = {
	tcpinit,
	udpinit,
	ipifcinit,
	icmpinit,
	icmp6init,
	nil,
};

	int main_pool_pcnt = 50;
	int heap_pool_pcnt = 30;
	int image_pool_pcnt = 20;
	int cflag = 0;
	int consoleprint = 1;
	int redirectconsole = 1;
	int iprintscreenputs = 0;
	char debug_keys = 1;
	int panicreset = 0;
	char *tkfont = "/fonts/lucidasans/unicode.6.font";
	int	tkstylus = 1;
	
char* conffile = "sds";
ulong kerndate = KERNDATE;
