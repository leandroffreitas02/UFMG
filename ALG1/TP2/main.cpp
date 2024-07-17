#include "rock.hpp"
#include <iostream>

int main() {

  while(1){
    int A, S;
    std::cin >> A >> S;

    if(!A && !S)
      return 0;

    Lineup shows(S);

    for(int i = 0; i < A; i++){
      std::vector<double> rating(S);

      for(int j = 0; j < S; j++)
        std::cin >> rating[j];
      
      shows.AddRating(rating);
    }

    ShowList ans = shows.ChooseShows();

    std::cout << ans.left + 1 << ' ' << ans.right + 1 << std::endl;
  }
}