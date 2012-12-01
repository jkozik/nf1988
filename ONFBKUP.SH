TODAY=`/bin/date +%m%d%y%H`
cd /nf
mkdir  /nfbkup/$TODAY
xcopy '*.*'  '\nfbkup\'$TODAY'\'  /m /s
