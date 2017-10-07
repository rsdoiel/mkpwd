/*********************************************************************
**
** $Id: mkpwd.c,v 1.6 2003/12/03 13:26:15 oliver Exp $
**
**********************************************************************
**
**	Copyright 1999-2003 Oliver Schroeder
**
**	Permission to use, copy, modify, and distribute this
**	software and its documentation for any purpose and 
**	without any fee is hereby granted, provided that the 
**	above copyright notice and this permission notice 
**	appear in all copies of the software and derivative 
**	works or modified versions thereof, and that both the 
**	copyright notice and this permission and disclaimer
**	notice appear in supporting documentation.
**
**	This software is provided "as is" WITHOUT ANY WARRANTY.
**
**	Oliver Schroeder <progs@o-schroeder.de>
**
*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

const char* PROGRAM	= "mkpwd";
const char* VERSION	= "1.6";
const char* COPYRIGHT	= "(c) 1999-2010 Oliver Schroeder";

/*********************************************************************
**
** global variables. these can be manipulated via switches
** adjust them for your preferred standard behavior.
**
*********************************************************************/
int	MIN_PWD_LENGTH  = 6;	/* minimum length of a password		*/
int	MAX_PWD_LENGTH	= 10;	/* maximum length of a password		*/
int	NUM_PWDS	= 1;	/* number of passwords to generate	*/
int	COMPLEXITY	= 1;	/* standard type is COMPLEX		*/
int	UPPER_LOWER	= 0;	/* standard is leave password untouched */
int	DO_CRYPT	= 0;	/* 0 - don't crypt, 1 - crypt		*/
char*	CRYPT_SALT	= 0;
int	RANGE;
char*	VALID_CHARS;

/*********************************************************************
**
** return error codes
**
*********************************************************************/
const int NO_ERROR	= 0;
const int ARG_ERROR	= 1;

/*********************************************************************
**
** here we define which characters are allowed in a password.
**
*********************************************************************/
char* COMPLEX_CHARS =
	"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]"
	"^_`abcdefghijklmnopqrstuvwxyz{|}~";
char* ALPHA_NUM =
	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char* NON_AMBIGUOUS =
	"23456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
char* ALPHA =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char* NUMERIC =
	"0123456789";
char* CONSONANT =
	"BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz";
char* VOCAL = "AEIOUYaeiouy";
char* HEX_NUM = "0123456789ABCDEF";
enum COMPLEXITY_MODES
{
	IS_COMPLEX		= 1,
	IS_ALPHANUM		= 2,
	IS_ALPHA		= 3,
	IS_NUMERIC		= 4,
	IS_ALPHANUM_READABLE	= 5,
	IS_ALPHA_READABLE	= 6,
	IS_HEX_NUM		= 7,
	IS_NON_AMBIGUOUS	= 8,
	INVALID_COMPLEXITY
};
enum UPPER_OR_LOWER_MODES
{
	TO_LOWER = 1,
	TO_UPPER = 2
};

extern	int errno;

/*********************************************************************
**
** print the version
**
*********************************************************************/
void Version ()
{
	printf ("\n%s version %s\n", PROGRAM, VERSION);
	printf ("copyright %s\n\n", COPYRIGHT);
}

/*********************************************************************
**
** print a help screen
**
*********************************************************************/
void Help ()
{
	Version ();
	printf ("syntax: %s [options] [count]\n", PROGRAM);
	printf ("if count is given, generate [count] passwords\n");
	printf ("\n");
	printf ("options are:\n");
	printf ("-v			show the version and exit\n");
	printf ("-h			show this help screenand exit\n");
	printf ("-n [length]		set minimum password length\n");
	printf ("-m [length]		set maximum password length\n");
	printf ("-t  [type]		set the complexity type of passwords\n");
	printf ("			type 1: complex, all printables chars\n");
	printf ("			type 2: alphanum, A-Z, a-z, 0-9\n");
	printf ("			type 3: alpha, A-Z, a-z\n");
	printf ("			type 4: numeric, 0-9\n");
	printf ("			type 5: alphanum, readable\n");
	printf ("			type 6: alpha, readable\n");
	printf ("			type 7: hexadecimal\n");
	printf ("			type 8: alphanum non-ambiguous\n");
	printf ("-u			use only uppercase characters\n");
	printf ("-l			use only lowercase characters\n");
	printf ("-c [salt]		crypt the password with crypt(3)\n");
	printf ("			using the two character string salt\n");
	printf ("			will print out \"pw crypt(pw)\"\n");
	printf ("\n");
}

