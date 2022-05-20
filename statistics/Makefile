CC = g++ -Wall 

statistics.o: statistics.cpp
	$(CC) -c statistics.cpp

CorrelationCovariance: statistics.o CorrelationCovariance.cpp
	$(CC) statistics.o CorrelationCovariance.cpp -o CorrelationCovariance.exe 

clean: 
	rm -f *.o
	rm -f *.exe