#include "ApplicationData.h"
#include "questions3_aux.h"
#include <string>

int questions3(ApplicationData& app_data) {
  int value = 0;
  int fav_int = app_data.getInteger("Favorite integer? ");
  double fav_double = app_data.getDouble("Favorite double? ");
  std::string fav_word = app_data.getString("Favorite word? ");
  value = fav_int;
  for(int i = 1; i <= fav_int; i++) {
    app_data.getOutputStream() << i << " " 
                               << fav_double << " "
                               << fav_word << std::endl;
  }
  return value;
}
