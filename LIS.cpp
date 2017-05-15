rep2(i,n) scanf("%d",&A[i]);
    int L[MAXN], L_id[MAXN], P[MAXN];

    int lis = 0, lis_end = 0;
    for (int i = 0; i < n; ++i) {
        int pos = upper_bound(L, L + lis, A[i]) - L;
        L[pos] = A[i];
        L_id[pos] = i;
        if (pos + 1 > lis) {
          lis = pos + 1;
          lis_end = i;
        }
    }
