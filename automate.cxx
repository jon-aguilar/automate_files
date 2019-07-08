
#include "automate.hxx"

#include <iostream>
#include <string>


/*
    -------------------- JON NOTES FOR PROJECT -----------------
    1.  save the variable res into a string 
        then inside the string you will parse 
        probably by spaces save the results in 
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



std::string automate::get_html_file()
{
    return "the string";
}
