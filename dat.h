typedef struct Conf	Conf;
typedef struct FPU	FPU;
typedef struct FPenv	FPenv;
typedef struct Label	Label;
typedef struct Lock	Lock;
typedef struct Mach	Mach;
typedef struct Ureg	Ureg;
typedef struct ISAConf	ISAConf;

typedef ulong Instr;

struct Conf
{
	ulong	nmach;			/* processors */
	ulong	nproc;			/* processes */
	ulong	npage0;			/* total physical pages of memory */
	ulong	npage1;			/* total physical pages of memory */
	ulong	topofmem;		/* highest physical address + 1 */
	ulong	npage;			/* total physical pages of memory */
	ulong	base0;			/* base of bank 0 */
	ulong	base1;			/* base of bank 1 */
	ulong	ialloc;			/* max interrupt time allocation in bytes */
	ulong	flashbase;
	ulong	pagetable;

	int		bsram;			/* start of SRAM memory */
	int		brom;			/* start of ROM data memory */

	int		bmap;			/* buttons map selection */
	int		screens;		/* number of screens */
	int		portrait;		/* display orientation */
	int		swcursor;		/* display swcursor */
};

#define NISAOPT 8
struct ISAConf {
	char	type[KNAMELEN];
	ulong	port;
	ulong	irq;
	int	itype;
	ulong	sairq;
	ulong	dma;
	ulong	mem;
	ulong	size;
	ulong	freq;

	int	nopt;
	char	*opt[NISAOPT];
};

/*
 * FPenv.status
 */
enum
{
	FPINIT,
	FPACTIVE,
	FPINACTIVE,
};

struct	FPenv
{
	ulong	status;
	ulong	control;
	ushort	fpistate;	/* emulated fp */
	ulong	regs[8][3];	/* emulated fp */	
};

/*
 * This structure must agree with fpsave and fprestore asm routines
 */
struct	FPU
{
	FPenv	env;
	uchar	regs[80];	/* floating point registers */
};

struct Label
{
	ulong	sp;
	ulong	pc;
};

struct Lock
{
	ulong	key;
	ulong	sr;
	ulong	pc;
	int	pri;
};

#include "../port/portdat.h"

/*
 *  machine dependent definitions not used by ../port/dat.h
 */
struct Mach
{
	/* OFFSETS OF THE FOLLOWING KNOWN BY l.s */
	ulong	splpc;		/* pc of last caller to splhi */

	/* ordering from here on irrelevant */
	ulong	ticks;			/* of the clock since boot time */
	Proc	*proc;			/* current process on this processor */
	Label	sched;			/* scheduler wakeup */
	Lock	alarmlock;		/* access to alarm list */
	void	*alarm;			/* alarms bound to this clock */
	ulong	cpuhz;
	int	machno;
	int	nrdy;

	/* stacks for exceptions */
	ulong   fiqstack[4];
	ulong   irqstack[4];
	ulong   abtstack[4];
	ulong   undstack[4];

	int	stack[1];
};

#define	MACHP(n)	(n == 0 ? (Mach*)(MACHADDR) : (Mach*)0)

extern Mach Mach0;
extern Mach *m;
extern Proc *up;

/*
 * Layout at virtual address 0.
 */
typedef struct Vectorpage {
	void	(*vectors[8])(void);
	uint	vtable[8];
} Vectorpage;
extern Vectorpage *page0;

typedef struct MemBank {
	uint	pbase;
	uint	plimit;
	uint	vbase;
	uint	vlimit;
} MemBank;
