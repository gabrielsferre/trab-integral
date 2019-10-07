ARQUIVO_TESTE_FUNC = testes_funcoes.c

testes_funcoes.out: $(ARQUIVO_TESTE_FUNC)
	gcc -Wall $(ARQUIVO_TESTE_FUNC) -o testes_funcoes.out

testa-funcoes: testes_funcoes.out
	./testes_funcoes.out

clean:
	rm testes_funcoes.out

