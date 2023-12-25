#include "random_word.hpp"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

using namespace nlohmann;

/* ~ à peu près la même logique que fwriten mais ici:
 * void *contents -> pointeur sur la donnée fournie
 * size_t size -> la taille de la donnée (vaut tojours 1)
 * size_t nmemb ->  la taille de la data
 *  void *userp -> user data
 */
static size_t WriteCallback (void* contents, size_t size, size_t nmemb, void* userp) {
  if (userp != nullptr) {
    ((std::string*)userp)->append ((char*)contents, size * nmemb);
    return size * nmemb;
  }
  return 0;
};

namespace random_word {
  void get_random_word (std::string& word) {
    CURL* curl          = nullptr;
    FILE* outfile       = nullptr;
    curl_slist* headers = nullptr;
    std::string readBuffer;

    headers = curl_slist_append (headers, "Accept: application/json");
    headers = curl_slist_append (headers, "Content-Type: application/json");
    headers = curl_slist_append (headers, "charset: utf-8");

    curl = curl_easy_init ();
    try {
      if (curl) {
        CURLcode res;

        curl_easy_setopt (curl, CURLOPT_URL, "https://trouve-mot.fr/api/random");
        curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt (curl, CURLOPT_TIMEOUT, 10L);
        curl_easy_setopt (curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt (curl, CURLOPT_USERAGENT, "libcrp/0.1");

        res = curl_easy_perform (curl);
        curl_easy_cleanup (curl);
        if (CURLE_OK == res) {
          json j_complete = json::parse (readBuffer);
          readBuffer.clear ();
          word = j_complete.at (0).at ("name");
        } else {
          throw (1);
        }
      }
    } catch (int errVal) {
      std::cout << "Error " << errVal << "request limit reached";
      exit (errVal);
    }
  };
} // namespace random_word