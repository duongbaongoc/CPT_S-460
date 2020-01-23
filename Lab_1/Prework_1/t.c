
/*********  t.c file *********************/

int prints(char *s)
{
	while(*s != '\0')
	{
		putc(*s);
		s++;
	}
	return 0;
}

int gets(char s[])
{
	char c;
	int i = 0;
	while (1)
	{
		c = getc();
		if (c == '\r')
		{
			break;
		}
		s[i] = c;
		i++;
	}
	s[i] = 0;
	return 0;
}

char ans[64];

main()
{
  while(1){
    prints("What's your name?");
    gets(ans);  prints("\n\r");

    if (ans[0]==0){
      prints("return to assembly and hang\n\r");
      break;
    }
    prints("Welcome "); prints(ans); prints("\n\r");
  }
}
  

