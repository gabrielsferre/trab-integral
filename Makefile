INTEGRAL_SEQ = integral_sequencial.c
INTEGRAL_CONC = integral_concorrente.c
TESTE_SEQ = testes_integral_sequencial.c
TESTE_CONC = testes_integral_concorrente.c
TESTE_COMP = testes_comparativos.c
FILA = ideia_fracassada/fila.h
TESTE_FILA = ideia_fracassada/testes_fila.c

testes_integral_sequencial.out: $(INTEGRAL_SEQ) $(TESTE_SEQ)
	gcc -Wall $(INTEGRAL_SEQ) $(TESTE_SEQ) -o testes_integral_sequencial.out -lm -lpthread

testes_integral_concorrente.out: $(INTEGRAL_SEQ) $(INTEGRAL_CONC) $(TESTE_CONC)
	gcc -Wall $(TESTE_CONC) $(INTEGRAL_CONC) $(INTEGRAL_SEQ) -o testes_integral_concorrente.out -lm -lpthread

testes_comparativos.out: $(INTEGRAL_SEQ) $(INTEGRAL_CONC) $(TESTE_COMP)
	gcc -Wall $(INTEGRAL_SEQ) $(INTEGRAL_CONC) $(TESTE_COMP) -o testes_comparativos.out -lm -lpthread

testes_fila.out: $(FILA) $(TESTE_FILA)
	gcc -Wall $(TESTE_FILA) -o testes_fila.out -lpthread

testa-integral-sequencial: testes_integral_sequencial.out
	./testes_integral_sequencial.out

testa-integral_concorrente: testes_integral_concorrente.out
	./testes_integral_concorrente.out

testa-comparativo: testes_comparativos.out
	./testes_comparativos.out

compila-testes: $(INTEGRAL_SEQ) $(INTEGRAL_CONC) $(TESTE_COMP)
	gcc -Wall $(INTEGRAL_SEQ) $(INTEGRAL_CONC) teste_a.c -o a.out -lm -lpthread
	gcc -Wall $(INTEGRAL_SEQ) $(INTEGRAL_CONC) teste_b.c -o b.out -lm -lpthread
	gcc -Wall $(INTEGRAL_SEQ) $(INTEGRAL_CONC) teste_c.c -o c.out -lm -lpthread
	gcc -Wall $(INTEGRAL_SEQ) $(INTEGRAL_CONC) teste_d.c -o d.out -lm -lpthread
	gcc -Wall $(INTEGRAL_SEQ) $(INTEGRAL_CONC) teste_e.c -o e.out -lm -lpthread
	gcc -Wall $(INTEGRAL_SEQ) $(INTEGRAL_CONC) teste_f.c -o f.out -lm -lpthread
	gcc -Wall $(INTEGRAL_SEQ) $(INTEGRAL_CONC) teste_g.c -o g.out -lm -lpthread







testa-fila: testes_fila.out
	./testes_fila.out

clean:
	rm *.out

