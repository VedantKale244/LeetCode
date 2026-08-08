class MyCalendarThree {
private:
    map<int, int> diff;

public:
    MyCalendarThree() {
    }

    int book(int startTime, int endTime) {
        diff[startTime]++;
        diff[endTime]--;

        int active = 0;
        int maximum = 0;

        for (auto &[time, change] : diff) {
            active += change;
            maximum = max(maximum, active);
        }

        return maximum;
    }
};