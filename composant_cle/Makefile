CPPFLAGS += `python3-config --includes`
LIBS = `python3-config --ldflags` -L/home/aminetabbakh20/python_cle_publique_2023/composant_cle/micro-ecc -luecc

COMPOSANT = cle_component
LIBSO = ${COMPOSANT}.so
LIBSO_OBJS = ${COMPOSANT}.o

all: test $(LIBSO)

include ../gcc.mk
include ../pybind11.mk

$(LIBSO): $(LIBSO_OBJS)
	$(CXX) -o $@ -shared $^ $(LIBS)

test: $(LIBSO)
	echo "execution du test"
	python3 test.py

clean:
	rm -f $(LIBSO) $(LIBSO_OBJS)

$(DESTINATION_LIBSO): $(LIBSO)
	cp $< $@
