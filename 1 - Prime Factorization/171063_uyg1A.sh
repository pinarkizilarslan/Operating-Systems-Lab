#I typed the "chmod +x 171063_uyg1A.sh" command to make my script executable.

echo ; echo --- Please press enter to advance ---
read input


echo --- 2.1: tempFiles folder created ---
mkdir -p tempFiles
read input


echo --- 2.2: This path and subpath are listed ---
ls -1rRs
read input


echo --- 2.3: .c and .sh moved to tempFiles folder ---
mv *.c *.sh ./tempFiles
ls -R
read input


echo --- 2.4: Files except tempFiles deleted ---
find . -maxdepth 1 -type f -delete
ls -R
read input


echo --- 2.5: Inside of file tempFiles has been copied ---
cp -RT tempFiles/ .
ls -R
read input


echo --- 2.6: tempFiles folder deleted ---
rm -r tempFiles/
ls -R
read input


echo --- 2.7: Building the C code ---
gcc 171063_uyg1A.c -o executableBuild
ls -R
read input


echo --- 2.8: Example run via console---
for((i=0;i<3;i++))
do
echo Bir sayı giriniz: 
./executableBuild >> 171063_uyg1A_output.txt
wc -wm 171063_uyg1A_output.txt
done
read input


echo --- 2.8: Reading 171063_uyg1A_output.txt
cat 171063_uyg1A_output.txt

