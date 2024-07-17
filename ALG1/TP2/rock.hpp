#ifndef ROCK_H
#define ROCK_H

#include <vector>

typedef struct{
    int left, right;
    double sum;
} ShowList;

class Lineup 
{
    public:
        Lineup(int n);
        void AddRating(std::vector<double> rating);
        ShowList ChooseShows();

    private:
        std::vector<double> ratings;
        int NumShows;

        ShowList MaxRatings(int l, int r);
        ShowList MaxCrossingRates(int l, int r);
};

#endif