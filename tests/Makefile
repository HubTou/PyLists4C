PROGRAMS=\
	test_append \
	test_changeSlice \
	test_comprehension \
	test_delSlice \
	test_filter \
	test_fromArray \
	test_fromTable \
	test_insert \
	test_insertList \
	test_insertSorted \
	test_iterator \
	test_list \
	test_min_max_sum \
	test_qsort \
	test_removeDuplicates \
	test_reverse \
	test_slice \
	test_sort \
	test_split \
	test_stats \
	test_str \
	test_toArray \
	test_value
CFLAGS=-O3 -Wall -Wextra -pipe -I.. # --std c99 is a minimum requirement
LDFLAGS += -L.. -lpylists4c -s

default: ../libpylists4c.a $(PROGRAMS) info

../libpylists4c.a:
	@echo
	@echo "Building the library"
	@cd ../src ; make ; make clean
	@echo

test_append: test_append.o
	$(CC) test_append.o $(LDFLAGS) -o $@

test_changeSlice: test_changeSlice.o
	$(CC) test_changeSlice.o $(LDFLAGS) -o $@

test_comprehension: test_comprehension.o
	$(CC) test_comprehension.o $(LDFLAGS) -o $@

test_delSlice: test_delSlice.o
	$(CC) test_delSlice.o $(LDFLAGS) -o $@

test_filter: test_filter.o
	$(CC) test_filter.o $(LDFLAGS) -o $@

test_fromArray: test_fromArray.o
	$(CC) test_fromArray.o $(LDFLAGS) -o $@

test_fromTable: test_fromTable.o
	$(CC) test_fromTable.o $(LDFLAGS) -o $@

test_insert: test_insert.o
	$(CC) test_insert.o $(LDFLAGS) -o $@

test_insertList: test_insertList.o
	$(CC) test_insertList.o $(LDFLAGS) -o $@

test_insertSorted: test_insertSorted.o
	$(CC) test_insertSorted.o $(LDFLAGS) -o $@

test_iterator: test_iterator.o
	$(CC) test_iterator.o $(LDFLAGS) -o $@

test_list: test_list.o
	$(CC) test_list.o $(LDFLAGS) -o $@

test_min_max_sum: test_min_max_sum.o
	$(CC) test_min_max_sum.o $(LDFLAGS) -o $@

test_qsort: test_qsort.o
	$(CC) test_qsort.o $(LDFLAGS) -o $@

test_removeDuplicates: test_removeDuplicates.o
	$(CC) test_removeDuplicates.o $(LDFLAGS) -o $@

test_reverse: test_reverse.o
	$(CC) test_reverse.o $(LDFLAGS) -o $@

test_slice: test_slice.o
	$(CC) test_slice.o $(LDFLAGS) -o $@

test_sort: test_sort.o
	$(CC) test_sort.o $(LDFLAGS) -o $@

test_split: test_split.o
	$(CC) test_split.o $(LDFLAGS) -o $@

test_stats: test_stats.o
	$(CC) test_stats.o $(LDFLAGS) -o $@

test_str: test_str.o
	$(CC) test_str.o $(LDFLAGS) -o $@

test_toArray: test_toArray.o
	$(CC) test_toArray.o $(LDFLAGS) -o $@

test_value: test_value.o
	$(CC) test_value.o $(LDFLAGS) -o $@

info:
	@echo
	@if [ -f ../libpylists4c.so ] ; \
    then \
		echo "The test programs have been DYNAMICALLY linked" ; \
		echo ; \
		echo "If you haven't performed an installation, you'll need to execute the following" ; \
		echo "command for the shared library to be found:" ; \
		echo "  export LD_LIBRARY_PATH=.." ; \
		echo ; \
		echo "If you have performed a user-only install, you can instead run:" ; \
		echo "  export LD_LIBRARY_PATH=~/lib" ; \
		echo ; \
		echo "And if you have performed a system-wide install," ; \
		echo "everything should work without further action :-)" ; \
		echo ; \
	else \
		echo "The test programs have been STATICALLY linked" ; \
	fi

clean:
	@rm -f *.o *.core

distclean: clean
	@rm -f $(PROGRAMS)

