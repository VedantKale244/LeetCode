class Solution {
public:
    int majorityElement(vector<int>& arr) {
        int n = arr.size();
        int candidate = 0;
        int cnt = 0;

        for(int i = 0; i < n; i++){
            if(cnt == 0){
                candidate = arr[i];
            }

            if(arr[i] == candidate){
                cnt++;
            }

            else{
                cnt--;
            }
        }
        return candidate;
    }
};