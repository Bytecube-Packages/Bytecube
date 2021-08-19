#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

string escape(string value) {
  stringstream ss;
  for (char c : value) {
    switch (c) {
      case '"':
        ss << "\\\"";
        break;
      case '\\':
        ss << "\\\\";
        break;
      default:
        ss << c;
        break;
    }
  }

  return ss.str();
}
string un_escape(string value) {
  stringstream ss;
  for (char c : value) {
    if (c == '\\') continue;
    ss << c;
  }

  return ss.str();
}

const string WHITESPACE = " \n\r\t\f\v";
string trim(const string &s) {
  size_t start = s.find_first_not_of(WHITESPACE);
  size_t end = s.find_last_not_of(WHITESPACE);

  if (start == string::npos) return "";
  if (end == string::npos) return "";
  return s.substr(start, end - start + 1);
}

namespace Util {
  class Json {
    public:
      static string stringify(Json object) {
        stringstream ss;
        
        if (object.type == "null") ss << "null";
        if (object.type == "boolean") ss << (object.boolean ? "true" : "false");
        if (object.type == "number") ss << object.integer;
        if (object.type == "string") ss << '"' << escape(object.str) << '"';

        if (object.type == "array") {
          ss << "[";
          for (int i = 0; i < object.array.size(); i++) {
            if (i > 0) ss << ",";
            ss << stringify(object.array[i]);
          }
          ss << "]";
        }
        if (object.type == "object") {
          ss << "{";
          for (map<string, Json>::iterator it = object.object.begin(); it != object.object.end(); it++) {
            if (it != object.object.begin()) ss << ",";
            ss << '"' << escape(it->first) << "\":" << stringify(it->second);
          }
          ss << "}";
        }

        return ss.str();
      }
      static Json parse(string str) {
        Json json;
        if (str.empty()) return json;
        str = trim(str);

        int array_level = 0;
        int object_level = 0;
        bool inside_string = false;

        if (str[0] == '[') {
          json.type = "array";
          int last = 1;
          for (int i = 1; i < str.size() - 1; i++) {
            if (str[i] == '\\') {
              i++;
              continue;
            } 
            if (str[i] == '"') inside_string = !inside_string;

            if (inside_string) continue;
            if (str[i] == '{') object_level++;
            if (str[i] == '}') object_level--;
            if (str[i] == '[') array_level++;
            if (str[i] == ']') array_level--;

            if (str[i] == ',' && object_level == 0 && array_level == 0) {
              json.array.push_back(parse(str.substr(last, i - last - 1)));
              last = i + 1;
            }
          }
          json.array.push_back(parse(str.substr(last)));
        }
        if (str[0] == '{') {
          json.type = "object";
          string key = "";

          int last = 1;
          for (int i = 1; i < str.size() - 1; i++) {
            if (str[i] == '\\') {
              i++;
              continue;
            } 
            if (str[i] == '"') inside_string = !inside_string;

            if (inside_string) continue;
            if (str[i] == '{') object_level++;
            if (str[i] == '}') object_level--;
            if (str[i] == '[') array_level++;
            if (str[i] == ']') array_level--;

            if (str[i] == ':' && object_level == 0 && array_level == 0) {
              key = parse(str.substr(last, i - last)).getValue("");
              last = i + 1;
            }

            if (str[i] == ',' && object_level == 0 && array_level == 0) {
              json.object[key] = parse(str.substr(last, i - last));
              last = i + 1;
              key = "";
            }
          }
          json.object[key] = parse(str.substr(last, str.size() - last - 1));
        }
        if (str.substr(0, 4) == "true") {
          json.type = "boolean";
          json.boolean = true;
        }
        if (str.substr(0, 5) == "false") {
          json.type = "boolean";
          json.boolean = false;
        }
        if (str.substr(0, 4) == "null") {
          json.type = "null";
        }
        if (str[0] == '-' || isdigit(str[0])) {
          json.type = "number";
          json.integer = stoi(str);
        }
        if (str[0] == '"') {
          json.type = "string";
          json.str = un_escape(str.substr(1, str.size() - 2));
        }

        return json;
      }

      string stringify() {
        return stringify(*this);
      }

      string type;
      Json() {
        type = "null";
      }
      Json(string value) {
        this->setValue(value);
      }
      Json(const char* value) {
        this->setValue(value);
      }
      Json(bool value) {
        this->setValue(value);
      }
      Json(int value) {
        this->setValue(value);
      }
      Json(vector<Json> value) {
        this->setValue(value);
      }
      Json(map<string, Json> value) {
        this->setValue(value);
      }

      string getValue(string backup) {
        if (type != "string") return backup;
        return str;
      }
      const char* getValue(const char* backup) {
        if (type != "string") return backup;
        return str.c_str();
      }
      bool getValue(bool backup) {
        if (type != "boolean") return backup;
        return boolean;
      }
      int getValue(int backup) {
        if (type != "integer") return backup;
        return integer;
      }
      vector<Json> getArray() {
        if (type != "array") return vector<Json>();
        return array;
      }
      map<string, Json> getMap() {
        if (type != "object") return map<string, Json>();
        return object;
      }

      void setValue(string value) {
        type = "string";
        str = value;
      }
      void setValue(const char* value) {
        type = "string";
        str = value;
      }
      void setValue(bool value) {
        type = "boolean";
        boolean = value;
      }
      void setValue(int value) {        
        type = "integer";
        integer = value;
      }
      void setValue(vector<Json> value) {
        type = "array";
        array = value;
      }
      void setValue(map<string, Json> value) {
        type = "object";
        object = value;
      }
    private:
      string str;
      bool boolean;
      int integer;

      vector<Json> array;
      map<string, Json> object;
  };
}
