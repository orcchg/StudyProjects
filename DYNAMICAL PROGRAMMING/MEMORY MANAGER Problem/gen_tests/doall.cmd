@echo off
:: Problem: memory
:: Test generation script

cl /nologo genzebra.cpp
cl /nologo gennoalloc.cpp
cl /nologo /O2 /TC merge.c
cl /nologo /O2 /GX gen_at_joinall.cpp
cl /nologo /O2 /GX gen_at_joinlocal.cpp
cl /nologo /O2 /GX gen_at_stairs.cpp
dcc32 -cc genariphm.dpr
dcc32 -cc gencluster.dpr
dcc32 -cc gencoffin.dpr
dcc32 -cc gengrob.dpr

;genzebra 37650 200 15 1 0 > 05 2> nul
;echo 05
;genzebra 23532 2000000000 10 1 0 > 06 2> nul
;echo 06

gen_at_stairs.exe 783552574 1000 150 > temp0
gen_at_joinall.exe 358943 1000 150 > temp1
gen_at_joinall.exe 333433 1000 150 > temp2
gen_at_joinall.exe 382235 1000 150 > temp3
gen_at_joinlocal.exe 3495848 1000 150 20 > temp4
merge temp0 temp1 temp2 temp3 temp4 >05
echo 05

gen_at_stairs.exe 783574 1000000000 1000 > temp0
gen_at_joinall.exe 35895843 1000000000 1000 > temp1
gen_at_joinall.exe 35895844 1000000000 1000 > temp2
gen_at_joinall.exe 35895847 1000000000 1000 > temp3
gen_at_joinlocal.exe 3495848 1000000000 1000 50 > temp4
merge temp0 temp1 temp2 temp3 temp4 >06
echo 06

del /q temp0 temp1 temp2 temp3 temp4

genzebra 32532 2000000000 100 1 0 > 07 2> nul
echo 07
gengrob.exe 916 660 0 1 2 3 2 10 > 08
echo 08
gengrob.exe 2671 40012 1 0 1 0 1 100 > 09
echo 09

genzebra 64343 2000000000 20000 0 0 > 10 2> nul
echo 10
genzebra 64343 2000000000 16000 1 0 > 11 2> nul
echo 11
genzebra 62343 2000000000 16000 1 1 > 12 2> nul
echo 12
genzebra 19843 2000000000 50000 0 1 > 13 2> nul
echo 13
genzebra 59843 2000000000 50000 0 0 > 14 2> nul
echo 14
gennoalloc 23523 10000 100000 20000 4000 0 > 15
echo 15
gennoalloc 52332 20000 100000 20000 4000 1 > 16
echo 16

genariphm 3494872 50000 > 17
echo 17
gencluster 3732367 50000 10 8 > 18
echo 18
gencoffin 81511 49000 2 2 400 > 19
echo 19
gengrob 111 48000 1 3 2 0 0 100 > 20
echo 20

