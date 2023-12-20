#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_PTRACE_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_PTRACE_H_
COSMOPOLITAN_C_START_

extern const int PTRACE_TRACEME;
extern const int PTRACE_PEEKTEXT;
extern const int PTRACE_PEEKDATA;
extern const int PTRACE_PEEKUSER;
extern const int PTRACE_POKETEXT;
extern const int PTRACE_POKEDATA;
extern const int PTRACE_POKEUSER;
extern const int PTRACE_CONT;
extern const int PTRACE_KILL;
extern const int PTRACE_SINGLESTEP;
extern const int PTRACE_GETREGS;
extern const int PTRACE_SETREGS;
extern const int PTRACE_GETFPREGS;
extern const int PTRACE_SETFPREGS;
extern const int PTRACE_ATTACH;
extern const int PTRACE_DETACH;
extern const int PTRACE_GETFPXREGS;
extern const int PTRACE_SETFPXREGS;
extern const int PTRACE_SYSCALL;
extern const int PTRACE_GETEVENTMSG;
extern const int PTRACE_GETSIGINFO;
extern const int PTRACE_SETOPTIONS;
extern const int PTRACE_SETSIGINFO;
extern const int PTRACE_GETREGSET;
extern const int PTRACE_GETSIGMASK;
extern const int PTRACE_INTERRUPT;
extern const int PTRACE_LISTEN;
extern const int PTRACE_PEEKSIGINFO;
extern const int PTRACE_SECCOMP_GET_FILTER;
extern const int PTRACE_SECCOMP_GET_METADATA;
extern const int PTRACE_SEIZE;
extern const int PTRACE_SETREGSET;
extern const int PTRACE_SETSIGMASK;
extern const int PTRACE_O_TRACESYSGOOD;
extern const int PTRACE_O_TRACEFORK;
extern const int PTRACE_O_TRACEVFORK;
extern const int PTRACE_O_TRACECLONE;
extern const int PTRACE_O_TRACEEXEC;
extern const int PTRACE_O_TRACEVFORKDONE;
extern const int PTRACE_O_TRACEEXIT;
extern const int PTRACE_O_TRACESECCOMP;
extern const int PTRACE_O_MASK;
extern const int PTRACE_EVENT_FORK;
extern const int PTRACE_EVENT_VFORK;
extern const int PTRACE_EVENT_CLONE;
extern const int PTRACE_EVENT_EXEC;
extern const int PTRACE_EVENT_VFORK_DONE;
extern const int PTRACE_EVENT_EXIT;
extern const int PTRACE_EVENT_STOP;
extern const int PTRACE_EVENT_SECCOMP;

COSMOPOLITAN_C_END_

#define PTRACE_TRACEME              PTRACE_TRACEME
#define PTRACE_PEEKTEXT             PTRACE_PEEKTEXT
#define PTRACE_PEEKDATA             PTRACE_PEEKDATA
#define PTRACE_PEEKUSER             PTRACE_PEEKUSER
#define PTRACE_POKETEXT             PTRACE_POKETEXT
#define PTRACE_POKEDATA             PTRACE_POKEDATA
#define PTRACE_POKEUSER             PTRACE_POKEUSER
#define PTRACE_CONT                 PTRACE_CONT
#define PTRACE_KILL                 PTRACE_KILL
#define PTRACE_SINGLESTEP           PTRACE_SINGLESTEP
#define PTRACE_GETREGS              PTRACE_GETREGS
#define PTRACE_SETREGS              PTRACE_SETREGS
#define PTRACE_GETFPREGS            PTRACE_GETFPREGS
#define PTRACE_SETFPREGS            PTRACE_SETFPREGS
#define PTRACE_ATTACH               PTRACE_ATTACH
#define PTRACE_DETACH               PTRACE_DETACH
#define PTRACE_GETFPXREGS           PTRACE_GETFPXREGS
#define PTRACE_SETFPXREGS           PTRACE_SETFPXREGS
#define PTRACE_SYSCALL              PTRACE_SYSCALL
#define PTRACE_GETEVENTMSG          PTRACE_GETEVENTMSG
#define PTRACE_GETSIGINFO           PTRACE_GETSIGINFO
#define PTRACE_SETOPTIONS           PTRACE_SETOPTIONS
#define PTRACE_SETSIGINFO           PTRACE_SETSIGINFO
#define PTRACE_GETREGSET            PTRACE_GETREGSET
#define PTRACE_GETSIGMASK           PTRACE_GETSIGMASK
#define PTRACE_INTERRUPT            PTRACE_INTERRUPT
#define PTRACE_LISTEN               PTRACE_LISTEN
#define PTRACE_PEEKSIGINFO          PTRACE_PEEKSIGINFO
#define PTRACE_SECCOMP_GET_FILTER   PTRACE_SECCOMP_GET_FILTER
#define PTRACE_SECCOMP_GET_METADATA PTRACE_SECCOMP_GET_METADATA
#define PTRACE_SEIZE                PTRACE_SEIZE
#define PTRACE_SETREGSET            PTRACE_SETREGSET
#define PTRACE_SETSIGMASK           PTRACE_SETSIGMASK
#define PTRACE_O_TRACESYSGOOD       PTRACE_O_TRACESYSGOOD
#define PTRACE_O_TRACEFORK          PTRACE_O_TRACEFORK
#define PTRACE_O_TRACEVFORK         PTRACE_O_TRACEVFORK
#define PTRACE_O_TRACECLONE         PTRACE_O_TRACECLONE
#define PTRACE_O_TRACEEXEC          PTRACE_O_TRACEEXEC
#define PTRACE_O_TRACEVFORKDONE     PTRACE_O_TRACEVFORKDONE
#define PTRACE_O_TRACEEXIT          PTRACE_O_TRACEEXIT
#define PTRACE_O_TRACESECCOMP       PTRACE_O_TRACESECCOMP
#define PTRACE_O_MASK               PTRACE_O_MASK
#define PTRACE_EVENT_FORK           PTRACE_EVENT_FORK
#define PTRACE_EVENT_VFORK          PTRACE_EVENT_VFORK
#define PTRACE_EVENT_CLONE          PTRACE_EVENT_CLONE
#define PTRACE_EVENT_EXEC           PTRACE_EVENT_EXEC
#define PTRACE_EVENT_VFORK_DONE     PTRACE_EVENT_VFORK_DONE
#define PTRACE_EVENT_EXIT           PTRACE_EVENT_EXIT
#define PTRACE_EVENT_STOP           PTRACE_EVENT_STOP
#define PTRACE_EVENT_SECCOMP        PTRACE_EVENT_SECCOMP

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_PTRACE_H_ */