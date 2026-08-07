class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

        unordered_set<string> st(wordList.begin(), wordList.end());

        if (!st.count(endWord))
            return 0;

        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        while (!q.empty()) {
            auto [word, level] = q.front();
            q.pop();

            if (word == endWord)
                return level;

            for (int i = 0; i < word.size(); i++) {
                char original = word[i];

                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;

                    if (st.count(word)) {
                        q.push({word, level + 1});
                        st.erase(word);
                    }
                }

                word[i] = original;
            }
        }

        return 0;
    }
};