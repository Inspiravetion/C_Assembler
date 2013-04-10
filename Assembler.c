#include "Assembler.h"

const char* DUMMY(const char** args, size_t size){
	int i = 0;
	while(i < size){
		printf("%s\n", args[i]);
		i++;
	}
	return "From Dummy...";
}

int main(int argc, char* argv[]){

	// Sifter s = *(New_Sifter("<(.*)><(.*)>", &DUMMY));
	// printf("Actual match: %s\n", s.Sift(&s, "<abc><123>"));
	// printf("shitty match: %s\n", s.Sift(&s, "<abc<123><a>")); 
	// printf("No match: %s\n", s.Sift(&s, ">abc123>"));
	// Sifter add = *(New_Sifter(IS_REG_WITH_OFFSET, &DUMMY));
	// printf("add test: %s\n", add.Sift(&add, "4($a0)"));

	// R_Type r = *(New_R_Type("111111", "22222", "33333", "44444", NULL));
	// printf("%s\n", r.toString(&r));

	// I_Type i = *(New_I_Type("111111", "22222", "33333", "1234567891011120"));
	// printf("%s\n", i.toString(&i));

	// J_Type j = *(New_J_Type("111111", "12345678910111213141516170"));
	// printf("%s\n", j.toString(&j));

	// Sifter Add = *(New_Sifter(ADD_REGEX, &DUMMY));
	// printf("%s\n", Add.Sift(&Add, "add 11111, 22222, 33333"));

	Sifter** sifters = Config_Sifters();

	printf("%s\n", (sifters[0])->Sift(sifters[0], "add 11111, 22222, 33333"));
	printf("%s\n", (sifters[1])->Sift(sifters[1], "sub 11111, 22222, 33333"));

	Clean_Up();

}