/*********************************************************************
**
** parse the commandline and set global variables accordingly
**
*********************************************************************/
void ParseParams ( int argc, char* argv[] )
{
	extern char*	optarg;
	extern int	optind, opterr;
	int		option_index = 0;
	int		c;
	
	c = 1;
	opterr = 0;
	while (c != EOF)
	{
		c = getopt (argc, argv, "vhn:m:t:ulc:");
		switch (c)
		{
		    case 'v': /* --version	*/
			    Version ();
			    exit (NO_ERROR);
		    case 'h': /* --help	*/
			    Help ();
			    exit (NO_ERROR);
		    case 'n': /* --min	*/
			    errno = 0;
			    MIN_PWD_LENGTH =strtol(optarg,(char**)NULL,10);
			    if (errno != 0)
			    {
				    printf ("miniumum is invalid!\n");
				    exit (ARG_ERROR);
			    }
			    break;
		    case 'm': /* --max	*/
			    errno = 0;
			    MAX_PWD_LENGTH =strtol(optarg,(char**)NULL,10);
			    if (errno != 0)
			    {
				    printf ("maximum is invalid!\n");
				    exit (ARG_ERROR);
			    }
			    break;
		    case 't': /* --type	*/
			    errno = 0;
			    COMPLEXITY = strtol (optarg,(char**)NULL,10);
			    if (errno != 0)
			    {
				    printf ("type is invalid!\n");
				    exit (ARG_ERROR);
			    }
			    if ((COMPLEXITY < 1) || (COMPLEXITY >= INVALID_COMPLEXITY))
			    {
				    printf("type is out of range (1-7)\n");
				    exit (ARG_ERROR);
			    }
			    break;
		    case 'u': /* --uppercase	*/
			    UPPER_LOWER = TO_UPPER;
			    break;
		    case 'l': /* --lowercase	*/
			    UPPER_LOWER = TO_LOWER;
			    break;
		    case 'c': /* crypt */
			    DO_CRYPT = (DO_CRYPT == 0);
			    CRYPT_SALT = optarg;
			    break;
		} // switch
	} // while
	if ((argc-optind) > 1)
	{
		Help ();
		exit (ARG_ERROR);
	}
	if ((argc - optind) == 1)
	{
		errno = 0;
		NUM_PWDS = strtol (argv [optind], (char**)NULL, 10);
		if (errno != 0)
		{
			printf ("count is invalid!\n");
			exit (ARG_ERROR);
		}
	}
	if ((DO_CRYPT) && ((CRYPT_SALT == 0) || (strlen (CRYPT_SALT) < 2)))
	{
		printf ("please specify at least 2 characters to -c\n");
		printf ("salt: %s\n", CRYPT_SALT);
		exit (ARG_ERROR);
	}
}

/*********************************************************************
**
** build passwords
**
*********************************************************************/
void BuildPassword ()
{
	int 	Length;
	int 	I, Current_Char;
	char	c;
	char	buffer [512];

	I = MAX_PWD_LENGTH - MIN_PWD_LENGTH;
	if (I != 0)
		Length = (int) rand () % I;
	else	Length = I;
	Length += MIN_PWD_LENGTH;
	for (I = 0; I < Length; I++)
	{
		Current_Char = (int) (rand () % RANGE);
		c = VALID_CHARS [Current_Char];
		switch (UPPER_LOWER)
		{
		    case TO_LOWER:
			    c = tolower (c);
			    break;
		    case TO_UPPER:
			    c = toupper (c);
			    break;
		}
		buffer[I] = c;
	} // for
	buffer[I] = '\0';
	if (DO_CRYPT == 1)
	{
		printf ("%s %s\n",buffer, crypt (buffer, CRYPT_SALT));
	}
	else	printf ("%s\n", buffer);
}

