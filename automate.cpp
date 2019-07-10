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





#include "automate.h"

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream> 
#include <sys/stat.h> 
#include <sys/types.h> 

#include <stdio.h>


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






// will be used to convert the html file to string 
size_t automate::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


// TODO: change the function to have string param like below ------------------------------------
//     to make it work call c_str() where the URL goes to convert to C string 
//std::string automate::html_to_string( std::string html_file )
std::string automate::html_to_string( )
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if( curl ) 
    {
        curl_easy_setopt( curl, CURLOPT_URL, "http://omega.uta.edu/~darin/CSE2320/" );

        // html to string and store in readBuffer
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        //std::cout << readBuffer << std::endl;
    }

    return readBuffer;
}

// each element in the vector 
// will have line from html_str
void automate::load_html_vector( std::string html_str )
{ 
    std::stringstream the_stream( html_str ); 
    std::string token; 

    // tokenize by new line
    while( getline(the_stream, token, '\n') ) 
    { 
        html_lines.push_back( token ); 
    } 

    //// Printing the token vector 
    //for(int i = 0; i < html_lines.size(); i++) 
    //    std::cout << "i: " << i << " " << html_lines[i] << '\n'; 
} 


void automate::load_hw_vector( )
{
    // variable count is for testing only 
    // just checking the hw_files are being found
    int count = 0;

    // stop at size - 1 
    // to avoid going out of bounds 
    // in the vector 
    for( int i = 0; i < html_lines.size() - 1; i++ )
    {
        // if homework is found on current line and 
        // .pdf is found on the next line  
        // then parse the .pdf line and 
        // store the homework_filename 
        // in hw_file_name vector
        if( html_lines[i].find("homework") != std::string::npos  &&
            html_lines[i + 1].find(".pdf") != std::string::npos )
        {
            //std::cout << "i: " << i << " " << html_lines[i + 1] << std::endl; 
            
            std::stringstream file_name_line( html_lines[i + 1] );
            std::string token;
            
            // parse the html_file_name line 
            // and store file_name in vector
            while( getline(file_name_line, token, '\"') )
            {
                if( token.find(".pdf") != std::string::npos )
                {
                    //std::cout << "\ttoken: " << token << std::endl;
                    hw_file_name.push_back( token );
                }

            }
            count++;
        }
    }
    std::cout << "count = " << count << std::endl;

    //for( int i = 0; i < hw_file_name.size(); i++ )
    //{
    //    std::cout << "--i: " << i << " " << hw_file_name[i] << std::endl;
    //}
}

//                       TODO ------------------------------------------------------------------------

// fix for multiple directories
// look back at my notes for fixing the problem 

// if dir already exists then the mkdir will
// fail. the mikdir doc says that it will fail in that condition
void automate::create_dir()
{
    for( int i = 0; i < hw_file_name.size(); i++ )
    {
        //std::cout << "--i: " << i << " " << hw_file_name[i] << std::endl;

        // creating the directory name
        char dir_name[50];

        sprintf( dir_name, "hw%02d", i + 1 );
        //std::string dir_name = buffer;
        
        std::cout << "dir_name: " << dir_name << std::endl;


        // Creating directory 
        if ( mkdir( dir_name, 0777) == -1 ) 
            std::cerr << "Error creating directory\n"; 

        else
            std::cout << "Directory " <<  dir_name  << " created\n"; 
    }
}


