
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

    //std::string line = "GeeksForGeeks is a must try\nThis is the next line"; 
    //std::cout << "first:\n" << line << std::endl;

    // Vector of string to save tokens 
    //std::vector <std::string> html_lines; 

    std::stringstream the_stream( html_str ); 

    std::string token; 

    // tokenize by new line
    while( getline(the_stream, token, '\n') ) 
    { 
        html_lines.push_back( token ); 
    } 

    // Printing the token vector 
    for(int i = 0; i < html_lines.size(); i++) 
        std::cout << "i: " << i << " " << html_lines[i] << '\n'; 
} 




