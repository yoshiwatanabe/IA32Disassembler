IA32Disassembler
================
How to write a disassembler.

Questions

Disassembling a machine code into human readable assembly code sounds complicate. When you look at the Intel instruction manual, you understand that it is. However it is not necessarily difficult to write one given that you decompose the task into smaller subordinate tasks.

There are several problems that pops up in your mind when you think about writing a disassembler.

How does the raw machine code look like?
How are machine code and assembly code related?
How do I get to the beginning of a machine code? Where does it come from?
What kind of documentation and specification do I need?
etc.
Dumpbin

The easiest way to get answers to those questions is to play with "dumpbin.exe" utility provided by Microsoft Visual C++ tools. This utility comes with every version of Visual C++, from 2.0 to 6.0 as far as I remember. Note that Visual C++ 1.52, a 16-bit edition, does NOT come with dumpbin.exe. Instead it came with exehdr.exe or something, and that doesn't work for 32-bit PE format executables.

Dumpbin.exe is a powerful PE format executable file dumper utility that can dump all kinds of stuff from any PE file. Here, we study the output of dumpbin.exe using /DISASM switch. It literally "disassembles" the content of "code" section of a given file. (basically we don't have to write a disassembler at all since we got one!).

The following is a sample dumpbin output "NOTEPAD.EXE".



One instruction appears in a single line at a time (except when it is too long and wraps to a following line). At the far left columns, you see addresses of each instruction. The first instruction "cmp" is located at address:

01B41000:
The middle column shows variable-length "raw machine code" per instruction. For example, the first instruction is:

83 3D E8 8E B4 01 00
Finally, the human-readable assembly language instruction appears. It is:

cmp dword ptr ds:[01B48EE8h], 0
You don't need to understand what this really means until you get to much later part in this document, but it roughly means that "compare a 4-byte big data located at address 01B48EE8 in the DS segment against literal value 0".

Notice that there are instructions that are 7-byte in length, like the first instruction, but others may be 2-byte long, 5-byte long, some are even just 1-byte long. The point is that Intel x86 (starting from 8086 up to the current Pentium II) use "variable-length instruction" as against "fixed-length" instructions. This is one of the differences from RISC processors, whose instructions are all the same length. Also contrast this with Java byte code. Although Java byte code is not a native "machine" code (well, it sometimes is... I think Sun has a hardware that directly interprets Java byte code), it is similar "encoding", and its instructions are all one byte.

Intel x86? Which processor are we going to work for?

One of the reasons of Intel's success in their processor business is their "backward compatibility" with legacy codes. The following is a brief history of Intel's x86 series processors.

1979 8088/8086
1982 80286
1985 i386
1989 i486
1993 Pentium
1997 Pentium Pro & MMX stuff
1998 Pentium II & Celeron
Each generation of processor became better and better by improving things like:

expanding data and address bus to increase addressing space
introducing protected mode for more reliable operating environment
increasing the size of cache
integrating with FPU
adding more instructions like MMX that EVERYBODY uses
adding multi-scaler pipelining
increasing clock cycle rate
and many other stuff that I have no idea
From our disassembler's point of view, we don't have to worry about processor specific things. It is all hidden, and instruction map is never "modified" although new instructions were added over two decades.

Also, for this project, I intended to completely ignored 16-bit code. However, as I discover, it was easier to include logics that are only applicable to 16-bit to the project since the processor architecture is built with 16-bit and 32-bit mode relatively strongly coupled. In another word, the amount of work to separate 16-bit stuff from 32-bit stuff is more than simply take both in to the project.

To answer the question of which processor would our disassembler work, it will work only back to i386. The reason: 80286 has no protected mode. Windows run only with protected mode.

Which Microsoft Windows?

Our disassembler is going to work primarily with Portable Executable format files (a.k.a PE file). This PE format files are standard executable file format for 32-bit Windows. 16-bit Windows executable are in format called NE (New Executable?), and it is not compatible with PE format. Types of program that are in PE format are:

User-mode executable file (EXE, DLL, and others) for Windows 95/98.
User-mode executable file (EXE, DLL, and others) for Windows NT.
Kernel-mode executable file (SYS) for Windows NT.
Kernel-mode executable for Windows 95 (and most of 98), normally called as VxD, are in LE format (a format that is somewhat more compatible with OS/2), and this is not compatible with PE file format.

However, as you will see, I designed the project in such way that the piece of software that "parse" a stream of machine code byes are completely ignorant about "where" it comes from. In another word, it could come from either PE file code section, or VxD's code segment. So it is possible to extend it so that it will work with non-PE format file.

Still, vast majority of executables we deal with everyday are in PE file format. So we will only work with PE file.

Any reference needed?

Only documentation that is going to be required is an Intel processor manual. It is officially called "Intel Architecture Software Developer's Manual" (ISBN-1555122744). There are three volumes, and the volume 2 contains most of the information we need. The problem is that this document is not sold in most of the book stores. However, it is available for free from Intel's download site.

Intel's official manual is not the only reference that we could use. In fact, there are other books that also contain information needed to write disassembler. I find that it is helpful to have several references so that when one book is not clear about something, I can check other books. I used "The Intel Microprocessors 8086/8088, 80186/80188, 80286, 80386, 80486, Pentium, and Pentium Pro Processor" by Barry B. Brey (ISBN-0132606704).

