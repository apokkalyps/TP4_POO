COMPIL=g++
EXT_SRC=cpp
CFLAGS=-Wall -g -D MAP
LDFLAGS=-lm
SRC=$(wildcard *.$(EXT_SRC))
OBJ_FOLDER=./obj
O_FILES=$(addprefix $(OBJ_FOLDER)/, $(SRC:.$(EXT_SRC)=.o))
EXEC=ex.out

# On n'affiche pas leurs commandes
.SILENT: $(EXEC) $(OBJ_FOLDER) valgrind clean cleanfull run
# On ne cree pas de fichier apres
.PHONY: clean valgrind run

#### --- EDITION DES LIENS --- ###
$(EXEC) : $(OBJ_FOLDER) $(O_FILES)
	echo "Edition des liens de <$@>"
	$(COMPIL) -o $(EXEC) $(O_FILES) $(LDFLAGS)

### --- COMPILATION SEPAREE --- ###
%.o : ../%.$(EXT_SRC) ../%.h
	@ echo "Compilation de <$@>"
	@ $(COMPIL) $(CFLAGS) -o $@ -c $<

$(OBJ_FOLDER) :
	echo "Creation du dossier <$@> pour stocker les fichiers .o."
	mkdir $(OBJ_FOLDER)

### --- OUTILS --- ###
clean:
	echo Nettoyage ...
	rm -f $(O_FILES) $(EXEC)

cleanfull:
	echo Nettoyage complet...
	rm -f $(O_FILES) $(EXEC)
	rm ./obj/* -f
	rmdir obj

valgrind: $(EXEC)
	echo Lancement de Valgrind ...
	valgrind --leak-check=full ./$(EXEC)

run: $(EXEC)
	echo Lancement ...
	./$(EXEC)
