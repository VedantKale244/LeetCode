class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int rows = mat.size();
        int cols = mat[0].size();

        k %= cols;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int originalCol;

                if (i % 2 == 0) {
                    originalCol = (j + k) % cols;          // left shift
                } else {
                    originalCol = (j - k + cols) % cols;   // right shift
                }

                if (mat[i][j] != mat[i][originalCol]) {
                    return false;
                }
            }
        }

        return true;
    }
};