compile:
	clang -g `xml2-config --cflags` -lxml2 -o currency currency.c ecb_api.c

run:
	make compile
	./currency list

clean:
	rm -f currency

test:
	make compile
	valgrind ./currency list

install:
	make compile
	cp currency /usr/local/bin/currency

uninstall:
	rm -f /usr/local/bin/currency
