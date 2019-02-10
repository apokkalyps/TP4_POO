COMPIL=g++
EXT_SRC=cpp
CFLAGS=-Wall -g -D MAP
LDFLAGS=-lm
SRC_FOLDER=src
SRC=$(wildcard *.$(EXT_SRC))
OBJ_FOLDER=./obj
O_FILES=$(addprefix $(OBJ_FOLDER)/, $(SRC:.$(EXT_SRC)=.o))
EXEC_FOLDER_NAME=bin
EXEC_FOLDER=../$(EXEC_FOLDER_NAME)
EXEC_NAME=analog
EXEC=$(EXEC_FOLDER)/$(EXEC_NAME)

# On n'affiche pas leurs commandes
.SILENT: $(EXEC) $(OBJ_FOLDER) $(EXEC_FOLDER) valgrind clean cleanfull run
# On ne cree pas de fichier apres
.PHONY: clean valgrind run

#### --- EDITION DES LIENS --- ###
$(EXEC) : $(EXEC_FOLDER) $(OBJ_FOLDER) $(O_FILES)
	echo "Edition des liens de <$@>"
	$(COMPIL) -o $(EXEC) $(O_FILES) $(LDFLAGS)

### --- COMPILATION SEPAREE --- ###
%.o : ../%.$(EXT_SRC) ../%.h
	@ echo "Compilation de <$@>"
	@ $(COMPIL) $(CFLAGS) -o $@ -c $<

$(OBJ_FOLDER) :
	echo "Creation du dossier <$@> pour stocker les fichiers .o."
	mkdir $(OBJ_FOLDER)

$(EXEC_FOLDER) :
	echo "Creation du dossier <$@> pour stocker l'executable $(EXEC)."
	mkdir ../$(EXEC_FOLDER_NAME)

### --- OUTILS --- ###
clean:
	echo Nettoyage ...
	rm -f $(O_FILES) $(EXEC)

cleanfull:
	echo Nettoyage complet...
	rm -f $(O_FILES) $(EXEC)
	rm $(OBJ_FOLDER)/* -f
	rm $(EXEC_FOLDER)/* -f
	rmdir $(OBJ_FOLDER)
	rmdir $(EXEC_FOLDER)
	

valgrind: $(EXEC)
	echo Lancement de Valgrind ...
	valgrind --leak-check=full ./$(EXEC)

run: $(EXEC)
	echo Lancement ...
	./$(EXEC)
