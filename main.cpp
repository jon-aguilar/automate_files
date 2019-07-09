
#include <iostream>
#include <string>

#include "automate.h"

int main( void )
{
    automate a;

    std::cout << "in the main right now\n";
        //curl_easy_setopt(curl, CURLOPT_URL, "http://omega.uta.edu/~darin/CSE2320/");
    
    //std::string html_str = a.html_to_string( "http://omega.uta.edu/~darin/CSE2320/" );
     
    std::string html_str = a.html_to_string( );
    std::cout << html_str << std::endl;

    return 0;
}

