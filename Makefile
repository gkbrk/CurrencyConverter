compile:
	clang -g `xml2-config --cflags` -lxml2 -o currency currency.c ecb_api.c

run:
	make compile
	./currency

clean:
	rm -f currency

test:
	valgrind ./currency