/*********************************************************************
**
** build a readable password.
** the current algorithm selects alternating characters of CONSONANTS
** and VOCALS.
**
*********************************************************************/
void BuildReadablePwd ()
{
	int 	Length;
	int 	I, Current_Char;
	char	c;

	I = MAX_PWD_LENGTH - MIN_PWD_LENGTH;
	if (I != 0)
		Length = (int) rand () % I;
	else	Length = I;
	Length += MIN_PWD_LENGTH;
	for (I = 0; I < Length; I++)
	{
		if (I%2 == 0)
		{
			/* a 20% chance for double vocals */
			Current_Char = (int) rand () % 5;
			if (Current_Char == 1)
				VALID_CHARS = VOCAL;
			else	VALID_CHARS = CONSONANT;
		}
		else	VALID_CHARS = VOCAL;
		if (COMPLEXITY == IS_ALPHANUM_READABLE)
		{
			/* a 10% chance that the next char is a NUMERIC */
			Current_Char = (int) rand () % 10;
			if (Current_Char == 1)
				VALID_CHARS = NUMERIC;
		}
		RANGE = strlen (VALID_CHARS);
		Current_Char = (int) (rand () % RANGE);
		c = VALID_CHARS [Current_Char];
		switch (UPPER_LOWER)
		{
		    case TO_LOWER:
			    c = tolower (c);
			    break;
		    case TO_UPPER:
			    c = toupper (c);
			    break;
		}
		printf ("%c", c);
	} // for
	printf ("\n");
}

/*********************************************************************
**
** initialize all globals according to parameters.
** initialize the random-number-generator.
**
*********************************************************************/
void PrepareAndDo ()
{
	int I;

	srand (time (0) * getpid () * getppid ());
	switch (COMPLEXITY)
	{
		case IS_COMPLEX:
			VALID_CHARS = COMPLEX_CHARS;
			RANGE = strlen (VALID_CHARS);
			for (I = 0; I < NUM_PWDS; I++)
				BuildPassword ();
			break;
		case IS_ALPHANUM:
			VALID_CHARS = ALPHA_NUM;
			RANGE = strlen (VALID_CHARS);
			for (I = 0; I < NUM_PWDS; I++)
				BuildPassword ();
			break;
		case IS_ALPHA:
			VALID_CHARS = ALPHA;
			RANGE = strlen (VALID_CHARS);
			for (I = 0; I < NUM_PWDS; I++)
				BuildPassword ();
			break;
		case IS_NUMERIC:
			VALID_CHARS = NUMERIC;
			RANGE = strlen (VALID_CHARS);
			for (I = 0; I < NUM_PWDS; I++)
				BuildPassword ();
			break;
		case IS_NON_AMBIGUOUS:
			VALID_CHARS = NON_AMBIGUOUS;
			RANGE = strlen (VALID_CHARS);
			for (I = 0; I < NUM_PWDS; I++)
				BuildPassword ();
			break;
		case IS_ALPHANUM_READABLE:
			for (I = 0; I < NUM_PWDS; I++)
				BuildReadablePwd ();
			break;
		case IS_ALPHA_READABLE:
			for (I = 0; I < NUM_PWDS; I++)
				BuildReadablePwd ();
			break;
		case IS_HEX_NUM:
			VALID_CHARS = HEX_NUM;
			RANGE = strlen (VALID_CHARS);
		        for (I=0; I< NUM_PWDS; I++)
				BuildPassword();
			break;
	} // switch
}

/*********************************************************************
**
** main
**
*********************************************************************/
int main ( int argc, char* argv [] )
{
	ParseParams (argc, argv);
	PrepareAndDo ();
	return (0);
}
