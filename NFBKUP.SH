TODAY=`/bin/date +%m%d%y%H`
cd c:/nf
if [ ! -d d:/bkup/$TODAY ]
then
   mkdir  d:/bkup/$TODAY
fi
# xcopy '*.*'  '\nfbkup\'$TODAY'\'  /m /s
echo "Source Directory - c:\\\nf"
echo "Target Directory - d:\\\bkup"
echo Backup Changed ...
echo "\n   Files matching-'??'"
xcopy '??' 'd:\bkup\'$TODAY /s/m
echo "\n   Files matching-'*.xls'"
xcopy '*.xls' 'd:\bkup\'$TODAY /s/m
echo "\n   Files matching-'chart'"
xcopy chart 'd:\bkup\'$TODAY /s/m
echo "\n   Files matching-'wk?'"
xcopy '*.wk?' 'd:\bkup\'$TODAY /s/m
echo "\n   Files matching-'*.c'"
xcopy '*.c' 'd:\bkup\'$TODAY /s/m
echo "\n   Files matching-'*.cpp'"
xcopy '*.cpp' 'd:\bkup\'$TODAY /s/m
echo "\n   Files matching-'*.h'"
xcopy '*.h' 'd:\bkup\'$TODAY /s/m
echo "\n   Files matching-'*.rc'"
xcopy '*.rc' 'd:\bkup\'$TODAY /s/m
echo "\n   Files matching-'*.exe'"
xcopy '*.exe' 'd:\bkup\'$TODAY /s/m
echo "\n d:\\\winappl\\\Sidekick95\\\userdata\\\'*.*'"
cd d:/winappl/sideki~1/userdata
pwd
xcopy '*.*' 'd:\bkup\'$TODAY /s/m
#echo "\n c:\\\autoexec.bat c:\\\config.sys"
#cd c:/
#xcopy autoexec.bat 'd:\bkup\'$TODAY /s/m
#xcopy config.sys 'd:\bkup\'$TODAY /s/m
#echo "\n c:\\win30\\system.dat c:\\\win30\\\user.dat c:\\\win30\\\*.ini"
#cd c:/win30
#xcopy system.dat 'd:\bkup\'$TODAY /s/m/h
#xcopy user.dat 'd:\bkup\'$TODAY /s/m/h
#xcopy '*.ini' 'd:\bkup\'$TODAY /s/m/h
echo "c:\\\ftw\\\penn.'*'"
cd c:/ftw
pwd
xcopy 'penn.*' 'd:\bkup\'$TODAY /s /m


#BYTES=$(command.com /c dir /s 'd:\bkup\'$TODAY | tail -2 | head -1 | cut -f3- -d' '  )
#echo $BYTES
