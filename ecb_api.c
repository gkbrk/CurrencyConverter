#include "ecb_api.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include <libxml/nanohttp.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

void uppercase(char *str){
    for (int i=0;str[i];i++){
        str[i] = toupper(str[i]);
    }
}

int ecbUpdateDatabase(int maximumAge){
    struct stat databaseStat;
    stat("database.xml", &databaseStat);
    int seconds = difftime(time(NULL), databaseStat.st_mtime);
    if (seconds > maximumAge){
        printf("Updating the currency database...\n");
        int status = xmlNanoHTTPFetch("http://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml", "database.xml", NULL);
        return status;
    }else{
        return 0;
    }
}

int ecbGetAllRates(ecbCurrency **currencyArray){
    xmlDoc *doc = xmlParseFile("database.xml");
    
    xmlXPathContextPtr xpath_context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr currencies = xmlXPathEvalExpression(BAD_CAST "//*[@currency]", xpath_context);
    int currencyCount = currencies->nodesetval->nodeNr;

    *currencyArray = malloc(sizeof(struct ecbCurrency) * currencyCount);
    for (int i=0;i<currencyCount;i++){
        struct ecbCurrency currency;
        xmlChar *currencyName = xmlGetNoNsProp(currencies->nodesetval->nodeTab[i], BAD_CAST "currency");
        strncpy(currency.name, (char *)currencyName, 4); 
        
        xmlChar *currencyRate = xmlGetNoNsProp(currencies->nodesetval->nodeTab[i], BAD_CAST "rate");
        currency.rate = atof((char *)currencyRate);

        (*currencyArray)[i] = currency;
        free(currencyName);
        free(currencyRate);
    }
    xmlXPathFreeObject(currencies);
    xmlXPathFreeContext(xpath_context);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return currencyCount;
}

double ecbGetEurRate(char *currencyName){
    uppercase(currencyName);
    if (strcmp(currencyName, "EUR") == 0){
        return 1;
    }

    ecbCurrency *currencies;
    int currencyCount = ecbGetAllRates(&currencies);

    for (int i=0;i<currencyCount;i++){
        uppercase(currencies[i].name); //The response from the API is already upper-case. This is just to be safe.
        if (strcmp(currencies[i].name, currencyName) == 0){
            double rate = currencies[i].rate;
            free(currencies);
            return rate;
        }
    }
    free(currencies);
    return -1;
}
