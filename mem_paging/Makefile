all: memtest.out memhuge.out
	@echo "Mem test without huge page"
	./memtest.out
	@echo "Mem test with huge page"
	./memhuge.out
memtest.out:
	gcc mem_test.c -o mem_test.out
memhuge.out:
	gcc mem_test_huge -o memhuge.out
clean:
	rm *.out