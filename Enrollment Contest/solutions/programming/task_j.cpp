#include <algorithm>
#include <iostream>
#include <string>

std::string findSum(std::string str1, std::string str2) 
{ 
    // Before proceeding further, make sure length 
    // of str2 is larger. 
    if (str1.length() > str2.length()) 
        swap(str1, str2); 
  
    // Take an empty string for storing result 
    std::string str = ""; 
  
    // Calculate length of both string 
    int n1 = str1.length(), n2 = str2.length(); 
  
    // Reverse both of strings 
    std::reverse(str1.begin(), str1.end()); 
    std::reverse(str2.begin(), str2.end()); 
  
    int carry = 0; 
    for (int i = 0; i < n1; ++i) 
    { 
        // Do school mathematics, compute sum of 
        // current digits and carry 
        int sum = ((str1[i] - '0') + (str2[i] - '0') + carry); 
        str.push_back(sum % 10 + '0'); 
  
        // Calculate carry for next step 
        carry = sum / 10; 
    } 
  
    // Add remaining digits of larger number 
    for (int i = n1; i < n2; ++i) 
    { 
        int sum = ((str2[i] - '0') + carry); 
        str.push_back(sum % 10 + '0'); 
        carry = sum / 10; 
    } 
  
    // Add remaining carry 
    if (carry) 
        str.push_back(carry + '0'); 
  
    // reverse resultant string 
    std::reverse(str.begin(), str.end()); 
  
    return str; 
} 

void check(const std::string &s) {
    std::size_t s_len = s.length();
    std::string a, b, c;
    for (int i = 1; i <= s_len / 2; ++i) {
        a = s.substr(0, i);
            
        //case i <= j:
        b = s.substr(i, (s_len - i) / 2);
        c = s.substr(i + (s_len - i) / 2);

        // chech a + b = c
        if (c == findSum(a, b)) {
            std::cout << a << "+" << b << "=" << c << std::endl;
            return;
        }

        //case i > j:
        //      case size(c) = i:
        
        auto start_c = s_len - i; 
        b = s.substr(i, start_c - i);
        c = s.substr(start_c);

        if (c == findSum(a, b)) {
            std::cout << a << "+" << b << "=" << c << std::endl;
            return;
        }

        //      case size(c) = i + 1:

        start_c = s_len - i - 1; 
        b = s.substr(i, start_c - i);
        c = s.substr(start_c);

        if (c == findSum(a, b)) {
            std::cout << a << "+" << b << "=" << c << std::endl;
            return;
        }
    }

    throw std::logic_error("One example should be found");
}

int main(int argc, char const *argv[])
{
    std::string abc;
    std::cin >> abc;
    check(abc);
    return 0;
}
