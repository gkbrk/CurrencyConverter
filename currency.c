#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "ecb_api.h"

int main(int argc, char *argv[]){
    ecbUpdateDatabase(15 * 60);
    
    if (argc > 1 && strcmp(argv[1], "list") == 0){
        ecbCurrency *currencies;
        int currencyCount = ecbGetAllRates(&currencies);
        for (int i=0;i<currencyCount;i++){
            printf("%s: %f\n", currencies[i].name, currencies[i].rate);
        }
        free(currencies);
    }else if (argc > 2 && strcmp(argv[1], "get") == 0){
        printf("1 %s: %.4f EUR\n", argv[2], ecbGetEurRate(argv[2]));
    }else if (argc > 4 && strcmp(argv[1], "convert") == 0){
        double value = atof(argv[2]);
        char *fromCurrency = argv[3];
        char *toCurrency = argv[4];

        double fromEurRate = ecbGetEurRate(fromCurrency);
        double toEurRate = ecbGetEurRate(toCurrency);

        double converted = value / fromEurRate * toEurRate;
        printf("%.4f %s -> %s: %.4f\n", value, fromCurrency, toCurrency, converted);
    }
}
