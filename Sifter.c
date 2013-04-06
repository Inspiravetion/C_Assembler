#include "Sifter.h"

//LookAheads
const char** Sift_(const char* source, regmatch_t* captures, size_t size);
const char* Base_(Sifter* self, const char* source);

/** 
 * Creates a new sifter with the given regexp and Custom processing function
 * DO NOT FORGET TO FREE THE SIFTER WHEN YOU ARE DONE WITH IT
 */
Sifter* New_Sifter(const char* exp, const char*(*func)(const char**, size_t)){
	Sifter *sifter = malloc(sizeof(sifter));
	sifter->strRegEx = exp;
	if(regcomp(&(sifter->regEx), exp, REG_EXTENDED)){
		printf("Could not compile regular expression.\n");
		exit(1);
	}
	sifter->Sift = &Base_;
	sifter->Custom = func;
	sifter->nGroups = sifter->regEx.re_nsub + 1;
	sifter->captures = malloc(sifter->nGroups * sizeof(regmatch_t));
	Register_Disposable(sifter->captures);
	Register_Disposable(sifter);
	return sifter;
}

/**
 * Base_ function that first tests the regex for a match and then, if there is one, 
 * passes the result of Sift_() to the Sifter->Custom() function
 * @param  self   Sifter* the Sifter struct whos scope its in
 * @param  source String source to attempt matching the regex with
 * @return        String the bit representation of the command or NULL if no match
 */
const char* Base_(Sifter* self, const char* source){
	if(regexec(&(self->regEx), source, self->nGroups, self->captures, 
		REG_EXTENDED) != 0){
		printf("about to return null\n");
		return NULL;
	}
	return self->Custom(Sift_(source, self->captures, self->nGroups), self->nGroups);
}

/**
 * Maps the regmatch_t captures to the actual substrings they represent and puts them into 
 * an array in order to be returned
 * @param  source   String the source to get all of the substrings from
 * @param  captures regmatch_t* array used to figure out which substrings to catch
 * @return          String[] of matched substrings
 */
const char** Sift_(const char* source, regmatch_t* captures, size_t size){
	const char** container = ((const char**) New_Array(sizeof(char*), size));
	int i = 0, low, high, length;
	while((captures[i].rm_so != (size_t) -1) && (i < size)){
		low = captures[i].rm_so;
		high = captures[i].rm_eo;
		length = high - low;
		char* temp = ((char*) New_Array(sizeof(char*), length + 1));
		strncat(temp, source + low, length);
		container[i] = temp;
		i++;
	}
	return container;
}

/******************************************************************************
******************************************************************************/

const char* myCustom(const char** dummy, size_t numGroups){
	int i = 0;
	while(i < numGroups){
		printf("%s\n", dummy[i]);
		i++;
	}
	return "Whatevs";
}

int main(int argc, char* argv[]){

	Sifter s = *(New_Sifter("<(.*)><(.*)>", &myCustom));
	printf("Actual match: %s\n", s.Sift(&s, "<abc><123>"));
	printf("shitty match: %s\n", s.Sift(&s, "<abc<123><a>")); 
	printf("No match: %s\n", s.Sift(&s, ">abc123>"));
	Sifter add = *(New_Sifter(IS_REG_WITH_OFFSET, &myCustom));
	printf("add test: %s\n", add.Sift(&add, "4($a0)"));


	Clean_Up();

}



