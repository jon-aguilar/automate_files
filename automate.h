#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>
#include <vector>

class automate
{
public:
    // TODO: change the function to have string param -----------------------------
    //std::string html_to_string( std::string html_file );
    std::string html_to_string( );
    void load_vector( std::string html_str ); 
     
private:
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    std::vector <std::string> html_lines;


};

#endif

