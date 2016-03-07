#include <stdio.h>
#include <stdlib.h>
#include "pokemonDB.h"

void die(const char* msg){
	fprintf(stderr,"%s\n",msg);
	exit(-1);
}

void printPokemon(Pokemon* pkmn){
	if(pkmn == NULL)
		die("ERROR: NULL pokemon is not printable");
	fprintf(stdout,"[%s] #%d\nAttack: %d\nDefense: %d\nSpecial: %d\nSpeed: %d\n",pkmn->name,pkmn->id,pkmn->atk,pkmn->def,pkmn->special,pkmn->speed);
}

void deletePokemonDB(PokemonDB* db){
	if(db->source)
		fclose(db->source);
	free(db);
}


//void loadPokemonDB(PokemonDB* db){}

/*void gotoBegining(Database*db){
	fseek(db->source,sizeof(int),SEEK_SET);
}*/

Pokemon getPokemonDB(PokemonDB* db,int id){
	Pokemon pkmn={};
	if(id > db->total){
		printf("There is no such Pokemon. Returning NULL instead.\n");
	return pkmn;
}
	fseek(db->source,sizeof(int)+(id-1)*sizeof(Pokemon)-1,SEEK_SET);
	
	fread(&pkmn.id,sizeof(int),1,db->source);
	fread(&pkmn.name,sizeof(char),11,db->source);
	pkmn.name[10]='\0';
	fread(&pkmn.atk,sizeof(int),1,db->source);
	fread(&pkmn.def,sizeof(int),1,db->source);
	fread(&pkmn.special,sizeof(int),1,db->source);
	fread(&pkmn.speed,sizeof(int),1,db->source);
	
	return pkmn;
}


void setPokemonDB(PokemonDB* db,int id, Pokemon* pkmn){
	if(id <= 0 || id > db->total)
		die("ERROR: Invalid pokemon id.");
	
	fseek(db->source,(id-1)*sizeof(Pokemon)+sizeof(int)-1,SEEK_SET);
	
	fwrite(&pkmn->id,sizeof(int),1,db->source);
	fwrite(pkmn->name,sizeof(char),11,db->source);
	fwrite(&pkmn->atk,sizeof(int),1,db->source);
	fwrite(&pkmn->def,sizeof(int),1,db->source);
	fwrite(&pkmn->special,sizeof(int),1,db->source);
	fwrite(&pkmn->speed,sizeof(int),1,db->source);

}


void addPokemonDB(PokemonDB* db, Pokemon* pkmn){
	db->total++;
	rewind(db->source);
	//fseek(db->source,0,SEEK_SET);
	fwrite(&db->total,sizeof(int),1,db->source);
	
	fseek(db->source,0,SEEK_END);
	fwrite(&pkmn->id,sizeof(int),1,db->source);
	fwrite(pkmn->name,sizeof(char),11,db->source);
	fwrite(&pkmn->atk,sizeof(int),1,db->source);
	fwrite(&pkmn->def,sizeof(int),1,db->source);
	fwrite(&pkmn->special,sizeof(int),1,db->source);
	fwrite(&pkmn->speed,sizeof(int),1,db->source);

		

}

PokemonDB* newPokemonDB(const char* path){
	PokemonDB* db=(PokemonDB*)malloc(sizeof(PokemonDB));
	if(!db)
		die("ERROR: Couldn't allocate memory for struct PokemonDB");
	db->source=fopen(path,"r+");
	if(!db->source)
		die("ERROR: source file could'n be opened");
		
	rewind(db->source);
	fread(&db->total,sizeof(int),1,db->source);
	if(db->total<0)
		die("ERROR: Wrong number of entries");

	//function pointers assignment
//	db->load=loadPokemonDB;
	db->get=getPokemonDB;
	db->set=setPokemonDB;
//	db->save=savePokemonDB;
	db->add=addPokemonDB;
	db->destroy=deletePokemonDB;
	
	return db;
}

//void savePokemonDB(PokemonDB* db){}oid printPokemon
