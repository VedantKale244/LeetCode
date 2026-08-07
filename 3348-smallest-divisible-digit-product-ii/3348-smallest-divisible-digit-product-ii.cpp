class Solution {
public:
    string smallestNumber(string num, long long t) {
        int need2 = 0, need3 = 0, need5 = 0, need7 = 0;

        while (t % 2 == 0) need2++, t /= 2;
        while (t % 3 == 0) need3++, t /= 3;
        while (t % 5 == 0) need5++, t /= 5;
        while (t % 7 == 0) need7++, t /= 7;

        if (t != 1) return "-1";

        static const int f2[10] = {0,0,1,0,2,0,1,0,3,0};
        static const int f3[10] = {0,0,0,1,0,0,1,0,0,2};
        static const int f5[10] = {0,0,0,0,0,1,0,0,0,0};
        static const int f7[10] = {0,0,0,0,0,0,0,1,0,0};

        const int MAX2 = 60;
        const int MAX3 = 40;
        const int INF = 1e9;

        vector<vector<int>> dp(MAX2, vector<int>(MAX3, INF));
        dp[0][0] = 0;

        vector<pair<int,int>> trans = {
            {1,0}, //2
            {0,1}, //3
            {2,0}, //4
            {1,1}, //6
            {3,0}, //8
            {0,2}  //9
        };

        for(int i=0;i<MAX2;i++){
            for(int j=0;j<MAX3;j++){
                if(dp[i][j]==INF) continue;

                for(auto [a,b]:trans){
                    int ni=min(MAX2-1,i+a);
                    int nj=min(MAX3-1,j+b);
                    dp[ni][nj]=min(dp[ni][nj],dp[i][j]+1);
                }
            }
        }

        for(int i=MAX2-1;i>=0;i--){
            for(int j=MAX3-1;j>=0;j--){
                if(i+1<MAX2)
                    dp[i][j]=min(dp[i][j],dp[i+1][j]);
                if(j+1<MAX3)
                    dp[i][j]=min(dp[i][j],dp[i][j+1]);
            }
        }

        int n=num.size();

        bool zero=false;
        int firstZero=n;

        for(int i=0;i<n;i++){
            if(num[i]=='0'){
                zero=true;
                firstZero=i;
                break;
            }
        }

        if(!zero){
            int a=need2,b=need3,c=need5,d=need7;

            for(char ch:num){
                int x=ch-'0';
                a=max(0,a-f2[x]);
                b=max(0,b-f3[x]);
                c=max(0,c-f5[x]);
                d=max(0,d-f7[x]);
            }

            if(a==0&&b==0&&c==0&&d==0)
                return num;
        }

        int limit=min(n-1,firstZero);

        int p2=0,p3=0,p5=0,p7=0;

        for(int i=0;i<limit;i++){
            int x=num[i]-'0';
            p2+=f2[x];
            p3+=f3[x];
            p5+=f5[x];
            p7+=f7[x];
        }

        for(int i=limit;i>=0;i--){

            for(int d=num[i]-'0'+1;d<=9;d++){

                int r2=max(0,need2-p2-f2[d]);
                int r3=max(0,need3-p3-f3[d]);
                int r5=max(0,need5-p5-f5[d]);
                int r7=max(0,need7-p7-f7[d]);

                int left=n-i-1;

                if(r5+r7+dp[r2][r3]>left)
                    continue;

                string ans=num.substr(0,i);
                ans.push_back(char('0'+d));

                while(left--){

                    for(int x=1;x<=9;x++){

                        int a=max(0,r2-f2[x]);
                        int b=max(0,r3-f3[x]);
                        int c=max(0,r5-f5[x]);
                        int e=max(0,r7-f7[x]);

                        if(c+e+dp[a][b]<=left){
                            ans.push_back(char('0'+x));
                            r2=a;
                            r3=b;
                            r5=c;
                            r7=e;
                            break;
                        }
                    }
                }

                return ans;
            }

            if(i){
                int x=num[i-1]-'0';
                p2-=f2[x];
                p3-=f3[x];
                p5-=f5[x];
                p7-=f7[x];
            }
        }

        int len=max(n+1,need5+need7+dp[need2][need3]);

        string ans;

        int r2=need2,r3=need3,r5=need5,r7=need7;

        for(int pos=0;pos<len;pos++){

            for(int x=1;x<=9;x++){

                int a=max(0,r2-f2[x]);
                int b=max(0,r3-f3[x]);
                int c=max(0,r5-f5[x]);
                int e=max(0,r7-f7[x]);

                if(c+e+dp[a][b]<=len-pos-1){
                    ans.push_back(char('0'+x));
                    r2=a;
                    r3=b;
                    r5=c;
                    r7=e;
                    break;
                }
            }
        }

        return ans;
    }
};