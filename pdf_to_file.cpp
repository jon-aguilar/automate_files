
// this will write the pdf to a file on local computer



#include <curl/curl.h>
#include <string>


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(void) 
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    //const char *url = "http://omega.uta.edu/~darin/CSE2320/2320-hw01.pdf";
    std::string url = "http://omega.uta.edu/~darin/CSE2320/2320-hw01.pdf";
    //char outfilename[1000000] = "hw01.pdf";
    std::string outfilename = "hw01.pdf";
    curl = curl_easy_init();

    if( curl ) 
    {
        fp = fopen( outfilename.c_str(), "wb" );
        curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );

        curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_data );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, fp );

        res = curl_easy_perform( curl );
        /* always cleanup */
        curl_easy_cleanup( curl );
        fclose( fp );
    }

    return 0;
}

