#include "rock.hpp"
#include <algorithm>
#include <iostream>

// A very big integer value used as a limit
const int INF = 0x3f3f3f3f;

Lineup::Lineup(int n)
{
    NumShows = n;
    ratings.resize(n, 0);
}

void Lineup::AddRating(std::vector<double> rating)
{
    for(int i = 0; i < NumShows; i++)
        ratings[i] += rating[i];
}

ShowList Lineup::ChooseShows()
// Finds out which shows the group must watch
{
    return MaxRatings(0, NumShows-1);
}

ShowList Lineup::MaxCrossingRates(int l, int r)
// Finds the list with the largest sum that contains the middle element
{
    int m = (l + r)/2;
    double LeftSum = -INF, RightSum = -INF;
    int LeftIndex = m, RightIndex = m;

    double sum = 0;

    for(int i = m; i >= l; i--){
        sum += ratings[i];

        if(sum >= LeftSum){
            LeftSum = sum;
            LeftIndex = i;
        }
    }

    sum = 0;

    for(int i = m; i <= r; i++){
        sum += ratings[i];

        if(sum >= RightSum){
            RightSum = sum;
            RightIndex = i;
        }
    }

    double MaxSum = std::max({LeftSum + RightSum - ratings[m], LeftSum, RightSum});

    if(MaxSum == LeftSum + RightSum - ratings[m])
        return {LeftIndex, RightIndex, MaxSum};

    else if(MaxSum == LeftSum)
        return {LeftIndex, m, MaxSum};
    
    else
        return {m, RightIndex, MaxSum};
}

ShowList Lineup::MaxRatings(int l, int r)
// Finds the list with the largest rating sum within the range [l, r]
{
    if(l > r)
        return {l, r, -INF};

    if(l == r)
        return {l, r, ratings[l]};

    int m = (l + r)/2;

    ShowList LeftRatings = MaxRatings(l, m-1);
    ShowList RightRatings = MaxRatings(m+1, r);
    ShowList CrossingRatings = MaxCrossingRates(l, r);

    double MaxSum = std::max({LeftRatings.sum, RightRatings.sum, CrossingRatings.sum});

    if(LeftRatings.sum == MaxSum)
        return LeftRatings;

    else if(RightRatings.sum == MaxSum)
        return RightRatings;
    
    else
        return CrossingRatings;
}