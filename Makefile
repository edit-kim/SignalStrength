all: SignalStrength
main.o : main.cpp
SignalStrength : main.o -ltins
	$(LINK.cc) $^  $(LDLIBS) -o $@

clean:
	rm -f SignalStrength *.o