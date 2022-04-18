OBJ := test.o BMP.o Smooth.o
CC := gcc
RESULT := test
.PHONY:run clean

$(RESULT): $(OBJ)
	$(CC)  -g $(OBJ) -o $(RESULT)
$(OBJ): %.o: %.c BMP.h
	$(CC) -g -c $< -o $@
run: $(RESULT)
	./$(RESULT)
clean:
	rm $(OBJ) $(RESULT)
