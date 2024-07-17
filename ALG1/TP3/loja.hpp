#include<vector>

class Store
{
    public:
        Store(int Rolls);
        void ReadValues();
        int MaxLengthShelf();

    private:
        std::vector<int> values;
        int NumRolls;
};