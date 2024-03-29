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
#include <unistd.h>


automate::automate( std::string url )
{
    std::string html_str = html_to_string( url );
    store_html_content( html_str );
    store_hw_names( );
}

// will be used to convert the html file to string 
size_t automate::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string automate::html_to_string( std::string url )
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if( curl ) 
    {
        curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );

        // html to string and store in readBuffer
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

// each element in the vector 
// will have line from html_str
void automate::store_html_content( std::string html_str )
{ 
    std::stringstream the_stream( html_str ); 
    std::string token; 

    // tokenize by new line
    while( getline(the_stream, token, '\n') ) 
    { 
        html_lines.push_back( token ); 
    } 
} 


void automate::store_hw_names( )
{
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
            std::stringstream file_name_line( html_lines[i + 1] );
            std::string token;
            
            // parse the html_file_name line 
            // and store file_name in vector
            while( getline(file_name_line, token, '\"') )
            {
                if( token.find(".pdf") != std::string::npos )
                {
                    hw_file_name.push_back( token );
                }

            }
        }
    }
}

// if dir already exists then the mkdir will
// fail. the mikdir doc says that it will fail in that condition
void automate::create_dir( std::string url )
{
    for( int i = 0; i < hw_file_name.size(); i++ )
    {
        // creating the directory name
        char dir_name[50];

        sprintf( dir_name, "hw%02d", i + 1 );
        std::cout << "dir_name: " << dir_name << std::endl;

        // Creating directory 
        // if the directory is created then 
        // then that means the pdf has already 
        // been downloaded before and does not 
        // need to re-download the pdf
        if( mkdir( dir_name, 0777) == -1 ) 
        {
            std::cerr << "---directory " << dir_name << " already created\n"; 
            continue;
        }
        download_pdf( url, hw_file_name[i], dir_name );
    }
}

// will be used for downloading the pdf
// in download_pdf()
size_t automate::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void automate::download_pdf( std::string url, std::string file_to_get, std::string hw_dir )
{
    CURL *curl;
    FILE *fp;
    CURLcode res;

    url += file_to_get;
    curl = curl_easy_init();

    // current working directory 
    // will be used to save the
    // hw file in the correct hw directory 
    std::string out_file = ""; 
    char curr_work_dir[1024];

    // construct the path for where
    // the hw file will be saved
    if( getcwd(curr_work_dir, sizeof(curr_work_dir)) != NULL )
    {
        std::string temp = curr_work_dir;
        out_file = temp + "/" + hw_dir + "/" + file_to_get; 
    }
    else
        std::cout << "error with cwd\n";

    // download the hw file from the website
    // the pdf path and saved file name will be 
    // stored in out_file
    if( curl ) 
    {
        fp = fopen( out_file.c_str(), "wb" );
        curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );

        curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_data );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, fp );

        res = curl_easy_perform( curl );
        /* always cleanup */
        curl_easy_cleanup( curl );
        fclose( fp );

        std::cout << "created file: " << out_file << std::endl;
    }
}


