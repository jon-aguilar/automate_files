// 
// MIT License
// 
// Copyright (c) 2019 Jonathan Aguilar
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.





#include <iostream>
#include <string>

#include "automate.h"


/*
    -------------------- JON NOTES FOR PROJECT -----------------
    1.  save the variable res into a string 
        then inside the string you will parse 
        probably by newlines save the results in 
        a vector

    2.  filter out the parsed-vector and look for 
        pdf file names. Save the pdf file names in
        an other vector.

    3.  next save the pdf file names in a file.txt
        this will help me avoid creating multiple directory 
        names.  the directory names will be based on the pdf files that were found
        and since the brezeale_html file will be opened multiple times i 
        dont want to overwrite the existing directories that have been created already
        since steps 1 and 2 not know what directories have been created.


*/


int main( void )
{
    automate a;

    std::cout << "in the main right now\n";
        //curl_easy_setopt(curl, CURLOPT_URL, "http://omega.uta.edu/~darin/CSE2320/");
    
    //std::string html_str = a.html_to_string( "http://omega.uta.edu/~darin/CSE2320/" );
     
    std::string url = "http://omega.uta.edu/~darin/CSE2320/";

    std::string html_str = a.html_to_string( url );
    //std::cout << html_str << std::endl;
    a.load_html_vector( html_str );
    a.load_hw_vector( );
    a.create_dir( );
    a.download_pdf( url );


    return 0;
}

