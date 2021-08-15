#include <sstream>
#include <string>
#include <map>

#include "url_encode.cpp"

using namespace std;

namespace Util{
  string to_http(map<string, string> object, bool encode = true) {
    stringstream ss;
    for (map<string, string>::iterator it = object.begin(); it != object.end(); ++it) {
      string seperator = it == object.begin() ? "?" : "&";

      string key = it->first;
      string value = it->second;

      if (encode) value = url_encode(value);
      ss << seperator << key << "=" << value;
    }

    return ss.str();
  }
}
