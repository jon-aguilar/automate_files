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


// will be used to convert the html file to string 
size_t automate::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


// TODO: change the function to have string param like below ------------------------------------
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
void automate::load_vector( std::string html_str )
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


void automate::find_hw_pdf( )
{
    int count = 0;

    // stop size - 1 
    // to avoid going out of bounds 
    // in the vector 
    for( int i = 0; i < html_lines.size() - 1; i++ )
    {
        //std::string line = html_lines[i];     

        if( html_lines[i].find("homework") != std::string::npos  &&
            html_lines[i + 1].find(".pdf") != std::string::npos )
        {
            std::cout << "i: " << i << " " << html_lines[i + 1] << std::endl; 
            count++;
        }

        //std::stringstream the_stream( line ); 
        //std::string token;

        //// tokenize the current line by a space, 
        //// then find the word homework
        //// if homework is found then the 
        //// next line should have the pdf 
        //// and the pdf will be stored in the vector hw_pdf
        //while( getline( the_stream, token, ' ') )
        //{
        //    if( token == "homework" )  
        //    {
        //        //std::cout << "i: " << i << " " << html_lines[i + 1] << std::endl; 
        //        
        //        if( html_lines[i + 1].find(".pdf") != std::string::npos )
        //        {
        //            std::cout << "i: " << i << " " << html_lines[i + 1] << std::endl; 
        //            count++;
        //        }


        //    }
        //}
    }
    std::cout << "count = " << count << std::endl;
}


// function below works  but is longer than it needs to be 
// so instead tokenizing each line. which is not needed yet
// just check each line and use string::find()
// to see if it matches homework and .pdf


// void automate::find_hw_pdf( )
// {
//     int count = 0;
// 
//     // stop size - 1 
//     // to avoid going out of bounds 
//     // in the vector 
//     for( int i = 0; i < html_lines.size() - 1; i++ )
//     {
//         std::string line = html_lines[i];     
// 
//         std::stringstream the_stream( line ); 
//         std::string token;
// 
//         // tokenize the current line by a space, 
//         // then find the word homework
//         // if homework is found then the 
//         // next line should have the pdf 
//         // and the pdf will be stored in the vector hw_pdf
//         while( getline( the_stream, token, ' ') )
//         {
//             if( token == "homework" )  
//             {
//                 //std::cout << "i: " << i << " " << html_lines[i + 1] << std::endl; 
//                 
//                 if( html_lines[i + 1].find(".pdf") != std::string::npos )
//                 {
//                     std::cout << "i: " << i << " " << html_lines[i + 1] << std::endl; 
//                     count++;
//                 }
// 
// 
//             }
//         }
//     }
//     std::cout << "count = " << count << std::endl;
// }
