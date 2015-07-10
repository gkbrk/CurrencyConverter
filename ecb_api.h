#pragma once

struct ecbCurrency{
    char name[4];
    double rate;
};

typedef struct ecbCurrency ecbCurrency;

int ecbUpdateDatabase(int time);
int ecbGetAllRates(ecbCurrency **currencyArray);
double ecbGetEurRate(char *currencyName);
