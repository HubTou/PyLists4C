LIBRARY=pylists4c

MAJOR_VERSION=1
MINOR_VERSION=1
PATCH_VERSION=0

LIB=lib$(LIBRARY).a
SOLIB=lib$(LIBRARY).so

OBJECTS= \
	append.o areEqual.o change.o changeSlice.o clear.o compareValues.o \
	comprehension.o concat.o contains.o copy.o count.o createElement.o debug.o \
	del.o delSlice.o extend.o filter.o fromArray.o get.o getAllocatedMemory.o \
	getLast.o index.o indexAll.o insert.o insertFirst.o insertList.o \
	insertSorted.o iterator.o join.o len.o list.o pop.o print.o remove.o \
	removeAll.o removeDuplicates.o reverse.o reversed.o \
	setDebugMessagesDisplay.o setFatalMallocErrors.o shuffle.o shuffled.o \
	slice.o sort.o sorted.o sortedByInsertion.o sortedByQsort.o split.o \
	stats.o statsPrint.o str.o toArray.o value.o types/Null.o types/Char.o \
	types/UChar.o types/Short.o types/UShort.o types/Int.o types/UInt.o \
	types/Long.o types/ULong.o types/LongLong.o types/ULongLong.o types/Float.o \
	types/Double.o types/LongDouble.o types/String.o types/Struct.o
CFLAGS=-O3 -fPIC -Wall -Wextra -pipe -I.. # --std c99 is a minimum requirement
LOCALDIR=/usr/local

default: ../$(LIB) ../$(SOLIB)

../$(LIB): $(OBJECTS)
	@echo
	@echo "Building the Static library:"
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

../$(SOLIB): $(OBJECTS)
	@echo
	@echo "Building the Shared Output (dynamic) library:"
	$(CC) --shared -s $(OBJECTS) -o $@

$(OBJECTS): ../$(LIBRARY).h

install: ../$(LIB) ../$(SOLIB) ../$(LIBRARY).h
	@if [ `id -u` = "0" ] ; \
	then \
		echo ; \
		echo "Performed system-wide installation in ${LOCALDIR} include and lib:" ; \
		install -c -m 644 ../$(LIB) $(LOCALDIR)/lib ; \
		install -c -m 755 ../$(SOLIB) $(LOCALDIR)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) ; \
		ln -sf lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) $(LOCALDIR)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION) ; \
		ln -sf lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) $(LOCALDIR)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION) ; \
		ln -sf lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) $(LOCALDIR)/lib/lib$(LIBRARY).so ; \
		install -c -m 644 ../$(LIBRARY).h $(LOCALDIR)/include ; \
		ldconfig ; \
		ls -l $(LOCALDIR)/include/$(LIBRARY).h $(LOCALDIR)/lib/lib$(LIBRARY).* ; \
		echo ; \
	else \
		echo ; \
		echo "Performed user-only installation in ${HOME} include and lib:" ; \
		install -d -m 755 $(HOME)/lib ; \
		install -d -m 755 $(HOME)/include ; \
		install -c -m 644 ../$(LIB) $(HOME)/lib ; \
		install -c -m 755 ../$(SOLIB) $(HOME)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) ; \
		ln -sf lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) $(HOME)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION) ; \
		ln -sf lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) $(HOME)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION) ; \
		ln -sf lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) $(HOME)/lib/lib$(LIBRARY).so ; \
		install -c -m 644 ../$(LIBRARY).h $(HOME)/include ; \
		ls -l $(HOME)/include/$(LIBRARY).h $(HOME)/lib/lib$(LIBRARY).* ; \
		echo ; \
	fi

uninstall:
	@if [ `id -u` = "0" ] ; \
	then \
		echo ; \
		echo "Performed system-wide uninstallation from ${LOCALDIR} include and lib" ; \
		rm -f $(LOCALDIR)/lib/$(LIB) ; \
		rm -f $(LOCALDIR)/lib/$(SOLIB) ; \
		rm -f $(LOCALDIR)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION) ; \
		rm -f $(LOCALDIR)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION) ; \
		rm -f $(LOCALDIR)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) ; \
		rm -f $(LOCALDIR)/include/$(LIBRARY).h ; \
		ldconfig ; \
		echo ; \
	else \
		echo ; \
		echo "Performed user-only uninstallation from ${HOME} include and lib" ; \
		rm -f $(HOME)/lib/$(LIB) ; \
		rm -f $(HOME)/lib/$(SOLIB) ; \
		rm -f $(HOME)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION) ; \
		rm -f $(HOME)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION) ; \
		rm -f $(HOME)/lib/lib$(LIBRARY).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) ; \
		rm -f $(HOME)/include/$(LIBRARY).h ; \
		echo ; \
	fi

clean:
	@rm -f $(OBJECTS)

distclean: clean
	@rm -f ../$(LIB) ../$(SOLIB)

