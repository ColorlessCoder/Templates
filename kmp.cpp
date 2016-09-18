vi kmp(char *str)
{
    int n=strlen(str);
    vi pif(n);
    pif[0]=0;
    for(int i=1;i<n;i++)
    {
        int j=pif[i-1];
        while(j>0  && (str[i]!=str[j]) )
            j=pif[j-1];
        if(str[i] == str[j]) j++;
        pif[i]=j;
    }
    return pif;
}

int main()
{
    char str[50010],str2[50010],str3[100010];
    int T,I=1;
    cin>>T;
    while(T--)
    {
        printf("Case %d: ",I++);
        scanf("%s",str2);
        scanf("%s",str);
        int n=strlen(str);
        int m=strlen(str2);
        int j=0;
        for(int i=0;i<n;i++)
            str3[j++]=str[i];
        str3[j++]='#';
        for(int i=0;i<m;i++)
            str3[j++]=str2[i];
        vi a=kmp(str3);
    }
    return 0;
}
