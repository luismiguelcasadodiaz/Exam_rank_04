#234567890123456789012345678901234567890123456789012345678901234567890123456789#
#        1         2         3         4         5         6         7         #
#..............................................................................#
# Luis Miguel Casado Díaz (LMCD) .gdbinit configuration file                   #
#                                                                              #
# 2024_06_09                                                                   #
#..............................................................................#

# To enable execution of this file, ensure you have a inside file
# ~/.config/gdb/gdbinit
# a line starting with add-auto-load-safe-path <absolute path to this file>
# add-auto-load-safe-path /home/......../circle4/namada_minshell/.gdbinit

# to enable Debuginfo
set debuginfod enabled on
# To print structs in a more readable form
set print pretty on
# Follow child at fork()
set follow-fork-mode child
# To keep father & child under control with "inferior" command
set detach-on-fork off
# Set Breakpoint at main function
break microshell_p.c:67
# Set other breakpoint
#break init.c:108
#break init.c:117
#break is_scene1.c:20 if y == 300
# set alias
break microshell_p.c:77

run /bin/ls | /usr/bin/grep microshell ; /bin/echo i love my microshelle

