#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main() {
    string S;
    cin >> S;

    string T;
    for (char c: S)
        T += string(1, '|') + c;
    T += "|";

    vector<int> radii(T.size());
    for (int center = 0, radius = 0; center < T.size(); ) {
        while (center - (radius+1) >= 0 && center + (radius+1) < T.size() && T[center - (radius+1)] == T[center + (radius+1)])
            ++radius;

        radii[center] = radius;

        int oldCenter = center;
        int oldRadius = radius;
        ++center;
        while (center < T.size() && center <= oldCenter + oldRadius) {
            assert(center < T.size());
            int mirroredCenter = oldCenter - (center - oldCenter);
            int maxRadius = oldCenter + oldRadius - center;

            if (radii[mirroredCenter] == maxRadius) {
                radius = maxRadius;
                break;
            }

            if (radii[mirroredCenter] < maxRadius) {
                radii[center] = radii[mirroredCenter];
                ++center;
                radius = 0;
            }
            else {
                radii[center] = maxRadius;
                ++center;
                radius = 0;
            }
        }
    }

    pair<int, int> res{ -1, -1 };
    for (int i = 0; i < radii.size(); ++i)
        res = max(res, make_pair(radii[i], i));
    cout << res.first << ' ' << res.second << endl;

    string R;
    for (int i = -res.first; i <= res.first; ++i) {
        int j = res.second + i;

        if (T[j] != '|')
            R += T[j];
    }

    cout << R << endl;
}
