#include < iostream > 
#include < fstream > 
#include < vector > 
#include < string > 
#include < algorithm > 
#include < map > 
#include < stdio.h > 
#include < ctype.h > 
#include < cstring >
using namespace std;
std::map < string, int > mymap;
std::map < string, int > myresult;
bool inference_engine(string temp, string kb[10000], int kbn) {

  
  if (temp.find_first_not_of(' ') == temp.npos)
    return true;

  kbn++;
  kb[kbn] = temp;

  static int tempcount = 0;
  tempcount++;

  std::pair < std::map < string, int > ::iterator, bool > ret;
  ret = mymap.insert(std::pair < string, int > (temp, 1));
  if (ret.second == false)
    return false;

  if (kbn > 20000)
    return false;

  
  char * temp_ptr = new char[temp.length() + 1];

  std::strcpy(temp_ptr, temp.c_str());

  char * ptr_to_temp = std::strtok(temp_ptr, " |");

  string temp_tokens[50];
  int k = 0;
  while (ptr_to_temp != 0) {

    temp_tokens[k] = ptr_to_temp;

    k++;
    ptr_to_temp = std::strtok(NULL, " |");

  }

  //till here the temp query has been tokenised and stored in temp_tokens
  k--;

  for (int l = 0; l <= k; l++) {
    bool sol = true;

    // here the alphabet of each of the temp_tokens is searched in kb 
    
    string copy_temp;
    copy_temp = temp_tokens[l];
    
    string cp, c;
    

    std::size_t p = temp.find("(");
    copy_temp = copy_temp.substr(0, p);

    if (copy_temp[0] == '~') {
      c.append(" ");
      copy_temp.erase(copy_temp.begin());
      c.append(copy_temp);
    } else {
      c.append("~");
      c.append(copy_temp);
    }

    
    for (int i = 1; i <= kbn; i++) {

      

      sol = true;

      for (string::size_type t = 0;
        (t = kb[i].find(c, t)) != string::npos;) //here the literal from the kb line is found matching with some literal in query
      {
        sol = true;

        
        unsigned brackets_temp_open = temp_tokens[l].find('('); //extracting the contents of temp (i.e, one literal in query ) within the brackets
        unsigned brackets_temp_close = temp_tokens[l].find(')');
        string contents_inside_brackets = temp_tokens[l].substr(brackets_temp_open + 1, brackets_temp_close - brackets_temp_open - 1);
        
        char * cstr_inside_contents = new char[contents_inside_brackets.length() + 1];

        std::strcpy(cstr_inside_contents, contents_inside_brackets.c_str());

        char * p_to_contents_inside_brackets = std::strtok(cstr_inside_contents, " ,");
        string contains_parameter_variables[10];
        int n = 0;
        while (p_to_contents_inside_brackets != 0)

        {
          contains_parameter_variables[n] = p_to_contents_inside_brackets;
          
          n++;
          p_to_contents_inside_brackets = std::strtok(NULL, " ,");
        }

        //this kb has the matching term 
        //now tokenising this kb 
        std::string str3 = kb[i].substr(t);
        
        char * cstrr = new char[str3.length() + 1];
        std::strcpy(cstrr, str3.c_str());
        char * kb_tokenr = std::strtok(cstrr, " |");
        string temp_kb_token;
        while (kb_tokenr != 0) {

          temp_kb_token = kb_tokenr;
          
          if (temp_kb_token[0] != ' ')
            temp_kb_token.insert(0, " ");
          
          std::size_t posf = temp_kb_token.find(c);
          if (posf != std::string::npos)
            break;

          kb_tokenr = std::strtok(NULL, "|");
        }
        

        unsigned brackets_kb_open = temp_kb_token.find('(');
        unsigned brackets_kb_close = temp_kb_token.find(')');
        string contents_inside_brackets_kb = temp_kb_token.substr(brackets_kb_open + 1, brackets_kb_close - brackets_kb_open - 1);

        char * cstr_inside_contents_kb = new char[contents_inside_brackets_kb.length() + 1];

        std::strcpy(cstr_inside_contents_kb, contents_inside_brackets_kb.c_str());

        char * p_to_contents_inside_brackets_kb = std::strtok(cstr_inside_contents_kb, " ,");
        string contains_parameter_variables_kb[10];
        int nkb = 0;
        while (p_to_contents_inside_brackets_kb != 0) {
          contains_parameter_variables_kb[nkb] = p_to_contents_inside_brackets_kb;
          
          nkb++;
          p_to_contents_inside_brackets_kb = std::strtok(NULL, " ,");

        }
        nkb--;
        string unification_temp_kb;
        unification_temp_kb.clear();
        unification_temp_kb.append(temp);
        unification_temp_kb.erase(unification_temp_kb.end() - 1);
        unification_temp_kb.append(kb[i]);

        

        int flag = 0;
        for (int m = 0; m <= nkb; m++)
          if (isupper(contains_parameter_variables_kb[m][0]) and isupper(contains_parameter_variables[m][0]) and contains_parameter_variables_kb[m].compare(contains_parameter_variables[m]) == 0)
            flag++;

        

        if (flag == nkb + 1) {
          
          sol = true;
          c = temp_kb_token;
        }

        for (int m = 0; m <= nkb; m++) {

          if (islower(contains_parameter_variables_kb[m][0]) and isupper(contains_parameter_variables[m][0]))

          {
            for (string::size_type o = 0;
              (o = unification_temp_kb.find(contains_parameter_variables_kb[m], o)) != string::npos;) { 
              if ((unification_temp_kb[o + 1] == ')'
                  or unification_temp_kb[o + 1] == ',') and(unification_temp_kb[o - 1] == '('
                  or unification_temp_kb[o - 1] == ',')) {

                unification_temp_kb.replace(o, contains_parameter_variables_kb[m].length(), contains_parameter_variables[m]);
                o += contains_parameter_variables[m].length();

                int yes = 0;
                for (int r = 0; r <= nkb; r++) {
                  if (contains_parameter_variables[r] == contains_parameter_variables_kb[m]) {
                    contains_parameter_variables[r] = contains_parameter_variables[m];
                    
                    yes = 1;
                  }

                }

                if (yes == 1) {
                  m = -1;
                  break;
                }

              } else o++;
            }

            
          } else if (isupper(contains_parameter_variables_kb[m][0]) and islower(contains_parameter_variables[m][0])) //find and replace all variable occurances with paramater

          {
            // temp.erase (temp_tokens[l]);  //cancel out literals
            for (string::size_type o = 0;
              (o = unification_temp_kb.find(contains_parameter_variables[m], o)) != string::npos;) {
              
              if ((unification_temp_kb[o + 1] == ')'
                  or unification_temp_kb[o + 1] == ',') and(unification_temp_kb[o - 1] == '('
                  or unification_temp_kb[o - 1] == ',')) {
                unification_temp_kb.replace(o, contains_parameter_variables[m].length(), contains_parameter_variables_kb[m]);
                o += contains_parameter_variables_kb[m].length();
                
                int yes = 0;
                for (int r = 0; r <= nkb; r++) {
                  if (contains_parameter_variables_kb[r] == contains_parameter_variables[m]) {
                    contains_parameter_variables_kb[r] = contains_parameter_variables_kb[m];

                    yes = 1;
                  }

                }

                if (yes == 1) {
                  m = -1;
                  break;
                }

              } else o++;

            }

                

          } else if (isupper(contains_parameter_variables_kb[m][0]) and isupper(contains_parameter_variables[m][0]) and contains_parameter_variables_kb[m].compare(contains_parameter_variables[m]) != 0) {
            sol = false;
            break;
          }
        }
        for (int m = 0; m <= nkb; m++) {

          if (islower(contains_parameter_variables_kb[m][0]) and islower(contains_parameter_variables[m][0]) and contains_parameter_variables_kb[m].compare(contains_parameter_variables[m]) != 0) {
            for (string::size_type o = 0;
              (o = unification_temp_kb.find(contains_parameter_variables_kb[m], o)) != string::npos;) {
              if ((unification_temp_kb[o + 1] == ')'
                  or unification_temp_kb[o + 1] == ',') and(unification_temp_kb[o - 1] == '('
                  or unification_temp_kb[o - 1] == ',')) {

                unification_temp_kb.replace(o, contains_parameter_variables_kb[m].length(), contains_parameter_variables[m]);
                o += contains_parameter_variables[m].length();
                
              } else o++;
            }

          }

        }

           
        if (sol) {
          

          std::size_t pos_kb_term = unification_temp_kb.find("|", unification_temp_kb.find(c) + 1, 1);

          unification_temp_kb.erase(unification_temp_kb.find(c), (pos_kb_term - unification_temp_kb.find(c) + 1));
          
          string cc = c;
          if (cc[1] == '~')
            cc.erase(cc.begin());
          
          if (cc[0] == '~')
            cc[0] = ' ';
          else
            cc[0] = '~';
          
          pos_kb_term = unification_temp_kb.find("|", unification_temp_kb.find(cc) + 1, 1);
          
          unification_temp_kb.erase(unification_temp_kb.find(cc), (pos_kb_term - unification_temp_kb.find(cc) + 2));
          
          for (string::size_type o = 0;
            (o = unification_temp_kb.find("|", o)) != string::npos;) {
            if (unification_temp_kb[o - 1] != ' ')
              unification_temp_kb.insert(o - 1, " ");
            if (unification_temp_kb[o + 1] != ' ')
              unification_temp_kb.insert(o + 1, " ");
            if (unification_temp_kb[o + 1] == ' '
              and unification_temp_kb[o + 2] == ' ')
              unification_temp_kb.erase(o + 2, 1);
            if (unification_temp_kb[o - 1] == ' '
              and unification_temp_kb[o - 2] == ' ')
              unification_temp_kb.erase(o - 2, 1);
            o++;
          }
          if (unification_temp_kb[0] != ' ')
            unification_temp_kb.insert(0, " ");

          
          string copy_unification_temp_kb = unification_temp_kb;
          myresult.clear();
          char * cstr_result = new char[copy_unification_temp_kb.length() + 1];

          std::strcpy(cstr_result, copy_unification_temp_kb.c_str());

          char * p_to_result = std::strtok(cstr_result, " (");
          string result_tok;
          std::size_t pos_of_or = 0;

          while (p_to_result != 0)

          {
            result_tok = p_to_result;
            

            std::pair < std::map < string, int > ::iterator, bool > res;
            res = myresult.insert(std::pair < string, int > (result_tok, 1));
            if (res.second == false)
              return false;

            pos_of_or = copy_unification_temp_kb.find("|", pos_of_or + 1, 1);

            char * p_cont = & copy_unification_temp_kb[pos_of_or + 1];
            p_to_result = std::strtok(p_cont, " (");

          }



          if (inference_engine(unification_temp_kb, kb, kbn))
            return true;

        } 
        t++;
      }

      
    }

  }

  //control came here means there is no match found so terminate search    

  return false;

}

