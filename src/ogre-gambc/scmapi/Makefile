SRC=ScmEval.scm
CSRC=$(SRC:.scm=.c)
OBJ=$(SRC:.scm=.o)

CPPSRC=ScmRepl.cpp
CPPOBJ=$(CPPSRC:.cpp=.o)

all:	ScmAPI.a

%.o:	%.scm
	$(GSC) -c $<
	$(CXX) -c $(CXXFLAGS) -D___LIBRARY  $*.c

%.o:	%.c
	$(CXX) -c $(CXXFLAGS) -D___LIBRARY   $<

%.o : %.cpp
		$(COMPILE.cpp) -MD -o $@ $<
		@cp $*.d $*.P; \
			sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
				-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

-include $(CPPSRC:.cpp=.P)

ScmAPI_.c:   $(CSRC)
	$(GSC) -link -o $@ $^

ScmAPI.a:	$(OBJ) ScmAPI_.o $(CPPOBJ)
	ar rc $@ $^

clean:
	rm -f $(CSRC) $(OBJ) $(CPPOBJ) ScmAPI_.* ScmAPI.a