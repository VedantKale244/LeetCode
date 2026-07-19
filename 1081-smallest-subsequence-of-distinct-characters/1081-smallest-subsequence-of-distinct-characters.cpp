class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> freq(26, 0);
        vector<bool> visited(26, false);

        for (char ch : s)
            freq[ch - 'a']++;

        string stack = "";

        for (char ch : s) {
            freq[ch - 'a']--;

            if (visited[ch - 'a'])
                continue;

            while (!stack.empty() &&
                   stack.back() > ch &&
                   freq[stack.back() - 'a'] > 0) {

                visited[stack.back() - 'a'] = false;
                stack.pop_back();
            }

            stack.push_back(ch);
            visited[ch - 'a'] = true;
        }

        return stack;
    }
};