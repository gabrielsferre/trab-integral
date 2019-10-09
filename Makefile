ARQUIVO_TESTE_FUNC = testes_funcoes.c
ARQUIVO_TESTE_FILA = testes_fila.c

testes_funcoes.out: $(ARQUIVO_TESTE_FUNC)
	gcc -Wall $(ARQUIVO_TESTE_FUNC) -o testes_funcoes.out

testes_fila.out: $(ARQUIVO_TESTE_FILA)
	gcc -Wall $(ARQUIVO_TESTE_FILA) -o testes_fila.out -lpthread

testa-funcoes: testes_funcoes.out
	./testes_funcoes.out

testa-fila: testes_fila.out
	./testes_fila.out

clean:
	rm *.out

