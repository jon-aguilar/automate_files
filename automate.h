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


class automate
{
public:
    std::string html_to_string( std::string url );
    void store_html_content( std::string html_str ); 
    void store_hw_names( ); 
    void create_dir( std::string url );

    automate( std::string url );

     
private:
    std::vector <std::string> html_lines;

    // in the form 2320-hw01.pdf
    std::vector <std::string> hw_file_name;

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

    void download_pdf( std::string url, std::string file_to_get, std::string hw_dir );

};

#endif

