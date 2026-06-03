class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime,
                           vector<int>& landDuration,
                           vector<int>& waterStartTime,
                           vector<int>& waterDuration) {

        long long ans = LLONG_MAX;

        int n = landStartTime.size();
        int m = waterStartTime.size();

        vector<pair<long long,long long>> water(m);
        for(int i=0;i<m;i++)
            water[i] = {waterStartTime[i], waterDuration[i]};

        sort(water.begin(), water.end());

        vector<long long> prefDur(m);
        vector<long long> suffFinish(m);

        prefDur[0] = water[0].second;
        for(int i=1;i<m;i++)
            prefDur[i] = min(prefDur[i-1], water[i].second);

        suffFinish[m-1] = water[m-1].first + water[m-1].second;
        for(int i=m-2;i>=0;i--)
            suffFinish[i] =
                min(suffFinish[i+1],
                    water[i].first + water[i].second);

        vector<long long> waterStarts(m);
        for(int i=0;i<m;i++)
            waterStarts[i] = water[i].first;

        for(int i=0;i<n;i++) {

            long long F =
                (long long)landStartTime[i] + landDuration[i];

            int pos =
                upper_bound(waterStarts.begin(),
                            waterStarts.end(), F)
                - waterStarts.begin();

            if(pos > 0)
                ans = min(ans,
                          F + prefDur[pos-1]);

            if(pos < m)
                ans = min(ans,
                          suffFinish[pos]);
        }

        vector<pair<long long,long long>> land(n);
        for(int i=0;i<n;i++)
            land[i] = {landStartTime[i], landDuration[i]};

        sort(land.begin(), land.end());

        vector<long long> prefLandDur(n);
        vector<long long> suffLandFinish(n);

        prefLandDur[0] = land[0].second;
        for(int i=1;i<n;i++)
            prefLandDur[i] =
                min(prefLandDur[i-1],
                    land[i].second);

        suffLandFinish[n-1] =
            land[n-1].first + land[n-1].second;

        for(int i=n-2;i>=0;i--)
            suffLandFinish[i] =
                min(suffLandFinish[i+1],
                    land[i].first + land[i].second);

        vector<long long> landStarts(n);
        for(int i=0;i<n;i++)
            landStarts[i] = land[i].first;

        for(int j=0;j<m;j++) {

            long long F =
                (long long)waterStartTime[j] + waterDuration[j];

            int pos =
                upper_bound(landStarts.begin(),
                            landStarts.end(), F)
                - landStarts.begin();

            if(pos > 0)
                ans = min(ans,
                          F + prefLandDur[pos-1]);

            if(pos < n)
                ans = min(ans,
                          suffLandFinish[pos]);
        }

        return (int)ans;
    }
};