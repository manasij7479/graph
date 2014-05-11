# awk -f test.awk testlist
BEGIN{
	pass=0;
	fail=0;
}
{
	expected=$2;
	
	for(i=3;i<=NF;++i)
		expected=expected "\\ "$i;
	
	retval=system("./check.sh "  $1 " " expected);
	if(retval==0)
		pass++;
	else 
		fail++;
}
END{
	printf("%d tests passed out of %d\n",pass,pass+fail);
}