INTEGRAL_SEQ = integral_sequencial.c
TESTE_SEQ = testes_integral_sequencial.c
TESTE_FILA = testes_fila.c

testes_integral_sequencial.out: $(INTEGRAL_SEQ) $(TESTE_SEQ)
	gcc -Wall $(INTEGRAL_SEQ) $(TESTE_SEQ) -o testes_integral_sequencial.out -lm -lpthread

testes_fila.out: $(TESTE_FILA)
	gcc -Wall $(TESTE_FILA) -o testes_fila.out -lpthread

testa-integral-sequencial: testes_integral_sequencial.out
	./testes_integral_sequencial.out

testa-fila: testes_fila.out
	./testes_fila.out

clean:
	rm *.out

