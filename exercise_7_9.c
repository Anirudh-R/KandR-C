
/* MACRO based version of isupper */
// saves time because of no function call overhead,
// but uses more space during compilation. (?)
// Also, calls like isupper(*p++) will lead to p being incremented twice

#define isupper(c) ((c)>='A' && (c)<='Z') ? 1 : 0



/* Function based version of isupper */
// costs time because of function call overhead
// calls like isupper(*p++) will not be a problem

int isupper(char c)
{
	if(c>='A' && c<='Z')
		return 1;
	else
		return 0;
}
