#ifndef POKEMON_DB
#define POKEMON_DB


typedef struct Pokemon{
	int id;	
	char name[11];
	int atk;
	int def;
	int special;
	int speed;
}Pokemon;

typedef struct PokemonDB{
	FILE* source;
	int total;
	Pokemon (*get)(struct PokemonDB*,int);	
	void (*set)(struct PokemonDB*,int,Pokemon*);
	void (*add)(struct PokemonDB*,Pokemon*);
	void (*destroy)(struct PokemonDB*);
}PokemonDB;

void die(const char*);
PokemonDB* newPokemonDB(const char*);
void printPokemon(Pokemon* pkmn);

#endif
