CXX = g++
CXXFLAGS = -O3 -Wall -std=c++11 -Iinclude
TARGET = xfce-mediaget
PREFIX = /usr/local

all: $(TARGET)

$(TARGET): src/main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

install: $(TARGET)
	install -D -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all install uninstall clean
