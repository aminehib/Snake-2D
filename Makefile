# Nom de l'exécutable
EXE = test

# Dossiers
SRC_DIR = src
OBJ_DIR = obj

# Compilateur et options
CXX = g++
CXXFLAGS = -Wall -O3 -std=c++17 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf

# Création automatique de obj/
$(shell mkdir -p $(OBJ_DIR))

# Détection automatique des fichiers source
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Cible par défaut
all: $(EXE)

# Compilation de l'exécutable
$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compilation des .cpp → .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXE)

