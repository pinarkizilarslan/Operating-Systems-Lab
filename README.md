# Introduction

### UNIX Basic: 
UNIX is an operating system which was first developed in the 1960s, and has been under constant development ever since. By operating system, we mean the suite of programs which make the computer work. It is a stable, multi-user, multi-tasking system for servers, desktops and laptops. <br>
UNIX systems also have a graphical user interface (GUI) similar to Microsoft Windows which provides an easy to use environment. There are many different versions of UNIX, although they share common similarities. The UNIX operating system is made up of three parts; the kernel, the shell and the programs.

`The kernel:` The kernel is the core of the UNIX operating system. Basically, the kernel is a large program that is loaded into memory when the machine is turned on, and it controls the allocation of hardware resources from that point forward. The kernel knows what hardware resources are available (like the processor(s), the on-board memory, the disk drives, network interfaces, etc.), and it has the necessary programs to talk to all the devices connected to it. 

`The shell:` The shell acts as an interface between the user and the kernel. The shell is a command line interpreter (CLI). It interprets the commands the user types in and arranges for them to be carried out. The commands are themselves programs: when they terminate, the shell gives the user another prompt. Users can use different shells on the same machine. UNIX system offers verity of shells like 1) Bourne shell 2) c shell 3) Korn shell 4) Bash shell (very powerful & recommended for use, Linux default shell). The shell keeps a list of the commands you have typed in. 

`The UNIX file system:` All the stored information on a UNIX computer is kept in a file system. Any time we interact with the UNIX shell, the shell considers us to be located somewhere within a file system. The place in the file system tree where we are located is called the current working directory.
The UNIX file system is hierarchical (resembling a tree structure). The tree is anchored at a place called the root, designated by a slash “/”. Every item in the UNIX file system tree is either a file, or a directory. A directory is like a file folder. A directory can contain files, and other directories. A directory contained within another is called the child of the other. A directory in the file system tree may have many children, but it can only have one parent. A file can hold information, but cannot contain other files, or directorie. <br><br>
To describe a specific location in the file system hierarchy, you must specify a "path". 
The path to a location can be defined as an absolute path from the root anchor point, or as a relative path, starting from the current location. When specifying a path, you simply trace a route through the file system tree, listing the sequence of directories you pass through as you go from one point to another. Each directory listed in the sequence is separated by a slash. 

<br><br>
