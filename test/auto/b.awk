BEGIN{
	pass=0;
	fail=0;
}
{
	retval=system("./cr.sh "  $1 " " $2);
	if(retval==0)
		pass++;
	else 
		fail++;
}
END{
	printf("%d tests passed out of %d\n",pass,pass+fail);
}