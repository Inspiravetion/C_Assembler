#include "Sifter.h"

//LookAheads
const char** Sift_(const char* source, regmatch_t* captures, size_t size);
const char* Base_(Sifter* self, const char* source);

/** 
 * Creates a new sifter with the given regexp and Custom processing function
 * DO NOT FORGET TO FREE THE SIFTER WHEN YOU ARE DONE WITH IT
 */
Sifter* New_Sifter(const char* exp, const char*(*func)(const char**)){
	Sifter *sifter = malloc(sizeof(sifter));
	sifter->strRegEx = exp;
	if(regcomp(&(sifter->regEx), exp, REG_EXTENDED)){
		printf("Could not compile regular expression.\n");
		exit(1);
	}
	sifter->Sift = &Base_;
	sifter->Custom = func;
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
	//top level call...exec the regex on the source string and returns false if no match
	//if match...calls Sift and passes the const char** array it makes into the Custom 
	//function registered
	return self->Custom(Sift_("dummy", self->captures, 3));
}

/**
 * Maps the regmatch_t captures to the actual substrings they represent and puts them into 
 * an array in order and then returns that array.
 * @param  source   String the source to get all of the substrings from
 * @param  captures regmatch_t* array used to figure out which substrings to catch
 * @return          String[] of matched substrings
 */
const char** Sift_(const char* source, regmatch_t* captures, size_t size){
	//take the matches out of the source string using the indeces 
	//in regmatch and then return an array of the captured substrings
	//in order of occurance
	const char** container = ((const char**) New_Array(sizeof(char*), size));
	container[0] = "Sift_()'s return";
	return container;
}

/******************************************************************************
******************************************************************************/

const char* myCustom(const char** dummy){
	return dummy[0];
}

int main(int argc, char* argv[]){

	Sifter s = *(New_Sifter("(.*)", &myCustom));
	printf("ONLY LOOK AT THIS!!!%s\n", s.Sift(&s, "source String"));

	Clean_Up();

}



