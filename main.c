#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pokemonDB.h"

int menu();
Pokemon askPokemon();
int askID();

int main(int argc, char*argv[]){
	if(argc == 0)
		die("ERROR: Input file missing");
	if(argc > 2)
		die("ERROR: Only one input file is needed");

	
	Pokemon pkmn;
	int ID=0;
	PokemonDB* db=newPokemonDB(argv[1]);
	int loop=1;
	while(loop){
		switch(menu()){
			case 1:
				pkmn=db->get(db,askID());
				printPokemon(&pkmn);
				break;
			case 2: 
				ID=askID();
				pkmn=askPokemon(ID);
				db->set(db,ID,&pkmn);
				printPokemon(&pkmn);
				break;
			case 3:
				ID=askID();
				pkmn=askPokemon(ID);
				db->add(db,&pkmn);
				printPokemon(&pkmn);
				break;
			default:
				loop=0;
			
		}	
	}
	db->destroy(db);

	return 0;
}


int menu(){
	int answer=0;
	do{
		fprintf(stdout,"Select an option:\n1)\tGet a pokemon\n2)\tSet a Pokemon\n3)\tAdd a pokemon\n4)\tExit\n> ");
		fscanf(stdin,"%d",&answer);
	}while(answer<1 || answer>4);	
	return answer;
}	

Pokemon askPokemon(int ID){
	char buffer[11]={'\0'};
	int stat=0;
	Pokemon res;

	fprintf(stdout,"Type in the Pokemon's name (MAX 10 characters)\n");
	fscanf(stdin,"%s",buffer);
	buffer[10]='\0';
	strncpy(res.name,buffer,10);

//	fprintf(stdout,"Type the Pokemon's ID: ");
//	fscanf(stdin,"%d",&stat);
//	res.id=stat;

	res.id=ID;

	fprintf(stdout,"Type the attack stat: ");
	fscanf(stdin,"%d",&stat);
	res.atk=stat;
	
	fprintf(stdout,"Type the defense stat: ");
	fscanf(stdin,"%d",&stat);
	res.def=stat;

	fprintf(stdout,"Type the special stat: ");
	fscanf(stdin,"%d",&stat);
	res.special=stat;

	fprintf(stdout,"Type the speed stat: ");
	fscanf(stdin,"%d",&stat);
	res.speed=stat;

	return res;
}

int askID(){
	int ID=0;
	do{
		fprintf(stdout,"Type the Pokemon's ID: ");
		fscanf(stdin,"%d",&ID);
	}while(ID<=0);
	return ID;
}