int main() {

  int q, kbn;

  string query[100];

  string kb[1000];

  char t[50];

  
  ifstream myReadFile;

  ofstream myWriteFile;

  myReadFile.open("input.txt");

  myWriteFile.open("output.txt");

  myReadFile >> q;

  for (int i = 0; i < q; i++)

  {

    myReadFile >> query[i];

    cout << "\n";

  }

  myReadFile >> kbn;

  for (int i = 0; i <= kbn; i++)

  {

    getline(myReadFile, kb[i], '\n');
    kb[i].append(" | ");

    cout << "\n";

  }

  for (int j = 0; j <= kbn; j++)
    kb[j].insert(0, " ");

  for (int i = 0; i < q; i++)

  {

    bool ans;

    

    string temp;
    string tempst;
    tempst = query[i];
    temp.insert(0, " ");
    if (tempst[0] != '~') {
      temp.append("~");
      temp.append(tempst);
    } else {
      temp.append(tempst);
      temp.erase(temp.begin() + 1);
    }

    temp.append(" | ");
    
    ans = inference_engine(temp, kb, kbn);

    if (ans)

      myWriteFile << "TRUE\n";

    else

      myWriteFile << "FALSE\n";

  }

  myReadFile.close();

  myWriteFile.close();

  return 0;

}