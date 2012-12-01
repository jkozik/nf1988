@echo off

set bkuprtdir=d:\bkup
c:\nf\newsrc\yymmddpp.exe %bkuprtdir%
call c:\yymmddhh
echo yymmddhh=%yymmddhh% bkuppath=%bkuppath%


echo Backup Directory - %bkuppath%
echo Source Directory - c:\nf
c:
cd c:\nf
rem pause

echo   Files matching-'??'
xcopy ?? %bkuppath% /s/m
echo   Files matching-'*.xls'
xcopy *.xls %bkuppath% /s/m
echo   Files matching-'chart'
xcopy chart %bkuppath% /s/m
echo   Files matching-'*.wk?'
xcopy *.wk? %bkuppath% /s/m
echo   Files matching-'*.c'
xcopy *.c %bkuppath% /s/m
echo   Files matching-'*.h'
xcopy *.h %bkuppath% /s/m
echo   Files matching-'*.cpp'
xcopy *.cpp %bkuppath% /s/m
echo   Files matching-'*.rc'
xcopy *.rc %bkuppath% /s/m
echo   Files matching-'*.exe'
xcopy *.exe %bkuppath% /s/m
rem pause

 
echo Source Directory - Sidekick
rem cd "C:\Program Files\Starfish\Internet Sidekick\userdata"
cd \Progra~1\Starfish\Sideki~1\userdata

xcopy *.* %bkuppath% /s/m

echo Source Directroy - Family Tree c:\ftw
cd c:\ftw
xcopy penn.* %bkuppath% /s/m
