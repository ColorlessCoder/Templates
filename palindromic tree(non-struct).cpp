const int MAXLEN = 300000+ 5;

    char s[MAXLEN];
struct PalindromicTree {
    int next[MAXLEN][26];
    int len[MAXLEN];
    int link[MAXLEN];
    int semi_link[MAXLEN];
    /**
        every node represents a palindrome
        len - the length of palindrome represented by current node
        next - transition from this node to other nodes by different characters
        link - node number of longest suffix palindrome of current node
    **/
    unsigned cnt[MAXLEN];
    //state tree[MAXLEN];

    int sz;
    int last;

    ///For finding total number of palindromes
    ///For finding total number of palindromes

    /**
        node 1 is root with len = -1
        node 2 is root with len = 0
    **/
    void init(int i)
    {
    //  tree[i].next.clear();
      cnt[i]=0;
     memset(next[i],-1,sizeof(next[i]));
    }
    PalindromicTree(int n) {
        //cnt2 = vector <long long> (n+10, 0);
        ///For finding total number of palindromes
        sz = last = 2;
       
    }
    void buildTree() {
        sz=last=2; 
        len[1] = -1; link[1] = 1;
        init(1);
        len[2] = 0; link[2] = 1;
        init(2);
        int n = strlen(s);
        for (int i = 0; i < n; i++) {
            Insert(i, s[i]-'a');
        }
        return;
    }
    /**
        returns true is a new palindromic substring is found adding new character c and false otherwise
    **/
    bool Insert(int pos, char c) {
        int cur = last, curlen = 0;

        while (true) {
            curlen = len[cur];
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
                break;
            cur = link[cur];
        }

        if (next[cur][c]!=-1) {
       // if (tree[cur].next[c]) {
            last = next[cur][c];
            cnt[last]++;
            // Common , !Unique
            return false;
        }
        sz++;
        last = sz;
        len[sz] = len[cur] + 2;
        init(sz);
        next[cur][c] = sz;

        if (len[sz] == 1) {
            link[sz] = 2;
            cnt[sz] = 1;
            return true;
        }

        while (true) {
            cur = link[cur];
            curlen = len[cur];
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                link[sz] = next[cur][c];
                break;
            }
        }
        cnt[sz] = 1;
        return true;
      } 
    
    /**
        call this function before working with different palindromic substring frequency
        cnt[i] - total frequency of palindromic node i
        palindromes - total number of palindromes(Unique + Non-unique)
        total number of unique palindromes is just the number of nodes in the tree except the 2 roots
    **/
   void palindromeCount() {
        for (int i = sz; i >= 3; i--) {
            cnt[link[i]] += cnt[i];
        }
        cnt[1] = cnt[2] = 0;
        // for(int i=0;i<=sz;i++) cout<<cnt[i]<<" ";
        //   cout<<endl;
        return ;
    }   
};
