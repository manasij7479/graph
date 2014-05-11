filename=$1
rp=`realpath $filename`
expected=$2
c=".c"
cplpl=".cpp"
if [[ `echo $rp | grep .c$ -o` == "$c" ]]
then
	cc $rp &>/dev/null
elif [[ `echo $rp | grep .cpp$ -o` == "$cplpl" ]]
then
	c++ $rp -std=c++11 &>/dev/null
fi

# 	echo $expected $out
if [ $? == 0 ]
then
	out=`./a.out`
	if [ "$expected" == "$out" ]
	then
		echo '[OK]'
		exit 0
	else
		echo '[VALUE ERROR]'
		exit 1
	fi
else
	echo '[BUILD ERROR]'
	exit 1
fi
