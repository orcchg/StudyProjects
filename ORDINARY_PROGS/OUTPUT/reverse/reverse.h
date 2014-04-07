void reverse(char s1[], int MAX){
	
	char s2[MAX+1];
	int i,j;
	
	j=MAX;
	for(i=0;i<=MAX;i++){
		s2[j]=s1[i];
		j--;
	}
	
	for(int l=1;l<=MAX;l++)
		putchar(s2[l]);
}