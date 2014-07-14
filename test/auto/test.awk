# awk -f test.awk testlist
BEGIN{
	pass=0;
	fail=0;
}
{
	expected=$2;
	
	for(i=3;i<=NF;++i)
		expected=expected "\\ "$i;
	
	retval=system("./auto/pycheck.py "  $1 " " expected);
	if(retval==0)
	{
		print "[OK]" #$1
		pass++;
	}
	else 
	{
		if(retval==1)
			print "[BUILD ERROR] : " $1
		if(retval==2)
			print "[VALUE ERROR] : " $1
		fail++;
	}
}
END{
	printf("%d passed out of %d\n",pass,pass+fail);
}