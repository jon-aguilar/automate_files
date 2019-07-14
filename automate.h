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


#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>
#include <vector>


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


// ---------  TODO: -----------------------------------------------------------------------------
//
//      Now that the hw_file_name vector is populated 
//      I need to download that file from brezeale website
//      which will require doing more libcurl 

//                          NOTE: 
//      when constructing directory names ( EX: hw01, hw02, ... )
//      remember the index of the element (vector) is basically telling you the number for 
//      the directory and since i know the directory name will start will hw_then_the_number

//      vector                      dir_names  (then convert num to string and pad zero )
//      i: 0    2320-hw01           hw01       i+1 to get number 
//      i: 1    2320-hw02           hw02       i+1 to get number
//      i: 2    2320-hw03           hw03       i+1 to get number

class automate
{
public:
    std::string html_to_string( std::string url );
    void load_html_vector( std::string html_str ); 
    void load_hw_vector( ); 
    void create_dir_n_pdf( std::string url );

     
private:
    std::vector <std::string> html_lines;

    // in the form 2320-hw01.pdf
    std::vector <std::string> hw_file_name;

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
    void download_pdf( std::string url, std::string file_to_get, std::string hw_dir );

};

#endif

