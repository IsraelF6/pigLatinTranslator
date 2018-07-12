/********************
  Israel Felhandler
	   7/7/18
*********************/

#include <stdio.h>
#include <string.h>

char * PigLatin(char str[]) {
	/* print original sentence */
	//printf("%s\n",str);
	
	char word[1000];
	char pigLatinWord[1000];
	char sentence[1000];

	int pos;

	/* Scan word from sentence, add to str to get to next word.
	 	%n gives the number of characters consumed thus far*/
	while (sscanf(str, "%s%n", word, &pos) == 1) {
		str += pos;

		/* Number of characters in the word */
		int sz = strlen(word);

		/* Check if last char of word does not end with A-Za-z */
		if(word[sz-1] < 65 || word[sz-1] > 122 || (word[sz-1] > 90 && word[sz-1] < 97)) {
			/* Check if penultimate char is a number, if so, no translation needed */
			if(word[sz-2] > 47 && word[sz-2] < 58)
				strcpy(pigLatinWord, word);

			else {
				/* Begin translation of word */
				for(int i=0; i<sz-2; i++)
					pigLatinWord[i] = word[i+1];

				/* Append 1st char of original word to end of translated word */
				pigLatinWord[sz-2] = word[0];
				/* Complete translation by appending "ay" */
				pigLatinWord[sz-1] = 'a';
				pigLatinWord[sz] = 'y';
				/* Take account for two added letters and append punctuation */
				pigLatinWord[sz+1] = word[sz-1];
			}	
		}

		/* Check if last char of word is a number */
		else if (word[sz-1] > 47 && word[sz-1] < 58)
			strcpy(pigLatinWord, word);

		/* No punctuation and no number at the end, just a plain word */
		else {
			/* Begin translation of word */
			for (int i=0; i<sz-1; i++) {
				pigLatinWord[i] = word[i+1];
			}

			/* Append 1st char of original word to end of translated word */
			pigLatinWord[sz-1] = word[0];
			/* Complete translation by appending "ay" */
			pigLatinWord[sz] = 'a';
			pigLatinWord[sz+1] = 'y';
		}
		
		/* Append translated word into pig latin sentence */
		strcat(sentence, pigLatinWord);
		/* Space char in between each word since sscanf skips blank space */
		strcat(sentence, " ");

		/* Reset memory of array before scanning next word*/
		for(int i=0; i<=strlen(word)+2; i++)
			pigLatinWord[i] = 0;
		for(int i=0; i<=strlen(word); i++)
			word[i] = 0;
		
	}/* End of while loop */

	strcpy(str, sentence);
	for(int i=0; i<=strlen(sentence); i++)
			sentence[i] = 0;
	return str;
}


/* Compares two strings one char at a time */
int check(char str1[], char str2[]){
	for(int i=0; i<10000; i++)	{
		// Ends loop when end of string is reached
		if (str1[i]=='\0')
			break;

		// Checks for correct translation one char at a time
		else if (str2[i]!=str1[i]){
			printf("test Failed. At i = %d, char '%c' does not match expected char '%c'.\n", i, str2[i], str1[i]);
			return 1;
		}
	}
	printf("Test Passed!\n");
	return 0;
}


/* Driver function */
int main(){
	int test1, test2, test3, test4;
	int failed=0;

	/* string to translate and corresponding with function
		and Manual pig latin translation to check against */
	char text1[] = "Alex, how did you do question 21?";
	char textcheck1[] = "lexAay, owhay idday ouyay oday uestionqay 21?";
	char text2[] = "Hey! I called you 50 times, is your phone on silent? You need to stop doing that!";
	char textcheck2[] = "eyHay! Iay alledcay ouyay 50 imestay, siay ouryay honepay noay ilentsay? ouYay eednay otay topsay oingday hattay!";
	char text3[] = "3, 2, 1, go!";
	char textcheck3[] = "3, 2, 1, ogay!";
	char text4[] = "I called you";
	// Removed an 'a' at index 10 betweeen the 'c' and the 'y' to show an error being caught
	char textcheck4[] = "Iay alledcy ouyay";


	/* Use text as input to function to get translation, 
		send function translation and manual translation 
		to check function to see if they match*/
	test1 = check(textcheck1, PigLatin(text1));
	test2 = check(textcheck2, PigLatin(text2));
	test3 = check(textcheck3, PigLatin(text3));

	failed = test1 + test2 + test3;

	/* Test4 fails to show that an error will be caught.
		comment out next 2 lines to avoid the failed-test test*/
	test4 = check(textcheck4, PigLatin(text4));
	failed += test4; 


	if (failed==0)
		printf("All tests passed!\n");
	else
		printf("Number of tests failed: %d\n", failed);
	
    return 0;
}