TODAY=`/bin/date +%m%d%y%H`
cd /nf
echo Put backup disk in a:
read x
mkdir 'a:\'$TODAY
dir /s /a:a /w /o
xcopy '??' 'a:\'$TODAY /s /m /w /p
xcopy chart 'a:\'$TODAY /s/m/w
xcopy '*.wk1' 'a:\'$TODAY /s/m/w
