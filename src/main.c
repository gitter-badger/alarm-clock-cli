#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

enum operations
{
	ADD
};

struct Options
{
	int op;
	char *at;
	char *name;
	char *plays;
};

struct Options *parseArguments(int argc, char *argv[])
{
	struct Options *options = (struct options *)malloc(sizeof(struct Options));
	int c;

	static struct option long_options[] =
		{
			{"add", no_argument, 0, 'a'},
			{"at", required_argument, 0, 't'},
			{"name", required_argument, 0, 'n'},
			{"plays", required_argument, 0, 'p'},
			{0, 0, 0, 0}};

	int option_index = 0;

	while ((c = getopt_long(argc, argv, "ft:", long_options, &option_index)) != -1)
	{
		switch (c)
		{
		case 'a':
			options->op = ADD;
			break;
		case 't':
			options->at = optarg;
			break;
		case 'n':
			options->name = optarg;
			break;
		case 'p':
			options->plays = optarg;
			break;
		default:
			abort();
		}
	}

	return options;
}

void playSound(char *soundPath)
{
	const char *playSoundCommandTemplate = "mpg321 \"%s\"";
	char *playSoundCommand = (char *)malloc(sizeof(char) * (strlen(soundPath) + strlen(playSoundCommandTemplate)));
	sprintf(playSoundCommand, playSoundCommandTemplate, soundPath);
	system(playSoundCommand);
}

int main(int argc, char *argv[])
{
	struct Options *options = parseArguments(argc, argv);
	int alarmHour, alarmMin;

	sscanf(options->at, "%d:%d", &alarmHour, &alarmMin);

	printf("\n%s\n%s\n%s\n", options->name, options->at, options->plays);

	do
	{
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		printf("%0.2d\n", timeinfo->tm_hour);
		printf("%0.2d\n", timeinfo->tm_min);

		if (timeinfo->tm_hour == alarmHour && timeinfo->tm_min == alarmMin)
		{
			playSound(options->plays);
			return 0;
		}

		sleep(60);
	} while (1);

	return 0;
}
