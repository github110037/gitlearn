OBJ := test.o BMP.o Smooth.o
CC := gcc
RESULT := test
CTAG := -g -O1
.PHONY:run clean

$(RESULT): $(OBJ)
	$(CC) $(CTAG)  $(OBJ) -o $(RESULT)
$(OBJ): %.o: %.c BMP.h
	$(CC) $(CTAG) -c $< -o $@
run: $(RESULT)
	./$(RESULT)
clean:
	rm $(OBJ) $(RESULT)
