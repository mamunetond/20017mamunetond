File Edit Options Buffers Tools Makefile Help
all: cppcalc

cppcalc: calc.o scanner.o token.o ast.o parser.o calculator.o
        $(CXX) -o $@ $^

calc.o: calc.cpp scanner.h token.h

calculator.o: calculator.cpp calculator.h parser.h ast.h

scanner.o: scanner.cpp scanner.h token.h

token.o: token.cpp token.h

ast.o: ast.cpp ast.h

parser.o: parser.cpp parser.h

clean:
        rm -f *.o
        rm -f cppcalc
