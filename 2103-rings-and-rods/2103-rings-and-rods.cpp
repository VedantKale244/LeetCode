class Solution {
public:
    int countPoints(string rings) {
        vector<set<char>> rods(10);

        for (int i = 0; i < rings.size(); i += 2) {
            char color = rings[i];
            int rod = rings[i + 1] - '0';
            rods[rod].insert(color);
        }

        int count = 0;

        for (int i = 0; i < 10; i++) {
            if (rods[i].size() == 3) {
                count++;
            }
        }

        return count;
    }
};