#!/bin/bash
#  #
#                                 COLORS                                       #
#  #
DEF_COLOR='\033[0;39m'
GRAY='\033[0;90m'
RED='\033[0;91m'
GREEN='\033[0;92m'
YELLOW='\033[0;93m'
BLUE='\033[0;94m'
MAGENTA='\033[0;95m'
CYAN='\033[0;96m'
WHITE='\033[0;97m'
BLACK='\033[0;99m'
ORANGE='\033[38;5;209m'
BROWN='\033[38;2;184;143;29m'
DARK_GRAY='\033[38;5;234m'
MID_GRAY='\033[38;5;245m'
DARK_GREEN='\033[38;2;75;179;82m'
DARK_YELLOW='\033[38;5;143m'

echo -e "${BLUE} TESTING ./microshell cd a b c d e ${DEF_COLOR}"
./microshell cd a b c d e
echo -e "${BLUE} TESTING ./microshell cd x ${DEF_COLOR}"
./microshell cd x
echo -e "${BLUE} TESTING ./microshell cd .. ${DEF_COLOR}"
./microshell cd ..
echo -e "${BLUE} TESTING ./microshell x ${DEF_COLOR}"
./microshell x
echo -e "${BLUE} TESTING ./microshell /bin/echo -e x ${DEF_COLOR}"
./microshell /bin/echo -e x
echo -e "${BLUE} TESTING ./microshell /bin/echo -e y ; /bin/ls | /usr/bin/wc -l ${DEF_COLOR}"
./microshell /bin/echo -e y ";" /bin/ls "|" /usr/bin/wc -l
echo -e "${BLUE} TESTING ./microshell /bin/sleep 3 | /bin/sleep 3 | /bin/sleep 3 | /bin/sleep 3 ${DEF_COLOR}"
./microshell /usr/bin/sleep 3 "|" /usr/bin/sleep 3 "|" /usr/bin/sleep 3 "|" /usr/bin/sleep 3
echo -e "${BLUE} TESTING ./microshell /bin/ls | /usr/bin/grep microshell ; /bin/echo -e i love my microshell ${DEF_COLOR}"
./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo -e i love my microshell 🥰
