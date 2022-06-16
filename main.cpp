#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
int main(int argc, char *argv[]) {
    int K, jobs, tmp;
    scanf("%d", &K);
    scanf("%d", &jobs);

    vector<int> job;
    vector<int> work(K);
    for (int i = 0; i < jobs; i++) {
        scanf("%d", &tmp);
        job.push_back(tmp);
    }

    sort(job.begin(), job.end());

    for (int i = 0; i < K; i++) {
        work[i] = 0;
    }

    for (int i = jobs - 1; i >= 0; i--) {
        int who = 0;
        for (int j = 0; j < work.size(); j++) {
            if (work[j] <= work[who]) {
                who = j;  //这小子很闲啊
            }
        }
        work[who] += job[i];
    }
    int what = -1;
    for (int j = 0; j < work.size(); j++) {
        if (work[j] > what) {
            what = work[j];  //这小子很闲啊
        }
    }
    printf("%d", what);

    return 0;
}