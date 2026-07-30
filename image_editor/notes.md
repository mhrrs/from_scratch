# Project: Image Editor:

# Goals for project:
- learn about filestreams
- learn about system calls
- learn more about pointers and memory management
- learn about bit manipulation (and memory types)
- makefiles


*MAKEFILES:*
- a simple build automation script used by the 'make' tool
- - tells us what files depend on what and how to compile or link them into the final executable
- instead of retyping your gcc commands every time, make automatically rebuilds only the files that changed




*FILE STREAMS:*
- a way for a program to read from or write to a file, treating the file as a continuous flow of bytes or characters, rather than manualy managing every bit of data.
what does this actually mean and how does that work underneath the hood?: the following things are created when you actually go to the file object in memory. You don't actually create or directly read the object. instead the function fopen creates:
- a file descriptor/handle: an integer that the OS uses to identify the open file (literally an integer)
- a buffer: a chunk of RAM (often ~4-8kb) that temporarily stores file data
- a position pointer: tracks where you currenlyt are in the file
- a mode flag: indicates whether you have read/write/binary/text permissions
- possibly error flags and EOF flags (EOF = end of file)
= in summary: FILE* just holds the metadata and buffer that manage how your program talks to the OS which then interacts with memory
- 'streaming' is just the act of the buffer being filled by the OS with unread bytes and returning them to the program. If the buffer is empty the library makes a system call to the OS like ReadFile(). The OS kernel takes the file descriptor and finds the actual file data on disk. The OS reads a chunk from the disk into kernel memory. Then that chunk is copied into your program's buffer (in user memory). then one byte (or multiple) are returned to your program. Your program is reading the file through a chunking method that works with the OS to make sure anything you haven't read yet gets refilled until the EOF flag is found.

*System Calls:*
- sys call is an assembly command that instructs the OS to enter kernel mode 
- if your program needs to access anything the kernel controls (hardware, memory, files, processes, or time) it must first reach out to the kernel via a 'system call' which is then either validated or rejected by the kernel for the thing that you are trying to do.

Your Program (user mode)
    ↓
System call (e.g. read(fd, buf, n))
    ↓
Kernel (privileged mode)
    ↓
Filesystem driver
    ↓
Disk controller
    ↓
Physical storage device



*How the kernel and user 'modes' interact within the OS:*
- both modes exist within the same physical memory and use the same CPU, but the processor maintains a privelige bit  that decides what you're allowed to do.
USER MODE:
- cannot execute privileged instructions (like writing to control registers or touching I/O ports)
- has restricted access to memory (your process only sees its own virtual address space)

KERNEL MODE:
- runs with full access to memory, hardware, and CPU instructions
- can touch any address and perform I/O

when done performing privleged kernel function with priveleged bit:
- the sysret assembly function is called which returns the user to to user mode

CPU running user code
┌────────────────────────────┐
│ mov rax, SYS_read          │
│ mov rdi, fd                │
│ mov rsi, buf               │
│ mov rdx, 100               │
│ syscall   ←──────┐         │
└──────────────────┘         │
                            ▼
                ┌──────────────────────┐
                │ Kernel syscall entry │
                │   save registers     │
                │   run sys_read()     │
                │   copy data to user  │
                │   set return value   │
                │   sysret             │
                └──────────────────────┘
                            ▲
┌────────────────────────────┐
│ (CPU back in user mode)    │
│  check return in rax       │
│  continue program          │
└────────────────────────────┘


# how the CPU maintains security at the physical level:

The CPU:
- holds registers (rax, rdi, etc)
- runs machine instructions (mov, add, syscall, sysret, etc)
- keeps track of the current mode bit (user vs kernel)
- enforces access control at the hardware level

the privelege bit (also called CPL) is part of the CPU's hardware state. its a 1 or 2 bit flag inside a control register that the OS cannot fake. when its 0 its in kernel mode and when its 3 its in user mode. Only the CPU itself can flip that bit.

The OS:
- software that runs on top of the CPU but its trusted by the hardware.
- defines what code should run when a syscall happens (the syscall handlers address)
- manages memory, processes, and devices
- sets up tables that the CPU uses for those mode transitions (interrupt descriptor table, syscall entry point)
- runs in kernel mode, so it can access privileged CPU instructions
CPU actually flips the bit, the OS dfines what the CPU should do when that flip happens
