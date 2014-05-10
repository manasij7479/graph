filename=$1
rp=`realpath $filename`
expected=$2
c=".c"
cplpl=".cpp"
if [[ `echo $rp | grep .c$ -o` == "$c" ]]
then
	gcc $rp
	out=`a.out`
elif [[ `echo $rp | grep .cpp$ -o` == "$cplpl" ]]
then
	g++ $rp -std=c++11 
	out=`./a.out`

fi
# 	echo $expected $out

if [ $expected == $out ]
then
	echo '[OK]'
	exit 0
else
	echo '[ERROR]'
	exit 1
fi