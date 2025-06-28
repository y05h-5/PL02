CC = gcc
PROGRAM = main
D_OUT = outputs/
B = build/
H = headers/
TEST = test.sh
OBJ = $(B)main.o $(B)line.o $(B)point.o $(B)triangle.o 
HEADER = $(H)Line.h $(H)Point.h $(H)Triangle.h
LIBS = -lm

all: $(PROGRAM).exe $(D_OUT) $(B) 

$(PROGRAM).exe: $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

$(B)%.o: %.c $(B) $(HEADER)
	$(CC) -c $< -o $@

$(B): 
	mkdir $(B)

$(D_OUT):
	mkdir $(D_OUT)

clean:
	rm -f *.exe outputs/* build/* result.txt

vclean: # violent clean
	rm -rf *.exe outputs/ build/ result.txt

test: $(TEST)
	./$^

.PHONY: clean test vclean